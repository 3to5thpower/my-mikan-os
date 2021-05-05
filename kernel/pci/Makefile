OBJS=pci.o asmfunc.o

.PHONY: all target clean
all: $(OBJS)
target: $(OBJS)

pci.o: pci.cpp Makefile
	$(CXX) $(CXXFLAGS) $(ARCH_OPT) -I../ -c $< -o $@

asmfunc.o: asmfunc.asm Makefile
	nasm -f elf64 -o $@ $<

clean:
	rm -rf *.o