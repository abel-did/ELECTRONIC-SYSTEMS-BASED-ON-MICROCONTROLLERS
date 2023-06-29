/**
 * Author :     Alexis Collado & Abel DIDOUH
 */

#include "ige3016_lib.h"

const uint32_t MCLK_FREQ = 3E6;  //3 MHz

volatile unsigned int flag_TIMER32 = 0;
volatile unsigned int flag_BP1 = 0;

void isr_timer32(void)
{
    if(rd_bit(*T32RIS1,0))
    {
        flag_TIMER32 = 1;
        set_bit(*T32INTCLR1, 0);
    }
}

void isr_button(void)
{
    if(rd_bit(*P1_IFG,BP1))
    {
        flag_BP1 = 1;
        clr_bit(*P1_IFG,BP1);
    }
}

int main()
{
    init_LEDR(0);
    init_BP();

    //Configuration des interruptions
        __asm( " CPSID I");      //Desactivation generale des interruptions
        *SCB_VTOR = (uint32_t )vtab;
        vtab[TIMER32_1+16] = isr_timer32;
        set_bit(*NVIC_ISER0, TIMER32_1);


        vtab[P1_INT+16] = isr_button;       //Enregistrement interruption P1
        clr_bit(*P1_IES,    BP1);           //Interruption sur front descendant
        set_bit(*P1_IE,     BP1);           //Autorisation interruption sur la ligne I/0
        *P1_IFG = 0;                        //Effacer toute interruption qui n'aurait pas ete traite
        set_bit(*NVIC_ISER1, P1_INT-32);    //Activation de l'interruption P1 sur le controlleur d'interruption

        __asm(" CPSIE I");       //Activation des interruptions


        init_timer32(MCLK_FREQ);

        while(1)
        {

            if (!((flag_TIMER32) || (flag_BP1 = 0)))
            {
                flag_BP1 = 0;
                flag_TIMER32 = 0;
                tog_bit(*P1_OUT, LEDR);

            }
            __asm(" WFI");
        }
        return 0;
}
