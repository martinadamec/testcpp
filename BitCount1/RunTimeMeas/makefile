#makefile to build .bin
CC = arm-none-eabi-gcc
CPP = arm-none-eabi-g++
CFLAGS = -mcpu=cortex-m3 -mthumb -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -funsigned-char -Wall -std=gnu++11 -fabi-version=0 -ffixed-r11 -ffixed-r12
SOURCE = ../algorithms/bitCount.cpp
INCLUDE_STARTUP = "/mnt/c/Users/Jens/Box Sync/Doctoraat/CaseStudies/Devices/Bare Metal LPC17xx/Startup files"
INCLUDE_CMSIS = "/mnt/c/Users/Jens/Box Sync/Doctoraat/CaseStudies/Devices/Bare Metal LPC17xx/CMSIS"
PLUGIN_TO_USE = -fplugin=/home/jens/GCC_Plugin/myPlugin.so
PLUGIN_ARG_1 = -fplugin-arg-myPlugin-function=bit_count
PLUGIN_ARG_2 = -fplugin-arg-myPlugin-maxReg=12
PLUGIN_ARG_3 = -fplugin-arg-myPlugin-sigMon=RASM_Opt

#WP
bitCountWP.disasm: bitCountWP.bin
	@/home/jens/Documents/Toolchains/gcc-arm-none-eabi-4_9-2015q3/bin/arm-none-eabi-objdump -d -f -M reg-names-std --demangle bitCountWP.elf >bitCountWP.disasm

bitCountWP.bin: bitCountWP.elf
	@/home/jens/Documents/Toolchains/gcc-arm-none-eabi-4_9-2015q3/bin/arm-none-eabi-objcopy -O binary bitCountWP.elf  bitCountWP.bin

bitCountWP.elf: startup_LPC17xx.o system_LPC17xx.o bitCountWP.o main.o
	@$(CPP) -T"/mnt/c/Users/Jens/Box Sync/Doctoraat/CaseStudies/Devices/Bare Metal LPC17xx/LPC1768.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"bitCount.map" $(CFLAGS) ./startup/startup_LPC17xx.o ./startup/system_LPC17xx.o  ./algorithms/bitCountWP.o  ./main.o -o bitCountWP.elf 

bitCountWP.o: $(SOURCE)
	$(CPP) $(CFLAGS) -c -I$(INCLUDE_STARTUP) -I$(INCLUDE_CMSIS) $(PLUGIN_TO_USE) $(PLUGIN_ARG_1) $(PLUGIN_ARG_2) $(PLUGIN_ARG_3) $(SOURCE) -o algorithms/bitCountWP.o


#NP
bitCountNP.disasm: bitCountNP.bin
	@/home/jens/Documents/Toolchains/gcc-arm-none-eabi-4_9-2015q3/bin/arm-none-eabi-objdump -d -f -M reg-names-std --demangle bitCountNP.elf >bitCountNP.disasm

bitCountNP.bin: bitCountNP.elf
	@/home/jens/Documents/Toolchains/gcc-arm-none-eabi-4_9-2015q3/bin/arm-none-eabi-objcopy -O binary bitCountNP.elf  bitCountNP.bin

bitCountNP.elf: startup_LPC17xx.o system_LPC17xx.o bitCountNP.o main.o
	@$(CPP) -T"/mnt/c/Users/Jens/Box Sync/Doctoraat/CaseStudies/Devices/Bare Metal LPC17xx/LPC1768.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"bitCount.map" $(CFLAGS) ./startup/startup_LPC17xx.o ./startup/system_LPC17xx.o  ./algorithms/bitCountNP.o  ./main.o -o bitCountNP.elf 

bitCountNP.o: $(SOURCE)
	@$(CPP) $(CFLAGS) -c -I$(INCLUDE_STARTUP) -I$(INCLUDE_CMSIS) $(SOURCE) -o algorithms/bitCountNP.o

#No change

startup_LPC17xx.o: ../startup/startup_LPC17xx.S
	@$(CC) $(CFLAGS) -g -x assembler-with-cpp -c -o startup/startup_LPC17xx.o ../startup/startup_LPC17xx.S

system_LPC17xx.o: ../startup/system_LPC17xx.c
	@$(CC) $(CFLAGS) -c -I$(INCLUDE_STARTUP) -I$(INCLUDE_CMSIS) -o startup/system_LPC17xx.o ../startup/system_LPC17xx.c

main.o: ./main.cpp
	@$(CPP) $(CFLAGS) -c -I$(INCLUDE_STARTUP) -I$(INCLUDE_CMSIS) -o main.o ./main.cpp

#clean
clean:
	rm -rf ./startup/*.o  ./algorithms/*.o  ./main.o bitCount*.* *.txt

#GDB
withPluginGDB: $(SOURCE)
	$(CPP) $(CFLAGS) -ggdb2 -I$(INCLUDE_STARTUP) -I$(INCLUDE_CMSIS) $(PLUGIN_TO_USE) $(PLUGIN_ARG_1) $(PLUGIN_ARG_2) $(PLUGIN_ARG_3) $(SOURCE) -o algorithms/bitcount.S -wrapper gdb,--args
