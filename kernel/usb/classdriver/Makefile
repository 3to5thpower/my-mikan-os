OBJS= base.o hid.o keyboard.o mouse.o


all: $(OBJS)
target: $(OBJS)

%.o: %.cpp Makefile
	$(CXX) $(CXXFLAGS) $(ARCH_OPT) -I../.. -c $< -o $@

clean:
	rm -rf *.o