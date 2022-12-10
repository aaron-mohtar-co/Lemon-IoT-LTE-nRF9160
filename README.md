# Lemon IoT LTE module
This repository is the primary location for support files for the Lemon IoT LTE module. The module is based on a [nRF9160 low power SiP with integrated LTE-M/NB-IOT modem and GNSS](https://www.nordicsemi.com/products/nrf9160)

## Board Files

Before you can target the Lemon IoT LTE module in Zephyr (nRF Connect SDK), board files will need to be downloaded from the [Zephyr board files](https://github.com/aaron-mohtar-co/Lemon-IoT-LTE-nrf9160/tree/main/Zephyr%20board%20files) folder and placed in the \Nordic\<SDK version>\zephyr\boards\arm folder.

Two targets exist 
* Lemon IoT NRF9160 and 
* Lemon IoT NRF9160 non secure.

## Serial Bootloader

If you don’t have access to an ARM programmer (Segger J-Link, Nordic Development Kit etc), then the most cost-effective method of programming the Lemon IoT LTE module is via the pre-installed serial bootloader. Information on ther serial bootloader can be found in the [bootloader/](https://github.com/aaron-mohtar-co/Lemon-IoT-LTE-nrf9160/tree/main/Bootloader) directory.

## Examples

Both the [zephyr OS](https://github.com/zephyrproject-rtos/zephyr/tree/main/samples) and [Nordic nRF SDK](https://github.com/nrfconnect/sdk-nrf/tree/main/samples/nrf9160) contain a wide variety of examples to base your next product on. 

In addition to these examples, we have some specific examples for the Lemon IoT LTE module in the [Examples](https://github.com/aaron-mohtar-co/Lemon-IoT-LTE-nrf9160/tree/main/Examples) folder.


