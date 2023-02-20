/**
 * Author : Abel DIDOUH
 * Date : 20 / 02 / 2023
 * Description : Library for PORT1 : 	BUTTON P1 1 
 * 				 	BUTTON P1 4
 * 				 	LED    P1 0
 * 		LED : Init / ON / OFF
 * 		PB1 : Init / READ
 * 		PB2 : Init / READ
 */

//Header
#include"libLB.h"

//Configure Register PORT1
const volatile uint8_t * P1_IN = (uint8_t) (PRBA);
volatile uint8_t * P1_OUT = (uint8_t) (PRBA + 0x2);
volatile uint8_t * P1_IN = (uint8_t) (PRBA + 0x4);
volatile uint8_t * P1_DIR = (uint8_t) (PRBA + 0x6);
volatile uint8_t * P1_REN = (uint8_t) (PRBA + 0xA);
volatile uint8_t * P1_SEL0 = (uint8_t) (PRBA + 0xA);
volatile uint8_t * P1_SEL1 = (uint8_t) (PRBA + 0xC);

//Configure BUTTON PORT1 1 
//Configure BUTTON PORT1 4
void init_pb()
{
	//BUTTON PORT1 	1
	//SEL0	       	0 
	//SEL1	       	0
	//DIR		0
	//REN		1
	//OUT		1
	clr_bit(*P1_SEL0, PB1);
	clr_bit(*P1_SEL1, PB1);
	clr_bit(*P1_DIR, PB1);
	set_bit(*P1_REN, PB1);
	set_bit(*P1_OUT, PB1);

	//BUTTON PORT1 	4
	//SEL0		0
	//SEL1		0
	//DIR		0
	//REN		1
	//OUT		1
	clr_bit(*P1_SEL0, PB2);
	clr_bit(*P1_SEL1, PB2);
	clr_bit(*P1_DIR, PB2);
	set_bit(*P1_REN, PB2);
	set_bit(*P1_OUT, PB2);
}
//Configure LED PORT1 0 --Color : RED
void init_ledR()
{
	clr_bit(*P1_SEL0, LEDR);
	clr_bit(*P1_SEL1, LEDR);
	set_bit(*P1_DIR, LEDR);
}
//Read BUTTON P1 1
//ON : 0
//OFF : 1
int rd_pb1()
{
	return rd_bit(*P1_IN, PB1);
}
//READ BUTTON P1 4 
//ON : 0
//OFF : 1
int rd_pb2()
{
	return rd_bit(*P1_IN, PB2);
}
//LED ON
void ledr_on()
{
	set_bit(*P1_OUT, LEDR);
}
//LED OFF
void ledr_off()
{
	clr_bit(*P1_OUT, LEDR);
}
//READ BUTTON P1 1 
//READ BUTTON P1 4
void pb_read(int* pb1, int* pb2)
{
	*pb1 = rd_bit(*P1_IN, PB1);
	*pb2 = rd_bit(*P1_IN, PB2);
}
