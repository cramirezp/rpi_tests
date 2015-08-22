#ifndef _RPI_GPIO_SENSOR_H
#define _RPI_GPIO_SENSOR_H

class Rpi_GPIO_sensor{
public:
	Rpi_GPIO_sensor();
	virtual ~Rpi_GPIO_sensor();

	// Actualizador de estado
	virtual void tick();
};

#endif // _RPI_GPIO_SENSOR_H