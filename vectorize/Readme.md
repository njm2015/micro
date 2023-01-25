# Inlining C Code

This app shows the optimizations when using inlining. Due to the fact that inlining removes a function definition from the executable, gprof cannot be used to directly compare two identical functions in the same execution and multiple executables must be used. Several rules in the makefile facilitate this which include the necessary defines.

- `make`: Compiles the two targets. One will have an inlined implementation of a compare function, the other will not.
- `make run`: Runs the binaries (and makes them if not built already)
- `make dump`: Dumps the disassembly of both binaries into separate files


### Analysis
Obviously, our inlined code will run faster, but here we can actually see why that is. Looking at the disassembly of the non-inlined code, this is what we see for the main loop:

~~~
char __attribute__ ((noinline)) cmp(int a, int b) {
    11e9:   f3 0f 1e fa             endbr64
    11ed:   55                      push   %rbp
    11ee:   48 89 e5                mov    %rsp,%rbp
    11f1:   ff 15 f1 2d 00 00       callq  *0x2df1(%rip)        # 3fe8 <mcount@GLIBC_2.2.5>

    return (a > b);
    11f7:   39 f7                   cmp    %esi,%edi
    11f9:   0f 9f c0                setg   %al

}
    11fc:   5d                      pop    %rbp
    11fd:   c3                      retq
    ...
    ... [Omitting some boring code]
    ...
        for (size_t i = 0; i < 1000000000; ++i)
    120f:   bb 00 00 00 00          mov    $0x0,%ebx
    size_t cnt= 0;
    1214:   41 bc 00 00 00 00       mov    $0x0,%r12d
        cnt+= cmp(i, 0);
    121a:   be 00 00 00 00          mov    $0x0,%esi
    121f:   89 df                   mov    %ebx,%edi
    1221:   e8 c3 ff ff ff          callq  11e9 <cmp>
    1226:   48 0f be c0             movsbq %al,%rax
    122a:   49 01 c4                add    %rax,%r12
    for (size_t i = 0; i < 1000000000; ++i)
    122d:   48 83 c3 01             add    $0x1,%rbx
    1231:   48 81 fb 00 ca 9a 3b    cmp    $0x3b9aca00,%rbx
    1238:   75 e0                   jne    121a <main+0x1c>
~~~
Note that the `cmp` function is clearly defined after compilation and that we have a `call` instruction that is executed once per iteration of the  loop. Also note that the `cmp` function consists of 8 instructions.

Compare the above disassembled output to the disassembly of our inlined code:
~~~
    for (size_t i = 0; i < 1000000000; ++i)
    11f7:   b8 00 00 00 00          mov    $0x0,%eax
    size_t cnt= 0;
    11fc:   ba 00 00 00 00          mov    $0x0,%edx
    return (a > b);
    1201:   85 c0                   test   %eax,%eax
    1203:   0f 9f c1                setg   %cl
    1206:   0f b6 c9                movzbl %cl,%ecx
        cnt+= cmp(i, 0);
    1209:   48 01 ca                add    %rcx,%rdx
    for (size_t i = 0; i < 1000000000; ++i)
    120c:   48 83 c0 01             add    $0x1,%rax
    1210:   48 3d 00 ca 9a 3b       cmp    $0x3b9aca00,%rax
    1216:   75 e9                   jne    1201 <main+0x18>
~~~
This output looks a bit different and you might think the `cmp` function was accidentally omitted from this code block, but after compilation, we realize that the `cmp` function effectively does not exist in this executable. The compiler has instead replaced the `cmp` functionality with a simple `test %eax, %eax` instruction,  which actually accomplishes the same functionality as all the instructions of the `cmp` function. 

**Note**: we did have to explicitly state that the `cmp` function in the `noinline_bin` executable not be inlined with the gcc `\_\_attribute\_\_ ((noinline))`. If this is not included, depending on the level of optimization you compile with, most compilers will automatically inline the function for you.
 
