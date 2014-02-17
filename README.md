Installing OpenOCD (On-Chip Debugger)
-------------------------------------

```
# Mac OS X
brew install openocd
```

```
# Ubuntu
sudo aptitude install checkinstall
tar -zxvf openocd-x.y.z.tar.gz
cd openocd-x.y.z.tar.gz
./bootstrap
./configure --prefix=/usr --enable-stlink --enable-jlink --enable-amtjtagaccel --enable-ft2232_libftdi
make
sudo checkinstall make install
```

Installing cross-compiler
-------------------------

```
# Ubuntu
sudo aptitude install gcc-arm-none-eabi
```

```
# Mac OS X
brew install mpfr gmp libmpc libelf texinfo
git clone https://github.com/jsnyder/arm-eabi-toolchain
cd arm-eabi-toolchain
make install-cross

echo "export PATH=~/arm-cs-tools/bin:$PATH" >>~/.zshrc
```

Installing ChibiOS
---------------

```
git clone https://github.com/ChibiOS/ChibiOS-RT
cd ChibiOS-RT/demos
cp -r ARMCM3-STM32L152-DISCOVERY ~/arm-devel
cd ~/arm-devel
rm -rf iar keil
```

Change `Makefile` to point CHIBIOS to the correct path. Alter main.c as desired. Then `make`.

Using OpenOCD to upload binary
------------------------------

```
cd ~/arm-devel
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

There's some neat stuff in one of the links below about using gdb to debug the process running on the chip. Something to keep in mind for the future.

Using st-flash instead of OpenOCD
--------------------------------- 

*Build st-flash*

```
# Ubuntu
sudo aptitude install build-essential autoconf

# Mac OS X
brew install libusb

git clone https://github.com/texane/stlink
cd stlink
./autogen.sh
./configure
make
cd flash
make

sudo cp ./st-flash ~/bin
```

*Uploading using st-flash*

```
st-flash write build/ch.bin 0x08000000
```

Relevant URLs
-------------

* [gcc and OpenOCD](http://sourcegate.wordpress.com/2012/09/18/getting-started-with-an-stm32l-discovery-with-linux-and-gcc/)
* [Getting started with ChibiOS](http://recursive-labs.com/rtos-guide/hello-world-chibios/)
* [Programming the STM32](http://startingelectronics.com/tutorials/STM32-microcontrollers/programming-STM32-flash-in-Linux/)
* [Doing it all on Mac OS X](http://blog.y3xz.com/blog/2012/10/07/setting-up-an-arm-eabi-toolchain-on-mac-os-x)
