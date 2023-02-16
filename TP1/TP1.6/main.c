/**
 * Author : Abel DIDOUH
 * Date : 16 / 02 / 2023
 * Description : A simple program that turns on YELLOW LED when the button P1.4 is pressed 
 * 		 else turns on RED LED
 */

#include <stdint.h>

#define PRBA 0x40004C00

const volatile uint8_t * const P1_IN = (void *) (PRBA);
volatile uint8_t * const P1_OUT = (void *) (PRBA + 0x2);
volatile uint8_t * const P1_DIR = (void *) (PRBA + 0x4);
volatile uint8_t * const P1_REN = (void *) (PRBA + 0x6);
volatile uint8_t * const P1_SEL0 = (void *) (PRBA + 0xA);
volatile uint8_t * const P1_SEL1 = (void *) (PRBA + 0xC);

const volatile uint8_t * const P2_IN = (void *) (PRBA + 0x1);
volatile uint8_t * const P2_OUT = (void *) (PRBA + 0x3);
volatile uint8_t * const P2_DIR = (void *) (PRBA + 0x5);
volatile uint8_t * const P2_REN = (void *) (PRBA + 0x7);
volatile uint8_t * const P2_SEL0 = (void *) (PRBA + 0xB);
volatile uint8_t * const P2_SEL1 = (void *) (PRBA + 0xD);

#define LEDR_P1 0		//RED LED PORT1 BIT0
const uint8_t LEDR_mask = 1 << LEDR_P1;

#define LEDR_P2 0		//RED LED PORT2 BIT0
#define LEDV_P2	1		//GREEN LED PORT2 BIT1
const uint8_t LEDJ_mask = 1 << LEDR_P2;
LEDJ_mask = 1 << LEDV_P2;

#define BUTTON_2 4		//BUTTON PORT1 BIT4
const uint8_t BUTTON_2_mask = 1 << BUTTON_2;


int main()
{
	//Configure BUTTON_2
	*P1_SEL0 &= ~BUTTON_2_mask;
	*P1_SEL1 &= ~BUTTON_2_mask;
	*P1_DIR  &= ~BUTTON_2_mask;
	*P1_REN  |= BUTTON_2_mask;
	*P1_OUT  |= BUTTON_2_mask;
	//Configure LEDR_P1
	*P1_SEL0 &= ~LEDR_mask;
	*P1_SEL1 &= ~LEDR_mask;
	*P1_DIR  |= LEDR_mask;
	//Configure YELLOW LED : LEDR_P2 + LEDV_P2
	*P2_SEL0 &= ~LEDJ_mask;
	*P2_SEL1 &= ~LEDJ_mask;
	*P2_DIR  |= LEDJ_mask;
	

	while(1)
	{
		if( *P1_IN & (1 << 4) )
		{
			*P1_OUT &= ~LEDR_mask;
			*P2_OUT |= LEDJ_mask;
		}
		else
		{
			*P1_OUT |= LEDR_mask;
			*P2_OUT &= ~LEDJ_mask;
		}
	}
	return 0;
}
