@/*******************************************************************************
@* DISCLAIMER
@* This software is supplied by Renesas Electronics Corporation and is only
@* intended for use with Renesas products. No other uses are authorized. This
@* software is owned by Renesas Electronics Corporation and is protected under
@* all applicable laws, including copyright laws.
@* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
@* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
@* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
@* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
@* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
@* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
@* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
@* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
@* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
@* Renesas reserves the right, without notice, to make changes to this software
@* and to discontinue the availability of this software. By using this software,
@* you agree to the additional terms and conditions found by accessing the
@* following link:
@* http://www.renesas.com/disclaimer
@* Copyright (C) 2018 Renesas Electronics Corporation. All rights reserved.
@*******************************************************************************/
.section ".rodata"

@.balign 32
@.global g_drp_lib_isp_bayer2grayscale_6
@g_drp_lib_isp_bayer2grayscale_6:
@.incbin "r_drp_simple_isp_bayer2grayscale_6.dat"

@.balign 32
@.global g_drp_lib_lrgb2l_gaussian_blur
@g_drp_lib_lrgb2l_gaussian_blur:
@.incbin "g_drp_lib_lrgb2l_gaussian_blur.dat"

@.balign 32
@.global g_drp_lib_find_contours_crop_t2
@g_drp_lib_find_contours_crop_t2:
@.incbin "r_drp_find_contours_crop_t2.dat"

.balign 32
.global g_drp_lib_bayer2grayscale
g_drp_lib_bayer2grayscale:
.incbin "r_drp_bayer2grayscale.dat"

.balign 32
.global g_drp_lib_thinning
g_drp_lib_thinning:
.incbin "r_drp_thinning.dat"

.balign 32
.global g_drp_lib_median_blur
g_drp_lib_median_blur:
.incbin "r_drp_median_blur.dat"

.balign 32
.global g_drp_lib_binarization_adaptive
g_drp_lib_binarization_adaptive:
.incbin "r_drp_binarization_adaptive.dat"

.balign 32
.global g_drp_lib_dilate
g_drp_lib_dilate:
.incbin "r_drp_dilate.dat"

.balign 32
.global g_drp_lib_erode
g_drp_lib_erode:
.incbin "r_drp_erode.dat"

.balign 32
.global g_drp_lib_find_contours
g_drp_lib_find_contours:
.incbin "r_drp_find_contours.dat"

@.balign 32
@.global g_drp_lib_canny_hysterisis
@g_drp_lib_canny_hysterisis:
@.incbin "r_drp_canny_hysterisis.dat"

@.balign 32
@.global g_drp_lib_canny_calculate
@g_drp_lib_canny_calculate:
@.incbin "r_drp_canny_calculate.dat"

.balign 32
.global g_drp_lib_sobel
g_drp_lib_sobel:
.incbin "r_drp_sobel.dat"

@.balign 32
@.global g_drp_lib_gaussian_blur
@g_drp_lib_gaussian_blur:
@.incbin "r_drp_gaussian_blur.dat"

@.balign 32
@.global g_drp_lib_cropping
@g_drp_lib_cropping:
@.incbin "r_drp_cropping.dat"

@.balign 32
@.global g_drp_lib_resize_bilinear
@g_drp_lib_resize_bilinear:
@.incbin "r_drp_resize_bilinear.dat"

.end
