# I2C Sensor Example (Sensirion SHTC3)

This example demonstrates how to use Device Tree overlays in your project to specify custom I/O allocation. It obtains the temperature & humidity from a I2C Sensirion [SHTC3](https://sensirion.com/products/catalog/SHTC3/) sensor connected to pins 30 (SDA) and pins 31 (SCL). 

The nRF9160 has four instantiated serial communications peripherals. Each can be configured as either I2C (also known as TWI or Two Wire Interface), SPI or UART. The Lemon LTE module already has allocated the first serial peripheral to UART (&uart0). 

Rather than constraining the developer to using pre-allocated buses and I/O, this allows flexibility in allocating resources suitable for your application. One application may require four UART ports, another one three I2C ports.

## DeviceTree overlays

On the Zephyr RTOS, I/O and peripherals are allocated in the Device Tree. The board files (located in zephyr/boards/arm/lemon_lte_nrf9160) generally hold the Device Tree specific to I/O for a given board. This makes sense as the PCB board connects the pins of the nRF9160 to the peripherals on the board such as I2C temperature and humidity sensors, accelerometers etc.

However, this I/O can be also modified or further defined by using a Device Tree overlay at the project level. Where you have a flexible module like the Lemon IoT LTE, this makes the most sense.

The Device Tree overlay sits in your project within the board folder. The Device Tree file should be given the same name as your board and an extension of overlay e.g. nrf9160_lemon_iot_ns.overlay.

The overlay has the same format than the Device Tree. For more information, please see the Zephyr [DeviceTree](https://docs.zephyrproject.org/latest/guides/dts/index.html) documentation.

The overlay file for this project looks like:

```
// For more help, browse the DeviceTree documentation at 
//  https://docs.zephyrproject.org/latest/guides/dts/index.html

// You can also visit the nRF DeviceTree extension documentation at 
//  https://nrfconnect.github.io/vscode-nrf-connect/devicetree/nrfdevicetree.html

&pinctrl {

	i2c2_default: i2c2_default {
		group1 {
			psels = <NRF_PSEL(TWIM_SDA, 0, 30)>,
				<NRF_PSEL(TWIM_SCL, 0, 31)>;
				bias-pull-up;
		};
	};

	i2c2_sleep: i2c2_sleep {
		group1 {
			psels = <NRF_PSEL(TWIM_SDA, 0, 30)>,
				<NRF_PSEL(TWIM_SCL, 0, 31)>;
			low-power-enable;
		};
	};
};

&i2c2 {
	compatible = "nordic,nrf-twim";
	status = "okay";
	pinctrl-0 = <&i2c2_default>;
	pinctrl-1 = <&i2c2_sleep>;
	pinctrl-names = "default", "sleep";
	clock-frequency = <100000>;
	shtcx@70 {
		compatible = "sensirion,shtcx";
		label = "SHTC3";
		reg = <0x70>;
		chip = "shtc3";
		measure-mode = "normal";
	};
};
```

The pin control (&pinctrl) node sets up the GPIO pin numbers including internal pull-up/down resistors. In this example, SDA is allocated pin 30 and SCL pin 31. 

The I2C2 (&i2c2) node sets up the I2C2 controller as a TWIM (Two wire interface - in Master mode) with a clock frequency of 100kHz. 

## Sensors

The Zephyr RTOS includes a [sensor subsystem]((https://docs.zephyrproject.org/latest/hardware/peripherals/sensor.html) with built-in support for common sensors such as the [Sensirion SHTC3](https://sensirion.com/products/catalog/SHTC3/).  

Configuration of the sensor (type, I2C address, measurement mode) is set up in the Device Tree in a subnode of the allocated I2C bus as below. The application can then use a common sensor_sample_fetch(), sensor_channel_get() api to read the sensor.

```
	shtcx@70 {
		compatible = "sensirion,shtcx";
		label = "SHTC3";
		reg = <0x70>;
		chip = "shtc3";
		measure-mode = "normal";
	};
```

Details of the node properties can be found at [Sensirion SHTCx Node Properties](https://docs.zephyrproject.org/3.0.0/reference/devicetree/bindings/sensor/sensirion%2Cshtcx.html)





