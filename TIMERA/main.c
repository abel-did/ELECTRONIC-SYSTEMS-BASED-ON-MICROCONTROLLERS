/*
 * Author : Abel DIDOUH
 * Date : 24 / 03 / 2023
 */
#include "ige3016_lib.h"

#define number 3000000/2

//Variable mise a jour par l'interruption - Communication avec la boucle principale
volatile uint8_t flag_TIMER32 = 0;

//Routine d'interruption TIMER32 Timer 1
void isr_timer1(void)
{
    if (rd_bit(*T32RIS1, 0))
    {
        flag_TIMER32 = 1;
        set_bit(*T32INTCLR1 ,0);        //Effacement de l'interruption de la ligne
    }
}


int main(void) {
    //Configuration pour la  LED P2 et extinction ou allumage de la led
    init_ledP2(0);                       //0 : extinction, 1 : allumage

    //Configuration TIMER 32
    init_timer32(number);

    //Configuration des interruptions
    __asm( " CPSID I\n"); //Desactivation generale des interruptions
    // Adresse de la table de vecteurs d'interuptions
    *SCB_VTOR = (uint32_t )vtab;

    vtab[TIMER1+16] = isr_timer1;                           //Enregistrement interruption TIMER1


    set_bit(*NVIC_ISER0, TIMER1);                           //Activation de l'interruption TIMER1 sur le controlleur d'interruption
        __asm(" CPSIE I; ISB");                             //Activation generale des interruptions

    while (1) {
        __asm("  WFI");                                     // Arret du processeur
        if (flag_TIMER32) {
            flag_TIMER32=0;                                 //atomique
            tog_bit(*P2_OUT, LEDP2_G);
        }
    }

    return 0;
}
