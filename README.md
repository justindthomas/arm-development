OpenOCD (On-Chip Debugger)

```
tar -zxvf openocd-x.y.z.tar.gz
cd openocd-x.y.z.tar.gz
./bootstrap
./configure --prefix=/usr --enable-stlink --enable-jlink --enable-amtjtagaccel --enable-ft2232_libftdi
make
sudo checkinstall make install
```

Cross-Compiler

```
sudo aptitude install gcc-arm-none-eabi
```

Install ChibiOS

```
git clone https://github.com/ChibiOS/ChibiOS-RT
cd ChibiOS-RT/demos
cp -r ARMCM3-STM32L152-DISCOVERY ~/
cd ~/ARMCM3-STM32L152-DISCOVERY
```

Change `Makefile` to point CHIBIOS to the correct path. Alter main.c as desired. Then `make`. Start debugger.

```
cd ~/ARMCM3-STM32L152-DISCOVERY
openocd -f /usr/share/openocd/scripts/board/stm32ldiscovery.cfg
```

From another terminal, upload the binary to the board.

```
telnet localhost 4444

# show current status
poll

# halt processor
reset halt

# show flash details
flash probe 0

# write binary to flash
flash write_image erase build/ch.bin 0x08000000

# reset unit and exit
reset
exit
```

Using st-flash instead of OpenOCD.

Build st-flash.

```
sudo aptitude install build-essential autoconf
git clone https://github.com/texane/stlink stlink.git
cd stlink.git
./autogen.sh
./configure
make
cd flash
make
sudo cp ./st-flash /usr/bin
```

Uploading using st-flash.

```
st-flash write build/ch.bin 0x08000000
```

Relevant URLs:

* [gcc and OpenOCD](http://sourcegate.wordpress.com/2012/09/18/getting-started-with-an-stm32l-discovery-with-linux-and-gcc/)
* [Getting started with ChibiOS](http://recursive-labs.com/rtos-guide/hello-world-chibios/)
* [Programming the STM32](http://startingelectronics.com/tutorials/STM32-microcontrollers/programming-STM32-flash-in-Linux/)
* [Doing it all on Mac OS X](http://blog.y3xz.com/blog/2012/10/07/setting-up-an-arm-eabi-toolchain-on-mac-os-x)
