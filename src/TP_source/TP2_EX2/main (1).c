/*
 * TP2 Ex. 2
 * Commande led1 par bouton 1 et interruption
 * Un appui allume/eteint
 *  Code a modifier si compiler avec optimisation (Ex 3)
 *  Modifie le on: 17/02/2023
 *      Author: Y. Blanchard
 */


#include <stdint.h>

//Declaration et creation de la table des vecteurs d'interruptions
typedef void (*pointer_to_ISR)(void);
#pragma RETAIN(vtab)
#pragma DATA_SECTION(vtab, ".vtable")
pointer_to_ISR vtab[64 + 16 ];

//System Control  Bloc (registres de controles mappes en memoire)
#define CORE_PERIPHERALS_BASE 0xE000E000

//Registre contenant l'adresse de la table d'interruption
volatile uint32_t *const SCB_VTOR = (void *)(CORE_PERIPHERALS_BASE + 0xD08);

//Registre d'activation des interruptions de 32 à 63
volatile uint32_t *const NVIC_ISER1 = (void *)(CORE_PERIPHERALS_BASE + 0x0104);

#define PIO_BASE 0x40004C00
#define P1_INT 35  //P1 interrupt line
volatile const uint8_t * const volatile P1_IN = (uint8_t *)(PIO_BASE + 0x0);
volatile uint8_t * const P1_OUT = (uint8_t*)(PIO_BASE + 2);
volatile uint8_t * const P1_DIR = (uint8_t*)(PIO_BASE + 4);
volatile uint8_t * const P1_SEL0 = (uint8_t*)(PIO_BASE + 0xA);
volatile uint8_t * const P1_SEL1 = (uint8_t*)(PIO_BASE + 0xC);
volatile uint8_t * const P1_REN = (uint8_t *)(PIO_BASE + 0x6);
volatile uint8_t * const P1_IES = (uint8_t *)(PIO_BASE + 0x18);
volatile uint8_t * const P1_IE = (uint8_t *)(PIO_BASE + 0x1A);
volatile uint8_t * const P1_IFG = (uint8_t *)(PIO_BASE + 0x1C);

// Masque pour la ledr et le bouton 1
#define  LEDR  0
#define  PB1  1
const uint8_t LEDR_mask = 1 << LEDR;
const uint8_t PB1_mask = 1 << PB1;

//Variable mise a jour par l'interruption - Communication avec la boucle principale
uint8_t PB1_a = 0;

//Routine d'interruption Digital IO Port P1
void isr_button(void) // Fonctionne en apparance mais effet de bord (sera vu en TP3)
{
    if (*P1_IFG & PB1_mask)  //Inutile quand un seul bouton poussoir, utile quand plusieurs sources d'interruptions
    {
        PB1_a = 1;
        *P1_IFG &= ~PB1_mask;  //Effacement de l'interruption de la ligne
    }
}

int main() {
    //Configuration pour la  LEDR et extinction
    *P1_DIR |= LEDR_mask;
    *P1_SEL1 &= (~LEDR_mask);
    *P1_SEL0 &= (~LEDR_mask);
    *P1_OUT &= ~LEDR_mask;

    //Configuration interrupteur 1
    *P1_DIR &=   ~PB1_mask;
    *P1_REN |=  PB1_mask;
    *P1_OUT |=  PB1_mask;
    *P1_SEL1 &=  (~PB1_mask);
    *P1_SEL0 &=  (~PB1_mask);

    //Configuration des interruptions
    __asm( " CPSID I\n"); //Desactivation generale des interruptions
       // Configuration
    *SCB_VTOR = (uint32_t )vtab;

    vtab[P1_INT+16] = isr_button; //Enregistrement interruption P1
    *P1_IES |= PB1_mask;   //Interruption sur front descendant
    *P1_IE |= PB1_mask;   //Autorisation interruption sur la ligne I/0
    *NVIC_ISER1 |= 1 << (P1_INT-32); //Activation de l'interruption P1 sur le controlleur d'interruption
        __asm(" CPSIE I; ISB"); //Activation generale des interruptions

    while (1) {
        __asm("  WFI"); // Arret du processeur
        if (PB1_a) {
            PB1_a=0; //atomique
            *P1_OUT ^= LEDR_mask;
        }
    }

    return 0;
}
