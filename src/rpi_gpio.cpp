#include "rpi_gpio.h"

Rpi_GPIO::Rpi_GPIO(){
	pin = {
		{3, RPI_GPIO_P1_03},
		{5, RPI_GPIO_P1_05},
		{7, RPI_GPIO_P1_07},
		{8, RPI_GPIO_P1_08},
		{10, RPI_GPIO_P1_10},
		{11, RPI_GPIO_P1_11},
		{12, RPI_GPIO_P1_12},
		{13, RPI_GPIO_P1_13},
		{15, RPI_GPIO_P1_15},
		{16, RPI_GPIO_P1_16},
		{18, RPI_GPIO_P1_18},
		{19, RPI_GPIO_P1_19},
		{21, RPI_GPIO_P1_21},
		{22, RPI_GPIO_P1_22},
		{23, RPI_GPIO_P1_23},
		{24, RPI_GPIO_P1_24},
		{26, RPI_GPIO_P1_26}
		};
	pin_is_used = {
		{pin[3], false},
		{pin[5], false},
		{pin[7], false},
		{pin[8], false},
		{pin[10], false},
		{pin[11], false},
		{pin[12], false},
		{pin[13], false},
		{pin[15], false},
		{pin[16], false},
		{pin[18], false},
		{pin[19], false},
		{pin[21], false},
		{pin[22], false},
		{pin[23], false},
		{pin[24], false},
		{pin[26], false}
		};
	sensor_pins_list = {};
	sensor_list  = {};

	Rpi_GPIO::init();
}
Rpi_GPIO::~Rpi_GPIO(){
	Rpi_GPIO::close();
}

bool Rpi_GPIO::init(){
	return bcm2835_init() == 1;
}

bool Rpi_GPIO::close(){
	return bcm2835_close() == 1;
}

bool Rpi_GPIO::pin_exists(int pin_number){
	return pin.find(pin_number) != pin.end();
}

bool Rpi_GPIO::sensor_exists(std::string tag){
	return sensor_list.find(tag) != sensor_list.end();
}

bool Rpi_GPIO::add_sensor(std::string tag, Rpi_GPIO_sensor *sensor, uint8_t pin_number){
	
	if(!pin_exists(pin_number))
		return false;

	if(pin_is_used[pin_number])
		return false;

	if(sensor_exists(tag))
		return false;

	pin_is_used[pin_number] = true;
	sensor_pins_list[tag] = {pin_number};
	sensor_list[tag] = sensor;

	return true;
}

bool Rpi_GPIO::add_sensor(std::string tag, Rpi_GPIO_sensor *sensor, std::vector<uint8_t> pin_numbers){

	if(sensor_exists(tag))
		return false;

	for(auto i = std::begin(pin_numbers); i!=std::end(pin_numbers); ++i){
		if(!pin_exists(*i))
			return false;
		if(pin_is_used[*i])
			return false;
	}

	for(auto i = std::begin(pin_numbers); i!=std::end(pin_numbers); ++i){
		bcm2835_gpio_fsel(pin[*i], BCM2835_GPIO_FSEL_INPT);
		bcm2835_gpio_set_pud(pin[*i], BCM2835_GPIO_PUD_DOWN);

		pin_is_used[*i] = true;
	}
	sensor_pins_list[tag] = pin_numbers;
	sensor_list[tag] = sensor;

	return true;
}

void Rpi_GPIO::tick(){
	for(auto i = sensor_list.begin(); i!=sensor_list.end(); ++i)
		(i->second)->tick();

	bcm2835_delay(1000);		// [ms]
}
