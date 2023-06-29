/**
 *  Configurer le "port map controller" pour router la sortie du timerA0 vers la broche connect�e sur la ledrgb_r PORT P2.0.
    Configurer le port P2, pour que la ligne soit en sortie et connect�e en interne sur la sortie du timerA.
    Configurer le timerA et le module de sortie pour qu'il g�n�re un signal de sortie � 1 pendant une demi-seconde,
        puis � 0 pendant une demi-seconde. La p�riode de l'horloge syst�me est au d�marrage est de 3 MHz
    D�marrer le timerA puis mettre le microcontr�leur en basse consommation.

    Utiliser un timerA avec un seul module de sortie, le module 0. Ce module fixant la p�riode de r�p�tition du timer, il est
    initialis� avec une demie p�riode, et � chaque fin de comptage, le signal de sortie du module est invers� (mode toggle).
    C'est ce signal de sortie qui est envoy� sur la led.
    TP 6.1
 */

#include "ige3016_lib.h"

#define freq 46875/2

int main(void) {
    //Configuration pour la  LED P2 et extinction de la led
    init_ledR_PORT2(0);

    //Configuration TIMERA0
    init_TIMERA0_one_module(freq);

    //Configuration PMAPCTL
    init_PMAPCTL();


    while (1) {
       __asm("  WFI");                                     // Arret du processeur
    }

    return 0;
}
