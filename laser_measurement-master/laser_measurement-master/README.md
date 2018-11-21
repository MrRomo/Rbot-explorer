# VL53L0X

[![Laser Movement recognition with PIC](https://img.youtube.com/vi/rw44PFi9w5A/0.jpg)](https://www.youtube.com/watch?v=rw44PFi9w5A)

Sample project using two laser VL53L0X sensors and a PIC microcontroller to read distances and drive leds ([tutorial](http://www.paolocarlobernardi.it/index.php/en/embedded-en)).
The project uses a couple of sensors to create an optical game with leds when you move your hand in proximity of the two sensors.
A library (VL53L0X.c) has been written following ST API and Arduino library. It is not a real library, it is more a portion of code encapsulated into one file, so it needs some external prerequisites: the PIC has been configured to work with timer0 IRQ and I2C fast mode.
The library is a real first draft not intended for professional use but for hobbyists that like to play with the sensor.

### Single shot or continuous
VL53L0X can work in continuous reading. In this mode it is the sensor that reads at the maximum speed leaving the user to read the distance register.

With "single shot" mode enabled it is possible to choose the high accuracy mode or the high speed mode, not both. Also "long range" can be selected.

### How to use
Check into VL53L0X.h file the number of sensors used and the I2C addresses.
In case of only one sensor some extra code inside VL53L0X_InitDevices() should be commented. Also the enable pin is not necessary.
In case of one sensor in continuous reading the main code is reduced to:

```
VL53L0X_InitDevices();
VL53L0X_ContinuousReading(&vl53l0xDev[LASER0], 0);

while(1) {
    uint16_t measure = VL53L0X_ReadRange(&vl53l0xDev[LASER0]);
}
```

### Prerequisites

You need Microchip MPLAB-X IDE V4.0 installed as well as MPLAB XC8 compiler.
For Linux-64 machines some libraries are needed; Microchip has a tutorial for this: [mplabx-lin64](http://microchipdeveloper.com/install:mplabx-lin64)

### Installing

To install the project on your machine the best way is to clone the repository:

```
cd MPLABXProjects
git clone https://github.com/PaoloCarlo/laser_measurement.git
```

Now you can open the project into MPLAB-X IDE

## Authors

* [PaoloCarlo](https://github.com/PaoloCarlo)


## License

This project is licensed under the Apache 2.0 License - see the [LICENSE.md](LICENSE.md) file for details

