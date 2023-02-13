/**
 * Author : Abel DIDOUH
 * Date : 13 / 02 / 2023
 * Description : A program that turns on the LED(PORT1.0) when the button P1.1 (PORT1.1)
 *               or the button P1.4 (PORT1.4) is pressed.
 */

#include <stdint.h>

#define PRBA 0x40004C00

const volatile uint8_t * const P1_IN = (void *) (PRBA);
volatile uint8_t * const P1_OUT = (void *) (PRBA + 0x2);
volatile uint8_t * const P1_DIR = (void *) (PRBA + 0x4);
volatile uint8_t * const P1_REN = (void *) (PRBA + 0x6);
volatile uint8_t * const P1_SEL0 = (void *) (PRBA + 0xA);
volatile uint8_t * const P1_SEL1 = (void *) (PRBA + 0xC);

#define LEDR 0
const uint8_t LEDR_mask = 1 << LEDR;

#define BUTTON_P1_1 1
const uint8_t BUTTON_P1_1_mask = 1 << BUTTON_P1_1;

#define BUTTON_P1_4 4
const uint8_t BUTTON_P1_4_mask = 1 << BUTTON_P1_4;

int main()
{
    //Configure LEDR
    *P1_SEL0 &= ~LEDR_mask;
    *P1_SEL1 &= ~LEDR_mask;
    *P1_DIR  |= LEDR_mask;

    //Configure BUTTON P1.1
    *P1_SEL0 &= ~BUTTON_P1_1_mask;
    *P1_SEL1 &= ~BUTTON_P1_1_mask;
    *P1_DIR  &= ~BUTTON_P1_1_mask;
    *P1_REN  |= BUTTON_P1_1_mask;
    *P1_OUT  |= BUTTON_P1_1_mask;

    //Configuration BUTTON P1.4
    *P1_SEL0 &= ~BUTTON_P1_4_mask;
    *P1_SEL1 &= ~BUTTON_P1_4_mask;
    *P1_DIR  &= ~BUTTON_P1_4_mask;
    *P1_REN  |= BUTTON_P1_4_mask;
    *P1_OUT  |= BUTTON_P1_4_mask;

    while(1)
    {
        if( (*P1_IN & (1 << BUTTON_P1_1)) && ( *P1_IN & (1 << BUTTON_P1_4)) )
        {
            *P1_OUT &= ~LEDR_mask;
        }
        else
        {
            *P1_OUT |= LEDR_mask;
        }
    }
    return 0;
}
