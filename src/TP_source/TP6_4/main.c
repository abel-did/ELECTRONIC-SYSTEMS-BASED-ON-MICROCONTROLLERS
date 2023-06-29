/**
 * TP6.4
 */
#include "ige3016_lib.h"

#define freq 46875/2

int main(void) {
    //Configuration pour la  LED P2 et extinction ou allumage de la led
    init_ledRGB_YELLOW();
    //Configuration TIMERA0
    init_TIMERA0_two_module(freq);

    //Configuration PMAPCTL
    init_PMAPCTL_RGB_led();


    while (1) {
       __asm("  WFI");                                     // Arret du processeur
    }

    return 0;
}
