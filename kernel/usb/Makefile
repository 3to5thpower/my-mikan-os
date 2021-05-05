OBJS=memory.o device.o xhci/ring.o xhci/trb.o xhci/xhci.o \
	xhci/port.o xhci/device.o xhci/devmgr.o xhci/registers.o \
	classdriver/base.o classdriver/hid.o classdriver/keyboard.o \
	classdriver/mouse.o


all: $(OBJS)
%.o: %.cpp Makefile
	$(CXX) $(CXXFLAGS) $(ARCH_OPT) -I.. -c $< -o $@

clean:
	rm -rf *.o