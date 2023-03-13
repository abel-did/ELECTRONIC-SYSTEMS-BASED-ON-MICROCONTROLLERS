/**
 * Abel DIDOUH
 *
 */
#include <stdint.h>

//Declaration et creation de la table des vecteurs d'interruptions
typedef void (*pointer_to_ISR)(void);
#pragma RETAIN(vtab)
#pragma DATA_SECTION(vtab, ".vtable")
pointer_to_ISR vtab[64 + 16 ];

//System Control  Bloc (registres de controles mappes en memoire)
#define CORE_PERIPHERALS_BASE 0xE000E000
//Registre contenant l'adresse de la table d'interruption
volatile uint32_t *const SCB_VTOR = (void *)(CORE_PERIPHERALS_BASE + 0xD08);
//Registre d'activation des interruptions de 0 / 31
volatile uint32_t *const NVIC_ISER0 = (void *)(CORE_PERIPHERALS_BASE + 0x0100);

#define RTC_C_BA 0x40004400
volatile uint16_t * const RTCCTL0 = (uint16_t*)(RTC_C_BA + 0x0);
volatile uint16_t * const RTCIV   = (uint16_t*)(RTC_C_BA + 0x0E);
#define RTC_C_INT 29  //Ligne d'interruption

//Variable mise a jour par l'interruption - Communication avec la boucle principale
uint16_t RTC_event = 0;

//Routine d'interruption RTC_C
void isr_rtc(void)
{
    if ( *RTCCTL0 & (1 << 5))
    {
        RTC_event = 1;
        *RTCIV &= ~(1 << 5);  //Effacement de l'interruption de la ligne
    }
}

int main()
{
    //Configuration des interruptions
    __asm( " CPSID I\n"); //Desactivation generale des interruptions
    // Configuration
    *SCB_VTOR = (uint32_t )vtab;

    vtab[RTC_C_INT+16] = isr_rtc;           //Enregistrement interruption RTC_C

    *NVIC_ISER0 |= 1 << (31-RTC_C_INT);     //Activation de l'interruption RTC_C sur le controlleur d'interruption
        __asm(" CPSIE I; ISB");             //Activation generale des interruptions

    while (1) {
        __asm("  WFI");                     // Arret du processeur
        if (RTC_event) {
            RTC_event = 0;
        }
    }
}


