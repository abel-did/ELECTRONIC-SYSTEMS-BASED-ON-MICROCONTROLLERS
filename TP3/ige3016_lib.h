/**
 * Author : Abel DIDOUH
 * Date : 13 / 03 / 2023
 * 0°) Operations sur les bits
 * 1°) Definitions et declarations pour les registres du port P1
 * 2°) Registres de configuration des interruptions du NVIC
 * 3°) Indices des lignes pour le bouton poussoir 1
 * 4°) Indices des lignes pour la LEDR  
 * 5°) Fonctions Initialiser le port P1 pour la ledr                    PORT 1.0
 * 6°) Fonctions Initialiser le port P1 pour le bouton poussoir 1       PORT 1.1
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

// 2°) Registres de configuration des interruptions du NVIC ---------------------------------------
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
//P1 interrupt line
#define P1_INT 35
//-------------------------------------------------------------------------------------------------

// 3°) Indice de la ligne pour la LEDR ------------------------------------------------------------
#define  PB1  1
//-------------------------------------------------------------------------------------------------

// 4°) Indice de la ligne pour la LEDR ------------------------------------------------------------  
#define  LEDR  0
//-------------------------------------------------------------------------------------------------

// 5°) Fonctions Initialiser le port P1 pour la ledr                    PORT 1.0 ------------------
void init_PB();
//-------------------------------------------------------------------------------------------------

// 6°) Fonctions Initialiser le port P1 pour le bouton poussoir 1       PORT 1.1 ------------------
void init_ledr();
//-------------------------------------------------------------------------------------------------

#endif
