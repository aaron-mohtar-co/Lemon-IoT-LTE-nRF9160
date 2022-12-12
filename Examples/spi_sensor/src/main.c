/*
 * nRF9160 ADXL345 3-axis Accelerometer Example
 *
 * This example uses Zephyr Sensor Framework and DeviceTree overlays (at a 
 * project level) to obtain X, Y & Z acceleration from an ADXL345 sensor.
 * 
 * API Reference:
 * https://docs.zephyrproject.org/latest/hardware/peripherals/sensor.html
 * https://docs.zephyrproject.org/latest/build/dts/api/bindings/sensor/adi%2Cadxl345-spi.html#dtbinding-adi-adxl345-spi
 * 
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <stdio.h>

void main(void)
{
 	// Get a device structure from a devicetree node with compatible
 	// "adi,adxl345". 
	const struct device *dev = DEVICE_DT_GET_ANY(adi_adxl345);

	if (dev == NULL) {
		printk("\nError: No devicetree node found for Analog Devices ADXL345.\n");
		return;
	}

	if (!device_is_ready(dev)) {
		printf("Device %s is not ready\n", dev->name);
		return;
	}

	printk("Found device %s. Reading sensor data:\n", dev->name);

	while (true) {
		struct sensor_value accel_x, accel_y, accel_z;

		sensor_sample_fetch(dev);
		sensor_channel_get(dev, SENSOR_CHAN_ACCEL_X, &accel_x);
		sensor_channel_get(dev, SENSOR_CHAN_ACCEL_Y, &accel_y);
		sensor_channel_get(dev, SENSOR_CHAN_ACCEL_Z, &accel_z);

		printk("X = %.2f m/s2, Y = %.2f m/s2, Z = %.2f m/s2\n", 
				sensor_value_to_double(&accel_x), 
				sensor_value_to_double(&accel_y), 
				sensor_value_to_double(&accel_z));

		k_sleep(K_MSEC(1000));
	}
}
