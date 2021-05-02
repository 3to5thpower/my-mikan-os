SHELL=/bin/zsh
CXX=clang++
CXXFLAGS=-O2 -Wall -Wextra -g -std=c++17 -I${BASEDIR}/include/c++/v1 -I${BASEDIR}/include -I${BASEDIR}/include/freetype2 -I${EDK2DIR}/MdePkg/Include -I${EDK2DIR}/MdePkg/Include/X64 -nostdlibinc -D__ELF__ -D_LDBL_EQ_DBL -D_GNU_SOURCE -D_POSIX_TIMERS -DEFIAPI='__attribute__((ms_abi))'

BASEDIR=${HOME}/osbook/devenv/x86_64-elf
EDK2DIR=${HOME}/edk2
LDFLAGS=-L${BASEDIR}/lib

ARCH_OPT=--target=x86_64-elf -ffreestanding -mno-red-zone -fno-exceptions -fno-rtti
ELF=kernel.elf
BOOTLOADER_PATH=${EDK2DIR}/Build/MikanLoaderX64/DEBUG_CLANG38/X64/Loader.efi
QEMU_RUNNER_PATH=${HOME}/osbook/devenv/run_qemu.sh

.PHONY: clean

run: main.o $(ELF)
	${QEMU_RUNNER_PATH} ${BOOTLOADER_PATH} $(ELF)

bootloader:
	cd ${EDK2DIR}; source ${EDK2DIR}/edksetup.sh;build

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(ARCH_OPT) -c main.cpp -o main.o

$(ELF): main.o
	ld.lld --entry KernelMain -z norelro --image-base 0x100000 --static -o $(ELF) main.o

install:
	sudo mount -t drvfs E: /mnt/usbmem
	sudo cp ${ELF} /mnt/usbmem/kernel.elf
	sudo cp ${BOOTLOADER_PATH} /mnt/usbmem/EFI/BOOT/BOOTX64.EFI
	sudo umount /mnt/usbmem

clean:
	rm -rf *.o *.elf *.img mnt

