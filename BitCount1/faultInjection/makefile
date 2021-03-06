#makefile to build .bin
CC = arm-none-eabi-gcc
CPP = arm-none-eabi-g++
CFLAGS = -mcpu=cortex-m3 -mthumb -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -funsigned-char -Wall -std=gnu++11 -fabi-version=0 -ffixed-r11 -ffixed-r12
SOURCE = ../algorithms/bitCount.cpp
INCLUDE_STARTUP = "/mnt/c/Users/Jens/Box Sync/Doctoraat/CaseStudies/Devices/Bare Metal LPC17xx/Startup files"
INCLUDE_CMSIS = "/mnt/c/Users/Jens/Box Sync/Doctoraat/CaseStudies/Devices/Bare Metal LPC17xx/CMSIS"

PLUGIN_NAME = myPlugin64
PLUGIN_TO_USE = -fplugin=/mnt/c/Users/Jens/Documents/GCC_Plugin/$(PLUGIN_NAME).so
PLUGIN_ARG_1 = -fplugin-arg-$(PLUGIN_NAME)-function=bit_count
PLUGIN_ARG_2 = -fplugin-arg-$(PLUGIN_NAME)-maxReg=12
PLUGIN_ARG_3 = -fplugin-arg-$(PLUGIN_NAME)-sigMon=RASM_Opt

#WP
bitCount.disasm: bitCount.bin
	@arm-none-eabi-objdump -d -f -M reg-names-std --demangle bitCount.elf >bitCount.disasm

bitCount.bin: bitCount.elf
	@arm-none-eabi-objcopy -O binary bitCount.elf  bitCount.bin

bitCount.elf: startup_LPC17xx.o system_LPC17xx.o bitCount.o main.o
	@$(CPP) -T"/mnt/c/Users/Jens/Box Sync/Doctoraat/CaseStudies/Devices/Bare Metal LPC17xx/LPC1768.ld" -nostartfiles --specs=nosys.specs -Xlinker --gc-sections -Wl,-Map,"bitCount.map" $(CFLAGS) ./startup/startup_LPC17xx.o ./startup/system_LPC17xx.o  ./algorithms/bitCount.o  ./main.o -o bitCount.elf 

bitCount.o: $(SOURCE)
	$(CPP) $(CFLAGS) -c -I$(INCLUDE_STARTUP) -I$(INCLUDE_CMSIS) $(PLUGIN_TO_USE) $(PLUGIN_ARG_1) $(PLUGIN_ARG_2) $(PLUGIN_ARG_3) $(SOURCE) -o algorithms/bitCount.o

#No change

startup_LPC17xx.o: ../startup/startup_LPC17xx.S
	@$(CC) $(CFLAGS) -g -x assembler-with-cpp -c -o startup/startup_LPC17xx.o ../startup/startup_LPC17xx.S

system_LPC17xx.o: ../startup/system_LPC17xx.c
	@$(CC) $(CFLAGS) -c -I$(INCLUDE_STARTUP) -I$(INCLUDE_CMSIS) -o startup/system_LPC17xx.o ../startup/system_LPC17xx.c

main.o: ../main.cpp
	@$(CPP) $(CFLAGS) -c -I$(INCLUDE_STARTUP) -I$(INCLUDE_CMSIS) -o main.o ../main.cpp

#clean
clean:
	rm -rf ./startup/*.o  ./algorithms/*.o  ./main.o bitCount.* *.txt *.xml

#GDB
withPluginGDB: $(SOURCE)
	$(CPP) $(CFLAGS) -ggdb2 -I$(INCLUDE_STARTUP) -I$(INCLUDE_CMSIS) $(PLUGIN_TO_USE) $(PLUGIN_ARG_1) $(PLUGIN_ARG_2) $(PLUGIN_ARG_3) $(SOURCE) -o algorithms/bitcount.S -wrapper gdb,--args
