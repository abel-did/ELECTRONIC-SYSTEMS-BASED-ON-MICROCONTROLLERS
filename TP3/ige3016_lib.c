/**
 * Author : Abel DIDOUH
 * Date : 13 / 03 / 2023
 * 1°) Definitions et declarations pour les registres du port P1
 * 2°) Registres de configuration des interruptions du NVIC
 * 3°) Indices des lignes pour le bouton poussoir 1
 * 4°) Indices des lignes pour la LEDR  
 * 5°) Fonctions Initialiser le port P1 pour la ledr                    PORT 1.0
 * 6°) Fonctions Initialiser le port P1 pour le bouton poussoir 1       PORT 1.1
 **/

#include "ige3016_lib.h"

// 1°) Definitions et declarations pour les registres du port P1 ----------------------------------
const volatile uint8_t * const P1_IN    = (uint8_t *)(PIO_BASE + 0x0);
volatile uint8_t * const P1_OUT         = (uint8_t *)(PIO_BASE + 0x2);
volatile uint8_t * const P1_DIR         = (uint8_t *)(PIO_BASE + 0x4);
volatile uint8_t * const P1_SEL0        = (uint8_t *)(PIO_BASE + 0xA);
volatile uint8_t * const P1_SEL1        = (uint8_t *)(PIO_BASE + 0xC);
volatile uint8_t * const P1_REN         = (uint8_t *)(PIO_BASE + 0x6);
volatile uint8_t * const P1_IES         = (uint8_t *)(PIO_BASE + 0x18);
volatile uint8_t * const P1_IE          = (uint8_t *)(PIO_BASE + 0x1A);
volatile uint8_t * const P1_IFG         = (uint8_t *)(PIO_BASE + 0x1C);
//-------------------------------------------------------------------------------------------------

// 2°) Registres de configuration des interruptions du NVIC ---------------------------------------
// Registre contenant l'adresse de la table d'interruption
volatile uint32_t *const SCB_VTOR   = (void *)(CORE_PERIPHERALS_BASE + 0xD08);
// Registre d'activation des interruptions de 32 vers 63
volatile uint32_t *const NVIC_ISER1 = (void *)(CORE_PERIPHERALS_BASE + 0x0104);
// Declaration et creation de la table des vecteurs d'interruptions
typedef void (*pointer_to_ISR)(void);
#pragma RETAIN(vtab)
#pragma DATA_SECTION(vtab, ".vtable")
pointer_to_ISR vtab[64 + 16 ];
//-------------------------------------------------------------------------------------------------

// 5°) Fonctions Initialiser le port P1 pour la ledr                    PORT 1.0 ------------------
void init_PB()
{
    //Init bouton P1
    clr_bit(*P1_DIR, PB1);
    set_bit(*P1_REN, PB1);
    set_bit(*P1_OUT, PB1);
    clr_bit(*P1_SEL1, PB1);
    clr_bit(*P1_SEL0, PB1);
}
//-------------------------------------------------------------------------------------------------

// 6°) Fonctions Initialiser le port P1 pour le bouton poussoir 1       PORT 1.1 ------------------
void init_ledr(int pNombre)
{
    set_bit(*P1_DIR, LEDR);
    clr_bit(*P1_SEL1, LEDR);
    clr_bit(*P1_SEL0, LEDR);
    if(pNombre == 1)                    // Allumage
    {
        set_bit(*P1_OUT, LEDR);
    }
    else                                // Extinction
    {
        clr_bit(*P1_OUT, LEDR);
    }
}
//-------------------------------------------------------------------------------------------------