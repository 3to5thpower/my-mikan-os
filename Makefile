subdirs:=kernel

.PHONY: clean $(subdirs)

all: $(subdirs)

$(subdirs):
	make -C $@ $(MAKECMDGOALS)

clean: $(subdirs)

