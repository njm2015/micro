LIKWID_LIB=/usr/local/lib/
LIKWID_INCLUDE=/usr/local/incude/

CC=gcc
CFLAGS=-pg -g -DLIKWID_PERFMON -L$(LIKWID_LIB) -I$(LIKWID_INCLUDE)
LDFLAGS=-llikwid -lpapi
#LDFLAGS=-lpapi
TARGET=arr_avg_bin

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

all: clean $(TARGET) arr.dat
	#$(TARGET)

arr.dat:
	make MAX_DIMX=$(MAX_DIMX) MAX_DIMY=$(MAX_DIMY) -C ../gen_data && bash -c ../gen_data/gen_data_bin

$(TARGET) : arr_avg.c
	$(CC) $(DEFINES) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean_all: clean
	rm arr.dat

clean:
	rm -f arr.dat
	rm -f $(TARGET).o
	rm -f $(TARGET)
