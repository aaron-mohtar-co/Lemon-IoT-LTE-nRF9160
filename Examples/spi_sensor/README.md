# SPI Sensor Example (Amalog Devices ADXL345)

This example demonstrates how to use Device Tree overlays in your project to specify custom I/O allocation. It obtains the acceleration from a SPI Analog Devices [ADXL345](https://www.analog.com/en/products/adxl345.html) sensor. 

```
*** Booting Zephyr OS build v3.2.99-ncs1 ***
Found device adxl345@0. Reading sensor data:
X = -1.84 m/s2, Y = 8.58 m/s2, Z = 0.61 m/s2
X = 0.00 m/s2, Y = 8.58 m/s2, Z = 0.61 m/s2
X = 0.00 m/s2, Y = 9.19 m/s2, Z = 0.61 m/s2
X = 0.00 m/s2, Y = 9.19 m/s2, Z = 0.61 m/s2
X = 0.00 m/s2, Y = 9.19 m/s2, Z = 0.61 m/s2
```

The nRF9160 has four instantiated serial communications peripherals. Each can be configured as either I2C (also known as TWI or Two Wire Interface), SPI or UART. The Lemon LTE module has allocated the first serial peripheral to UART (&uart0). 

Rather than constraining the developer to using pre-allocated peripherals, buses and GPIO, this allows flexibility in allocating resources suitable for your application. One application may require four UART ports, while a different one may require three I2C ports.

## DeviceTree overlays

On the Zephyr RTOS, I/O and peripherals are allocated in the Device Tree. The board files (located in zephyr/boards/arm/lemon_lte_nrf9160) generally hold the Device Tree specific to I/O for a given board. This makes sense as the printed circuit board physically connects the pins of the nRF9160 to the peripherals located on the board, for example temperature and humidity sensors, accelerometers etc. 

However, this Device Tree can be modified or further defined by using a Device Tree overlay at the project level. Where you have a flexible module like the Lemon IoT LTE, this makes the most sense.

The Device Tree overlay sits in your project within the [board](https://github.com/aaron-mohtar-co/Lemon-IoT-LTE-nrf9160/tree/main/Examples/spi_sensor/boards) folder. The Device Tree file should be given the same name as your board and an extension of 'overlay' e.g. nrf9160_lemon_iot_ns.overlay.

The overlay has the same format than the Device Tree. For more information, please see the Zephyr [DeviceTree](https://docs.zephyrproject.org/latest/guides/dts/index.html) documentation.

The overlay file for this project looks like:

```
&pinctrl {
	spi2_default: spi2_default {
		group1 {
			psels = <NRF_PSEL(SPIM_SCK, 0, 13)>,
				<NRF_PSEL(SPIM_MISO, 0, 12)>,
				<NRF_PSEL(SPIM_MOSI, 0, 11)>;
		};
	};

	spi2_sleep: spi2_sleep {
		group1 {
			psels = <NRF_PSEL(SPIM_SCK, 0, 13)>,
				<NRF_PSEL(SPIM_MISO, 0, 12)>,
				<NRF_PSEL(SPIM_MOSI, 0, 11)>;
			low-power-enable;
		};
	};
};

&spi2 {
	compatible = "nordic,nrf-spim";
	status = "okay";
	cs-gpios = <&gpio0 10 GPIO_ACTIVE_LOW>;
	pinctrl-0 = <&spi2_default>;
	pinctrl-1 = <&spi2_sleep>;
	pinctrl-names = "default", "sleep";
	adxl345: adxl345@0 {
		compatible = "adi,adxl345";
		reg = <0>; 
		spi-max-frequency = <1000000>;
	};
};

```

The pin control (&pinctrl) node sets up the GPIO pin numbering including connecting any internal pull-up/down resistors. Documentation on Nordic specific pinctrl properties can be found [here](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/ug_pinctrl.html).

The SPI2 (&spi2) node sets up the SPI controller as a 'nrf-spim' or Nordic SPI Master. 

## Zephyr Sensor Subsystem

The Zephyr RTOS includes a [sensor subsystem](https://docs.zephyrproject.org/latest/hardware/peripherals/sensor.html) with built-in support for common sensors such as the [Sensirion SHTC3](https://sensirion.com/products/catalog/SHTC3/).  

Configuration of the sensor (chip select, clock-frequency etc) is set up in the Device Tree as a subnode of the allocated SPI bus - see below. The application can then use a common API, sensor_sample_fetch(), sensor_channel_get() to read the sensor.

```
	adxl345: adxl345@0 {
		compatible = "adi,adxl345";
		reg = <0>; 
		spi-max-frequency = <1000000>;
	};
```

The reg = <0> indicates to use the first allocated chip select in the cs-gpios property. In this case, it is GPIO10.

Details of the node properties can be found at [Analog ADXL345 Node Properties](https://docs.zephyrproject.org/latest/build/dts/api/bindings/sensor/adi%2Cadxl345-spi.html#dtbinding-adi-adxl345-spi).
