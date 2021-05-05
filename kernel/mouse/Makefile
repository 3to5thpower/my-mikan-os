OBJS=mouse.o

.PHONY: all target clean
all: $(OBJS)
target: $(OBJS)

%.o: %.cpp Makefile
	$(CXX) $(CXXFLAGS) $(ARCH_OPT) -I../ -c $< -o $@

clean:
	rm -rf *.o