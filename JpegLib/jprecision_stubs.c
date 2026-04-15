/*-----------------------------------------------------------------------------

    jprecision_stubs.c

    No-op stub implementations for libjpeg-turbo 12-bit and 16-bit precision
    init functions. These are referenced internally by jdmaster.c and jcinit.c
    but are never called when processing standard 8-bit JPEG images (the only
    precision used by this application).

    The actual implementations are generated from libjpeg-turbo template files
    (jdmaster.c -> jdmaster12.c / jdmaster16.c etc.) which are not included in
    this build. Stubs are safe here.

-----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stddef.h>
#include "jpeglib.h"

/* Decompressor init stubs */
void j12init_d_diff_controller    (j_decompress_ptr cinfo)  { (void)cinfo; }
void j12init_upsampler             (j_decompress_ptr cinfo) { (void)cinfo; }
void j12init_lossless_decompressor (j_decompress_ptr cinfo) { (void)cinfo; }
void j12init_d_main_controller     (j_decompress_ptr cinfo) { (void)cinfo; }
void j12init_1pass_quantizer       (j_decompress_ptr cinfo) { (void)cinfo; }
void j12init_d_post_controller     (j_decompress_ptr cinfo) { (void)cinfo; }
void j12init_inverse_dct           (j_decompress_ptr cinfo) { (void)cinfo; }
void j12init_merged_upsampler      (j_decompress_ptr cinfo) { (void)cinfo; }
void j12init_2pass_quantizer       (j_decompress_ptr cinfo) { (void)cinfo; }
void j12init_color_deconverter     (j_decompress_ptr cinfo) { (void)cinfo; }
void j12init_d_coef_controller     (j_decompress_ptr cinfo) { (void)cinfo; }

void j16init_d_diff_controller     (j_decompress_ptr cinfo) { (void)cinfo; }
void j16init_d_main_controller     (j_decompress_ptr cinfo) { (void)cinfo; }
void j16init_d_post_controller     (j_decompress_ptr cinfo) { (void)cinfo; }
void j16init_color_deconverter     (j_decompress_ptr cinfo) { (void)cinfo; }
void j16init_lossless_decompressor (j_decompress_ptr cinfo) { (void)cinfo; }
void j16init_upsampler             (j_decompress_ptr cinfo) { (void)cinfo; }

/* Compressor init stubs */
void j12init_color_converter       (j_compress_ptr cinfo)   { (void)cinfo; }
void j12init_c_prep_controller     (j_compress_ptr cinfo)   { (void)cinfo; }
void j12init_c_main_controller     (j_compress_ptr cinfo)   { (void)cinfo; }
void j12init_c_diff_controller     (j_compress_ptr cinfo)   { (void)cinfo; }
void j12init_c_coef_controller     (j_compress_ptr cinfo)   { (void)cinfo; }
void j12init_forward_dct           (j_compress_ptr cinfo)   { (void)cinfo; }
void j12init_lossless_compressor   (j_compress_ptr cinfo)   { (void)cinfo; }
void j12init_downsampler           (j_compress_ptr cinfo)   { (void)cinfo; }

void j16init_lossless_compressor   (j_compress_ptr cinfo)   { (void)cinfo; }
void j16init_c_prep_controller     (j_compress_ptr cinfo)   { (void)cinfo; }
void j16init_c_diff_controller     (j_compress_ptr cinfo)   { (void)cinfo; }
void j16init_downsampler           (j_compress_ptr cinfo)   { (void)cinfo; }
void j16init_c_main_controller     (j_compress_ptr cinfo)   { (void)cinfo; }
void j16init_color_converter       (j_compress_ptr cinfo)   { (void)cinfo; }
