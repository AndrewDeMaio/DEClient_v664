/* Version ID for the JPEG library.
 * Might be useful for tests like "#if JPEG_LIB_VERSION >= 60".
 */
#define JPEG_LIB_VERSION  62

/* libjpeg-turbo version */
#define LIBJPEG_TURBO_VERSION  "3.1.0"

/* libjpeg-turbo version in integer form */
#define LIBJPEG_TURBO_VERSION_NUMBER  3001000

/* Support in-memory source/destination managers */
#define MEM_SRCDST_SUPPORTED  1

/* Arithmetic coding is not supported in this build */
/* #undef C_ARITH_CODING_SUPPORTED */
/* #undef D_ARITH_CODING_SUPPORTED */

/* SIMD is not enabled in this build */
/* #undef WITH_SIMD */

/* This version of libjpeg-turbo supports run-time selection of data
 * precision, but BITS_IN_JSAMPLE is still defined for compatibility.
 * The unmodified libjpeg API behaves as 8-bit precision.
 */
#ifndef BITS_IN_JSAMPLE
#define BITS_IN_JSAMPLE  8
#endif

#ifdef _WIN32

#undef RIGHT_SHIFT_IS_UNSIGNED

/* Define "boolean" as unsigned char, not int, per Windows custom */
#ifndef __RPCNDR_H__            /* don't conflict if rpcndr.h already read */
typedef unsigned char boolean;
#endif
#define HAVE_BOOLEAN            /* prevent jmorecfg.h from redefining it */

/* Define "INT32" as int, not long, per Windows custom */
#if !(defined(_BASETSD_H_) || defined(_BASETSD_H))   /* don't conflict if basetsd.h already read */
typedef short INT16;
typedef signed int INT32;
#endif
#define XMD_H                   /* prevent jmorecfg.h from redefining it */

#endif /* _WIN32 */
