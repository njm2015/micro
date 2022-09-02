CC=gcc
CFLAGS=-pg -std=gnu11
LDFLAGS=
TARGET=inline_bin
C_SRCS=$(wildcard *.c)

ifndef MAX_DIM 
    DEFINES=-DMAX_DIM=1000 
else 
    DEFINES=-DMAX_DIM=$(MAX_DIM) 
endif

all: clean $(TARGET) arr.dat
	#$(TARGET)

arr.dat:
	make MAX_DIM=$(MAX_DIM) -C ../gen_data && bash -c ../gen_data/gen_data_bin

$(TARGET) : $(C_SRCS)
	$(CC) $(DEFINES) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean_all: clean
	rm arr.dat

clean:
	rm -f arr.dat
	rm -f $(TARGET).o
	rm -f $(TARGET)
