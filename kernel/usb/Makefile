OBJS=memory.o device.o 
	

all: $(OBJS)
target: $(OBJS)

%.o: %.cpp Makefile
	$(CXX) $(CXXFLAGS) $(ARCH_OPT) -I.. -c $< -o $@

clean:
	rm -rf *.o