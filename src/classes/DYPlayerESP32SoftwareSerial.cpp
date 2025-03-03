#ifdef ESP_PLATFORM

#include "DYPlayerESP32SoftwareSerial.h"

#define BUFFER_SIZE_RX 256
#define BUFFER_SIZE_TX 256

namespace DY
{
	PlayerEsp32SoftwareSerial::PlayerEsp32SoftwareSerial(uart_port_t uart_num, uint8_t pin_tx, uint8_t pin_rx)
	{
		SWSerial.begin(9600, SWSERIAL_8N1, pin_rx, pin_tx);
		while(!SWSerial);
	}
	void PlayerEsp32SoftwareSerial::serialWrite(uint8_t *buffer, uint8_t len)
	{
		SWSerial.write((char *)buffer, len);
	}
	bool PlayerEsp32SoftwareSerial::serialRead(uint8_t *buffer, uint8_t len)
	{
		int length = 0;
		// Retry to get the data from the module for a second, then give up. The
		// next command should go a usual..
		uint8_t retry = 100;
		while (length < len && retry > 0)
		{
			length = SWSerial.available();
			vTaskDelay(10 / portTICK_PERIOD_MS);
			retry--;
		}
		length = SWSerial.readBytes(buffer, length);
		if (length == len)
		{
		  return true;
		}
		return false;
	}
}
#endif
