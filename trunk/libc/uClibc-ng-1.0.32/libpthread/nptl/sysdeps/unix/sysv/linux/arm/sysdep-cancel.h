/* Copyright (C) 2003-2017 Free Software Foundation, Inc.

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

#include <sysdep.h>
#include <tcb-offsets.h>
#ifndef __ASSEMBLER__
# include <pthreadP.h>
#endif

#if !defined NOT_IN_libc || defined IS_IN_libpthread || defined IS_IN_librt

# ifdef IS_IN_libpthread
#  define __local_multiple_threads __pthread_multiple_threads
# elif !defined NOT_IN_libc
#  define __local_multiple_threads __libc_multiple_threads
# endif

# if defined IS_IN_libpthread || !defined NOT_IN_libc
extern int __local_multiple_threads attribute_hidden;
#  define SINGLE_THREAD_P __builtin_expect (__local_multiple_threads == 0, 1)
# else
/*  There is no __local_multiple_threads for librt, so use the TCB.  */
#  define SINGLE_THREAD_P						\
  __builtin_expect (THREAD_GETMEM (THREAD_SELF,				\
				   header.multiple_threads) == 0, 1)
# endif

#else

/* For rtld, et cetera.  */
# define SINGLE_THREAD_P 1
# define NO_CANCELLATION 1

#endif

#define RTLD_SINGLE_THREAD_P \
  __builtin_expect (THREAD_GETMEM (THREAD_SELF, \
				   header.multiple_threads) == 0, 1)
