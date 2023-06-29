#include "ige3016_lib.h"

int flag_bp = 0;

void isr_BP1(void)
{
    if(rd_bit(*P1_IFG, BP1))
    {
        flag_bp = 1;
        clr_bit(*P1_IFG, BP1);
    }
}

int main(void)
{
    init_BP();
    init_LEDR(0);

    __asm( " CPSID I\n");               //Desactivation generale des interruptions
                                        // Adresse de la table de vecteurs d'interuptions
    *SCB_VTOR = (uint32_t )vtab;
    vtab[P1_INT+16] = isr_BP1;          //Enregistrement interruption P1

    clr_bit(*P1_IES, BP1);              //Interruption sur front descendant
    set_bit(*P1_IE, BP1);               //Autorisation interruption sur la ligne I/0

    *P1_IFG = 0;                        //Effacer toute interruption qui n'aurait pas ete traite
    set_bit(*NVIC_ISER1, P1_INT-32);    //Activation de l'interruption P1 sur le controlleur d'interruption

    __asm(" CPSIE I; ISB");             //Activation generale des interruptions

    while(1)
    {
        __asm(" WFI");
        if(flag_bp)
        {
            flag_bp = 0;
            tog_bit(*P1_OUT, LEDR);

        }
    }


    return 0;
}
