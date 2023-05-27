# defer

A (non-portable) go-like defer statement for C.

## Usage

```c
void func(void)
{
    FILE* f = fopen("LICENSE", "rb");
    if (!f) return;
    DEFER 
    {
        if (f)
        {
            fprintf(stderr, "Closing file f...\n");
            fclose(f);
            fprintf(stderr, "File f closed.\n");
        }
    } END_DEFER;
    // Do some stuff with f
    // ...
}
```

Output (see test.c for full example) :

```shell
$ gcc test.c -Imetalang99/include/ -o test && ./test
  Closing file f...
  File f closed.
```

> **Warning**
> 
> **Do NOT use the `__COUNTER__` macro between a `DEFER` and its corresponding `END_DEFER`, and (of course), do NOT nest `DEFER`s.**

You can even run Valgrind to make sure the `FILE` has been deallocated. On my machine, I get :

```shell
$ valgrind ./test
==13317== Memcheck, a memory error detector
==13317== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==13317== Using Valgrind-3.19.0 and LibVEX; rerun with -h for copyright info
==13317== Command: ./test
==13317== 
MIT License

Copyright (c) 2023 Axel PASCON

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
Closing file...
File closed.
==13317== 
==13317== HEAP SUMMARY:
==13317==     in use at exit: 0 bytes in 0 blocks
==13317==   total heap usage: 2 allocs, 2 frees, 4,568 bytes allocated
==13317== 
==13317== All heap blocks were freed -- no leaks are possible
==13317== 
==13317== For lists of detected and suppressed errors, rerun with: -s
==13317== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## How does it works ?

This C defer implementation uses GCC's nested functions extension, to declare a function with the body of your `DEFER`, and then declare a useless variable, with the `cleanup` GCC's attribute, so the previously defined nested function is called at the end of the scope.

> **NOTE**
> For Clang, some work remains to be done since nested functions are not allowed. The Clang implementation will probably use Blocks extension, wich needs `libblocksruntime-dev` (on Ubuntu).
