OBJS=graphics.o

.PHONY: all target clean
all: $(OBJS)
target: $(OBJS)

graphics.o: graphics.cpp Makefile
	$(CXX) $(CXXFLAGS) $(ARCH_OPT) -I../ -c $< -o $@

clean:
	rm -rf *.o