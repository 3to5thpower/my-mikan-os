OBJS=console.o

.PHONY: all target clean
all: $(OBJS)
target: $(OBJS)

%.o: %.cpp Makefile
	$(CXX) $(CXXFLAGS) $(ARCH_OPT)  -c $< -o $@

clean:
	rm -rf *.o