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
 * File Name    : r_drp_lrgb2lcrop.h
 * Description  : This source code is the header file of R_DRP_LRGB2LCROP processing.
 ******************************************************************************/
#ifndef R_DRP_LRGB2LCROP_H
#define R_DRP_LRGB2LCROP_H

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

typedef struct {
	uint32_t src;         /* address of input image. */
	uint32_t l_dst;       /* address of output image gray channel. */
	uint32_t spare;       /* spare for later use */
	uint16_t width;       /* the horizontal size (pixels) of image. */
	uint16_t height;      /* the vertical size (pixels) of image. */
	uint16_t tXstart;     /* x start for crop */ 
	uint16_t tYstart ;    /* y start for crop */
	uint16_t tWidth  ;    /* with of crop window */
	uint16_t tHeight ;    /* height if crop window */
	uint16_t tXplace ;    /* place in target window at x position */
	uint16_t tYplace ;    /* place in target window at y position */
	uint16_t tPwidth ;    /* with of target picture */
	uint16_t tPheight;    /* height of target picture */
} r_drp_lrgb2lcrop_t ;

#endif /* R_DRP_LRGB2LCROP_H */

/* end of file */
