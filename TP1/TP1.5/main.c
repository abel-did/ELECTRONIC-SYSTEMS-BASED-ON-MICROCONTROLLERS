/**
 * Author : Abel DIDOUH
 * Date : 15 / 02 / 2023
 * Description : A program that turns on the BLUE LED(PORT2.2) when the button P1.4 (PORT1.4)
 *               is not pressed else turns on the GREEN LED(PORT2.1).
 */

#include <stdint.h>

#define PRBA 0x40004C00

const volatile uint8_t * const P1_IN = (void *) (PRBA);
volatile uint8_t * const P1_OUT = (void *) (PRBA + 0x2);
volatile uint8_t * const P1_DIR = (void *) (PRBA + 0x4);
volatile uint8_t * const P1_REN = (void *) (PRBA + 0x6);
volatile uint8_t * const P1_SEL0 = (void *) (PRBA + 0xA);
volatile uint8_t * const P1_SEL1 = (void *) (PRBA + 0xC);

const volatile uint8_t * const P2_IN = (void *) (PRBA + 0x1);
volatile uint8_t * const P2_OUT = (void *) (PRBA + 0x3);
volatile uint8_t * const P2_DIR = (void *) (PRBA + 0x5);
volatile uint8_t * const P2_REN = (void *) (PRBA + 0x7);
volatile uint8_t * const P2_SEL0 = (void *) (PRBA + 0xB);
volatile uint8_t * const P2_SEL1 = (void *) (PRBA + 0xD);

#define LED2_2 2
const uint8_t LED_mask = 1 << LED2_2;

#define LED2_1 1
const uint8_t LED_mask_1 = 1 << LED2_1;

#define BUTTON 4
const uint8_t BUTTON_mask = 1 << BUTTON;

int main()
{
    //Configure BUTTON
    *P1_SEL0 &= ~BUTTON_mask;
    *P1_SEL1 &= ~BUTTON_mask;
    *P1_DIR  &= ~BUTTON_mask;
    *P1_REN  |= BUTTON_mask;
    *P1_OUT  |= BUTTON_mask;
    //Configure BLUE LED
    *P2_SEL0 &= ~LED_mask;
    *P2_SEL1 &= ~LED_mask;
    *P2_DIR  |= LED_mask;
    //Configure GREEN LED
    *P2_SEL0 &= ~LED_mask_1;
    *P2_SEL1 &= ~LED_mask_1;
    *P2_DIR  |= LED_mask_1;


    while(1)
    {
        if( *P1_IN & (1 << BUTTON) )
        {
            *P2_OUT |= LED_mask;
            *P2_OUT &= ~LED_mask_1;
        }
        else
        {
            *P2_OUT &= ~LED_mask;
            *P2_OUT |= LED_mask_1;
        }
    }
    return 0;
}
