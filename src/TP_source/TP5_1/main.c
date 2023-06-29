/**
 * Author :     Alexis Collado & Abel DIDOUH
 */

#include "ige3016_lib.h"

const uint32_t MCLK_FREQ = 3E6;  //3 MHz

volatile unsigned int flag_TIMER32 = 0;

void isr_timer32(void)
{
    if(rd_bit(*T32RIS1,0))
    {
        flag_TIMER32 = 1;
        set_bit(*T32INTCLR1, 0);
    }
}

int main()
{
    init_LEDR(0);
    init_timer32(MCLK_FREQ);

    //Configuration des interruptions
        __asm( " CPSID I");      //Desactivation generale des interruptions
        *SCB_VTOR = (uint32_t )vtab;
        vtab[TIMER32_1+16] = isr_timer32;
        set_bit(*NVIC_ISER0, TIMER32_1);
        __asm(" CPSIE I");       //Activation des interruptions

        while(1)
        {
            __asm(" WFI");
            if(flag_TIMER32)
            {
                tog_bit(*P1_OUT, LEDR);
                flag_TIMER32 = 0;
            }
        }
}
