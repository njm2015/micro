LIKWID_LIB=/usr/local/lib/
LIKWID_INCLUDE=/usr/local/include/
LIKWID_FLAGS=-pg -DLIKWID_PERFMON -L$(LIKWID_LIB) -I$(LIKWID_INCLUDE)

CC = gcc
CFLAGS = -g -O0 $(LIKWID_FLAGS)
LDFLAGS=-llikwid 
CFLAGS_DISABLE_SSE2 = -g -O0 -mno-sse2 $(LIKWID_FLAGS)
DEFINES = -DSTREAM_ARRAY_SIZE=80000000 -DNTIMES=20

all: stream_c.exe

.PHONY: sse2
sse2: all

.PHONY: disable-sse2
disable-sse2: stream.c
	$(CC) $(CFLAGS_DISABLE_SSE2) $(DEFINES) stream.c -o stream_c_no_sse2.exe $(LDFLAGS)

stream_c.exe: stream.c
	$(CC) $(CFLAGS) $(DEFINES) stream.c -o stream_c.exe $(LDFLAGS)

clean:
	rm *.exe

