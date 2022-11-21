CC=gcc
CFLAGS=-O3 -g
LDFLAGS=
TARGET=gen_data_bin

ifndef MAX_DIMY
	DEFINES := -DMAX_DIMY=1000
else
	DEFINES := -DMAX_DIMY=$(MAX_DIMY)
endif

ifndef MAX_DIMX
	DEFINES := $(DEFINES) -DMAX_DIMX=1000
else
	DEFINES := $(DEFINES) -DMAX_DIMX=$(MAX_DIMX)
endif

$(info $(DEFINES))

all: clean $(TARGET)

$(TARGET): gen_data.o
	$(CC) $(LDFLAGS) -o $@ $<

%.o : %.c
	$(CC) $(DEFINES) $(CFLAGS) -o $@ -c $^

clean:
	rm -rf $(TARGET)
	rm -rf *.o
	rm -rf arr.dat

