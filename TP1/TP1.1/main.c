/*
 * main.c
 *
 *  Created on: 8 févr. 2023
 *  Author: Abel DID
 */

#include <stdint.h>

const unsigned int tempo = 256000;

//Definition des registres du port
#define PIO_BASE 0x40004C00
volatile uint8_t * const P1_OUT = (void *) (PIO_BASE + 0x02);
volatile uint8_t * const P1_DIR = (void *) (PIO_BASE + 0x04);
volatile uint8_t * const P1_SEL0 = (void *) (PIO_BASE + 0x0A);
volatile uint8_t * const P1_SEL1 = (void *) (PIO_BASE + 0x0C);
//Masque pour le bit correspondant à la LED
#define LEDR 0
const uint8_t LEDR_mask = 1 << LEDR;

int main()
{
    *P1_DIR |= LEDR_mask;
    *P1_SEL1 &= ~LEDR_mask;
    *P1_SEL0 &= ~LEDR_mask;

    while (1)
    {
        unsigned int i;
        //Controle LED
        *P1_OUT &= ~LEDR_mask;                                      // 0000 0010 & ~ 0000 0001 = 0000 0010
        for(i = 0; i < tempo; i++) { }
        //Controle LED
        *P1_OUT |= LEDR_mask;                                       // 0000 0010 | 0000 0001 = 0000 0011
        for(i = 0; i < tempo; i++) { }
    }

}
