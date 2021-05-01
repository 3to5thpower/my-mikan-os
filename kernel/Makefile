SHELL=/bin/zsh
CXX=clang++
CXXFLAGS=-O2 -Wall -Wextra -g -std=c++17

ARCH_OPT=--target=x86_64-elf -ffreestanding -mno-red-zone -fno-exceptions -fno-rtti
ELF=kernel.elf
BOOTLOADER_PATH=${HOME}/edk2/Build/MikanLoaderX64/DEBUG_CLANG38/X64/Loader.efi
QEMU_RUNNER_PATH=${HOME}/osbook/devenv/run_qemu.sh

setup:
	source ${HOME}/edk2/edksetup.sh

bootloader: setup
	build

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(ARCH_OPT) -c main.cpp -o main.o

$(ELF): main.o
	ld.lld --entry KernelMain -z norelro --image-base 0x100000 --static -o $(ELF) main.o

run: main.o $(ELF)
	${QEMU_RUNNER_PATH} ${BOOTLOADER_PATH} $(ELF)

install:
	sudo mount -t drvfs E: /mnt/usbmem
	sudo cp ${ELF} /mnt/usbmem/kernel.elf
	sudo cp ${BOOTLOADER_PATH} /mnt/usbmem/EFI/BOOT/BOOTX64.EFI
	sudo umount /mnt/usbmem

