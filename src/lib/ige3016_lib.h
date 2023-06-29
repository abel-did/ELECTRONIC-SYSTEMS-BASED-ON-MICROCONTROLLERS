/**
 * Author 	: Abel DIDOUH
 * Date		: 27 / 03 / 2023
 *
 * 0°) 		Operation sur les bits
 * 1°) 		Definitions et declarations pour les registres du port P1
 * 2°) 		Indice de la ligne pour le BP1 PORT1.1 / BP2 PORT1.4
 * 3°) 		Indice de la ligne pour la LEDR PORT1.0
 * 4°)		Fonctions Initialiser BP1 PORT1.1 / BP2 PORT1.4
 * 5°)    	Fonctions Initialiser LEDR PORT1.0                            
 * 6°) 		Definitions et declarations pour les registres du port P2
 * 7°) 		Indice de la ligne pour la LED PORT2
 * 8°) 		Fonctions Initialiser le port P2 pour la led       PORT2.0 PORT2.1 PORT2.2
 * 9°)		Definitions et declarations pour les registres de configuration des interruptions du NVIC
 * 10°)		Definitions et declarations pour les registres du Timer32 Timer 1
 * 11°) 	Fonctions Initialiser le TIMER 32 TIMER 1 
 * 12°) 	Definitions et declarations pour les registres du TimerA Timer 0 
 * 13°) 	Definitions et declarations pour les registres du PMAPCTL
 * 14°) 	Fonctions Initialiser - Configuration du timer TA0CTL TA0_CTL0 TA0_CCR0 TA0_CCR1
 * 15°) 	Fonctions Initialiser - Configuration du PMAPCTL 
 * 14°)     Fonctions Initialiser - Configuration du timer TA0CTL TA0_CTL0 TA0_CCR0 TA0_CCR1
 * 15°)     Fonctions Initialiser - Configuration du PMAPCTL
 * 16°)     Fonctions Initialiser - Configuration du TIMERA0 deux modules
 * 17°)     Fonctions Initialiser - Configuration du PMAPCTL deux modules
 * 18°)     Fonctions Initialiser - Configuration du PMAPCTL LED BLANCHE
 * 19°)     Fonctions Initialiser - Configuration des sorties LEDRGB
 **/

#ifndef     IGE3016_LIB_H_ 
#define     IGE3016_LIB_H_

#include <stdint.h>

// 0°) Operation sur les bits ---------------------------------------------------------------------
    //Set_bit                                           --Mise a 1
#define set_bit(X,Y) (X = X | ((uintmax_t) 1 << Y))
    //Clr_bit                                           --Mise a 0
#define clr_bit(X,Y) (X = X &~ ((uintmax_t) 1 << Y))
    //Tog_bit                                           --Inverse le bit
#define tog_bit(X,Y) (X = X ^ ((uintmax_t) 1<< Y))
    //rd_bit                                            --Lecture du bit
#define rd_bit(X,Y) ((X >> Y) & 1)
//-------------------------------------------------------------------------------------------------

// 1°) Definitions et declarations pour les registres du port P1 ----------------------------------
//Port Register Base Adress
#define PIO_BASE 0x40004C00
//Registres Port 1
extern const volatile uint8_t * const P1_IN;
extern volatile uint8_t * const P1_OUT;
extern volatile uint8_t * const P1_DIR;
extern volatile uint8_t * const P1_SEL0;
extern volatile uint8_t * const P1_SEL1;
extern volatile uint8_t * const P1_REN;
extern volatile uint8_t * const P1_IES;
extern volatile uint8_t * const P1_IE;
extern volatile uint8_t * const P1_IFG;
//-------------------------------------------------------------------------------------------------

// 2°) Indice de la ligne pour le BP1 PORT1.1 / BP2 PORT1.4 ---------------------------------------
#define  PB1  1
#define  PB2  4
//-------------------------------------------------------------------------------------------------

// 3°) Indice de la ligne pour la LEDR PORT1.0 ----------------------------------------------------
#define  LEDR  0
//-------------------------------------------------------------------------------------------------

// 4°) Fonctions Initialiser BP1 PORT1.1 / BP2 PORT1.4				 ------------------
void init_BP(void);
//-------------------------------------------------------------------------------------------------

// 5°) Fonctions Initialiser LEDR PORT1.0					 ------------------
void init_LEDR(int pEtatLed);
//-------------------------------------------------------------------------------------------------

// 6°) Definitions et declarations pour les registres du port P2 ----------------------------------
//Registres Port 2
extern const volatile uint8_t * const P2_IN;
extern volatile uint8_t * const P2_OUT;
extern volatile uint8_t * const P2_DIR;
extern volatile uint8_t * const P2_SEL0;
extern volatile uint8_t * const P2_SEL1;
extern volatile uint8_t * const P2_REN;
extern volatile uint8_t * const P2_IES;
extern volatile uint8_t * const P2_IE;
extern volatile uint8_t * const P2_IFG;
//-------------------------------------------------------------------------------------------------

// 7°) Indice de la ligne pour la LED PORT2--------------------------------------------------------
#define     LEDP2_R     0
#define     LEDP2_G     1
#define     LEDP2_B     2
//-------------------------------------------------------------------------------------------------

// 8°) Fonctions Initialiser le port P2 pour la led       PORT2.0 PORT2.1 PORT2.2 -----------------
void init_ledR_PORT2(int pEtatLed);
//-------------------------------------------------------------------------------------------------

// 9°) Registres de configuration des interruptions du NVIC --------------------------------------
//Declaration et creation de la table des vecteurs d'interruptions
typedef void (*pointer_to_ISR)(void);
#pragma RETAIN(vtab)
#pragma DATA_SECTION(vtab, ".vtable")
extern pointer_to_ISR vtab[64 + 16 ];
//System Control  Bloc (registres de controles mappes en memoire)
#define CORE_PERIPHERALS_BASE 0xE000E000
//Registre contenant l'adresse de la table d'interruption
extern volatile uint32_t *const SCB_VTOR;
//Registre d'activation des interruptions de 32 vers 63
extern volatile uint32_t *const NVIC_ISER1;
//Registre d'activation des interruptions de 0 vers 31
extern volatile uint32_t *const NVIC_ISER0;
//P1 interrupt line
#define P1_INT 35
//TIMER 1
#define TIMER1 25
//-------------------------------------------------------------------------------------------------

// 10°) Definitions et declarations pour les registres du Timer32 Timer 1
#define TIMER32_BA 0x4000C000
extern volatile uint32_t * const T32LOAD1;
extern volatile uint32_t * const T32VALUE1;
extern volatile uint32_t * const T32CONTROL1;
extern volatile uint32_t * const T32INTCLR1;
extern volatile uint32_t * const T32RIS1;
extern volatile uint32_t * const T32MIS1;
extern volatile uint32_t * const T32BGLOAD1;
//-------------------------------------------------------------------------------------------------

// 11°) Fonctions Initialiser le TIMER 32 TIMER 1                     T32CONTROL1 -----------------
void init_timer32(unsigned int pValeurDecrementation);
//-------------------------------------------------------------------------------------------------

// 12°) Definitions et declarations pour les registres du TimerA Timer 0 --------------------------
#define TA0_BASE 0x40000000
extern volatile uint16_t * const TA0_CTL;
extern volatile uint16_t * const TA0_CTL0;
extern volatile uint16_t * const TA0_CTL1;
extern volatile uint16_t * const TA0_CTL2;
extern volatile uint16_t * const TA0_CTL3;
extern volatile uint16_t * const TA0_CTL4;
extern volatile uint16_t * const TA0_CTL5;
extern volatile uint16_t * const TA0_CTL6;
extern volatile uint16_t * const TA0_R;
extern volatile uint16_t * const TA0_CCR0;
extern volatile uint16_t * const TA0_CCR1;
extern volatile uint16_t * const TA0_CCR2;
extern volatile uint16_t * const TA0_CCR3;
extern volatile uint16_t * const TA0_CCR4;
extern volatile uint16_t * const TA0_CCR5;
extern volatile uint16_t * const TA0_CCR6;
extern volatile uint16_t * const TA0_IV;
extern volatile uint16_t * const TA0_EX0;
//-------------------------------------------------------------------------------------------------

// 13°) Definitions et declarations pour les registres du PMAPCTL ---------------------------------
#define PMAP_BA 0x40005000
extern volatile uint16_t * const PMAP_KEYID;
extern volatile uint16_t * const PMAP_CTL;
extern volatile uint8_t * const PMAP_P2MAP0;
extern volatile uint8_t * const PMAP_P2MAP1;
extern volatile uint8_t * const PMAP_P2MAP2;
//-------------------------------------------------------------------------------------------------

// 14°) Fonctions Initialiser - Configuration du timer TA0CTL TA0_CTL0 TA0_CCR0 TA0_CCR1 ----------
void init_TIMERA0_one_module(int unsigned pPeriodeTimer);
//-------------------------------------------------------------------------------------------------

// 15°) Fonctions Initialiser - Configuration du PMAPCTL ------------------------------------------
void init_PMAPCTL(void);
//-------------------------------------------------------------------------------------------------

// 16°) Fonctions Initialiser - Configuration du TIMERA0 deux modules -----------------------------
void init_TIMERA0_two_module(int unsigned pPeriodeTimer);
//-------------------------------------------------------------------------------------------------

// 17°) Fonctions Initialiser - Configuration du PMAPCTL deux modules -----------------------------
void init_PMAPCTL_two_module(void);
//-------------------------------------------------------------------------------------------------

// 18°) Fonctions Initialiser - Configuration du PMAPCTL LED RGB     ------------------------------
void init_PMAPCTL_RGB_led(void);
//-------------------------------------------------------------------------------------------------

// 19°) Fonctions Initialiser - Configuration des sorties LEDRGB ----------------------------------
void init_ledRGB_WHITE(void);
//-------------------------------------------------------------------------------------------------

// 20°) Fonctions Initialiser - Configuration des sorties LEDRGB ----------------------------------
void init_ledRGB_YELLOW(void);
//-------------------------------------------------------------------------------------------------

#endif
