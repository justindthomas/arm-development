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
unzip ChibiOS_2.4.1.zip
cd ~/ChibiOS_2.4.1/demos
cp -r ARMCM3-STM32L152-DISCOVERY ~/
cd ~/ARMCM3-STM32L152-DISCOVERY
```

Alter main.c as desired. Then `make`. Start debugger.

```
cd ~/ARMCM3-STM32L152-DISCOVERY
openocd -f /usr/share/openocd/scripts/board/stm32ldiscovery.cfg
```

From another terminal, upload the binary to the board.

```
telnet localhost 4444
poll
reset halt
flash probe 0
flash write_image erase build/ch.bin 0x08000000
reset
exit
```

Relevant URLS:

* [gcc and OpenOCD](http://sourcegate.wordpress.com/2012/09/18/getting-started-with-an-stm32l-discovery-with-linux-and-gcc/)
* [Getting started with ChibiOS](http://recursive-labs.com/rtos-guide/hello-world-chibios/)
* [Programming the STM32](http://startingelectronics.com/tutorials/STM32-microcontrollers/programming-STM32-flash-in-Linux/)
