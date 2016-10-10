#makefile to build .bin
CC = /home/jens/Documents/Toolchains/gcc-arm-none-eabi-4_9-2015q3/bin/arm-none-eabi-gcc
CPP = /home/jens/Documents/Toolchains/gcc-arm-none-eabi-4_9-2015q3/bin/arm-none-eabi-g++
CFLAGS = -mcpu=cortex-m3 -mthumb -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -funsigned-char -Wall -std=gnu++11 -fabi-version=0  -ffixed-r11 -ffixed-r12 --specs=nosys.specs
SOURCE = ./algorithms/bitCount.cpp
INCLUDE_STARTUP = "/home/jens/Documents/Devices/Bare Metal LPC17xx/Startup files"
INCLUDE_CMSIS = "/home/jens/Documents/Devices/Bare Metal LPC17xx/CMSIS"

bitCount.disasm: bitCount.bin
	@/home/jens/Documents/Toolchains/gcc-arm-none-eabi-4_9-2015q3/bin/arm-none-eabi-objdump -d -f -M reg-names-std --demangle bitCount.elf >bitCount.disasm

bitCount.bin: bitCount.elf
	@/home/jens/Documents/Toolchains/gcc-arm-none-eabi-4_9-2015q3/bin/arm-none-eabi-objcopy -O binary bitCount.elf  bitCount.bin

bitCount.elf: bitCount.o main.o
	@$(CPP) -T"/home/jens/Documents/Devices/Bare Metal LPC17xx/LPC1768.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"bitCount.map" $(CFLAGS) ./startup/startup_LPC17xx.o ./startup/system_LPC17xx.o  ./algorithms/bitCount.o  ./main.o -o bitCount.elf 

bitCount.o: $(SOURCE)
	@$(CPP) $(CFLAGS) -c -I$(INCLUDE_STARTUP) -I$(INCLUDE_CMSIS) $(SOURCE) -o algorithms/bitCount.o

main.o: ./main.cpp
	@$(CPP) $(CFLAGS) -c -I$(INCLUDE_STARTUP) -I$(INCLUDE_CMSIS) -o main.o ./main.cpp

clean:
	rm -rf  ./algorithms/*.o  ./main.o bitCount.*
