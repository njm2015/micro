# Vectorized Code with the STREAM Benchmark

This app demonstrates how to vectorize a simple application by using the STREAM benchmark code as a base. We'll run the code that's distributed with the benchmark, explain exactly what the output is showing us, then tweak a few compilation flags exploring specifically x86 vector instructions and common things to expect when exploiting them for potential speedup. 

**Note**: while I'm not a fan of the `.exe` extension on the binaries, the STREAM library uses this as a convention, so I'll ablige for this app.

- `make`: makes the rules that come standard with the STREAM Benchmark code. This will produce `stream_f.exe` and `stream_c`.exe
- `make sse2`: produces an executable compiled with SSE2 flags producing the executable `stream_sse2.exe`
- `make avx`: produces an executable compiled with AVX flags producing the executable `stream_avx.exe`
- `make avx2`: produces an executable compiled with AVX2 flags producing the executable `stream_avx2.exe`
- `make avx512`: produces an executable compiled with AVX512 flags producing the executable `stream_avx512.exe`

### Analysis

Right off the bat this guide gets a little confusing as I've tricked you before we've even gotten started. The above list of `make` statements seem perfectly logical, and I would agree that they are, they just don't refect compilation reality as we know it. Let's dive into the first statement, just a plain `make` command which only passes a `-O0` optimization flag to the compiler. 


