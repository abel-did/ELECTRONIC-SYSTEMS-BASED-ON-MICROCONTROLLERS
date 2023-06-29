#include <stdint.h>

const unsigned int tempo = 256000;

#define PRBA 0x40004C00             //PORT REGISTER BASE ADRESS

volatile uint8_t * const P1_OUT = (void *) (PRBA + 0x2);
volatile uint8_t * const P1_DIR = (void *) (PRBA + 0x4);
volatile uint8_t * const P1_SEL0 = (void *) (PRBA + 0xA);
volatile uint8_t * const P1_SEL1 = (void *) (PRBA + 0xC);

#define LEDR 0
const uint8_t LEDR_mask = 1 << LEDR;

int main()
{
    *P1_SEL0 &= ~ LEDR_mask;
    *P1_SEL1 &= ~ LEDR_mask;
    *P1_DIR |= LEDR_mask;

    while(1)
    {
        unsigned int i = 0;
        *P1_OUT &= ~ LEDR_mask;             //Extinction
        for(i = 0; i < tempo; i++) {}
        *P1_OUT |= LEDR_mask;               //Allumage
        for(i = 0; i < tempo; i++) {}
    }

}
