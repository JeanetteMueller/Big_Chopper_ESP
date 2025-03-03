#ifdef ESP_PLATFORM
#ifndef PlayerEsp32SoftwareSerial_h
#define PlayerEsp32SoftwareSerial_h
#include "DYPlayer.h"
#include <driver/uart.h>
#include <SoftwareSerial.h>

namespace DY
{
	class PlayerEsp32SoftwareSerial : public DYPlayer
	{
	public:
		PlayerEsp32SoftwareSerial(uart_port_t uart_num, uint8_t pin_rx, uint8_t pin_tx);
		void serialWrite(uint8_t *buffer, uint8_t len);
		bool serialRead(uint8_t *buffer, uint8_t len);
		uart_port_t uart_num;

	protected:
		EspSoftwareSerial::UART SWSerial;
	};
}
#endif
#endif
