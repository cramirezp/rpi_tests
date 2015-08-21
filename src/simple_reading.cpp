#include <iostream>
#include <cstdint>
#include <bcm2835.h>


int main(int argc, char *argv[]){

	if(!bcm2835_init())
		return 1;


	bcm2835_gpio_fsel(RPI_GPIO_P1_11, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_set_pud(RPI_GPIO_P1_11, BCM2835_GPIO_PUD_DOWN);

	for(;;){
		bcm2835_delay(1000);		// 1000[ms]
		uint8_t pin11 = bcm2835_gpio_lev(RPI_GPIO_P1_11);

		std::cout << "Medida pin 11: " << (int)pin11 << std::endl;
	}

	if(!bcm2835_close())
		return 2;

	return 0;
}