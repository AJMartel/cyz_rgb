#include <avr/interrupt.h>
#include <limits.h>
#include "usiTwi/usiTwiSlave.h"
#include "cyz/cyz_rgb.h"
#include "cyz/cyz_cmd.h"

int main(void)
{
	CYZ_RGB_GET_INSTANCE();
	CYZ_CMD_GET_INSTANCE();

	cyz_rgb.color.r = 255;
	CYZ_CMD_load_boot_params();
	usiTwiSlaveInit(0x0d);

	TIFR   = (1 << TOV0);  /* clear interrupt flag */
	TIMSK  = (1 << TOIE0); /* enable overflow interrupt */
	TCCR0B = (1 << CS00);  /* start timer, no prescale */
	sei(); // enable interrupts

	for(;;)
	{
		while(usiTwiDataInReceiveBuffer()) {
			_CYZ_CMD_receive_one_byte(usiTwiReceiveByte());
		}

		while (_CYZ_CMD_is_data_in_send_buffer()) {
			usiTwiTransmitByte(_CYZ_CMD_get_one_byte_from_send_buffer());
		}
	}

	return 1;
}

/*	Triggered when timer overflows. */
/*  This runs fast enough that 255 calls are less than a glimpse for a human. */
/*  TODO: figure out _actual_ math */
ISR(SIG_OVERFLOW0)
{
	_CYZ_CMD_tick();
	_CYZ_RGB_pulse();
}
