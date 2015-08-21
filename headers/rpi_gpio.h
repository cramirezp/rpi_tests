#include <map>
#include <vector>

#include <stdint.h>
#include <bcm2835.h>


class Rpi_GPIO{
private:
	// Pin access
	std::map<int, uint8_t> pin;
	// Pin state <- TODO struct with, none/IN/OUT/SPI/CLK/etc.
	std::map<uint8_t, bool> pin_is_used;

protected:
public:
	
	Rpi_GPIO();
	~Rpi_GPIO();

	bool init();
	bool close();

	bool pin_exists(uint8_t);

	bool add_sensor(uint8_t pin_number);
	template<uint8_t N>
	bool add_sensor(std::array<uint8_t, N> pin_number);
};