/**
 * Author : Abel DIDOUH
 * Date : 24 / 03 / 2023
 *
 * 1°) Definitions et declarations pour les registres du port P1
 * 2°) Registres de configuration des interruptions du NVIC
 * 3°) Indices des lignes pour le bouton poussoir 1
 * 4°) Indices des lignes pour la LEDR
 * 5°) 5°) Fonctions Initialiser le port P1 pour le bouton poussoir 1       PORT 1.0
 * 6°) Fonctions Initialiser le port P1 pour la led                         PORT 1.1
 * 7°) Definitions et declarations pour les registres du Timer32            Timer 1
 * 8°) Definitions et declarations pour les registres du port P2
 * 9°) Fonctions Initialiser le port P2 pour la led                         PORT 2.2
 * 10°) Fonctions Initialiser le TIMER 32 TIMER 1                           T32CONTROL1
 * 11°) Definitions et declarations pour les registres du TimerA Timer 0    TIMERA0
 * 12°) Fonctions Initialiser le TIMERA TIMER 0                             TIMERA0
 * 13°) Definitions et declarations pour les registres du PMAPCTL
 * 14°) Fonctions Initialiser - Configuration du PMAPCTL
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
// Registre d'activation des interruptions de 0 vers 31
volatile uint32_t *const NVIC_ISER0 = (void *)(CORE_PERIPHERALS_BASE + 0x0100);
// Declaration et creation de la table des vecteurs d'interruptions
typedef void (*pointer_to_ISR)(void);
#pragma RETAIN(vtab)
#pragma DATA_SECTION(vtab, ".vtable")
pointer_to_ISR vtab[64 + 16 ];
//-------------------------------------------------------------------------------------------------

// 5°) Fonctions Initialiser le port P1 pour le bouton poussoir 1       PORT 1.0 ------------------
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

// 6°) Fonctions Initialiser le port P1 pour la led                     PORT 1.1 ------------------
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

// 7°) Definitions et declarations pour les registres du Timer32 Timer 1 --------------------------
volatile uint32_t * const T32LOAD1  = (void *)(TIMER32_BA + 0x00);
volatile uint32_t * const T32VALUE1 = (void *)(TIMER32_BA + 0x04);
volatile uint32_t * const T32CONTROL1 = (void *)(TIMER32_BA + 0x08);
volatile uint32_t * const T32INTCLR1  = (void *)(TIMER32_BA + 0x0C);
volatile uint32_t * const T32RIS1     = (void *)(TIMER32_BA + 0x10);
volatile uint32_t * const T32MIS1     = (void *)(TIMER32_BA + 0x14);
volatile uint32_t * const T32BGLOAD1  = (void *)(TIMER32_BA + 0x18);
//-------------------------------------------------------------------------------------------------

// 8°) Definitions et declarations pour les registres du port P2 ----------------------------------
//Registres Port 2
const volatile uint8_t * const P2_IN    = (uint8_t *)(PIO_BASE + 0x1);
volatile uint8_t * const P2_OUT         = (uint8_t *)(PIO_BASE + 0x3);
volatile uint8_t * const P2_DIR         = (uint8_t *)(PIO_BASE + 0x5);
volatile uint8_t * const P2_SEL0        = (uint8_t *)(PIO_BASE + 0xB);
volatile uint8_t * const P2_SEL1        = (uint8_t *)(PIO_BASE + 0xD);
volatile uint8_t * const P2_REN         = (uint8_t *)(PIO_BASE + 0x7);
volatile uint8_t * const P2_IES         = (uint8_t *)(PIO_BASE + 0x19);
volatile uint8_t * const P2_IE          = (uint8_t *)(PIO_BASE + 0x1B);
volatile uint8_t * const P2_IFG         = (uint8_t *)(PIO_BASE + 0x1D);
//-------------------------------------------------------------------------------------------------

// 9°) Fonctions Initialiser le port P2 pour la led                     PORT 2.2 ------------------
void init_ledP2(int pEtatLed)
{
    set_bit(*P2_SEL0, LEDP2_R);
    clr_bit(*P2_SEL1, LEDP2_R);
    set_bit(*P2_DIR, LEDP2_R);
    if(pEtatLed == 1)                    // Allumage
    {
        set_bit(*P2_OUT, LEDP2_R);
    }
    else                                // Extinction
    {
        clr_bit(*P2_OUT, LEDP2_R);
    }
}
//-------------------------------------------------------------------------------------------------

// 10°) Fonctions Initialiser le TIMER 32 TIMER 1                     T32CONTROL1 ------------------
void init_timer32(unsigned int pValeurDecrementation)
{
    clr_bit(*T32RIS1, 0);

    clr_bit(*T32CONTROL1, 0);           //Wrapping mode
    set_bit(*T32CONTROL1, 1);           //32 bit
    clr_bit(*T32CONTROL1, 2);           //clk is divided by 1
    clr_bit(*T32CONTROL1, 3);           //clk is divided by 1
    set_bit(*T32CONTROL1, 5);           //Interrupt enable bit
    set_bit(*T32CONTROL1, 6);           //Timer is in periodic mode
    set_bit(*T32CONTROL1, 7);           //Timer enabled

    *T32LOAD1 = pValeurDecrementation; //The value from which the Timer 1 counter decrements
}
//-------------------------------------------------------------------------------------------------

// 11°) Definitions et declarations pour les registres du TimerA Timer 0
volatile uint16_t * const TA0_CTL   =   (uint16_t *)(TA0_BASE + 0x00);      //Controle du timer
volatile uint16_t * const TA0_CTL0  =   (uint16_t *)(TA0_BASE + 0x02);      //Controle du module de sortie
volatile uint16_t * const TA0_CTL1  =   (uint16_t *)(TA0_BASE + 0x04);
volatile uint16_t * const TA0_CTL2  =   (uint16_t *)(TA0_BASE + 0x06);
volatile uint16_t * const TA0_CTL3  =   (uint16_t *)(TA0_BASE + 0x08);
volatile uint16_t * const TA0_CTL4  =   (uint16_t *)(TA0_BASE + 0x0A);
volatile uint16_t * const TA0_CTL5  =   (uint16_t *)(TA0_BASE + 0x0C);
volatile uint16_t * const TA0_CTL6  =   (uint16_t *)(TA0_BASE + 0x0E);      //Controle du module de sortie
volatile uint16_t * const TA0_R     =   (uint16_t *)(TA0_BASE + 0x10);      //Registre de comptage
volatile uint16_t * const TA0_CCR0  =   (uint16_t *)(TA0_BASE + 0x12);      //Registre de capture
volatile uint16_t * const TA0_CCR1  =   (uint16_t *)(TA0_BASE + 0x14);
volatile uint16_t * const TA0_CCR2  =   (uint16_t *)(TA0_BASE + 0x16);
volatile uint16_t * const TA0_CCR3  =   (uint16_t *)(TA0_BASE + 0x18);
volatile uint16_t * const TA0_CCR4  =   (uint16_t *)(TA0_BASE + 0x1A);
volatile uint16_t * const TA0_CCR5  =   (uint16_t *)(TA0_BASE + 0x1C);
volatile uint16_t * const TA0_CCR6  =   (uint16_t *)(TA0_BASE + 0x1E);      //Registre de capture
volatile uint16_t * const TA0_IV    =   (uint16_t *)(TA0_BASE + 0x2E);      //Vecteur d'interruption
volatile uint16_t * const TA0_EX0   =   (uint16_t *)(TA0_BASE + 0x20);      //Choix de la pré division d'horloge
//-------------------------------------------------------------------------------------------------

// 12°) Fonctions Initialiser - Configuration du timer TA0CTL TA0_CTL0 TA0_CCR0 TA0_CCR1 ----------
void init_TIMERA0(int unsigned pPeriodeTimer)
{
    //TA0CTL
    clr_bit(*TA0_CTL, 0);           //Disable TAIFG
    clr_bit(*TA0_CTL, 1);           //TAIE      Timer_A interrupt disabled
    set_bit(*TA0_CTL, 2);           //TACLR     Timer_A clear Reinitialisation du compteur
    set_bit(*TA0_CTL, 4);           //MC        Up Mode Timer counts up to TA0CCR0
    clr_bit(*TA0_CTL, 5);           //MC
    clr_bit(*TA0_CTL, 6);           //ID        Input Divider 0
    clr_bit(*TA0_CTL, 7);           //ID        Input Divider 0
    clr_bit(*TA0_CTL, 8);           //TASSEL    Conservation horloge systeme
    set_bit(*TA0_CTL, 9);           //TASSEL    SMCLK

    //TA0_CTL0
    clr_bit(*TA0_CTL0, 4);          //CCIE      Pas d'interruption
    clr_bit(*TA0_CTL0, 5);          //OUTMOD    Mode de sortie Toggle / Set
    set_bit(*TA0_CTL0, 6);
    set_bit(*TA0_CTL0, 7);
    clr_bit(*TA0_CTL0, 8);          //CAP Mode : compare

    //TA0_CCR0
    *TA0_CCR0 = pPeriodeTimer - 1;  //Periode du timer

    //TA0_CCR1
    *TA0_CCR1 = pPeriodeTimer/2-1; //Rapport cyclique
}
//-------------------------------------------------------------------------------------------------

// 13°) Definitions et declarations pour les registres du PMAPCTL ---------------------------------
volatile uint16_t * const PMAP_KEYID    = (uint16_t *)(PMAP_BA + 0x00);        //Port Mapping Key
volatile uint16_t * const PMAP_CTL      = (uint16_t *)(PMAP_BA + 0x02);        //Port Mapping Control
volatile uint16_t * const PMAP_P2MAP0   = (uint16_t *)(PMAP_BA + 0x10);        //Port Mapping P2.0
//-------------------------------------------------------------------------------------------------

// 14°) Fonctions Initialiser - Configuration du PMAPCTL ------------------------------------------
void init_PMAPCTL()
{
    *PMAP_KEYID     =   0x02D52;
    *PMAP_P2MAP0    =   20;
    *PMAP_KEYID     =   0x02;
}
//-------------------------------------------------------------------------------------------------

