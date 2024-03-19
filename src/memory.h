////////// Memory and Ram Tracker Funktionen ****** 

#include <avr/io.h> 
#define FREE_MARK 0x77
extern uint8_t __bss_end;                    // lowest stack address
extern uint8_t __stack;                      // highest stack address

uint16_t stack_size( void )             // available stack
{
	return (uint16_t)&__stack - (uint16_t)&__bss_end + 1;
}


uint16_t stack_free( void )             // aktuell freier stack bei Aufruf
{
	uint8_t flag = 1;
	uint16_t i, frei = 0;
	uint8_t *mp = &__bss_end;

	for( i = SP - (uint16_t)&__bss_end + 1; i; i--){
		if ( *mp != FREE_MARK )  {
			flag = 0;
		}  
		frei += flag;
		*mp++ = FREE_MARK;
	}
	return frei;
}


uint16_t stack_unused( void )           // bis dahin unbenutzter stack bei Aufruf
{
	uint8_t flag = 1;
	uint16_t i, frei = 0;
	uint8_t * mp = &__bss_end;

	for( i = SP - (uint16_t)&__bss_end + 1; i; i--){
		if ( *mp != FREE_MARK )  {
			flag = 0;
		}  
		frei += flag;
		mp++;
	}
	return frei;
}