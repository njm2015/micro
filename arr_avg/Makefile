LIKWID_LIB=/usr/local/lib/
LIKWID_INCLUDE=/usr/local/incude/

CC=gcc
CFLAGS=-pg -g
LDFLAGS=
TARGET=arr_avg_bin

ifndef MAX_DIM
	DEFINES=-DMAX_DIM=1000
else
	DEFINES=-DMAX_DIM=$(MAX_DIM)
endif

all: clean $(TARGET) arr.dat
	#$(TARGET)

arr.dat:
	make MAX_DIM=$(MAX_DIM) -C ../gen_data && bash -c ../gen_data/gen_data_bin

$(TARGET) : arr_avg.c
	$(CC) $(DEFINES) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean_all: clean
	rm arr.dat

clean:
	rm -f arr.dat
	rm -f $(TARGET).o
	rm -f $(TARGET)
