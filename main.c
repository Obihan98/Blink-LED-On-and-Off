/*
 * BlinkWhenClick.c
 *
 * Created: 4/8/2022 5:17:56 PM
 * Author : Orhan Ozbasaran
 */ 

#include <avr/io.h>

#define XTAL_FRQ 8000000lu
#define SET_BIT(p,i) ((p) |=  (1 << (i)))
#define CLR_BIT(p,i) ((p) &= ~(1 << (i)))
#define GET_BIT(p,i) ((p) &   (1 << (i)))

void avr_wait(unsigned short msec)
{
	TCCR0 = 3;
	while (msec--) {
		TCNT0 = (unsigned char)(256 - (XTAL_FRQ / 64) * 0.001);
		SET_BIT(TIFR, TOV0);
		while (!GET_BIT(TIFR, TOV0));
	}
	TCCR0 = 0;
}

int main(void)
{
    DDRB = 1;
	PORTB = 1;
    while (1) 
    {
		if (PINB & 2)
		{
			PORTB = 0;
		}
		else
		{
			PORTB = 1;
			avr_wait(500);
			PORTB = 0;
			avr_wait(500);
		}
    }
}

