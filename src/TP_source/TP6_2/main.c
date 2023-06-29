/**
 * TP 6.2
 */
#include "ige3016_lib.h"

#define freq 46875/2

int main(void) {
    //Configuration pour la  LED P2 et extinction de la led
    init_ledR_PORT2(0);

    //Configuration TIMERA0
    init_TIMERA0_two_module(freq);

    //Configuration PMAPCTL
    init_PMAPCTL_two_module();


    while (1) {
       __asm("  WFI");                                     // Arret du processeur
    }

    return 0;
}
