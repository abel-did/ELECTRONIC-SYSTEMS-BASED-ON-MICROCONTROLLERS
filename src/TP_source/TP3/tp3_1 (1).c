#include "ige3016_lib.h"

//Variable mise a jour par l'interruption - Communication avec la boucle principale
volatile uint8_t PB1_a = 0;

//Routine d'interruption Digital IO Port P1 pour le bouton BP1
void isr_button(void) // Fonctionne en apparance mais effet de bord (sera vu en TP3)
{
    if (rd_bit(*P1_IFG, PB1))  //Inutile quand un seul bouton poussoir, utile quand plusieurs sources d'interruptions
    {
        PB1_a = 1;
        clr_bit(*P1_IFG,PB1);  //Effacement de l'interruption de la ligne
    }
}


int main(void) {
    //Configuration pour la  LEDR et extinction ou allumage de la led
    init_ledr(0);  //0 : extinction, 1 : allumage

    //Configuration interrupteur 1
    init_PB();

    //Configuration des interruptions
    __asm( " CPSID I\n"); //Desactivation generale des interruptions
       // Adresse de la table de vecteurs d'interuptions
    *SCB_VTOR = (uint32_t )vtab;

    vtab[P1_INT+16] = isr_button; //Enregistrement interruption P1
    clr_bit(*P1_IES, PB1);   //Interruption sur front descendant
    set_bit(*P1_IE, PB1);   //Autorisation interruption sur la ligne I/0
    *P1_IFG = 0;  //Effacer toute interruption qui n'aurait pas ete traite
    set_bit(*NVIC_ISER1, P1_INT-32); //Activation de l'interruption P1 sur le controlleur d'interruption
        __asm(" CPSIE I; ISB"); //Activation generale des interruptions

    while (1) {
        __asm("  WFI"); // Arret du processeur
        if (PB1_a) {
            PB1_a=0; //atomique
            tog_bit(*P1_OUT, LEDR);
        }
    }

    return 0;
}

