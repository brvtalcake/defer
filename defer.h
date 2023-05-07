/*
 * MIT License
 * 
 * Copyright (c) 2023 Axel PASCON
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef DEFER_H
#define DEFER_H

#include <metalang99.h>

#if !defined(__GNUC__) && !defined(__clang__)
    #error "This header is GCC/Clang specific"
#endif

#if defined(DEFER_PRIMITIVE_CAT)
    #undef DEFER_PRIMITIVE_CAT
#endif
#define DEFER_PRIMITIVE_CAT(x, y) x##y
#if defined(DEFER_CAT)
    #undef DEFER_CAT
#endif
#define DEFER_CAT(x, y) DEFER_PRIMITIVE_CAT(x, y)
#if defined(DEFER_PRIMITIVE_ID)
    #undef DEFER_PRIMITIVE_ID
#endif
#define DEFER_PRIMITIVE_ID(x) x
#if defined(DEFER_ID)
    #undef DEFER_ID
#endif
#define DEFER_ID(x) DEFER_PRIMITIVE_ID(x)
#if defined(DEFER_SUB)
    #undef DEFER_SUB
#endif
#define DEFER_SUB(x, y) ML99_EVAL(ML99_call(ML99_sub, v(x), v(y)))

#if defined(DEFER)
    #undef DEFER
#endif
#define DEFER                                          \
    void DEFER_CAT(deferred_, __COUNTER__)(int *dummy) \
    {                                                  \
        (void)dummy;

#if defined(END_DEFER)
    #undef END_DEFER
#endif
#define END_DEFER                                                                           \
    ;};                                                                                     \
    int DEFER_CAT(DEFER_CAT(deferred_, DEFER_ID(DEFER_SUB(__COUNTER__, 1))), _dummy)        \
    __attribute__((cleanup(DEFER_CAT(deferred_, DEFER_ID(DEFER_SUB(__COUNTER__, 2)))))) = 0

#endif // DEFER_H
