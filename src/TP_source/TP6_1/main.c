/**
 *  Configurer le "port map controller" pour router la sortie du timerA0 vers la broche connectée sur la ledrgb_r PORT P2.0.
    Configurer le port P2, pour que la ligne soit en sortie et connectée en interne sur la sortie du timerA.
    Configurer le timerA et le module de sortie pour qu'il génère un signal de sortie à 1 pendant une demi-seconde,
        puis à 0 pendant une demi-seconde. La période de l'horloge système est au démarrage est de 3 MHz
    Démarrer le timerA puis mettre le microcontrôleur en basse consommation.

    Utiliser un timerA avec un seul module de sortie, le module 0. Ce module fixant la période de répétition du timer, il est
    initialisé avec une demie période, et à chaque fin de comptage, le signal de sortie du module est inversé (mode toggle).
    C'est ce signal de sortie qui est envoyé sur la led.
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
