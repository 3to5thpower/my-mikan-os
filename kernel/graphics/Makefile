OBJS=graphics.o font.o

.PHONY: all target clean
all: $(OBJS)
target: $(OBJS)

graphics.o: src/graphics.cpp Makefile
	$(CXX) $(CXXFLAGS) $(ARCH_OPT) -I ./include -c $< -o $@

font.o: src/font.cpp src/graphics.cpp Makefile
	$(CXX) $(CXXFLAGS) $(ARCH_OPT) -I ./include -c $< -o $@

clean:
	rm -rf *.o