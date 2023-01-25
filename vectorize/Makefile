CC=gcc
CFLAGS=-std=gnu11 -g -Winline -O1
LDFLAGS=
TARGETS=inline_bin noinline_bin
C_SRCS=$(wildcard *.c)
DEFINES=-DINLINE

all: clean $(TARGETS)

inline_bin: $(C_SRCS)
	$(CC) $(DEFINES) $(CFLAGS) $^ -o $@ $(LDFLAGS)

noinline_bin: $(C_SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean_all: clean
	rm arr.dat

clean:
	rm -f *.o
	rm -f $(TARGETS)
	rm -f *.dis

run: all
	time ./noinline_bin
	echo "\n\n"
	time ./inline_bin

dump: $(TARGETS) $(foreach target, $(TARGETS), $(target).dis)
	
%.dis:
	objdump -d -S -s $(basename $@) > $@
