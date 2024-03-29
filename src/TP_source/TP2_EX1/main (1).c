/**
 * Un appui sur le bouton 1 (PORT 1.1) BT1 allume la led rouge LEDR (PORT 1.0), un autre appui sur le bouton 1 �teint la led
 */

#include <stdint.h>

#define PRBA 0x40004C00

volatile uint8_t * const P1_IN  = (uint8_t *)(PRBA);
volatile uint8_t * const P1_OUT = (uint8_t *)(PRBA + 0x2);
volatile uint8_t * const P1_DIR = (uint8_t *)(PRBA + 0x4);
volatile uint8_t * const P1_REN = (uint8_t *)(PRBA + 0x6);
volatile uint8_t * const P1_SEL0 = (uint8_t *)(PRBA + 0xA);
volatile uint8_t * const P1_SEL1 = (uint8_t *)(PRBA + 0xC);

#define LEDR 0
const  uint8_t LEDR_mask = 1 << LEDR;

#define BT1 1
const uint8_t BT1_mask = 1 << BT1;

int main()
{
    //Configuration BT1
    /**
     * P1_SEL0 : 0
     * P1_SEL1 : 0
     * P1_DIR  : 0
     * P1_REN  : 1
     * P1_OUT  : 1
     */
    *P1_SEL0 &= ~ BT1_mask;
    *P1_SEL1 &= ~ BT1_mask;
    *P1_DIR  &= ~ BT1_mask;
    *P1_REN  |=   BT1_mask;
    *P1_OUT  |=   BT1_mask;

    //Configuration LEDR
    /**
     * P1_SEL0 : 0
     * P1_SEL1 : 0
     * P1_DIR  : 1
     */
    *P1_SEL0 &= ~LEDR_mask;
    *P1_SEL1 &= ~LEDR_mask;
    *P1_DIR  |= LEDR_mask;


    //Extinction LEDR
    *P1_OUT &= ~ LEDR_mask;

    int valeurBT1_avant = !(*P1_IN & BT1_mask);
    int valeurBT1_actuelle = 0;

    while(1)
    {

        //Detection front descendant

        valeurBT1_actuelle = !(*P1_IN & BT1_mask);

        if(valeurBT1_actuelle == 0)
        {
            if(valeurBT1_avant == 1)
            {
                *P1_OUT ^= LEDR_mask;
            }
        }
        valeurBT1_avant = valeurBT1_actuelle;




    }

    return 0;
}
