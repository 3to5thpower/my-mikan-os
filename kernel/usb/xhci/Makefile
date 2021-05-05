OBJS= ring.o trb.o xhci.o port.o device.o devmgr.o registers.o 

all: $(OBJS)
target: $(OBJS)

%.o: %.cpp Makefile
	$(CXX) $(CXXFLAGS) $(ARCH_OPT) -I../.. -c $< -o $@

clean:
	rm -rf *.o