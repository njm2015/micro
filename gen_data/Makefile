CC=gcc
CFLAGS=-O3 -g
LDFLAGS=
TARGET=gen_data_bin

ifndef MAX_DIM
	DEFINES=-DMAX_DIM=1000
else
	DEFINES=-DMAX_DIM=$(MAX_DIM)
endif

all: clean $(TARGET)

$(TARGET): gen_data.o
	$(CC) $(LDFLAGS) -o $@ $<

%.o : %.c
	$(CC) $(DEFINES) $(CFLAGS) -o $@ -c $^

clean:
	rm -rf $(TARGET)
	rm -rf *.o
	rm -rf arr.dat

