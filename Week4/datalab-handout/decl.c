#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TMin INT_MIN
#define TMax INT_MAX

#include "btest.h"
#include "bits.h"

test_rec test_set[] = {
/* Copyright (C) 1991-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
/* We do not support C11 <threads.h>.  */
 {"logicalShift", (funct_t) logicalShift, (funct_t) test_logicalShift,
   2, "! ~ & ^ | + << >>", 20, 3,
  {{TMin, TMax},{0,31},{TMin,TMax}}},
 {"remainderPower2", (funct_t) remainderPower2, (funct_t) test_remainderPower2, 2,
    "! ~ & ^ | + << >>", 20, 3,
  {{TMin, TMax},{0,30},{TMin,TMax}}},
 {"specialBits", (funct_t) specialBits, (funct_t) test_specialBits, 0,
    "! ~ & ^ | + << >>", 3, 1,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"floatAbsVal", (funct_t) floatAbsVal, (funct_t) test_floatAbsVal, 1,
    "$", 10, 2,
     {{1, 1},{1,1},{1,1}}},
 {"floatScale4", (funct_t) floatScale4, (funct_t) test_floatScale4, 1,
    "$", 30, 4,
     {{1, 1},{1,1},{1,1}}},
 {"floatNegate", (funct_t) floatNegate, (funct_t) test_floatNegate, 1,
    "$", 10, 2,
     {{1, 1},{1,1},{1,1}}},
 {"satMul2", (funct_t) satMul2, (funct_t) test_satMul2, 1,
    "~ & ^ | + << >>", 20, 3,
  {{TMin,TMax},{TMin,TMax},{TMin,TMax}}},
 {"thirdBits", (funct_t) thirdBits, (funct_t) test_thirdBits, 0,
    "! ~ & ^ | + << >>", 8, 1,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"signMag2TwosComp", (funct_t) signMag2TwosComp, (funct_t) test_signMag2TwosComp, 1, "! ~ & ^ | + << >>", 15, 4,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
  {"", NULL, NULL, 0, "", 0, 0,
   {{0, 0},{0,0},{0,0}}}
};
