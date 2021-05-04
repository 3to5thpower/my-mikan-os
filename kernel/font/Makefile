OBJS=font.o hankaku.o

.PHONY: all target clean
all: $(OBJS)
target: $(OBJS)

font.o: font.cpp Makefile
	$(CXX) $(CXXFLAGS) $(ARCH_OPT) -c $< -o $@

hankaku.bin: 
	python3 makefont.py -o hankaku.bin hankaku.txt

hankaku.o: hankaku.bin
	objcopy -I binary -O elf64-x86-64 -B i386:x86-64 hankaku.bin hankaku.o

clean:
	rm -rf *.o *.bin