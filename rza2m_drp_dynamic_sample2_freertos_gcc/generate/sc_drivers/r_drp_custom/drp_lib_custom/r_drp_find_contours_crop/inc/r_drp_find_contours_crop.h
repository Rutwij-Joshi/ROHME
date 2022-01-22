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
 * File Name    : r_drp_find_contours_crop.h
 * Description  : This source code is the header file of R_DRP_FIND_CONTOURS_CROP processing.
 ******************************************************************************/
#ifndef R_DRP_FIND_CONTOURS_CROP_H
#define R_DRP_FIND_CONTOURS_CROP_H

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


// please use aspectfloat4contourfixedint(x) for mode FFF seting 011, 100 and 101
// to get valid results the values must be in range   [ 0.004  .. 255.99] 
#define aspectfloat4contourfixedint(x)((x)>=0?(int)((x*256.0)+0.5):(int)(256))  

/* Structure of interface parameters between CPU and DRP library. */
typedef struct
{
	uint32_t src;												/* Address of input one lane image							*/
	uint32_t dst_rect;											/* Address of rectangle information							*/
	uint16_t width;												/* The horizontal size (pixels) of image multiple of 8byte  */
	uint16_t height;											/* The vertical size (pixels) of image	minimum 5 lines		*/
	uint32_t work;												/* Address of work area										*/
																/* minimum size = width * height / 4 + 8					*/
																/* keep in internal ram										*/
	uint32_t dst_region;										/* Address of region information							*/
	uint32_t dst_rect_size;										/* Size of dst_rect area									*/
	uint32_t dst_region_size;									/* Size of dst_region area									*/
	uint16_t threshold_widthOrMin;								/* Threshold of width or min value							*/
	uint16_t threshold_heightOrMax;								/* Threshold of height or max value							*/
	uint16_t x_crop;											/* Crop window x position									*/
	uint16_t y_crop;											/* Crop window y position									*/
	uint16_t width_crop;										/* Crop window width	(min 3)								*/
	uint16_t height_crop;										/* Crop window height	(min 3)								*/
	uint8_t  mode ;												/* 0000RFFF (bit-field)		  	 	    					*/
																/*  R - output coordinates relative to crop	window upper left (0 0)			*/
																/*		  0 - off (coordinates are relative to src picture), 1 -on 			*/
																/*  F - filter for box/region found											*/
																/*		000 - boxWidth	>=	threshold_widthOrMin && boxHeight >= threshold_heightOrMax																	*/
																/*		001 - regionCnt >   threshold_region																											*/
																/*		010 - boxWidth	>=	threshold_widthOrMin			  && boxHeight >= threshold_heightOrMax					&& regionCnt >=	threshold_region	*/
																/*		011 - boxWidth/boxHeight*256 >= threshold_widthOrMin  && boxWidth/boxHeight*256 <= threshold_heightOrMax	&& regionCnt >=	threshold_region	*/
																/*		100 - boxWidth/boxHeight*256 >= threshold_widthOrMin  && regionCnt >=	threshold_region														*/
																/*		101 - boxWidth/boxHeight*256 <= threshold_heightOrMax && regionCnt >=	threshold_region														*/	
																/*      110 - reserved																																	*/
																/*      111 - reserved																																	*/
	uint8_t dmode	;											/* WCBP000A (bit-field)		  	 	    										*/
																/*  W - draw cropping window 						-> dst_rgbDebug(RGB/ARGB)	*/
                                                                /*		  0 - off, 1 -on 														*/
																/*  C - draw contour data stored in dst_region into -> dst_rgbDebug(RGB/ARGB)	*/
                                                                /*		  0 - off, 1 -on 														*/
																/*  B - boundingBox	 draw bounding box into 		-> dst_rgbDebug(RGB/ARGB)	*/
                                                                /*		  0 - off, 1 -on 														*/
																/*  P - debug		 copy picture src 				-> dst_rgbDebug(RGB/ARGB)	*/
																/*		  0 - off, 1 -on 														*/
																/*  A - output fromat for debug 					-> dst_rgbDebug(RGB/ARGB)	*/
                                                                /*		  0 - RGB (24bit), 1 -ARGB(32bit) A channel set to 0					*/

	uint16_t threshold_region ;									/* Threshold contour count (number of found contour pixel) (example 30)																					*/
	uint32_t dst_rgbDebug;										/* Output address for RGB picture, debug bounding box(blue), found region(red), found pixel(green)														*/
																/* please set to NULL if not used. Size is same as "width" * "height" of "src" 																			*/
} r_drp_find_contours_crop_t;



/* fault  status output will be in the first record of r_drp_find_contours_crop_dst_rect_t (only if there is any error condition found)
** condition: x_coordinate== y_coordinate== width == height == 0 && ((count &0x07) != 0 )
** the following errors are recognized
** if (count & 0x01) { printf("Error: window out of right border\n"); } 
** if (count & 0x02) { printf("window out of bottom border\n"); } 
** if (count & 0x04) { printf("box to small\n"); }  
*/

/* Structure of rectangle information */
typedef struct
{
    uint16_t x_coordinate; /* left upper X-coordinate of rectangle */
    uint16_t y_coordinate; /* left upper Y-coordinate of rectangle */
    uint16_t width;        /* The horizontal size (pixels) of rectangle */
    uint16_t height;       /* The vertical size (pixels) of rectangle */
    uint32_t count;        /* Count of region information */
    uint32_t addr;         /* Head pointer of region information */
} r_drp_find_contours_crop_dst_rect_t;


/* Structure of region information */
typedef struct
{
    uint16_t x_coordinate;    /* X-coordinate of pixel */
    uint16_t y_coordinate;    /* Y-coordinate of pixel */
} r_drp_find_contours_crop_dst_region_t;


#endif /* R_DRP_FIND_CONTOURS_CROP_H */

/* end of file */
