
#include <LPC21xx.H>
#include "lcd.h"
#include "keypad_init.h"
#include "project_title.h"
#include "uart.h"

#define IN1 (1U<<23)
#define IN2 (1U<<24)
#define EN1 (1U<<25)
#define SENSOR (1U<<16)

unsigned char key_lut[4][4] = {
    {7, 8, 9, '/'},
    {4, 5, 6, 'x'},
    {1, 2, 3, '-'},
    {'@', 0, '=', '+'}
};

unsigned int batch = 0;
volatile unsigned int count = 0;
unsigned int key_flag = 0;
unsigned int batch_count = 0;
volatile unsigned int terminate = 0;

/* Kill switch: EINT1 */
void kill(void) __irq
{
    IOCLR0 = EN1 | IN1 | IN2;
    terminate = 1;

    EXTINT = 0x02;
    VICVectAddr = 0;
}

int main(void)
{
    PINSEL0 |=  (1U<<29);
    PINSEL0 &= ~(1U<<28);

    IODIR0 |= SENSOR;

    VICIntSelect = 0x00000000;
    VICVectAddr0 = (unsigned long)kill;
    VICVectCntl0 = 0x20 | 15;

    EXTMODE = 0x02;
    EXTPOLAR = 0x02;
    EXTINT = 0x02;

    VICIntEnable = (1U<<15);

    proj_title();
    uart_config();

    while(1)
    {
        batch_count++;
        batch = 0;
        count = 0;
        key_flag = 0;

        LCD_COMMAND(0x01);
        LCD_STRING("ENTER BATCH ");
        LCD_DATA(batch_count + '0');
        LCD_DATA(':');
        LCD_COMMAND(0xC0);

        while(key_flag == 0)
        {
            keypad_init();
            value = key_lut[row_val][col_val];

            if(value == '@')
            {
                IOCLR0 = EN1 | IN1 | IN2;
                LCD_COMMAND(0x01);
                LCD_STRING("TERMINATED");
                delay_ms(1000);
                return 0;
            }

            if(value != '=')
            {
                if(value < 10)
                {
                    LCD_DATA(value + '0');
                    batch = (batch * 10) + value;
                }
                else
                {
                    LCD_COMMAND(0x01);
                    LCD_STRING("INVALID KEY");
                    delay_ms(1000);

                    LCD_COMMAND(0x01);
                    LCD_STRING("ENTER BATCH ");
                    LCD_DATA(batch_count + '0');
                    LCD_DATA(':');
                    LCD_COMMAND(0xC0);

                    batch = 0;
                }
            }

            if(value == '=')
            {
                if(batch == 0)
                {
                    LCD_COMMAND(0x01);
                    LCD_STRING("INVALID BATCH");
                    delay_ms(1000);
                    LCD_COMMAND(0x01);
                    LCD_STRING("ENTER BATCH ");
                    LCD_DATA(batch_count + '0');
                    LCD_DATA(':');
                    LCD_COMMAND(0xC0);
                    batch = 0;
                    continue;
                }

                LCD_COMMAND(0x01);
                LCD_STRING("BATCH:");
                LCD_COMMAND(0xC0);
                LCD_INT(batch);
                delay_ms(1500);

                LCD_COMMAND(0x01);
                LCD_STRING("MOTOR ON");

                key_flag = 1;
            }
        }

        /* Prepare motor GPIO */
        IODIR0 |= IN1 | IN2 | EN1;

        /* Start motor */
        IOSET0 = IN1 | EN1;
        IOCLR0 = IN2;

        /* Count sensor pulses until batch completes or kill switch */
        while((count < batch) && (terminate == 0))
        {
            if((IOPIN0 & SENSOR) != 0)
            {
                count++;

                while((IOPIN0 & SENSOR) != 0)
                {
                    if(terminate != 0)
                        break;
                }
            }
        }

        /* Stop motor */
        IOCLR0 = EN1 | IN1 | IN2;

        LCD_COMMAND(0x01);

        if(terminate != 0)
            LCD_STRING("BATCH STOPPED");
        else
            LCD_STRING("BATCH COMPLETE");

        delay_ms(1000);

        /* Send SMS */
        LCD_COMMAND(0x01);
        LCD_STRING("SENDING SMS...");

        uart_str("AT\r\n");
        delay_ms(1000);

        uart_str("AT+CMGF=1\r\n");
        delay_ms(1000);

        uart_str("AT+CMGS=\"+919876543210\"\r\n");
        delay_ms(1000);

        uart_str("Batch ");
        uart_int(batch_count);

        if(terminate != 0)
            uart_str(" stopped.\r\nQuantity: ");
        else
            uart_str(" completed.\r\nQuantity: ");

        uart_int(count);
        uart_str("\r\n");

        uart_tx(26);
        delay_ms(1000);

        if(terminate != 0)
        {
            LCD_COMMAND(0x01);
            LCD_STRING("RESET REQUIRED");

            /* Remain stopped after emergency termination */
            while(1)
            {
                IOCLR0 = EN1 | IN1 | IN2;
            }
        }

        key_flag = 0;
        count = 0;
        batch = 0;
    }
}
