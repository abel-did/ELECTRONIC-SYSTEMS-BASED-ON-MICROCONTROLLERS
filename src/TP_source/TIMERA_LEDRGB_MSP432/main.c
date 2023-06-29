/*
 * Author : Abel DIDOUH
 * Date : 25 / 03 / 2023
 */
#include "ige3016_lib.h"

#define pwm_freq 3000000/200

int main(void) {
    //Configuration pour la  LED P2 et extinction ou allumage de la led
    init_ledRGB(0,0);                       //0 : extinction 0 : LEDR

    //Configuration TIMERA0
    init_TIMERA0(pwm_freq);

    //Configuration PMAPCTL
    init_PMAPCTL();


    while (1) {
       __asm("  WFI");                                     // Arret du processeur
    }

    return 0;
}
