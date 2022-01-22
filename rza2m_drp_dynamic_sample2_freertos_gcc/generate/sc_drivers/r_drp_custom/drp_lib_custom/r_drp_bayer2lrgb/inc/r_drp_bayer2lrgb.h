/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
* Copyright (C) 2019 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
 * File Name    : r_drp_bayer2lrgb.h
 * Description  : This source code is the header file of R_DRP_BAYER2LRGB processing.
 ******************************************************************************/
#ifndef R_DRP_BAYER2LRGB_H
#define R_DRP_BAYER2LRGB_H

/*******************************************************************************
Global Typedef definitions
*******************************************************************************/
#ifdef BDL
typedef unsigned long long uint64_t;
typedef unsigned long      uint32_t;
typedef unsigned short     uint16_t;
typedef unsigned char      uint8_t;
typedef signed long long   int64_t;
typedef signed long        int32_t;
typedef signed short       int16_t;
typedef signed char        int8_t;
#else /* BDL */
#include <stdint.h>
#endif /* BDL */

/* Structure of interface parameters between CPU and DRP library. */

typedef struct
{
    uint32_t src;       /* Address of input image. */
    uint32_t dst;       /* Address of output image. */
    uint16_t width;     /* The horizontal size (pixels) of image. */
    uint16_t height;    /* The vertical size (pixels) of image. */
    uint8_t top;        /* Boundary processing(top) */
    uint8_t bottom;     /* Boundary processing(bottom) */
    uint8_t pattern;     /* 0- bayer pattern RGGB, 1-bayer pattern BGGR */
    uint8_t spare2;     /* unused */
   	uint32_t dst_layersum; 	/* Address of output sum of llayer over all pixel (pointer to an uint32_t variable) */
   	uint32_t  spare3;  /* unsued */
} r_drp_bayer2lrgb_t;

/* lum sum struct (dst_layersum) */
typedef struct
{
	uint32_t layersum;     	 	/* sum of all active l channel pixel values */
	uint32_t layeractivepixel; 	/* number of active l channel pixel         */
								/* lmiddle = layersum / layeractivepixel    */
} r_drp_bayer2lrgb_layer_t;

#endif /* R_DRP_BAYER2LRGB_H */

/* end of file */
