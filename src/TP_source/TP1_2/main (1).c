
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

#define BUTTON 1
const uint8_t BUTTON_mask = 1 << BUTTON;

int main()
{
    //Configuration pour la  LEDR
    *P1_SEL0 &= ~LEDR_mask;
    *P1_SEL1 &= ~LEDR_mask;
    *P1_DIR |= LEDR_mask;

    //Configuration a rajouter pour l'interrupteur 1
    *P1_SEL0 &= ~ BUTTON_mask;
    *P1_SEL1 &= ~ BUTTON_mask;
    *P1_DIR  &= ~BUTTON_mask; // entrée
    *P1_REN |= BUTTON_mask; //RES Pull up ou pull down
    *P1_OUT |= BUTTON_mask; // res pull up

    while(1)
    {
        if( *P1_IN  & (1 << BUTTON) )
        {
            *P1_OUT &= ~ LEDR_mask;
        }
        else
        {
           *P1_OUT |=  LEDR_mask;
        }
    }

    return 0;
}

/**
#include<stdint.h>

const unsigned int tempo = 256000

#define PRBA 0x40004C00
const volatile uint8_t * const P1_IN = (void *)(PRBA);
volatile uint8_t * const P1_DIR = (void *)(PRBA + 0x2);
volatile uint8_t * const P1_REN =


int main()
{

}
**/



























































