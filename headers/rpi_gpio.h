#ifndef _RPI_GPIO_H
#define _RPI_GPIO_H

#include <map>
#include <vector>
#include <string>

#include <stdint.h>
#include <bcm2835.h>

#include "rpi_gpio_sensor.h"


class Rpi_GPIO{
private:
	// Pin access
	std::map<int, uint8_t> pin;
	// Pin state <- TODO struct with, none/IN/OUT/SPI/CLK/etc.
	std::map<uint8_t, bool> pin_is_used;
	// Sensor's tag
	std::map<std::string, Rpi_GPIO_sensor*> sensor_list;
	// Sensor list
	std::map<std::string, std::vector<uint8_t>> sensor_pins_list;


	bool init();
	bool close();

protected:
public:
	
	Rpi_GPIO();
	~Rpi_GPIO();

	bool pin_exists(int pin_number);
	bool sensor_exists(std::string tag);

	bool add_sensor(std::string tag, Rpi_GPIO_sensor *sensor, uint8_t pin_number);
	bool add_sensor(std::string tag, Rpi_GPIO_sensor *sensor, std::vector<uint8_t> pin_numbers);

	void tick();
};

#endif // _RPI_GPIO_H