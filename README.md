# Lemon IoT LTE Board
This repository is the official location for support files for the [Lemon IoT LTE nRF9160 Board](https://lemon-iot.com/index.php/product/lemon-iot-lte-cat-m1-nb-iot-nrf9160-board/). 

The board is based on a [nRF9160 low power SiP with integrated LTE-M/NB-IOT modem and GNSS](https://www.nordicsemi.com/products/nrf9160) from Nordic Semiconductor.

<p align="center"><img src="https://raw.githubusercontent.com/aaron-mohtar-co/Lemon-IoT-LTE-nrf9160/main/Zephyr%20board%20files/arm/lemon_iot_lte_nrf9160/doc/img/lemon_iot_lte_nrf9160_render.jpg" width=50% height=50%></p>

## Board Files

Before you can target the Lemon IoT LTE board in Zephyr (nRF Connect SDK), board files will need to be downloaded from the [Zephyr board files](https://github.com/aaron-mohtar-co/Lemon-IoT-LTE-nrf9160/tree/main/Zephyr%20board%20files) folder and placed in the \Nordic\<SDK version>\zephyr\boards\arm folder.

Two targets exist 
* Lemon IoT NRF9160 and 
* Lemon IoT NRF9160 non-secure.

The board files also contain the device tree. The following GPIO has been allocated on the following pins:

<p align="center"><img src="https://raw.githubusercontent.com/aaron-mohtar-co/Lemon-IoT-LTE-nrf9160/main/Zephyr%20board%20files/arm/lemon_iot_lte_nrf9160/doc/img/lemon_iot_lte_nrf9160_diagram.jpg" width=50% height=50%></p>

Other I/O, for example, I2C, SPI & extra UART communication buses can be added by using DeviceTree overlays in your application project. This provides the end user with the most flexibility in allocating I/O. For an example on how to achieve this, please see the [I2C Sensor Example](https://github.com/aaron-mohtar-co/Lemon-IoT-LTE-nrf9160/tree/main/Examples/i2c_sensor) or [SPI Sensor Example](https://github.com/aaron-mohtar-co/Lemon-IoT-LTE-nrf9160/tree/main/Examples/spi_sensor)

The nRF9160 has four instantiated serial communications peripherals. Each can be configured as either I2C (Also known as TWI or Two Wire Interface), SPI or UART. The Lemon LTE module already has allocated the first serial peripheral to UART (&uart0). This requires additional serial peripherals to be allocated with unique instances, for example &i2c1. Using &i2c0 will conflict with the already allocated &uart0.     

## Serial Bootloader

If you don’t have access to an ARM programmer (Segger J-Link, Nordic Development Kit etc), then the most cost-effective method of programming the Lemon IoT LTE module is via the pre-installed serial bootloader. Information on the serial bootloader can be found in the [bootloader/](https://github.com/aaron-mohtar-co/Lemon-IoT-LTE-nrf9160/tree/main/Bootloader) directory.

## Examples

Both the [zephyr OS](https://github.com/zephyrproject-rtos/zephyr/tree/main/samples) and [Nordic nRF SDK](https://github.com/nrfconnect/sdk-nrf/tree/main/samples/nrf9160) contain a wide variety of examples to base your next product on. 

In addition to these examples, we have some specific examples for the Lemon IoT LTE module in the [Examples](https://github.com/aaron-mohtar-co/Lemon-IoT-LTE-nrf9160/tree/main/Examples) folder.


