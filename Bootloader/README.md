# Bootloader & Utility

If you don’t have access to an ARM programmer (Segger J-Link, Nordic Development Kit etc), then the most cost-effective method of programming the Lemon IoT LTE module is via the pre-installed serial bootloader. 

Firmware image files can be uploaded over the UART port using a commonly available USB to UART adapter.

The bootloader uses libraries from [MCU Boot](https://www.mcuboot.com/). MCU Boot is an open-source project with the goal to define a common interface for a secure bootloader for 32-bit Microcontrollers. To date, it is used via the [Zephyr](https://www.zephyrproject.org/) and [Mynewt](https://mynewt.apache.org/) Real Time Operating Systems. 

Both operating systems have their own managers to upload firmware – [MCUmgr](https://github.com/zephyrproject-rtos/mcumgr) for Zephyr and [Newtmgr](https://github.com/apache/mynewt-newtmgr) for Mynewt. As MCUboot provides a common interface, either can be used. 

Zephyr applications that are uploaded using the bootloader must be configured with CONFIG_BOOTLOADER_MCUBOOT=y. Setting this option reserves space for the bootloader and allows the application to be chain-loaded. This can do done by editing the prj.conf file of via Kconfig (Boot Options -> MCUboot bootloader support). 

The MCUBOOT_SIGNATURE_KEY_FILE is set automatically via nRF Connect and uses the default key. This bootloader is intended for development and educational purposes only. Device security should be considered for production.

## Download and Setup

Precompiled binaries of Newtmgr can be downloaded from https://dlcdn.apache.org/mynewt/. The Windows versions are compressed using .tgz.

Alternatively, you can download the Windows version 1.10.0 from [above](https://github.com/aaron-mohtar-co/Lemon-IoT-LTE-nrf9160/raw/main/Bootloader/apache-mynewt-newtmgr-bin-windows-1.10.0.zip) in a more user friendly .zip form.

Extract into a suitable directory. 

The first time you use newtmgr, you will need to create a connection profile. In the example below, the profile is called serial, but it can be any unique name to identify the connection. Change COM6 to your enumerated COM port.

```
newtmgr conn add serial type=serial connstring="dev=COM6,baud=115200"
```

## Upload new firmware via serial bootloader

To upload new firmware to your Lemon IoT LTE module:

1.	Hold down the PB1 while pressing and releasing the reset button.
2.	D1 should illuminate red to indicate the device is in boot loader mode.
3.	Execute the following where zephyr\app_update.bin points to the firmware you want to upload

```
newtmgr -c serial image upload zephyr\app_update.bin
```

## Reprogramming the bootloader

All Lemon IoT LTE modules come pre-loaded with the MCUboot bootloader from the factory. 

The bootloader is stored in write protected Flash memory. However, if the bootloader is overridden using a third party programmer, it can be restored by programming your Lemon IoT LTE module with the bootloader.hex via nRF Connect and a third party programmer such as a J-Link. 




