///**********************************************************************************************************************
//* b2g->bin->find_contours working? DISCLAIMER
//* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
//* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
//* applicable laws, including copyright laws.
//* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
//* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
//* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
//* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
//* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
//* THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
//* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
//* this software. By using this software, you agree to the additional terms and conditions found by accessing the
//* following link:
//* http://www.renesas.com/disclaimer
//* Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
//**********************************************************************************************************************/
//
///**********************************************************************************************************************
//Includes   <System Includes> , "Project Includes"
//**********************************************************************************************************************/
//#include <stdio.h>
//#include <fcntl.h>
//
//#include "r_typedefs.h"
//#include "iodefine.h"
//#include "r_cache_lld_rza2m.h"
//
//#include "r_bcd_camera.h"
//#include "r_bcd_lcd.h"
//#include "draw.h"
//#include "perform.h"
//#include "r_mmu_lld_rza2m.h"
//
//#include "r_dk2_if.h"
//#include "r_drp_simple_isp.h"
//#include "r_drp_bayer2grayscale.h"
//#include "r_drp_median_blur.h"
//#include "r_drp_corner_harris.h"
//#include "r_drp_dilate.h"
//#include "r_drp_binarization_adaptive.h"
//#include "r_drp_binarization_fixed.h"
//#include "r_drp_median_blur.h"
//#include "r_drp_thinning.h"
//#include "r_drp_sobel.h"
//#include "r_drp_dilate.h"
//#include "r_drp_find_contours.h"
//#include "r_drp_prewitt.h"
//#include "r_drp_gaussian_blur.h"
//#include "r_drp_canny_calculate.h"
//#include "r_drp_canny_hysterisis.h"
//
//
///**********************************************************************************************************************
//  Local Typedef definitions
// *********************************************************************************************************************/
//
//typedef struct contours_rect_t
//{
//    uint16_t x;
//    uint16_t y;
//    uint16_t width;
//    uint16_t height;
//    uint32_t num;
//    uint32_t addr;
//} contours_rect_t;
//
//typedef struct
//{
//    uint16_t x;
//    uint16_t y;
//} contours_region_t;
//
///**********************************************************************************************************************
//Macro definitions
//**********************************************************************************************************************/
//#define TILE_0          (0)
//#define TILE_1          (1)
//#define TILE_2          (2)
//#define TILE_3          (3)
//#define TILE_4          (4)
//#define TILE_5          (5)
//
//#define DRP_NOT_FINISH  (0)
//#define DRP_FINISH      (1)
//
//#define HARRIS_SHIFT_NUM    (3)
//
//#define FIND_CONTOURS_NUM (6)
//
//#define DRP_DRV_ASSERT(x) if ((x) != 0) goto sample_finish
//
//#define LEN(arr) ((int) (sizeof (arr) / sizeof (arr)[0]))
//
//#define WEAK_LEVEL      (0x28)
//#define STRONG_LEVEL    (0x58)
//
//#define HYSTERISIS_COUNT  (2)
//
///**********************************************************************************************************************
//Imported global variables and functions (from other files)
//**********************************************************************************************************************/
//extern uint8_t g_drp_lib_bayer2grayscale[];
//extern uint8_t g_drp_lib_binarization_adaptive[];
////extern uint8_t g_drp_lib_binarization_fixed[];
//extern uint8_t g_drp_lib_median_blur[];
////extern uint8_t g_drp_lib_thinning[];
////extern uint8_t g_drp_lib_dilate[];
//extern uint8_t g_drp_lib_find_contours[];
//extern uint8_t g_drp_lib_sobel[];
////extern uint8_t g_drp_lib_gaussian_blur[];
////extern uint8_t g_drp_lib_canny_calculate[];
////extern uint8_t g_drp_lib_canny_hysterisis[];
//
///**********************************************************************************************************************
//Private global variables and functions
//**********************************************************************************************************************/
//static uint8_t drp_lib_id[R_DK2_TILE_NUM] = {0};
//static volatile uint8_t drp_lib_status[R_DK2_TILE_NUM] = {DRP_NOT_FINISH};
//static uint8_t work_buf[R_BCD_CAMERA_WIDTH * R_BCD_CAMERA_HEIGHT] 					__attribute__ ((aligned(32)));
//static uint8_t work_buf_2[R_BCD_CAMERA_WIDTH * R_BCD_CAMERA_HEIGHT] 				__attribute__ ((aligned(32)));
//static uint8_t work_buf_3[R_BCD_CAMERA_WIDTH * R_BCD_CAMERA_HEIGHT] 				__attribute__ ((aligned(32)));
////static uint8_t work_buf_4[R_BCD_CAMERA_WIDTH * R_BCD_CAMERA_HEIGHT] 				__attribute__ ((aligned(32)));
//static uint8_t work_buf_5[R_BCD_CAMERA_WIDTH * R_BCD_CAMERA_HEIGHT] 				__attribute__ ((aligned(32)));
////static uint8_t work_buf_6[R_BCD_CAMERA_WIDTH * R_BCD_CAMERA_HEIGHT] 				__attribute__ ((section("ImageWork_RAM")));
//
//
//static r_drp_bayer2grayscale_t param_b2g[R_DK2_TILE_NUM]						 	__attribute__ ((section("UNCACHED_BSS")));
//static r_drp_binarization_adaptive_t param_binarization_adaptive 					__attribute__ ((section("UNCACHED_BSS")));
//static r_drp_median_blur_t param_median[R_DK2_TILE_NUM] 							__attribute__ ((section("UNCACHED_BSS")));
////static r_drp_thinning_t param_thinning[2] 										__attribute__ ((section("UNCACHED_BSS")));
////static r_drp_dilate_t param_dilate[R_DK2_TILE_NUM]								__attribute__ ((section("UNCACHED_BSS")));
//static r_drp_find_contours_t param_find_contours 									__attribute__ ((section("Uncache_BSS")));
//contours_region_t g_contours_region_adr[FIND_CONTOURS_NUM + 1]  					__attribute__ ((section("Uncache_IRAM")));
//contours_rect_t g_contours_rect_adr[FIND_CONTOURS_NUM + 1] 							__attribute__ ((section("Uncache_IRAM")));
//static r_drp_sobel_t param_sobel[R_DK2_TILE_NUM] 									__attribute__ ((section("UNCACHED_BSS")));
////static r_drp_gaussian_blur_t param_gaussian_blur[R_DK2_TILE_NUM] 					__attribute__ ((section("UNCACHED_BSS")));
////static r_drp_canny_calculate_t  param_canny_cal[1]     							__attribute__ ((section("Uncache_IRAM")));
////static r_drp_canny_calculate_t  param_canny_cal     								__attribute__ ((section("Uncache_IRAM")));
//
////static r_drp_canny_hysterisis_t             param_canny_hyst    					__attribute__ ((section("Uncache_IRAM")));
////static r_drp_prewitt_t param_sobel[R_DK2_TILE_NUM] 								__attribute__ ((section("UNCACHED_BSS")));
//
//
//
////static uint8_t frame_RAM_E[R_BCD_CAMERA_HEIGHT * R_BCD_CAMERA_WIDTH]          __attribute__ ((section("ImageWork_RAM")));  /* BinarizationAdaptive */
////static uint8_t frame_RAM_D[R_BCD_CAMERA_HEIGHT * R_BCD_CAMERA_WIDTH]          __attribute__ ((section("ImageWork_RAM")));  /* BinarizationAdaptive */
//static uint8_t work3[((R_BCD_CAMERA_HEIGHT * R_BCD_CAMERA_WIDTH) / 64) + 2]   __attribute__ ((section("ImageWork_RAM")));  /* Work area for BinarizationAdaptive */
////static uint8_t work4[R_BCD_CAMERA_HEIGHT * R_BCD_CAMERA_WIDTH]   			  __attribute__ ((section("ImageWork_RAM")));  /* Work area for FindContours */
//static uint8_t work2[R_BCD_CAMERA_HEIGHT * R_BCD_CAMERA_WIDTH]                __attribute__ ((section("ImageWork_RAM")));  /* Work area for Canny Hysterisis and Find Conturs */
//static uint8_t work_find_contours[R_BCD_CAMERA_HEIGHT * R_BCD_CAMERA_WIDTH]                __attribute__ ((section("ImageWork_RAM")));  /* Work area Find Conturs */
////static uint8_t work_canny_calculate[((R_BCD_CAMERA_HEIGHT +2) * R_BCD_CAMERA_WIDTH)*2]       __attribute__ ((section("ImageWork_RAM")));  /* Work area for Canny Calculate */
////static uint8_t work_canny_hyst[R_BCD_CAMERA_HEIGHT * R_BCD_CAMERA_WIDTH]                __attribute__ ((section("ImageWork_RAM")));  /* Work area for Canny Hysterisis and Find Conturs */
////static uint8_t thinning_result_buf[R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT+(2*3)) * 2] __attribute__ ((section("ImageWork_RAM")));
//static void cb_drp_finish(uint8_t id);
////static void write_harris_data(uint8_t *psrc, uint32_t *pdst);
//static uint32_t bcd_drp_check_empty_contours(uint32_t i);
//
///**********************************************************************************************************************
//* Function Name: cb_drp_finish
//* Description  : This function is a callback function called from the
//*              : DRP driver at the finish of the DRP library processing.
//* Arguments    : id
//*              :   The ID of the DRP library that finished processing.
//* Return Value : -
//**********************************************************************************************************************/
//static void cb_drp_finish(uint8_t id)
//{
//    uint32_t tile_no;
//
//    /* Change the operation state of the DRP library notified by the argument to finish */
//    for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//    {
//        if (drp_lib_id[tile_no] == id)
//        {
//            drp_lib_status[tile_no] = DRP_FINISH;
//            break;
//        }
//    }
//
//    return;
//}
///**********************************************************************************************************************
//* End of function cb_drp_finish
//**********************************************************************************************************************/
//
///**********************************************************************************************************************
//* Function Name: sample_main
//* Description  : First function called after initialization is completed
//* Arguments    : -
//* Return Value : -
//**********************************************************************************************************************/
//void sample_main(void)
//{
//    int32_t frame_buf_id;
//    uint8_t buf[80];
//    int32_t ret_val;
//    uint32_t us;
//    uint32_t input_bufadr;
//    uint32_t output_bufadr;
//    uint32_t work_bufadr;
//    uint32_t work_bufadr_bin2med;
////    uint32_t work_bufadr_med2thin;
//    uint32_t work_bufadr_med2dilate;
//    uint32_t work_bufadr_med2contours;
//    uint32_t extra_bufadr;
////    uint32_t intermediate_bufadr;
//    uint32_t tile_no;
//    uint8_t * p_input_bufadr;
//    uint8_t * p_output_bufadr;
//    uint8_t * p_work_bufadr;
//    uint8_t * p_work_bufadr_bin2med;
////    uint8_t * p_work_bufadr_med2thin;
//    uint8_t * p_work_bufadr_med2dilate;
//    uint8_t * p_extra_bufadr;
////    uint32_t * p_frame_ram1;
////    uint8_t * p_work_bufadr_med2dilate;
//    uint8_t * p_work_bufadr_med2contours;
////    uint32_t bufsize_thinning;
////    uint32_t bufsize;
////    uint8_t * p_frame_ram1;
////    uint8_t * p_frame_ram2;
////    uint8_t * p_frame_ram3;
//
//    /* Initialization of VIN and MIPI driver */
//    R_BCD_CameraInit();
//
//    /* Initialization of LCD driver */
//    R_BCD_LcdInit();
//
//    /* Capture Start */
//    R_BCD_CameraCaptureStart();
//
//    /* Initialize of Performance counter */
//    PerformInit();
//
//    /********************************/
//    /* Initialization of DRP driver */
//    /********************************/
//    R_DK2_Initialize();
//
//    /* main loop */
//    while (1)
//    {
////    	R_BCD_LcdClearGraphicsBuffer();
//        /* Wait until camera capture is complete */
//        while ((frame_buf_id = R_BCD_CameraGetCaptureStatus()) == R_BCD_CAMERA_NOT_CAPTURED)
//        {
//            /* DO NOTHING */
//        }
//        p_input_bufadr  			= R_BCD_CameraGetFrameAddress(frame_buf_id);
//        p_output_bufadr 			= R_BCD_LcdGetVramAddress();
//        p_work_bufadr   			= (uint8_t *)&work_buf[0];
//        p_work_bufadr_bin2med 		= (uint8_t *)&work_buf_2[0];
//        p_work_bufadr_med2contours 	= (uint8_t *)&work_buf_3[0];
//        p_work_bufadr_med2dilate 	= (uint8_t *)&work_buf_5[0];
//
//
//        /* convert to phisical address */
//        R_MMU_VAtoPA((uint32_t)p_input_bufadr, &input_bufadr);
//
//        /* convert to phisical address */
//        R_MMU_VAtoPA((uint32_t)p_output_bufadr, &output_bufadr);
//
//        /* convert to phisical address */
//        R_MMU_VAtoPA((uint32_t)p_work_bufadr, &work_bufadr);
//
//        /* convert to phisical address */
//        R_MMU_VAtoPA((uint32_t)p_work_bufadr_bin2med, &work_bufadr_bin2med);
//
//        /* convert to phisical address */
//        R_MMU_VAtoPA((uint32_t)p_work_bufadr_med2contours, &work_bufadr_med2contours);
//
//        /* convert to phisical address */
//        R_MMU_VAtoPA((uint32_t)p_work_bufadr_med2dilate, &work_bufadr_med2dilate);
//
////        p_extra_bufadr 				= (uint8_t *)&work2[0];
////        R_MMU_VAtoPA((uint32_t)p_extra_bufadr, &extra_bufadr);
//
//
//
//
////        printf("sizeof input to b2g: %li", sizeof(input_bufadr));
//        printf("Hi0 \n");
//
//        /******************************/
//        /* Load DRP Library           */
//        /*        +-----------------+ */
//        /* tile 0 | Bayer2Grayscale | */
//        /*        +-----------------+ */
//        /* tile 1 | Bayer2Grayscale | */
//        /*        +-----------------+ */
//        /* tile 2 | Bayer2Grayscale | */
//        /*        +-----------------+ */
//        /* tile 3 | Bayer2Grayscale | */
//        /*        +-----------------+ */
//        /* tile 4 | Bayer2Grayscale | */
//        /*        +-----------------+ */
//        /* tile 5 | Bayer2Grayscale | */
//        /*        +-----------------+ */
//        /******************************/
//        ret_val = R_DK2_Load(&g_drp_lib_bayer2grayscale[0],
//                            R_DK2_TILE_0 | R_DK2_TILE_1 | R_DK2_TILE_2 | R_DK2_TILE_3 | R_DK2_TILE_4 | R_DK2_TILE_5,
//                            R_DK2_TILE_PATTERN_1_1_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
//        DRP_DRV_ASSERT(ret_val);
////        printf("b2g load ret val = %d", ret_val);
//
//        /************************/
//        /* Activate DRP Library */
//        /************************/
//        ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
//                                | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], 0);
//        DRP_DRV_ASSERT(ret_val);
////        printf("b2g activate ret val = %d", ret_val);
//
//        /* Set start time of process*/
//        PerformSetStartTime(0);;
//
//
//
//        /***************************************/
//        /* Set R_DK2_Start function parameters */
//        /***************************************/
//        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//        {
//            /* Set the address of buffer to be read/write by DRP */
//            param_b2g[tile_no].src = input_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//                                                                                                            * tile_no);
//            param_b2g[tile_no].dst = work_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//                                                                                                            * tile_no);
////            param_b2g[tile_no].dst = output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////                                                                                                             * tile_no);
//
//            /* Set Image size */
//            param_b2g[tile_no].width = R_BCD_CAMERA_WIDTH;
//            param_b2g[tile_no].height = R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM;
//
//            /* Set whether to perform top or bottom edge border processing. */
//            param_b2g[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
//            param_b2g[tile_no].bottom = (tile_no == TILE_5) ? 1 : 0;
//
//            /* Initialize variables to be used in termination judgment of the DRP library */
//            drp_lib_status[tile_no] = DRP_NOT_FINISH;
//
//            /*********************/
//            /* Start DRP Library */
//            /*********************/
//            ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_b2g[tile_no], sizeof(r_drp_bayer2grayscale_t));
//            DRP_DRV_ASSERT(ret_val);
////            printf("b2g start ret val = %d", ret_val);
//        }
//
//        /***************************************/
//        /* Wait until DRP processing is finish */
//        /***************************************/
//        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//        {
//            while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
//            {
//                /* DO NOTHING */
//            }
//        }
//
//        /* Set end time of process */
//        PerformSetEndTime(0);
//        printf("Bayer2Grayscale End \n");
//
//
//        /**********************/
//        /* Unload DRP Library */
//        /**********************/
//        ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
//                                                            | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], &drp_lib_id[0]);
//        DRP_DRV_ASSERT(ret_val);
////        printf("b2g unload ret val = %d", ret_val);
//
////        /* Clear the current capture state and enable the detection of the next capture completion */
////        R_BCD_CameraClearCaptureStatus();
////
////        /* Capture Start */
////        R_BCD_CameraCaptureStart();
//
////        /* Display image processing result */
////        R_BCD_LcdSwapVideoBuffer();
//
////        printf("sizeof output of b2g: %li", sizeof(work_bufadr));
//
//
//
//        /******************************************************************************************************/
//        /************************************/
//        /* Load DRP Library                 */
//        /*        +-----------------------+ */
//        /* tile 0 |                       | */
//        /*        +                       + */
//        /* tile 1 | BinarizationAdaptive  | */
//        /*        +                       + */
//        /* tile 2 |                       | */
//        /*        +-----------------------+ */
//        /* tile 3 |                       | */
//        /*        +                       + */
//        /* tile 4 |                       | */
//        /*        |                       | */
//        /* tile 5 |                       | */
//        /*        +-----------------------+ */
//        /************************************/
//
//		/*############    -  BinarizationAdaptive  -    ##############*/
//
//
//
//		/*****************************************/
//		/* Load DRP Library BinarizationAdaptive */
//		/*****************************************/
//		ret_val = R_DK2_Load(&g_drp_lib_binarization_adaptive[0],
//				R_DK2_TILE_0,
//				R_DK2_TILE_PATTERN_3_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
//		DRP_DRV_ASSERT(ret_val);
////		printf("bin-ad load ret val = %d", ret_val);
//
//		/*****************************************/
//		/* Activate DRP Lib BinarizationAdaptive */
//		/*****************************************/
//		ret_val = R_DK2_Activate(drp_lib_id[TILE_0], 0);
//		DRP_DRV_ASSERT(ret_val);
////		printf("bin-ad activate ret val = %d", ret_val);
//
//		/* Set start time of process*/
//		PerformSetStartTime(1);
//
//		/****************************************************************/
//		/* Set R_DK2_Start function parameters for BinarizationAdaptive */
//		/****************************************************************/
//
//		param_binarization_adaptive.src        = work_bufadr;     					/* Address of image to be binarized. */
//		param_binarization_adaptive.dst        = work_bufadr_bin2med;       		/* Address to output binarized result. */
////		param_binarization_adaptive.dst        = output_bufadr;
//		param_binarization_adaptive.width      = (uint16_t)R_BCD_CAMERA_WIDTH;   	/* The horizontal size (pixels) of the image to be binarized. */
//		param_binarization_adaptive.height     = (uint16_t)R_BCD_CAMERA_HEIGHT;  	/* The vertical size (pixels) of the image to be binarized. */
//		param_binarization_adaptive.work       = (uint32_t)&work3[0];            	/* Address of the work buffer used by the library. */
//		param_binarization_adaptive.range      = 0x03;                            	/* A luminance difference to judge whether it is effective average luminance.(8x8 pixel) */
//
//		/* Initialize variables to be used in termination judgment of the DRP application */
//		drp_lib_status[TILE_0] = DRP_NOT_FINISH;
//
//		/******************************************/
//		/* Start DRP Library BinarizationAdaptive */
//		/******************************************/
//		ret_val = R_DK2_Start(drp_lib_id[TILE_0], (void *)&param_binarization_adaptive, sizeof(r_drp_binarization_adaptive_t));
//		DRP_DRV_ASSERT(ret_val);
////		printf("bin-ad start ret val = %d", ret_val);
//
//
//		/*******************************************************/
//		/* Wait until BinarizationAdaptive processing finished */
//		/*******************************************************/
//		while (drp_lib_status[TILE_0] == DRP_NOT_FINISH);  // BinarizationAdaptive
//
//		/*******************************************/
//		/* Unload DRP library BinarizationAdaptive */
//		/*******************************************/
//		ret_val = R_DK2_Unload(drp_lib_id[TILE_0], &drp_lib_id[TILE_0]);
//		DRP_DRV_ASSERT(ret_val);
////		printf("bin-ad unload ret val = %d", ret_val);
//
//		/* Set end time of DRP processing */
//		PerformSetEndTime(1);
//		printf("BinarizationAdaptive End \n");
//
//		/******************************************************************************************************/
//
//
////		/******************************************************************************************************/
////		/******************************/
////		/* Load DRP Library           */
////		/*        +-----------------+ */
////		/* tile 0 |  gaussian blur	| */
////		/*        +-----------------+ */
////		/* tile 1 |  gaussian blur	| */
////		/*        +-----------------+ */
////		/* tile 2 |  gaussian blur	| */
////		/*        +-----------------+ */
////		/* tile 3 |  gaussian blur	| */
////		/*        +-----------------+ */
////		/* tile 4 |  gaussian blur	| */
////		/*        +-----------------+ */
////		/* tile 5 |  gaussian blur	| */
////		/*        +-----------------+ */
////		/******************************/
////		ret_val = R_DK2_Load(&g_drp_lib_gaussian_blur[0],
////				R_DK2_TILE_0 | R_DK2_TILE_1 | R_DK2_TILE_2 | R_DK2_TILE_3 | R_DK2_TILE_4 | R_DK2_TILE_5,
////				R_DK2_TILE_PATTERN_1_1_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
////		DRP_DRV_ASSERT(ret_val);
////		//        printf("b2g load ret val = %d", ret_val);
////
////		/************************/
////		/* Activate DRP Library */
////		/************************/
////		ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
////																										   | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], 0);
////		DRP_DRV_ASSERT(ret_val);
////		//        printf("b2g activate ret val = %d", ret_val);
////
////		/* Set start time of process*/
////		PerformSetStartTime(6);;
////
////
////
////		/***************************************/
////		/* Set R_DK2_Start function parameters */
////		/***************************************/
////		for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
////		{
////			/* Set the address of buffer to be read/write by DRP */
////			param_gaussian_blur[tile_no].src = work_bufadr_bin2med + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////					* tile_no);
////			//        	param_gaussian_blur[tile_no].dst = work_bufadr_bin2med + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////			//        			* tile_no);
////			param_gaussian_blur[tile_no].dst = output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////					* tile_no);
////
////			/* Set Image size */
////			param_gaussian_blur[tile_no].width = R_BCD_CAMERA_WIDTH;
////			param_gaussian_blur[tile_no].height = R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM;
////
////			/* Set whether to perform top or bottom edge border processing. */
////			param_gaussian_blur[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
////			param_gaussian_blur[tile_no].bottom = (tile_no == TILE_5) ? 1 : 0;
////
////			/* Initialize variables to be used in termination judgment of the DRP library */
////			drp_lib_status[tile_no] = DRP_NOT_FINISH;
////
////			/*********************/
////			/* Start DRP Library */
////			/*********************/
////			ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_gaussian_blur[tile_no], sizeof(r_drp_gaussian_blur_t));
////			DRP_DRV_ASSERT(ret_val);
////			//            printf("b2g start ret val = %d", ret_val);
////		}
////
////		/***************************************/
////		/* Wait until DRP processing is finish */
////		/***************************************/
////		for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
////		{
////			while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
////			{
////				/* DO NOTHING */
////			}
////		}
////
////		/* Set end time of process */
////		PerformSetEndTime(6);
////		printf("Hi1 \n");
////
////
////		/**********************/
////		/* Unload DRP Library */
////		/**********************/
////		ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
////																										 | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], &drp_lib_id[0]);
////		DRP_DRV_ASSERT(ret_val);
////
////
////		/******************************************************************************************************/
//
//
//
//		/******************************************************************************************************/
//		/**************************/
//		/* Load DRP Library       */
//		/*        +-------------+ */
//		/* tile 0 | Median blur | */
//		/*        +-------------+ */
//		/* tile 1 | Median blur | */
//		/*        +-------------+ */
//		/* tile 2 | Median blur | */
//		/*        +-------------+ */
//		/* tile 3 | Median blur | */
//		/*        +-------------+ */
//		/* tile 4 | Median blur | */
//		/*        +-------------+ */
//		/* tile 5 | Median blur | */
//		/*        +-------------+ */
//		/**************************/
//		ret_val = R_DK2_Load(&g_drp_lib_median_blur[0],
//				R_DK2_TILE_0 | R_DK2_TILE_1 | R_DK2_TILE_2 | R_DK2_TILE_3 | R_DK2_TILE_4 | R_DK2_TILE_5,
//				R_DK2_TILE_PATTERN_1_1_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
//		DRP_DRV_ASSERT(ret_val);
//		/************************/
//		/* Activate DRP Library */
//		/************************/
//		ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
//																										   | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], 0);
//		DRP_DRV_ASSERT(ret_val);
//		/* Set start time of process*/
//		PerformSetStartTime(2);
//		/***************************************/
//		/* Set R_DK2_Start function parameters */
//		/***************************************/
//		for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//		{
//			/* Set the address of buffer to be read/write by DRP */
//			param_median[tile_no].src = work_bufadr_bin2med + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//					* tile_no);
//			param_median[tile_no].dst = work_bufadr_med2dilate + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//					* tile_no);
////			param_median[tile_no].dst = output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////								* tile_no);
////			param_median[tile_no].dst = (uint32_t)&p_work_bufadr_med2thin[0];   + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////					* tile_no);
////			R_MMU_VAtoPA((uint32_t)param_median[tile_no].dst, &(param_median[tile_no].dst ));
//
//			/* Set Image size */
//			param_median[tile_no].width = R_BCD_CAMERA_WIDTH;
//			param_median[tile_no].height = R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM;
//			/* Set whether to perform top or bottom edge border processing. */
//			param_median[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
//			param_median[tile_no].bottom = (tile_no == TILE_5) ? 1 : 0;
//			/* Initialize variables to be used in termination judgment of the DRP library */
//			drp_lib_status[tile_no] = DRP_NOT_FINISH;
//			/*********************/
//			/* Start DRP Library */
//			/*********************/
//			ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_median[tile_no], sizeof(r_drp_median_blur_t));
//			DRP_DRV_ASSERT(ret_val);
//		}
//
//		/***************************************/
//		/* Wait until DRP processing is finish */
//		/***************************************/
//		for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//		{
//			while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
//			{
//				/* DO NOTHING */
//			}
//		}
//
//		/* Set end time of process */
//		PerformSetEndTime(2);
//		/**********************/
//		/* Unload DRP library */
//		/**********************/
//		ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3] |
//				drp_lib_id[TILE_4] | drp_lib_id[TILE_5], &drp_lib_id[TILE_0]);
//		DRP_DRV_ASSERT(ret_val);
//
//
//		//		/* Clear the current capture state and enable the detection of the next capture completion */
//		//		R_BCD_CameraClearCaptureStatus();
//		//
//		//		/* Capture Start */
//		//		R_BCD_CameraCaptureStart();
//
////		/* Display image processing result */
////		R_BCD_LcdSwapVideoBuffer();
//
//		printf("MedianBlur End \n");
//
////		printf("sizeof output of binarization: %li", sizeof(work_bufadr_bin2med));
//
//		/******************************************************************************************************/
//
//
////        /******************************************************************************************************/
////        /******************************/
////        /* Load DRP Library           */
////        /*        +-----------------+ */
////        /* tile 0 |                 | */
////        /*        +                 + */
////        /* tile 1 |    Thinning     | */
////        /*        +                 + */
////        /* tile 2 |                 | */
////        /*        +-----------------+ */
////        /* tile 3 |                 | */
////        /*        +                 + */
////        /* tile 4 |    Thinning     | */
////        /*        +                 + */
////        /* tile 5 |                 | */
////        /*        +-----------------+ */
////        /******************************/
////        ret_val = R_DK2_Load(&g_drp_lib_thinning[0], R_DK2_TILE_0 | R_DK2_TILE_3,
////        		R_DK2_TILE_PATTERN_3_3, NULL, &cb_drp_finish, &drp_lib_id[0]);
////        DRP_DRV_ASSERT(ret_val);
////
////        /********************/
////        /* Activate DRP Lib */
////        /********************/
////        ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_3], 0);
////        DRP_DRV_ASSERT(ret_val);
////
////        /* Set start time of process*/
////        PerformSetStartTime(3);
////
////        /***************************************/
////        /* Set R_DK2_Start function parameters */
////        /***************************************/
////        for (tile_no = TILE_0; tile_no <= TILE_3; tile_no += 3)
////        {
////        	/* Set Image size */
////        	param_thinning[tile_no].width = R_BCD_CAMERA_WIDTH;
////        	param_thinning[tile_no].height = (R_BCD_CAMERA_HEIGHT / 2);
////
////        	/* Set Buffer size */
////        	bufsize_thinning = (uint32_t)(param_thinning[tile_no].width * param_thinning[tile_no].height);
////
////        	/* Set the address of buffer to be read/write by DRP */
////        	param_thinning[tile_no].src = work_bufadr_med2thin + ((tile_no / 3) * bufsize_thinning);
//////        	param_thinning[tile_no].dst = output_bufadr  + ((tile_no / 3) * bufsize_thinning);
////        	param_thinning[tile_no].dst = output_bufadr  + ((tile_no / 3) * bufsize_thinning);
////
////
////        	/* Set additional information (currently no additional information) */
////        	param_thinning[tile_no].result =
////        			(uint32_t)&thinning_result_buf[((tile_no / 3) * (bufsize_thinning + (R_BCD_CAMERA_WIDTH*2) ))*2];
////        	param_thinning[tile_no].threshold = 0x01;
////        	param_thinning[tile_no].reverse = 1;
////
////        	/* Set whether to perform top or bottom edge border processing. */
////        	param_thinning[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
////        	param_thinning[tile_no].bottom = (tile_no == TILE_3) ? 1 : 0;
////
////        	param_thinning[tile_no].step = 0;
////
////
////
////        	/* Initialize variables to be used in termination judgment of the DRP library */
////        	drp_lib_status[tile_no] = DRP_NOT_FINISH;
////
////        	/*********************/
////        	/* Start DRP Library */
////        	/*********************/
////        	ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_thinning[tile_no],
////        			sizeof(r_drp_thinning_t));
////        	DRP_DRV_ASSERT(ret_val);
////        }
////
////        /***************************************/
////        /* Wait until DRP processing is finish */
////        /***************************************/
////        for (tile_no = TILE_0; tile_no <= TILE_3; tile_no += 3)
////        {
////        	/***************************************/
////        	/* Wait until DRP processing is finish */
////        	/***************************************/
////        	while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
////        	{
////        		/* DO NOTHING */
////        	}
////        }
////
////        /* Set end time of DRP processing */
////        PerformSetEndTime(3);
////
////        /**********************/
////        /* Unload DRP library */
////        /**********************/
////        ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_3] , &drp_lib_id[TILE_0]);
////        DRP_DRV_ASSERT(ret_val);
////
////
////        /******************************************************************************************************/
//
//
////        /******************************************************************************************************/
////        /**************************/
////        /* Load DRP Library       */
////        /*        +-------------+ */
////        /* tile 0 |   Dilate 	| */
////        /*        +-------------+ */
////        /* tile 1 |   Dilate 	| */
////        /*        +-------------+ */
////        /* tile 2 |   Dilate 	| */
////        /*        +-------------+ */
////        /* tile 3 |   Dilate 	| */
////        /*        +-------------+ */
////        /* tile 4 |   Dilate 	| */
////        /*        +-------------+ */
////        /* tile 5 |   Dilate 	| */
////        /*        +-------------+ */
////        /**************************/
////        ret_val = R_DK2_Load(&g_drp_lib_dilate[0],
////        		R_DK2_TILE_0 | R_DK2_TILE_1 | R_DK2_TILE_2 | R_DK2_TILE_3 | R_DK2_TILE_4 | R_DK2_TILE_5,
////				R_DK2_TILE_PATTERN_1_1_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
////        DRP_DRV_ASSERT(ret_val);
////        /************************/
////        /* Activate DRP Library */
////        /************************/
////        ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
////																										   | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], 0);
////        DRP_DRV_ASSERT(ret_val);
////        /* Set start time of process*/
////        PerformSetStartTime(2);
////        /***************************************/
////        /* Set R_DK2_Start function parameters */
////        /***************************************/
////        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
////        {
////        	/* Set the address of buffer to be read/write by DRP */
////        	param_dilate[tile_no].src = work_bufadr_med2thin + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////        			* tile_no);
////        	param_dilate[tile_no].dst = output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////        			* tile_no);
////        	/* Set Image size */
////        	param_dilate[tile_no].width = R_BCD_CAMERA_WIDTH;
////        	param_dilate[tile_no].height = R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM;
////        	/* Set whether to perform top or bottom edge border processing. */
////        	param_dilate[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
////        	param_dilate[tile_no].bottom = (tile_no == TILE_5) ? 1 : 0;
////        	/* Initialize variables to be used in termination judgment of the DRP library */
////        	drp_lib_status[tile_no] = DRP_NOT_FINISH;
////        	/*********************/
////        	/* Start DRP Library */
////        	/*********************/
////        	ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_dilate[tile_no], sizeof(r_drp_dilate_t));
////        	DRP_DRV_ASSERT(ret_val);
////        }
////
////        /***************************************/
////        /* Wait until DRP processing is finish */
////        /***************************************/
////        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
////        {
////        	while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
////        	{
////        		/* DO NOTHING */
////        	}
////        }
////
////        /* Set end time of process */
////        PerformSetEndTime(2);
////        /**********************/
////        /* Unload DRP library */
////        /**********************/
////        ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3] |
////        		drp_lib_id[TILE_4] | drp_lib_id[TILE_5], &drp_lib_id[TILE_0]);
////        DRP_DRV_ASSERT(ret_val);
//
//
//
//		/******************************************************************************************************/
//		/******************************/
//		/* Load DRP Library           */
//		/*        +-----------------+ */
//		/* tile 0 | 	Sobel		| */
//		/*        +-----------------+ */
//		/* tile 1 | 	Sobel		| */
//		/*        +-----------------+ */
//		/* tile 2 | 	Sobel		| */
//		/*        +-----------------+ */
//		/* tile 3 | 	Sobel		| */
//		/*        +-----------------+ */
//		/* tile 4 | 	Sobel		| */
//		/*        +-----------------+ */
//		/* tile 5 | 	Sobel		| */
//		/*        +-----------------+ */
//		/******************************/
//		ret_val = R_DK2_Load(&g_drp_lib_sobel[0],
//				R_DK2_TILE_0 | R_DK2_TILE_1 | R_DK2_TILE_2 | R_DK2_TILE_3 | R_DK2_TILE_4 | R_DK2_TILE_5,
//				R_DK2_TILE_PATTERN_1_1_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
//		DRP_DRV_ASSERT(ret_val);
//		//        printf("b2g load ret val = %d", ret_val);
//
//		/************************/
//		/* Activate DRP Library */
//		/************************/
//		ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
//																										   | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], 0);
//		DRP_DRV_ASSERT(ret_val);
//		//        printf("b2g activate ret val = %d", ret_val);
//
//		/* Set start time of process*/
//		PerformSetStartTime(7);;
//
//
//
//		/***************************************/
//		/* Set R_DK2_Start function parameters */
//		/***************************************/
//		for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//		{
//			/* Set the address of buffer to be read/write by DRP */
//			param_sobel[tile_no].src = work_bufadr_med2dilate + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//					* tile_no);
//			//            param_b2g[tile_no].dst = work_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//			//                                                                                                            * tile_no);
//			param_sobel[tile_no].dst = output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//					* tile_no);
//
//			/* Set Image size */
//			param_sobel[tile_no].width = R_BCD_CAMERA_WIDTH;
//			param_sobel[tile_no].height = R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM;
//
//			/* Set whether to perform top or bottom edge border processing. */
//			param_sobel[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
//			param_sobel[tile_no].bottom = (tile_no == TILE_5) ? 1 : 0;
//
//			/* Initialize variables to be used in termination judgment of the DRP library */
//			drp_lib_status[tile_no] = DRP_NOT_FINISH;
//
//			/*********************/
//			/* Start DRP Library */
//			/*********************/
//			ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_sobel[tile_no], sizeof(r_drp_sobel_t));
//			DRP_DRV_ASSERT(ret_val);
////			ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_sobel[tile_no], sizeof(r_drp_prewitt_t));
////			DRP_DRV_ASSERT(ret_val);
//			//            printf("b2g start ret val = %d", ret_val);
//		}
//
//		/***************************************/
//		/* Wait until DRP processing is finish */
//		/***************************************/
//		for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//		{
//			while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
//			{
//				/* DO NOTHING */
//			}
//		}
//
//		/* Set end time of process */
//		PerformSetEndTime(7);
//		printf("Sobel End \n");
//
//
//		/**********************/
//		/* Unload DRP Library */
//		/**********************/
//		ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
//																										 | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], &drp_lib_id[0]);
//		DRP_DRV_ASSERT(ret_val);
//
//
//		/******************************************************************************************************/
//
//
////		/***********************************/
////		/* Load DRP Library                */
////		/*        +----------------------+ */
////		/* tile 0 |                      | */
////		/*        +   Canny Calculate    + */
////		/* tile 1 |                      | */
////		/*        +----------------------+ */
////		/* tile 2 | 					 | */
////		/*        +----------------------+ */
////		/* tile 3 | 					 | */
////		/*        +----------------------+ */
////		/* tile 4 |                      | */
////		/*        +----------------------+ */
////		/* tile 5 |                      | */
////		/*        +----------------------+ */
////		/***********************************/
////
////		/* Set start time of process*/
////		PerformSetStartTime(8);
////
////
////		/*##################################*/
////		/* load DRP Library Canny Calculate */
////		/*##################################*/
////
////		ret_val = R_DK2_Load(&g_drp_lib_canny_calculate[0],
////							 R_DK2_TILE_0,
////							 R_DK2_TILE_PATTERN_2_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
////		DRP_DRV_ASSERT(ret_val);
////
////		/*##################################*/
////		/* Activate DRP Lib Canny Calculate */
////		/*##################################*/
////		ret_val = R_DK2_Activate(drp_lib_id[TILE_0], 0);
////		DRP_DRV_ASSERT(ret_val);
////
////
////		/***************************************/
////		/* Set R_DK2_Start function parameters */
////		/***************************************/
//////		tile_no = TILE_0;
////
////		/* Set Image size */
////		param_canny_cal.width  = R_BCD_CAMERA_WIDTH;
////		param_canny_cal.height = R_BCD_CAMERA_HEIGHT;
////
////		/* Set Buffer size */
//////		bufsize = (uint32_t)(param_canny_cal.width * param_canny_cal.height);
////
////		/* Set the address of buffer to be read/write by DRP */
////		param_canny_cal.src = work_bufadr_med2thin;
////		param_canny_cal.dst = work_bufadr_med2contours;
//////		R_MMU_VAtoPA((uint32_t)param_canny_cal[tile_no].src, &(param_canny_cal[tile_no].src ));
//////		R_MMU_VAtoPA((uint32_t)param_canny_cal[tile_no].dst, &(param_canny_cal[tile_no].dst ));
////
////		/* Set additional information (currently no additional information) */
////		param_canny_cal.work = (uint32_t)&work_canny_calculate[0];
//////		param_canny_cal.work = (uint32_t)&p_frame_ram1[0];
////		R_MMU_VAtoPA((uint32_t)param_canny_cal.work, &(param_canny_cal.work ));
////
////		param_canny_cal.threshold_high = STRONG_LEVEL;
////		param_canny_cal.threshold_low = WEAK_LEVEL;
////
////		/* Set whether to perform top or bottom edge border processing. */
////		param_canny_cal.top    = (tile_no == TILE_0) ? 1 : 0;
////		param_canny_cal.bottom = (tile_no == TILE_0) ? 1 : 0;
////
////		/* Initialize variables to be used in termination judgment of the DRP library */
////		drp_lib_status[tile_no] = DRP_NOT_FINISH;
////
////		/*********************/
////		/* Start DRP Library */
////		/*********************/
////		ret_val = R_DK2_Start(drp_lib_id[TILE_0], (void *)&param_canny_cal, sizeof(r_drp_canny_calculate_t));
////		DRP_DRV_ASSERT(ret_val);
////
////		/***************************************/
////		/* Wait until DRP processing is finish */
////		/***************************************/
////		while (drp_lib_status[TILE_0] == DRP_NOT_FINISH);
////
////		/**********************/
////		/* Unload DRP library */
////		/**********************/
////		ret_val = R_DK2_Unload(drp_lib_id[TILE_0], &drp_lib_id[TILE_0]);
////		DRP_DRV_ASSERT(ret_val);
////
////		/* Set end time of DRP processing */
////		PerformSetEndTime(8);
////
////		printf("Hi4 \n");
////
////
//////		ret_val = R_DK2_Load(&g_drp_lib_canny_calculate[0],
//////							 R_DK2_TILE_0,
//////							 R_DK2_TILE_PATTERN_2_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
//////		DRP_DRV_ASSERT(ret_val);
//////
//////		/*##################################*/
//////		/* Activate DRP Lib Canny Calculate */
//////		/*##################################*/
//////		ret_val = R_DK2_Activate(drp_lib_id[TILE_0], 0);
//////		DRP_DRV_ASSERT(ret_val);
//////
//////		PerformSetStartTime(3);
//////
//////		/***************************************/
//////		/* Set R_DK2_Start function parameters */
//////		/***************************************/
//////		tile_no = TILE_0;
//////
//////		/* Set Image size */
//////		param_canny_cal[tile_no].width  = R_BCD_CAMERA_WIDTH;
//////		param_canny_cal[tile_no].height = R_BCD_CAMERA_HEIGHT;
//////
//////		/* Set Buffer size */
//////		bufsize = (uint32_t)(param_canny_cal[tile_no].width * param_canny_cal[tile_no].height);
//////
//////		/* Set the address of buffer to be read/write by DRP */
//////		param_canny_cal[tile_no].src = work_bufadr_med2thin;
//////		param_canny_cal[tile_no].dst = work_bufadr_med2contours;
////////		R_MMU_VAtoPA((uint32_t)param_canny_cal[tile_no].src, &(param_canny_cal[tile_no].src ));
////////		R_MMU_VAtoPA((uint32_t)param_canny_cal[tile_no].dst, &(param_canny_cal[tile_no].dst ));
//////
//////		/* Set additional information (currently no additional information) */
////////		param_canny_cal[tile_no].work = (uint32_t)p_frame_ram1[0];
//////		param_canny_cal[tile_no].work = (uint32_t)&p_frame_ram1[(tile_no * (bufsize + (R_BCD_CAMERA_WIDTH*2) ))*2];
//////		R_MMU_VAtoPA((uint32_t)param_canny_cal[tile_no].work, &(param_canny_cal[tile_no].work ));
//////
//////		param_canny_cal[tile_no].threshold_high = STRONG_LEVEL;
//////		param_canny_cal[tile_no].threshold_low = WEAK_LEVEL;
//////
//////		/* Set whether to perform top or bottom edge border processing. */
//////		param_canny_cal[tile_no].top    = (tile_no == TILE_0) ? 1 : 0;
//////		param_canny_cal[tile_no].bottom = (tile_no == TILE_0) ? 1 : 0;
//////
//////		/* Initialize variables to be used in termination judgment of the DRP library */
//////		drp_lib_status[tile_no] = DRP_NOT_FINISH;
//////
//////		/*********************/
//////		/* Start DRP Library */
//////		/*********************/
//////		ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_canny_cal[tile_no / 2], sizeof(r_drp_canny_calculate_t));
//////		DRP_DRV_ASSERT(ret_val);
//////
//////		/***************************************/
//////		/* Wait until DRP processing is finish */
//////		/***************************************/
//////		while (drp_lib_status[TILE_0] == DRP_NOT_FINISH);
//////
//////		/**********************/
//////		/* Unload DRP library */
//////		/**********************/
//////		ret_val = R_DK2_Unload(drp_lib_id[TILE_0], &drp_lib_id[TILE_0]);
//////		DRP_DRV_ASSERT(ret_val);
//////
//////		/* Set end time of DRP processing */
//////		PerformSetEndTime(3);
////
////
////
////
////		/*******************************/
////		/* Load DRP Library            */
////		/*        +------------------+ */
////		/* tile 0 |                  | */
////		/*        +                  + */
////		/* tile 1 |                  | */
////		/*        +                  + */
////		/* tile 2 |                  | */
////		/*        + Canny Hysterisis + */
////		/* tile 3 |                  | */
////		/*        +                  + */
////		/* tile 4 |                  | */
////		/*        +                  + */
////		/* tile 5 |                  | */
////		/*        +------------------+ */
////		/*******************************/
////
////		/* Set start time of Canny Hyst process */
////		PerformSetStartTime(4);
////
////		ret_val = R_DK2_Load(&g_drp_lib_canny_hysterisis[0],
////							 R_DK2_TILE_0,
////							 R_DK2_TILE_PATTERN_6, NULL, &cb_drp_finish, &drp_lib_id[0]);
////		DRP_DRV_ASSERT(ret_val);
////
////		printf("CH load \n");
////
////		/************************/
////		/* Activate DRP Library */
////		/************************/
////		ret_val = R_DK2_Activate(drp_lib_id[TILE_0], 0);
////		DRP_DRV_ASSERT(ret_val);
////
////		printf("CH activate \n");
////
////		/***************************************/
////		/* Set R_DK2_Start function parameters */
////		/***************************************/
////		/* Set Image size */
////		param_canny_hyst.width = R_BCD_CAMERA_WIDTH;
////		param_canny_hyst.height = R_BCD_CAMERA_HEIGHT;
////
////		/* Set the address of buffer to be read/write by DRP */
////		param_canny_hyst.src = work_bufadr_med2contours;
////		param_canny_hyst.dst = output_bufadr;
//////		R_MMU_VAtoPA((uint32_t)param_canny_hyst.src, &(param_canny_hyst.src ));
//////		R_MMU_VAtoPA((uint32_t)param_canny_hyst.dst, &(param_canny_hyst.dst ));
////
////		/* Set additional information (currently no additional information) */
////		param_canny_hyst.work = (uint32_t)&work_canny_hyst[0];
//////		param_canny_hyst.work = (uint32_t)&p_frame_ram2[0];
////		R_MMU_VAtoPA((uint32_t)param_canny_hyst.work, &(param_canny_hyst.work ));
////		param_canny_hyst.iterations = HYSTERISIS_COUNT;
////
////		/* Initialize variables to be used in termination judgment of the DRP library */
////		drp_lib_status[TILE_0] = DRP_NOT_FINISH;
////
////		/*********************/
////		/* Start DRP Library */
////		/*********************/
////		ret_val = R_DK2_Start(drp_lib_id[TILE_0], (void *)&param_canny_hyst, sizeof(r_drp_canny_hysterisis_t));
////		DRP_DRV_ASSERT(ret_val);
////
////		printf("CH start \n");
////
////		/***************************************/
////		/* Wait until DRP processing is finish */
////		/***************************************/
////		while (drp_lib_status[TILE_0] == DRP_NOT_FINISH)
////		{
////			printf("in loop \n");
////		}
////
////		/**********************/
////		/* Unload DRP Library */
////		/**********************/
////		ret_val = R_DK2_Unload(drp_lib_id[TILE_0], &drp_lib_id[TILE_0]);
////		DRP_DRV_ASSERT(ret_val);
////
////		printf("CH unload \n");
////
////		/* Set end time of DRP processing */
////		PerformSetEndTime(4);
////
////		printf("Hi5 \n");
////
////
////		/******************************************************************************************************/
//
//
//		/******************************************************************************************************/
//		/************************************/
//        /* Load DRP Library                 */
//        /*        +-----------------------+ */
//        /* tile 0 |                       | */
//        /*        +                       + */
//        /* tile 1 |       		  	      | */
//        /*        +                       + */
//        /* tile 2 |                       | */
//        /*        +-----------------------+ */
//        /* tile 3 |                       | */
//        /*        +     FindContours      + */
//        /* tile 4 |                       | */
//        /*        +-----------------------+ */
//        /* tile 5 |                       | */
//        /*        +-----------------------+ */
//        /************************************/
//
//
//        /*****************************************/
//        /* Load DRP Library BinarizationAdaptive */
//        /*****************************************/
//        ret_val = R_DK2_Load(&g_drp_lib_find_contours[0],
//        		R_DK2_TILE_3,
//				R_DK2_TILE_PATTERN_3_2_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
////        ret_val = R_DK2_Load(&g_drp_lib_find_contours[0],
////        		R_DK2_TILE_0,
////				R_DK2_TILE_PATTERN_2_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
//        DRP_DRV_ASSERT(ret_val);
//        //		printf("bin-ad load ret val = %d", ret_val);
//        printf("load find contours \n");
//
//        /*****************************************/
//        /* Activate DRP Lib BinarizationAdaptive */
//        /*****************************************/
//        ret_val = R_DK2_Activate(drp_lib_id[TILE_3], 0);
////        ret_val = R_DK2_Activate(drp_lib_id[TILE_3], 0);
//        DRP_DRV_ASSERT(ret_val);
//        //		printf("bin-ad activate ret val = %d", ret_val);
//        printf("activate find contours \n");
//
//        /* Set start time of process*/
//        PerformSetStartTime(3);
//
//
//        /****************************************************************/
//        /* Set R_DK2_Start function parameters for BinarizationAdaptive */
//        /****************************************************************/
//        /* Cast to an appropriate type */
//        param_find_contours.src = output_bufadr;
////        param_find_contours.src = (uint32_t)&p_output_bufadr[0];
//
//        /* Cast to an appropriate type */
////        R_MMU_VAtoPA((uint32_t) param_find_contours.src, &(param_find_contours.src));
//
//        /* Cast to an appropriate type */
//        param_find_contours.dst_region = (uint32_t)&g_contours_region_adr[0];
//
//        /* Cast to an appropriate type */
//        R_MMU_VAtoPA((uint32_t) param_find_contours.dst_region, &(param_find_contours.dst_region));
//
//        /* Set Image size */
//        param_find_contours.width = (uint16_t)R_BCD_CAMERA_WIDTH;
//        param_find_contours.height = (uint16_t)R_BCD_CAMERA_HEIGHT;
//
//        /* Set whether to perform top or bottom edge border processing. */
//        /* Cast to an appropriate type */
////        param_find_contours.work = (uint32_t)&p_frame_ram1[0];
////        param_find_contours.work = p_frame_ram1;
//
//        /*Error when work 4 is used*/
//        param_find_contours.work = (uint32_t)&work_find_contours[0];    /* Address of work area; minimum size = width * height / 4 + 8 */
////        param_find_contours.work = (uint32_t)work_find_contours;
//
//        /* Cast to an appropriate type */
//        R_MMU_VAtoPA((uint32_t) param_find_contours.work, &(param_find_contours.work));
//
//        /* Cast to an appropriate type */
//        param_find_contours.dst_rect = (uint32_t)&g_contours_rect_adr[0];
//
//        /* Cast to an appropriate type */
//        R_MMU_VAtoPA((uint32_t) param_find_contours.dst_rect, &(param_find_contours.dst_rect));
//
//        //         param_find_contours.dst_region_size = FIND_CONTOURS_NUM;
////        Dont assign a lower value (eg 100 to dst_region)
////        param_find_contours.dst_region_size = 500000;
//        param_find_contours.dst_region_size = 0;
//        param_find_contours.dst_rect_size = FIND_CONTOURS_NUM;
////        param_find_contours.dst_rect_size = 20000;
//        param_find_contours.threshold_width = 70;
//        param_find_contours.threshold_height = 70;
//
//
//        /* Initialize variables to be used in termination judgment of the DRP application */
//        drp_lib_status[TILE_3] = DRP_NOT_FINISH;
//
//        /******************************************/
//        /* Start DRP Library BinarizationAdaptive */
//        /******************************************/
//        ret_val = R_DK2_Start(drp_lib_id[TILE_3], (void *)&param_find_contours, sizeof(r_drp_find_contours_t));
//        DRP_DRV_ASSERT(ret_val);
//        //		printf("bin-ad start ret val = %d", ret_val);
//        printf("start find contours \n");
//
//
//        /*******************************************************/
//        /* Wait until BinarizationAdaptive processing finished */
//        /*******************************************************/
////        while (drp_lib_status[TILE_3] == DRP_NOT_FINISH);
//
//		while (drp_lib_status[TILE_3] == DRP_NOT_FINISH)
//		{
//			/* DO NOTHING */
////			printf("***still in loop*** \n");
//		}
//
//        printf("drp finished \n");
//
//        /*******************************************/
//        /* Unload DRP library BinarizationAdaptive */
//        /*******************************************/
//        ret_val = R_DK2_Unload(drp_lib_id[TILE_3], &drp_lib_id[TILE_3]);
//        DRP_DRV_ASSERT(ret_val);
//        //		printf("bin-ad unload ret val = %d", ret_val);
//        printf("unload find contours \n");
//
//        PerformSetEndTime(3);
//
//
//        /******************************************************************************************************/
//
//
//
//        printf("FindContour End \n");
//        uint32_t num_contours = 0;
//        int32_t x, y, length, height;
//        uint8_t  color;
////        R_BCD_LcdClearGraphicsBuffer();
////        printf("size of g_contours_rect_adr = %i \n",sizeof(g_contours_rect_adr));
//        printf("g_contours_rect_adr[0].x = %i \n",g_contours_rect_adr[0].x);
////        R_BCD_LcdWriteLine( 100         ,  100          , 200         , 200, color);
////
////        /* Write the data(buf) on the cache to physical memory */
////        R_CACHE_L1DataCleanLine(R_BCD_LcdGetOLVramAddress(), (R_BCD_LCD_WIDTH * R_BCD_LCD_HEIGHT));
////
////        /* Write the data(buf) on the cache to physical memory */
////        R_CACHE_L1DataCleanLine(output_bufadr, ((R_BCD_LCD_WIDTH * R_BCD_LCD_HEIGHT) * 4));
////
//////        R_BCD_CameraClearCaptureStatus();
////
//////        R_BCD_LcdSwapGraphicsBuffer();
////        R_BCD_LcdSwapVideoBuffer();
//
//
//        while ((bcd_drp_check_empty_contours(num_contours)) && (num_contours <= (uint32_t)FIND_CONTOURS_NUM))
//        {
//        	x     = g_contours_rect_adr[num_contours].x;
//        	printf("\n%li x = %li ", num_contours, x);
//        	y     = g_contours_rect_adr[num_contours].y;
//        	printf("\n%li y = %li ", num_contours, y);
//        	length = g_contours_rect_adr[num_contours].width;
//        	printf("\n%li length = %li ", num_contours, length);
//        	height = g_contours_rect_adr[num_contours].height;
//        	printf("\n%li height = %li ", num_contours, height);
//
//        	color = RED;
//        	R_BCD_LcdWriteLine( x          ,  y          , (x + length),  y          , color);
//        	R_BCD_LcdWriteLine((x + length),  y          , (x + length), (y + height), color);
//        	R_BCD_LcdWriteLine( x          , (y + height), (x + length), (y + height), color);
//        	R_BCD_LcdWriteLine( x          ,  y          ,  x          , (y + height), color);
////        	R_BCD_LcdWriteLine( 100         ,  100          ,  x          , 200, color);
//
//        	num_contours++;
//        }
//
//    	/* Write the data(buf) on the cache to physical memory */
//    	R_CACHE_L1DataCleanLine(R_BCD_LcdGetOLVramAddress(), (R_BCD_LCD_WIDTH * R_BCD_LCD_HEIGHT));
//
//    	/* Write the data(buf) on the cache to physical memory */
//    	R_CACHE_L1DataCleanLine(output_bufadr, ((R_BCD_LCD_WIDTH * R_BCD_LCD_HEIGHT) * 4));
//
//    	//        R_BCD_CameraClearCaptureStatus();
//
////    	        R_BCD_LcdSwapGraphicsBuffer();
//    	R_BCD_LcdSwapVideoBuffer();
//
//    	printf("\nContour Drawing End \n");
//
//
//        /******************************************************************************************************/
//
//
//
//		us = PerformGetElapsedTime_us(0);
//		sprintf((void *)&buf[0],"Bayer2Grayscale : %d.%d[ms]", (int)(us / 1000), (int)((us - ((us / 1000) * 1000))
//				/ 100));
//		R_BCD_LcdWriteString(&buf[0], 2, 2, GREEN);
//
//		us = PerformGetElapsedTime_us(1);
//		sprintf((void *)&buf[0],"binarization : %d.%d[ms]", (int)(us / 1000), (int)((us - ((us / 1000) * 1000))
//				/ 100));
//		R_BCD_LcdWriteString(&buf[0], 2, 32, GREEN);
//
//		us = PerformGetElapsedTime_us(2);
//		sprintf((void *)&buf[0],"Median blur : %d.%d[ms]", (int)(us / 1000), (int)((us - ((us / 1000) * 1000))
//				/ 100));
//		R_BCD_LcdWriteString(&buf[0], 2, 62, GREEN);
//
//		us = PerformGetElapsedTime_us(7);
//		sprintf((void *)&buf[0],"Sobel : %d.%d[ms]", (int)(us / 1000), (int)((us - ((us / 1000) * 1000))
//				/ 100));
//		R_BCD_LcdWriteString(&buf[0], 2, 92, GREEN);
//
//		us = PerformGetElapsedTime_us(3);
//		sprintf((void *)&buf[0],"Find Contours : %d.%d[ms]", (int)(us / 1000), (int)((us - ((us / 1000) * 1000))
//				/ 100));
//		R_BCD_LcdWriteString(&buf[0], 2, 122, GREEN);
//
//
//		/* Write the data(buf) on the cache to physical memory */
//		R_CACHE_L1DataCleanLine(R_BCD_LcdGetOLVramAddress(), (R_BCD_LCD_WIDTH * R_BCD_LCD_HEIGHT));
//
//		/* Write the data(buf) on the cache to physical memory */
//		R_CACHE_L1DataCleanLine(output_bufadr, ((R_BCD_LCD_WIDTH * R_BCD_LCD_HEIGHT) * 4));
//
//		/* Clear the current capture state and enable the detection of the next capture completion */
//		R_BCD_CameraClearCaptureStatus();
//
////		R_BCD_LcdSwapGraphicsBuffer();
//		R_BCD_LcdSwapVideoBuffer();
//
//		R_BCD_LcdClearGraphicsBuffer();
//
//    }
//
//    sample_finish:
//
//	return;
//}
//
//////        /* Display image processing result */
//////        R_BCD_LcdSwapVideoBuffer();
////
////
//////        /* Display image processing result */
//////        R_BCD_LcdSwapVideoBuffer();
////
//////        /* Write the data(buf) on the cache to physical memory */
//////        R_CACHE_L1DataCleanLine(R_BCD_LcdGetOLVramAddress(), (R_BCD_LCD_WIDTH * R_BCD_LCD_HEIGHT));
////
////        /* Write the data(buf) on the cache to physical memory */
//////        R_CACHE_L1DataCleanLine(output_bufadr, ((R_BCD_LCD_WIDTH * R_BCD_LCD_HEIGHT) * 4));
////
////        /* Display overlay buffer written processing time */
//////        R_BCD_LcdSwapGraphicsBuffer();
////
//////        R_BCD_LcdClearGraphicsBuffer();
//////
//////        /* Clear the current capture state and enable the detection of the next capture completion */
//////        R_BCD_CameraClearCaptureStatus();
//////
//////        /* Capture Start */
//////        R_BCD_CameraCaptureStart();
//////
//////        /* Display image processing result */
////        R_BCD_LcdSwapVideoBuffer();
////
////		/* Display time taken for image processing */
//////        R_BCD_LcdClearGraphicsBuffer();
////		us = PerformGetElapsedTime_us(0);
////		sprintf((void *)&buf[0],"Bayer2Grayscale : %d.%d[ms]", (int)(us / 1000), (int)((us - ((us / 1000) * 1000))
////				/ 100));
////		R_BCD_LcdWriteString(&buf[0], 2, 2, GREEN);
////		us = PerformGetElapsedTime_us(1);
////		sprintf((void *)&buf[0],"binarization : %d.%d[ms]", (int)(us / 1000), (int)((us - ((us / 1000) * 1000))
////				/ 100));
////		R_BCD_LcdWriteString(&buf[0], 2, 32, GREEN);
////		us = PerformGetElapsedTime_us(2);
////		sprintf((void *)&buf[0],"Median blur : %d.%d[ms]", (int)(us / 1000), (int)((us - ((us / 1000) * 1000))
////				/ 100));
////		R_BCD_LcdWriteString(&buf[0], 2, 62, GREEN);
////		us = PerformGetElapsedTime_us(3);
////		sprintf((void *)&buf[0],"Find Contours : %d.%d[ms]", (int)(us / 1000), (int)((us - ((us / 1000) * 1000))
////				/ 100));
////		R_BCD_LcdWriteString(&buf[0], 2, 92, GREEN);
////		/* Write the data(buf) on the cache to physical memory */
////		R_CACHE_L1DataCleanLine(R_BCD_LcdGetOLVramAddress(), (R_BCD_LCD_WIDTH * R_BCD_LCD_HEIGHT));
////
////		/* Write the data(buf) on the cache to physical memory */
////		R_CACHE_L1DataCleanLine(R_BCD_LcdGetOLVramAddress(), ((R_BCD_LCD_WIDTH * R_BCD_LCD_HEIGHT) / 2));
////
////		/* Display overlay buffer written processing time */
////		R_BCD_LcdSwapGraphicsBuffer();
////
////    }
////
////sample_finish:
////
////    return;
////}
///**********************************************************************************************************************
//* End of function sample_main
//**********************************************************************************************************************/
//
//
///******************************************************************************
// * Function Name: bcd_drp_check_empty_contours
// * Description  :
// * Arguments    : -
// * Return Value : -
// ******************************************************************************/
//static uint32_t bcd_drp_check_empty_contours(uint32_t i)
//{
//
//    if(g_contours_rect_adr[i].x)
//    {
//        return 1;
//    }
//    else if(g_contours_rect_adr[i].y)
//    {
//        return 1;
//    }
//    else if(g_contours_rect_adr[i].width)
//    {
//        return 1;
//    }
//    else if(g_contours_rect_adr[i].height)
//    {
//        return 1;
//    }
//    else if(g_contours_rect_adr[i].num)
//    {
//        return 1;
//    }
//    else if(g_contours_rect_adr[i].addr)
//    {
//        return 1;
//    }
//    else
//    {
//        return 0;
//    }
//}
///**********************************************************************************************************************
// End of function bcd_drp_check_empty_contours
//
//
//
///* End of File */



///**********************************************************************************************************************
//* b2g->bin->find_contours working? DISCLAIMER
//* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
//* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
//* applicable laws, including copyright laws.
//* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
//* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
//* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
//* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
//* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
//* THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
//* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
//* this software. By using this software, you agree to the additional terms and conditions found by accessing the
//* following link:
//* http://www.renesas.com/disclaimer
//* Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
//**********************************************************************************************************************/
//
///**********************************************************************************************************************
//Includes   <System Includes> , "Project Includes"
//**********************************************************************************************************************/
//#include <stdio.h>
//#include <fcntl.h>
//
//#include "r_typedefs.h"
//#include "iodefine.h"
//#include "r_cache_lld_rza2m.h"
//
//#include "r_bcd_camera.h"
//#include "r_bcd_lcd.h"
//#include "draw.h"
//#include "perform.h"
//#include "r_mmu_lld_rza2m.h"
//#include "r_bcd_ae.h"
//
//#include "r_dk2_if.h"
//#include "r_drp_simple_isp.h"
//#include "r_drp_bayer2grayscale.h"
//#include "r_drp_median_blur.h"
//#include "r_drp_corner_harris.h"
//#include "r_drp_dilate.h"
//#include "r_drp_binarization_adaptive.h"
//#include "r_drp_median_blur.h"
//#include "r_drp_thinning.h"
//#include "r_drp_dilate.h"
//#include "r_drp_find_contours.h"
//#include "r_drp_sobel.h"
//#include "r_drp_gaussian_blur.h"
//
//#include "r_drp_bayer2lrgb_color_correction_x_t6.h"
//#include "r_drp_lrgb2l_gaussian_blur_x.h"
//#include "r_drp_canny_calculate.h"
//#include "r_drp_canny_hysterisis.h"
////#include "r_drp_dilate.h"
//#include "r_drp_binarization_adaptive.h"
//#include "r_drp_find_contours_crop_x_t2.h"
//
///**********************************************************************************************************************
//  Local Typedef definitions
// *********************************************************************************************************************/
//
//typedef struct contours_rect_t
//{
//    uint16_t x;
//    uint16_t y;
//    uint16_t width;
//    uint16_t height;
//    uint32_t num;
//    uint32_t addr;
//} contours_rect_t;
//
//typedef struct
//{
//    uint16_t x;
//    uint16_t y;
//} contours_region_t;
//
///**********************************************************************************************************************
//Macro definitions
//**********************************************************************************************************************/
//#define TILE_0          (0)
//#define TILE_1          (1)
//#define TILE_2          (2)
//#define TILE_3          (3)
//#define TILE_4          (4)
//#define TILE_5          (5)
//
//#define DRP_NOT_FINISH  (0)
//#define DRP_FINISH      (1)
//
//#define HARRIS_SHIFT_NUM    (3)
//
//#define HYSTERISIS_COUNT  (2)
//#define FIND_CONTOURS_NUM (10)
//
//#define DRP_DRV_ASSERT(x) if ((x) != 0) goto sample_finish
//
//#define LEN(arr) ((int) (sizeof (arr) / sizeof (arr)[0]))
//
//#define GAMMA_VALUE      ((double)1.2)
//
//#define WEAK_LEVEL      (0x28)
//#define STRONG_LEVEL    (0x58)
//
///**********************************************************************************************************************
//Imported global variables and functions (from other files)
//**********************************************************************************************************************/
////extern uint8_t g_drp_lib_bayer2grayscale[];
////extern uint8_t g_drp_lib_binarization_adaptive[];
////extern uint8_t g_drp_lib_binarization_fixed[];
////extern uint8_t g_drp_lib_median_blur[];
////extern uint8_t g_drp_lib_thinning[];
////extern uint8_t g_drp_lib_dilate[];
////extern uint8_t g_drp_lib_find_contours[];
////extern uint8_t g_drp_lib_sobel[];
////extern uint8_t g_drp_lib_gaussian_blur[];
//
//extern uint8_t g_drp_lib_bayer2lrgb_color_correction_t6[];
//extern uint8_t g_drp_lib_find_contours_crop_t2[];
//extern uint8_t g_drp_lib_lrgb2l_gaussian_blur[];
//extern uint8_t g_drp_lib_canny_calculate[];
//extern uint8_t g_drp_lib_canny_hysterisis[];
//extern uint8_t g_drp_lib_dilate[];
//extern uint8_t g_drp_lib_binarization_adaptive[];
//
///**********************************************************************************************************************
//Private global variables and functions
//**********************************************************************************************************************/
//static uint8_t drp_lib_id[R_DK2_TILE_NUM] = {0};
//static volatile uint8_t drp_lib_status[R_DK2_TILE_NUM] = {DRP_NOT_FINISH};
////static uint8_t work_buf[R_BCD_CAMERA_WIDTH * R_BCD_CAMERA_HEIGHT] __attribute__ ((aligned(32)));
////static uint8_t work_buf_2[R_BCD_CAMERA_WIDTH * R_BCD_CAMERA_HEIGHT] __attribute__ ((aligned(32)));
////static uint8_t work_buf_3[R_BCD_CAMERA_WIDTH * R_BCD_CAMERA_HEIGHT] __attribute__ ((aligned(32)));
////static uint8_t work_buf_4[R_BCD_CAMERA_WIDTH * R_BCD_CAMERA_HEIGHT] __attribute__ ((aligned(32)));
//
//
//static uint8_t  look_up_table[256]                                             __attribute__ ((section("Uncache_IRAM")));
//
////static r_drp_bayer2grayscale_t param_b2g[R_DK2_TILE_NUM] __attribute__ ((section("UNCACHED_BSS")));
//static r_drp_binarization_adaptive_t param_binarization_adaptive __attribute__ ((section("UNCACHED_BSS")));
////static r_drp_median_blur_t param_median[R_DK2_TILE_NUM] __attribute__ ((section("UNCACHED_BSS")));
////static r_drp_thinning_t param_thinning[R_DK2_TILE_NUM] __attribute__ ((section("UNCACHED_BSS")));
////static r_drp_dilate_t param_dilate __attribute__ ((section("UNCACHED_BSS")));
////static r_drp_find_contours_t param_find_contours __attribute__ ((section("Uncache_BSS")));
//contours_region_t g_contours_region_adr[FIND_CONTOURS_NUM + 1]  __attribute__ ((section("Uncache_IRAM")));
//contours_rect_t g_contours_rect_adr[FIND_CONTOURS_NUM + 1] __attribute__ ((section("Uncache_IRAM")));
////static r_drp_sobel_t param_sobel[R_DK2_TILE_NUM] __attribute__ ((section("UNCACHED_BSS")));
////static r_drp_gaussian_blur_t param_gaussian_blur[R_DK2_TILE_NUM] __attribute__ ((section("UNCACHED_BSS")));
//
//static r_drp_bayer2lrgb_color_correction_t param_bayer2lrgb_color_correction   __attribute__ ((section("Uncache_IRAM")));
//static r_drp_bayer2lrgb_color_correction_layer_t    bayer2argb_layersum        __attribute__ ((section("Uncache_IRAM")));
//static r_drp_lrgb2l_gaussian_blur_t        param_lrgb2l_gaussian_blur[2]       __attribute__ ((section("Uncache_IRAM")));
//
//static r_drp_canny_calculate_t  param_canny_cal[1]                             __attribute__ ((section("Uncache_IRAM")));
//static r_drp_canny_hysterisis_t param_canny_hyst                               __attribute__ ((section("Uncache_IRAM")));
//static r_drp_dilate_t           param_dilate                                   __attribute__ ((section("Uncache_IRAM")));
//
//static r_drp_find_contours_crop_t          param_find_contours_crop            __attribute__ ((section("Uncache_IRAM")));
//
//
//static uint8_t frame_RAM_A[R_BCD_CAMERA_HEIGHT * R_BCD_CAMERA_WIDTH]          __attribute__ ((section("ImageWork_RAM")));  /* Gaussian Blur        */
//static uint8_t frame_RAM_B[R_BCD_CAMERA_HEIGHT * R_BCD_CAMERA_WIDTH]          __attribute__ ((section("ImageWork_RAM")));  /* Canny Calculate      */
//static uint8_t frame_RAM_C[R_BCD_CAMERA_HEIGHT * R_BCD_CAMERA_WIDTH]          __attribute__ ((section("ImageWork_RAM")));  /* Canny Hysterisis     */
//static uint8_t frame_RAM_D[R_BCD_CAMERA_HEIGHT * R_BCD_CAMERA_WIDTH]          __attribute__ ((section("ImageWork_RAM")));  /* Dilate               */
//static uint8_t frame_RAM_E[R_BCD_CAMERA_HEIGHT * R_BCD_CAMERA_WIDTH]          __attribute__ ((section("ImageWork_RAM")));  /* BinarizationAdaptive */
//static uint8_t work1[((R_BCD_CAMERA_HEIGHT +2) * R_BCD_CAMERA_WIDTH)*2]       __attribute__ ((section("ImageWork_RAM")));  /* Work area for Canny Calculate */
//static uint8_t work2[R_BCD_CAMERA_HEIGHT * R_BCD_CAMERA_WIDTH]                __attribute__ ((section("ImageWork_RAM")));  /* Work area for Canny Hysterisis and Find Conturs */
//static uint8_t work3[((R_BCD_CAMERA_HEIGHT * R_BCD_CAMERA_WIDTH) / 64) + 2]   __attribute__ ((section("ImageWork_RAM")));  /* Work area for BinarizationAdaptive */
////static uint8_t work4[R_BCD_CAMERA_HEIGHT * R_BCD_CAMERA_WIDTH]   			  __attribute__ ((section("ImageWork_RAM")));  /* Work area for FindContours */
////static uint8_t work2[R_BCD_CAMERA_HEIGHT * R_BCD_CAMERA_WIDTH]                __attribute__ ((section("ImageWork_RAM")));  /* Work area for Canny Hysterisis and Find Conturs */
////static uint8_t work_find_contours[R_BCD_CAMERA_HEIGHT * R_BCD_CAMERA_WIDTH]                __attribute__ ((section("ImageWork_RAM")));  /* Work area Find Conturs */
////static uint8_t thinning_result_buf[R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT+(2*3)) * 2] __attribute__ ((aligned(32)));
//static void cb_drp_finish(uint8_t id);
//static uint32_t bcd_drp_check_empty_contours(uint32_t i);
//
///**********************************************************************************************************************
//* Function Name: cb_drp_finish
//* Description  : This function is a callback function called from the
//*              : DRP driver at the finish of the DRP library processing.
//* Arguments    : id
//*              :   The ID of the DRP library that finished processing.
//* Return Value : -
//**********************************************************************************************************************/
//static void cb_drp_finish(uint8_t id)
//{
//    uint32_t tile_no;
//
//    /* Change the operation state of the DRP library notified by the argument to finish */
//    for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//    {
//        if (drp_lib_id[tile_no] == id)
//        {
//            drp_lib_status[tile_no] = DRP_FINISH;
//            break;
//        }
//    }
//
//    return;
//}
///**********************************************************************************************************************
//* End of function cb_drp_finish
//**********************************************************************************************************************/
//
///**********************************************************************************************************************
//* Function Name: sample_main
//* Description  : First function called after initialization is completed
//* Arguments    : -
//* Return Value : -
//**********************************************************************************************************************/
//void sample_main(void)
//{
//    int32_t frame_buf_id;
//    uint8_t buf[80];
//    int32_t ret_val;
//    uint32_t us;
////    uint32_t input_bufadr;
////    uint32_t output_bufadr;
//    uint8_t *input_bufadr;
//    uint8_t *output_bufadr;
//    uint32_t work_bufadr;
//    uint32_t work_bufadr_bin2med;
//    uint32_t work_bufadr_med2thin;
////    uint32_t work_bufadr_med2dilate;
//    uint32_t work_bufadr_med2contours;
//    uint32_t intermediate_bufadr;
//    uint32_t tile_no;
//    uint8_t * p_input_bufadr;
//    uint8_t * p_output_bufadr;
//    uint8_t * p_work_bufadr;
//    uint8_t * p_work_bufadr_bin2med;
//    uint8_t * p_work_bufadr_med2thin;
//    uint32_t * p_frame_ram1;
////    uint8_t * p_work_bufadr_med2dilate;
//    uint8_t * p_work_bufadr_med2contours;
//    uint32_t bufsize_thinning;
//
//    r_bcd_ae_setting_t ae_setting;
//    uint32_t bufsize;
//    uint16_t brightness;
//
//    /* Initialization of VIN and MIPI driver */
//    R_BCD_CameraInit();
//
//    /* Initialization of LCD driver */
//    R_BCD_LcdInit();
//
//    /* Capture Start */
//    R_BCD_CameraClearCaptureStatus();
//    R_BCD_CameraCaptureStart();
//
//    /* Initialize of Performance counter */
//    PerformInit();
//
//    /********************************/
//    /* Initialization of DRP driver */
//    /********************************/
//    R_DK2_Initialize();
//
//
//    R_BCD_AeInit(&ae_setting);
//    R_BCD_AeMakeGammaTable(&ae_setting, GAMMA_VALUE, look_up_table);
//
//    /* Wait until camera capture is complete */
//    while ((frame_buf_id = R_BCD_CameraGetCaptureStatus()) == R_BCD_CAMERA_NOT_CAPTURED)
//    {
//        /* DO NOTHING */
//    }
//
//    /* main loop */
//    while (1)
//    {
//
//
//        if (1) {     /* find all contours */
//
//        	printf("Bayer2lrgbColorCorrection start");
//
//        	/**************************************/
//        	/* Load DRP Library                   */
//        	/*        +-------------------------+ */
//        	/* tile 0 |                         | */
//        	/*        |                         | */
//        	/* tile 1 |                         | */
//        	/*        |                         | */
//        	/* tile 2 |                         | */
//        	/*        |Bayer2lrgbColorCorrection| */
//        	/* tile 3 |     (WhiteBalance)      | */
//        	/*        |                         | */
//        	/* tile 4 |                         | */
//        	/*        |                         | */
//        	/* tile 5 |                         | */
//        	/*        +-------------------------+ */
//        	/**************************************/
//
//        	/* Set start time of process*/
//        	PerformSetStartTime(1);
//
//        	ret_val = R_DK2_Load(&g_drp_lib_bayer2lrgb_color_correction_t6[0],
//        			R_DK2_TILE_0 ,
//					R_DK2_TILE_PATTERN_6, NULL, &cb_drp_finish, &drp_lib_id[0]);
//        	DRP_DRV_ASSERT(ret_val);
//        	/***********************
//        			 Activate DRP Library
//        	 ***********************/
//        	ret_val = R_DK2_Activate(drp_lib_id[TILE_0], 0);
//        	DRP_DRV_ASSERT(ret_val);
//
//        	/* Start Bayer2RGB */
//        	/* Set Bayer2RgbColorCorrection parameters */
//        	input_bufadr  = R_BCD_CameraGetFrameAddress(frame_buf_id);
//        	output_bufadr = R_BCD_LcdGetVramAddress();              /* address of the video buffer which is not currently being displayed */
//
////            /* convert to phisical address */
////            R_MMU_VAtoPA((uint32_t)p_input_bufadr, &input_bufadr);
////
////            /* convert to phisical address */
////            R_MMU_VAtoPA((uint32_t)p_output_bufadr, &output_bufadr);
//        	/**************************************
//        			 Set R_DK2_Start function parameters
//        	 **************************************/
//
//        	/* Set the address of buffer to be read/write by DRP */
////        	param_bayer2lrgb_color_correction.src = (uint32_t)input_bufadr;
////        	param_bayer2lrgb_color_correction.dst = (uint32_t)output_bufadr;
//////        	R_MMU_VAtoPA((uint32_t)param_bayer2lrgb_color_correction.src,  &(param_bayer2lrgb_color_correction.src));
//////        	R_MMU_VAtoPA((uint32_t)param_bayer2lrgb_color_correction.dst,  &(param_bayer2lrgb_color_correction.dst));
//            R_MMU_VAtoPA((uint32_t)input_bufadr,  &(param_bayer2lrgb_color_correction.src));
//            R_MMU_VAtoPA((uint32_t)output_bufadr, &(param_bayer2lrgb_color_correction.dst));
//
//
//
//        	/* Set Image size */
//        	param_bayer2lrgb_color_correction.width  = R_BCD_CAMERA_WIDTH;
//        	param_bayer2lrgb_color_correction.height = R_BCD_CAMERA_HEIGHT;
//
//        	/* Set magnification */
//        	if ( R_BCD_CameraBayerMode ) { // PCAM5C has bayer mode 3
//        		param_bayer2lrgb_color_correction.gain_r = 0x1050;
//        		param_bayer2lrgb_color_correction.gain_g = 0x1000;
//        		param_bayer2lrgb_color_correction.gain_b = 0x1050;
//        	} else { // IMX219_B has bayer mode 0
//        		param_bayer2lrgb_color_correction.gain_r = 0x148F;
//        		param_bayer2lrgb_color_correction.gain_g = 0x1000;
//        		param_bayer2lrgb_color_correction.gain_b = 0x1A72;
//        	}
//        	// camera specific bayer pattern R_BCD_CameraBayerMode 0-RGGB 3-BGGR 255-unset
//        	param_bayer2lrgb_color_correction.pattern = R_BCD_CameraBayerMode ;
//
//        	param_bayer2lrgb_color_correction.dst_layersum = (uint32_t)&bayer2argb_layersum;
//        	R_MMU_VAtoPA((uint32_t)param_bayer2lrgb_color_correction.dst_layersum, &(param_bayer2lrgb_color_correction.dst_layersum));
//
//        	/* Initialize variables to be used in termination judgment of the DRP library */
//        	drp_lib_status[TILE_0] = DRP_NOT_FINISH;
//
//        	/********************
//        			 Start DRP Library
//        	 ********************/
//        	ret_val = R_DK2_Start(drp_lib_id[TILE_0], (void *)&param_bayer2lrgb_color_correction, sizeof(r_drp_bayer2lrgb_color_correction_t));
//        	DRP_DRV_ASSERT(ret_val);
//
//        	/**************************************
//        			 Wait until DRP processing is finish
//        	 **************************************/
//        	while (drp_lib_status[TILE_0] == DRP_NOT_FINISH)
//        	{
//        		/* Wait drp finish */
//        	}
//
//        	/*********************
//        			 Unload DRP library
//        	 *********************/
//        	ret_val = R_DK2_Unload(drp_lib_id[TILE_0], &drp_lib_id[TILE_0]);
//        	DRP_DRV_ASSERT(ret_val);
//
//
//        	/* Set AE */
//        	if (bayer2argb_layersum.layeractivepixel != 0) {
//        		brightness = (uint16_t)(bayer2argb_layersum.layersum / bayer2argb_layersum.layeractivepixel);
//        		R_BCD_AeRunAutoExpousure(&ae_setting, brightness);
//        	}
//
//
//        	/* Clear the current capture state and enable the detection of the next capture completion */
//        	R_BCD_CameraClearCaptureStatus();
//
//        	/* Set end time of process*/
//        	PerformSetEndTime(1);
//
//        	//        			/***********************************/
//        	//        			/* Load DRP Library                */
//        	//        			/*        +----------------------+ */
//        	//        			/* tile 0 |                      | */
//        	//        			/*        +   Canny Calculate    + */
//        	//        			/* tile 1 |                      | */
//        	//        			/*        +----------------------+ */
//        	//        			/* tile 2 | lrgb2l_gaussian_blur | */
//        	//        			/*        +----------------------+ */
//        	//        			/* tile 3 | lrgb2l_gaussian_blur | */
//        	//        			/*        +----------------------+ */
//        	//        			/* tile 4 |                      | */
//        	//        			/*        +----------------------+ */
//        	//        			/* tile 5 |                      | */
//        	//        			/*        +----------------------+ */
//        	//        			/***********************************/
//        	//
//        	//        			/* Set start time of process*/
//        	//        			PerformSetStartTime(2);
//        	//
//        	//        			/*****************************************/
//        	//        			/* load DRP Library lrgb2l_gaussian_blur */
//        	//        			/*****************************************/
//        	//        			ret_val = R_DK2_Load(&g_drp_lib_lrgb2l_gaussian_blur[0],
//        	//        								R_DK2_TILE_2 | R_DK2_TILE_3,
//        	//        								R_DK2_TILE_PATTERN_2_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
//        	//        			DRP_DRV_ASSERT(ret_val);
//        	//
//        	//        			/*********************************************/
//        	//        			/* Activate DRP Library lrgb2l_gaussian_blur */
//        	//        			/*********************************************/
//        	//        			ret_val = R_DK2_Activate(drp_lib_id[TILE_2] | drp_lib_id[TILE_3], 0);
//        	//        			DRP_DRV_ASSERT(ret_val);
//        	//
//        	//        		    /****************************************************************/
//        	//        			/* Set R_DK2_Start function parameters　for　lrgb2l_gaussian_blur */
//        	//        			/****************************************************************/
//        	//        			/* Set the address of buffer to be read/write by DRP */
//        	//        			for (tile_no = TILE_2; tile_no <= TILE_3; tile_no++)
//        	//        			{
//        	//        				/* Set Image size */
//        	//
//        	//        				param_lrgb2l_gaussian_blur[tile_no - 2].width  = R_BCD_CAMERA_WIDTH;
//        	//        				param_lrgb2l_gaussian_blur[tile_no - 2].height = R_BCD_CAMERA_HEIGHT / 2;
//        	//
//        	//        				output_bufadr = R_BCD_LcdGetVramAddress();              /* address of the video buffer which is not currently being displayed */
//        	//
//        	//        				/* Set the address of buffer to be read/write by DRP */
//        	////        			    param_lrgb2l_gaussian_blur[tile_no - 2].src = (uint32_t)(output_bufadr + (param_lrgb2l_gaussian_blur[tile_no - 2].width * param_lrgb2l_gaussian_blur[tile_no - 2].height * (uint16_t)((tile_no - 2u) * 4u)));
//        	////        			    param_lrgb2l_gaussian_blur[tile_no - 2].dst = (uint32_t)&frame_RAM_A[(param_lrgb2l_gaussian_blur[tile_no - 2].width * param_lrgb2l_gaussian_blur[tile_no - 2].height * (uint16_t)(tile_no - 2u) )];
//        	//        				param_lrgb2l_gaussian_blur[tile_no - 2].src = (uint32_t)&frame_RAM_A[(param_lrgb2l_gaussian_blur[tile_no - 2].width * param_lrgb2l_gaussian_blur[tile_no - 2].height * (uint16_t)(tile_no - 2u) )];
//        	//        				param_lrgb2l_gaussian_blur[tile_no - 2].dst = (uint32_t)&frame_RAM_B[(param_lrgb2l_gaussian_blur[tile_no - 2].width * param_lrgb2l_gaussian_blur[tile_no - 2].height * (uint16_t)(tile_no - 2u) )];
//        	//        				R_MMU_VAtoPA((uint32_t)param_lrgb2l_gaussian_blur[tile_no - 2].src, &(param_lrgb2l_gaussian_blur[tile_no - 2].src ));
//        	//        				R_MMU_VAtoPA((uint32_t)param_lrgb2l_gaussian_blur[tile_no - 2].dst, &(param_lrgb2l_gaussian_blur[tile_no - 2].dst ));
//        	//
//        	//        				/* Set whether to perform top or bottom edge border processing. */
//        	//        				param_lrgb2l_gaussian_blur[tile_no - 2].top    = (tile_no == TILE_2) ? 1 : 0;
//        	//        				param_lrgb2l_gaussian_blur[tile_no - 2].bottom = (tile_no == TILE_3) ? 1 : 0;
//        	//
//        	//        				param_lrgb2l_gaussian_blur[tile_no - 2].spare1 =  0;
//        	//        				param_lrgb2l_gaussian_blur[tile_no - 2].spare2 =  0;
//        	//
//        	//        				/* Initialize variables to be used in termination judgment of the DRP application */
//        	//        				drp_lib_status[tile_no] = DRP_NOT_FINISH;
//        	//
//        	//        				/*********************/
//        	//        				/* Start DRP Library */
//        	//        				/*********************/
//        	//        				ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_lrgb2l_gaussian_blur[tile_no - 2], sizeof(r_drp_lrgb2l_gaussian_blur_t));
//        	//        				DRP_DRV_ASSERT(ret_val);
//        	//        			}
//        	//
//        	//        			/*##################################*/
//        	//        			/* load DRP Library Canny Calculate */
//        	//        			/*##################################*/
//        	//
//        	//        			ret_val = R_DK2_Load(&g_drp_lib_canny_calculate[0],
//        	//        								 R_DK2_TILE_0,
//        	//        								 R_DK2_TILE_PATTERN_2_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
//        	//        			DRP_DRV_ASSERT(ret_val);
//        	//
//        	//        			/*##################################*/
//        	//        			/* Activate DRP Lib Canny Calculate */
//        	//        			/*##################################*/
//        	//        			ret_val = R_DK2_Activate(drp_lib_id[TILE_0], 0);
//        	//        			DRP_DRV_ASSERT(ret_val);
//        	//
//        	//
//        	//        			/***************************************/
//        	//        			 /* Wait until DRP processing is finish */
//        	//        			 /***************************************/
//        	//        			for (tile_no = TILE_2; tile_no <= TILE_3; tile_no += 1)
//        	//        			{
//        	//        				/***************************************/
//        	//        				/* Wait until DRP processing is finish */
//        	//        				/***************************************/
//        	//        				while (drp_lib_status[tile_no] == DRP_NOT_FINISH);
//        	//        			}
//        	//
//        	//        			/**********************/
//        	//        			/* Unload DRP library */
//        	//        			/**********************/
//        	//        			ret_val = R_DK2_Unload(drp_lib_id[TILE_2] | drp_lib_id[TILE_3], &drp_lib_id[TILE_2]);
//        	//        			DRP_DRV_ASSERT(ret_val);
//        	//
//        	//        			/* Set end time of process*/
//        	//        			PerformSetEndTime(2);
//        	//
//        	//        			/*############   <-  lrgb2l_gaussian_blur        ##############*/
//        	//
//        	//        			/*############         Canny Calculate      ->   ##############*/
//        	//
//        	//        			/* Set start time of process*/
//        	//        			PerformSetStartTime(3);
//        	//
//        	//        			/***************************************/
//        	//        			/* Set R_DK2_Start function parameters */
//        	//        			/***************************************/
//        	//        			tile_no = TILE_0;
//        	//
//        	//        			/* Set Image size */
//        	//        			param_canny_cal[tile_no].width  = R_BCD_CAMERA_WIDTH;
//        	//        			param_canny_cal[tile_no].height = R_BCD_CAMERA_HEIGHT;
//        	//
//        	//        			/* Set Buffer size */
//        	//        			bufsize = (uint32_t)(param_canny_cal[tile_no].width * param_canny_cal[tile_no].height);
//        	//
//        	//        			/* Set the address of buffer to be read/write by DRP */
//        	////        			param_canny_cal[tile_no].src = (uint32_t)&frame_RAM_A[(tile_no * bufsize)];
//        	////        			param_canny_cal[tile_no].dst = (uint32_t)&frame_RAM_B[(tile_no * bufsize)];
//        	//        			param_canny_cal[tile_no].src = (uint32_t)&frame_RAM_B[(tile_no * bufsize)];
//        	//        			param_canny_cal[tile_no].dst = (uint32_t)&output_bufadr;
//        	//        			R_MMU_VAtoPA((uint32_t)param_canny_cal[tile_no].src, &(param_canny_cal[tile_no].src ));
//        	//        			R_MMU_VAtoPA((uint32_t)param_canny_cal[tile_no].dst, &(param_canny_cal[tile_no].dst ));
//        	//
//        	//        			/* Set additional information (currently no additional information) */
//        	//        			param_canny_cal[tile_no].work = (uint32_t)&work1[(tile_no * (bufsize + (R_BCD_CAMERA_WIDTH*2) ))*2];
//        	//        			R_MMU_VAtoPA((uint32_t)param_canny_cal[tile_no].work, &(param_canny_cal[tile_no].work ));
//        	//
//        	//        			param_canny_cal[tile_no].threshold_high = STRONG_LEVEL;
//        	//        			param_canny_cal[tile_no].threshold_low = WEAK_LEVEL;
//        	//
//        	//        			/* Set whether to perform top or bottom edge border processing. */
//        	//        			param_canny_cal[tile_no].top    = (tile_no == TILE_0) ? 1 : 0;
//        	//        			param_canny_cal[tile_no].bottom = (tile_no == TILE_0) ? 1 : 0;
//        	//
//        	//        			/* Initialize variables to be used in termination judgment of the DRP library */
//        	//        			drp_lib_status[tile_no] = DRP_NOT_FINISH;
//        	//
//        	//        			/*********************/
//        	//        			/* Start DRP Library */
//        	//        			/*********************/
//        	//        			ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_canny_cal[tile_no / 2], sizeof(r_drp_canny_calculate_t));
//        	//        			DRP_DRV_ASSERT(ret_val);
//        	//
//        	//        			/***************************************/
//        	//        			/* Wait until DRP processing is finish */
//        	//        			/***************************************/
//        	//        			while (drp_lib_status[TILE_0] == DRP_NOT_FINISH);
//        	//
//        	//        			/**********************/
//        	//        			/* Unload DRP library */
//        	//        			/**********************/
//        	//        			ret_val = R_DK2_Unload(drp_lib_id[TILE_0], &drp_lib_id[TILE_0]);
//        	//        			DRP_DRV_ASSERT(ret_val);
//        	//
//        	//        			/* Set end time of DRP processing */
//        	//        			PerformSetEndTime(3);
//
//        	//        			/*******************************/
//        	//        			/* Load DRP Library            */
//        	//        			/*        +------------------+ */
//        	//        			/* tile 0 |                  | */
//        	//        			/*        +                  + */
//        	//        			/* tile 1 |                  | */
//        	//        			/*        +                  + */
//        	//        			/* tile 2 |                  | */
//        	//        			/*        + Canny Hysterisis + */
//        	//        			/* tile 3 |                  | */
//        	//        			/*        +                  + */
//        	//        			/* tile 4 |                  | */
//        	//        			/*        +                  + */
//        	//        			/* tile 5 |                  | */
//        	//        			/*        +------------------+ */
//        	//        			/*******************************/
//        	//
//        	//        			/* Set start time of Canny Hyst process */
//        	//        			PerformSetStartTime(4);
//        	//
//        	//        			ret_val = R_DK2_Load(&g_drp_lib_canny_hysterisis[0],
//        	//        								 R_DK2_TILE_0,
//        	//        								 R_DK2_TILE_PATTERN_6, NULL, &cb_drp_finish, &drp_lib_id[0]);
//        	//        			DRP_DRV_ASSERT(ret_val);
//        	//
//        	//        			/************************/
//        	//        			/* Activate DRP Library */
//        	//        			/************************/
//        	//        			ret_val = R_DK2_Activate(drp_lib_id[TILE_0], 0);
//        	//        			DRP_DRV_ASSERT(ret_val);
//        	//
//        	//        			/***************************************/
//        	//        			/* Set R_DK2_Start function parameters */
//        	//        			/***************************************/
//        	//        			/* Set Image size */
//        	//        			param_canny_hyst.width = R_BCD_CAMERA_WIDTH;
//        	//        			param_canny_hyst.height = R_BCD_CAMERA_HEIGHT;
//        	//
//        	//        			/* Set the address of buffer to be read/write by DRP */
//        	//        			param_canny_hyst.src = (uint32_t)&frame_RAM_B[0];
//        	//        			param_canny_hyst.dst = (uint32_t)&frame_RAM_C[0];
//        	//        			R_MMU_VAtoPA((uint32_t)param_canny_hyst.src, &(param_canny_hyst.src ));
//        	//        			R_MMU_VAtoPA((uint32_t)param_canny_hyst.dst, &(param_canny_hyst.dst ));
//        	//
//        	//        			/* Set additional information (currently no additional information) */
//        	//        			param_canny_hyst.work = (uint32_t)&work2[0];
//        	//        			R_MMU_VAtoPA((uint32_t)param_canny_hyst.work, &(param_canny_hyst.work ));
//        	//        			param_canny_hyst.iterations = HYSTERISIS_COUNT;
//        	//
//        	//        			/* Initialize variables to be used in termination judgment of the DRP library */
//        	//        			drp_lib_status[TILE_0] = DRP_NOT_FINISH;
//        	//
//        	//        			/*********************/
//        	//        			/* Start DRP Library */
//        	//        			/*********************/
//        	//        			ret_val = R_DK2_Start(drp_lib_id[TILE_0], (void *)&param_canny_hyst, sizeof(r_drp_canny_hysterisis_t));
//        	//        			DRP_DRV_ASSERT(ret_val);
//        	//
//        	//        			/***************************************/
//        	//        			/* Wait until DRP processing is finish */
//        	//        			/***************************************/
//        	//        			while (drp_lib_status[TILE_0] == DRP_NOT_FINISH);
//        	//
//        	//        			/**********************/
//        	//        			/* Unload DRP Library */
//        	//        			/**********************/
//        	//        			ret_val = R_DK2_Unload(drp_lib_id[TILE_0], &drp_lib_id[TILE_0]);
//        	//        			DRP_DRV_ASSERT(ret_val);
//        	//
//        	//        			/* Set end time of DRP processing */
//        	//        			PerformSetEndTime(4);
//        	//
//        	//        			/************************************/
//        	//        			/* Load DRP Library                 */
//        	//        			/*        +-----------------------+ */
//        	//        			/* tile 0 |                       | */
//        	//        			/*        +                       + */
//        	//        			/* tile 1 | BinarizationAdaptive  | */
//        	//        			/*        +                       + */
//        	//        			/* tile 2 |                       | */
//        	//        			/*        +-----------------------+ */
//        	//        			/* tile 3 |                       | */
//        	//        			/*        +   FindContours_crop   + */    /* find countours with dedicated aspect ratio */
//        	//        			/* tile 4 |                       | */
//        	//        			/*        +-----------------------+ */
//        	//        			/* tile 5 |        Dilate         | */
//        	//        			/*        +-----------------------+ */
//        	//        			/************************************/
//        	//
//        	//        			/* Set start time of process*/
//        	//        			PerformSetStartTime(5);
//        	//
//        	//        			/*############             Dilate  ->           ##############*/
//        	//
//        	//        			ret_val = R_DK2_Load(&g_drp_lib_dilate[0],
//        	//        								R_DK2_TILE_5,
//        	//        								R_DK2_TILE_PATTERN_3_2_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
//        	//        			DRP_DRV_ASSERT(ret_val);
//        	//
//        	//        			/************************/
//        	//        			/* Activate DRP Library */
//        	//        			/************************/
//        	//        			ret_val = R_DK2_Activate(drp_lib_id[TILE_5], 0);
//        	//        			DRP_DRV_ASSERT(ret_val);
//        	//
//        	//        			/**********************************************************/
//        	//        			/* Set R_DK2_Start function parameters　for　Gaussian Blur */
//        	//        			/*********************************************************/
//        	//
//        	//        			/* Set Image size */
//        	//        			param_dilate.width  = R_BCD_CAMERA_WIDTH;
//        	//        			param_dilate.height = R_BCD_CAMERA_HEIGHT;
//        	//
//        	//        			/* Set the address of buffer to be read/write by DRP */
//        	//        			param_dilate.src = (uint32_t)&frame_RAM_C[0];
//        	//        			param_dilate.dst = (uint32_t)&frame_RAM_D[0];
//        	//        			R_MMU_VAtoPA((uint32_t)param_dilate.src, &(param_dilate.src ));
//        	//        			R_MMU_VAtoPA((uint32_t)param_dilate.dst, &(param_dilate.dst ));
//        	//
//        	//        			/* Set whether to perform top or bottom edge border processing. */
//        	//        			param_dilate.top    = 1;
//        	//        			param_dilate.bottom = 1;
//        	//
//        	//        			/* Initialize variables to be used in termination judgment of the DRP application */
//        	//        			drp_lib_status[TILE_5] = DRP_NOT_FINISH;
//        	//
//        	//        			/****************************/
//        	//        			/* Start DRP Library Dilate */
//        	//        			/****************************/
//        	//        			ret_val = R_DK2_Start(drp_lib_id[TILE_5], (void *)&param_dilate, sizeof(r_drp_dilate_t));
//        	//        			DRP_DRV_ASSERT(ret_val);
//        	//
//        	//
//        	//        			/*#######################################*/
//        	//        			/* Load DRP Library FindContours_crop    */
//        	//        			/*#######################################*/
//        	//
//        	//        			ret_val = R_DK2_Load(&g_drp_lib_find_contours_crop_t2[0],
//        	//        								  R_DK2_TILE_3,
//        	//        								  R_DK2_TILE_PATTERN_3_2_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
//        	//        			DRP_DRV_ASSERT(ret_val);
//        	//
//        	//        			/*####################################*/
//        	//        			/* Activate DRP Lib FindContours_crop */
//        	//        			/*####################################*/
//        	//        			ret_val = R_DK2_Activate(drp_lib_id[TILE_3], 0);
//        	//        			DRP_DRV_ASSERT(ret_val);
//        	//
//        	//
//        	//        			/************************************************/
//        	//        			/* Wait until DRP processing (Dilate) is finish */
//        	//        			/************************************************/
//        	//        			while (drp_lib_status[TILE_5] == DRP_NOT_FINISH);
//        	//
//        	//        			/**********************/
//        	//        			/* Unload DRP library */
//        	//        			/**********************/
//        	//        			ret_val = R_DK2_Unload(drp_lib_id[TILE_5], &drp_lib_id[0]);
//        	//        			DRP_DRV_ASSERT(ret_val);
//        	//
//        	//        			/* Set end time of DRP processing */
//        	//        			PerformSetEndTime(5);
//        	//
//        	//        			/*############   <-        Dilate               ##############*/
//        	//
//        	//        			/*############        FindContours_crop    ->   ##############*/
//        	//
//        	//        			/* Set start time of process*/
//        	//        			PerformSetStartTime(6);     // FindContours_crop
//        	//
//        	//        			/*************************************************************/
//        	//        			/* Set R_DK2_Start function parameters for FindContours_crop */
//        	//        			/*************************************************************/
//        	//
//        	//        			param_find_contours_crop.src = (uint32_t)&frame_RAM_D[0];               /* Address of input one lane image */
//        	//        			R_MMU_VAtoPA((uint32_t)param_find_contours_crop.src, &(param_find_contours_crop.src ));
//        	//
//        	//        			param_find_contours_crop.dst_rect = (uint32_t)&g_contours_rect_adr[0];    /* Address of rectangle information */
//        	//        			R_MMU_VAtoPA((uint32_t)param_find_contours_crop.dst_rect, &(param_find_contours_crop.dst_rect ));
//        	//
//        	//        			param_find_contours_crop.dst_rect_size         = FIND_CONTOURS_NUM;    /* max amount of rectangles to be generated */
//        	//
//        	//        			/* Set Image size */
//        	//        			param_find_contours_crop.width  = R_BCD_CAMERA_WIDTH;   /* The horizontal size (pixels) of image multiple of 8byte */
//        	//        			param_find_contours_crop.height = R_BCD_CAMERA_HEIGHT;  /* The vertical size (pixels) of image	minimum 5 lines    */
//        	//
//        	//        			/* Set whether to perform top or bottom edge border processing. */
//        	//        			param_find_contours_crop.work = (uint32_t)&work2[0];    /* Address of work area; minimum size = width * height / 4 + 8 */
//        	//        			R_MMU_VAtoPA((uint32_t)param_find_contours_crop.work, &(param_find_contours_crop.work ));
//        	//
//        	//        			param_find_contours_crop.dst_region = (uint32_t)&g_contours_region_adr[0];  /* Address of region information */
//        	//        			R_MMU_VAtoPA((uint32_t)param_find_contours_crop.dst_region, &(param_find_contours_crop.dst_region ));
//        	//
//        	//        			param_find_contours_crop.dst_region_size       = 0;     /* 0: no region output */
//        	//        			// param_find_contours_crop.dst_region_size = 10;       /* region information output for 10 pixel*/
//        	//
//        	//        			param_find_contours_crop.threshold_widthOrMin  = aspectfloat4contourfixedint(3.0); 	/* Threshold of width or min value		*/
//        	//        			param_find_contours_crop.threshold_heightOrMax = aspectfloat4contourfixedint(5.5); 	/* Threshold of height or max value		*/
//        	//
//        	//        			param_find_contours_crop.x_crop                = 8;                    /* Crop window x position     */
//        	//        			param_find_contours_crop.y_crop                = 8;                    /* Crop window y position     */
//        	//
//        	//        			param_find_contours_crop.width_crop            = (uint16_t)(R_BCD_CAMERA_WIDTH  - 16);  /* Crop window width  (min 3) */
//        	//        			param_find_contours_crop.height_crop           = (uint16_t)(R_BCD_CAMERA_HEIGHT - 16);  /* Crop window height (min 3) */
//        	//
//        	//        			param_find_contours_crop.mode                  = 0b00000011 ;
//        	//        				/* 0000RFFF (bit field)		  	 	    									*/
//        	//        				/*  R - origin of output coordinates										*/
//        	//        				/*		  0 - off (coordinates are relative to src picture)					*/
//        	//        				/*		  1 - on  (coordinates relative to crop	window upper left (0 0)) 	*/
//        	//        				/*  F - filter for box/region found											*/
//        	//        				/*		000 - boxWidth	>=	threshold_widthOrMin && boxHeight > threshold_heightOrMax																	*/
//        	//        				/*		001 - regionCnt >   threshold_region																											*/
//        	//        				/*		010 - boxWidth	>=	threshold_widthOrMin			  && boxHeight > threshold_heightOrMax					&& regionCnt >	threshold_region	*/
//        	//        				/*		011 - boxWidth/boxHeight*256 >= threshold_widthOrMin  && boxWidth/boxHeight*256 <= threshold_heightOrMax	&& regionCnt >	threshold_region	*/
//        	//        				/*		100 - boxWidth/boxHeight*256 >= threshold_widthOrMin  && regionCnt >	threshold_region														*/
//        	//        				/*		101 - boxWidth/boxHeight*256 <= threshold_heightOrMax && regionCnt >	threshold_region														*/
//        	//        				/*      110 - reserved																																	*/
//        	//        				/*      111 - reserved																																	*/
//        	//
//        	//        			param_find_contours_crop.dmode                  = 0b00000001 ;
//        	//        				/* WCBP000A (bit field)		  	 	    					*/
//        	//        				/*  W - draw cropping window 						-> dst_rgbDebug(RGB)	*/
//        	//        				/*		  0 - off, 1 -on 													*/
//        	//        				/*  C - draw contour data stored in dst_region into -> dst_rgbDebug(RGB)	*/
//        	//        				/*		  0 - off, 1 -on 													*/
//        	//        				/*  B - boundingBox	 draw bounding box into 		-> dst_rgbDebug(RGB)	*/
//        	//        				/*		  0 - off, 1 -on 													*/
//        	//        				/*  P - debug		 copy picture src 				-> dst_rgbDebug(RGB)	*/
//        	//        				/*		  0 - off, 1 -on 													*/
//        	//        				/*  A - output format for debug 					-> dst_rgbDebug(RGB)	*/
//        	//        				/*		  0 - RGB (24bit), 1 -ARGB(32bit) A channel set to 0				*/
//        	//
//        	//        			param_find_contours_crop.threshold_region       = 500 ;		/* Threshold contour count (number of found contour pixel) (example 30)                            */
//        	//        			param_find_contours_crop.dst_rgbDebug           = 0 ; 		/* Output address for RGB picture, debug bounding box(blue), found region(red), found pixel(green) */
//        	//        																		/*please set to NULL if not used. Size is same as "width" * "height" of "src"                      */
//        	//
//        	//
//        	//        			/* Initialize variables to be used in termination judgment of the DRP library */
//        	//        			drp_lib_status[TILE_3] = DRP_NOT_FINISH;
//        	//
//        	//        			/***************************************/
//        	//        			/* Start DRP Library FindContours_crop */
//        	//        			/***************************************/
//        	//        			ret_val = R_DK2_Start(drp_lib_id[TILE_3], (void *)&param_find_contours_crop, sizeof(r_drp_find_contours_crop_t));
//        	//        			DRP_DRV_ASSERT(ret_val);
//        	//
//        	//
//        	//        			/*############    -  BinarizationAdaptive  -    ##############*/
//        	//
//        	//        			/*****************************************/
//        	//        			/* Load DRP Library BinarizationAdaptive */
//        	//        			/*****************************************/
//        	//        			ret_val = R_DK2_Load(&g_drp_lib_binarization_adaptive[0],
//        	//        			                      R_DK2_TILE_0,
//        	//        				                  R_DK2_TILE_PATTERN_3_2_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
//        	//        			DRP_DRV_ASSERT(ret_val);
//        	//
//        	//        			/*****************************************/
//        	//        			/* Activate DRP Lib BinarizationAdaptive */
//        	//        			/*****************************************/
//        	//        			ret_val = R_DK2_Activate(drp_lib_id[TILE_0], 0);
//        	//        			DRP_DRV_ASSERT(ret_val);
//        	//
//        	//        			/****************************************************************/
//        	//        			/* Set R_DK2_Start function parameters for BinarizationAdaptive */
//        	//        			/****************************************************************/
//        	//
//        	//        			param_binarization_adaptive.src        = (uint32_t)&frame_RAM_A[0];      /* Address of image to be binarized. */
//        	//        			param_binarization_adaptive.dst        = (uint32_t)&frame_RAM_E[0];      /* Address to output binarized result. */
//        	//        			param_binarization_adaptive.width      = (uint16_t)R_BCD_CAMERA_WIDTH;   /* The horizontal size (pixels) of the image to be binarized. */
//        	//        			param_binarization_adaptive.height     = (uint16_t)R_BCD_CAMERA_HEIGHT;  /* The vertical size (pixels) of the image to be binarized. */
//        	//        			param_binarization_adaptive.work       = (uint32_t)&work3[0];            /* Address of the work buffer used by the library. */
//        	//        			param_binarization_adaptive.range      = 0x0;                            /* A luminance difference to judge whether it is effective average luminance.(8x8 pixel) */
//        	//
//        	//        			/* Initialize variables to be used in termination judgment of the DRP application */
//        	//        			drp_lib_status[TILE_0] = DRP_NOT_FINISH;
//        	//
//        	//        			/******************************************/
//        	//        			/* Start DRP Library BinarizationAdaptive */
//        	//        			/******************************************/
//        	//        			ret_val = R_DK2_Start(drp_lib_id[TILE_0], (void *)&param_binarization_adaptive, sizeof(r_drp_binarization_adaptive_t));
//        	//        			DRP_DRV_ASSERT(ret_val);
//        	//
//        	//
//        	//        			/*****************************************/
//        	//        			/* Wait until FindContours_crop finished */
//        	//        			/*****************************************/
//        	//        			while (drp_lib_status[TILE_3] == DRP_NOT_FINISH);  // FindContours_crop
//        	//
//        	//        			/*############   <-   FindContours_crop         ##############*/
//        	//
//        	//        			/* Set end time of DRP processing */
//        	//        			PerformSetEndTime(6);
//
//        } /* find all contours */
//
//
//
////        p_input_bufadr  = R_BCD_CameraGetFrameAddress(frame_buf_id);
////        p_output_bufadr = R_BCD_LcdGetVramAddress();
////        p_work_bufadr   = (uint8_t *)&work_buf[0];
////        p_work_bufadr_bin2med = (uint8_t *)&work_buf_2[0];
////        p_work_bufadr_med2contours = (uint8_t *)&work_buf_3[0];
////
////        /* convert to phisical address */
////        R_MMU_VAtoPA((uint32_t)p_input_bufadr, &input_bufadr);
////
////        /* convert to phisical address */
////        R_MMU_VAtoPA((uint32_t)p_output_bufadr, &output_bufadr);
////
////        /* convert to phisical address */
////        R_MMU_VAtoPA((uint32_t)p_work_bufadr, &work_bufadr);
////
////        /* convert to phisical address */
////        R_MMU_VAtoPA((uint32_t)p_work_bufadr_bin2med, &work_bufadr_bin2med);
////
////        /* convert to phisical address */
////        R_MMU_VAtoPA((uint32_t)p_work_bufadr_med2contours, &work_bufadr_med2contours);
////
////        /* convert to phisical address */
////        R_MMU_VAtoPA((uint32_t)p_work_bufadr_med2thin, &work_bufadr_med2thin);
//////        printf("sizeof input to b2g: %li", sizeof(input_bufadr));
////        printf("Hi0 \n");
////
////        /******************************/
////        /* Load DRP Library           */
////        /*        +-----------------+ */
////        /* tile 0 | Bayer2Grayscale | */
////        /*        +-----------------+ */
////        /* tile 1 | Bayer2Grayscale | */
////        /*        +-----------------+ */
////        /* tile 2 | Bayer2Grayscale | */
////        /*        +-----------------+ */
////        /* tile 3 | Bayer2Grayscale | */
////        /*        +-----------------+ */
////        /* tile 4 | Bayer2Grayscale | */
////        /*        +-----------------+ */
////        /* tile 5 | Bayer2Grayscale | */
////        /*        +-----------------+ */
////        /******************************/
////        ret_val = R_DK2_Load(&g_drp_lib_bayer2grayscale[0],
////                            R_DK2_TILE_0 | R_DK2_TILE_1 | R_DK2_TILE_2 | R_DK2_TILE_3 | R_DK2_TILE_4 | R_DK2_TILE_5,
////                            R_DK2_TILE_PATTERN_1_1_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
////        DRP_DRV_ASSERT(ret_val);
//////        printf("b2g load ret val = %d", ret_val);
////
////        /************************/
////        /* Activate DRP Library */
////        /************************/
////        ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
////                                | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], 0);
////        DRP_DRV_ASSERT(ret_val);
//////        printf("b2g activate ret val = %d", ret_val);
////
////        /* Set start time of process*/
////        PerformSetStartTime(0);;
////
////
////
////        /***************************************/
////        /* Set R_DK2_Start function parameters */
////        /***************************************/
////        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
////        {
////            /* Set the address of buffer to be read/write by DRP */
////            param_b2g[tile_no].src = input_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////                                                                                                            * tile_no);
////            param_b2g[tile_no].dst = work_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////                                                                                                            * tile_no);
//////            param_b2g[tile_no].dst = output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//////                                                                                                             * tile_no);
////
////            /* Set Image size */
////            param_b2g[tile_no].width = R_BCD_CAMERA_WIDTH;
////            param_b2g[tile_no].height = R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM;
////
////            /* Set whether to perform top or bottom edge border processing. */
////            param_b2g[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
////            param_b2g[tile_no].bottom = (tile_no == TILE_5) ? 1 : 0;
////
////            /* Initialize variables to be used in termination judgment of the DRP library */
////            drp_lib_status[tile_no] = DRP_NOT_FINISH;
////
////            /*********************/
////            /* Start DRP Library */
////            /*********************/
////            ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_b2g[tile_no], sizeof(r_drp_bayer2grayscale_t));
////            DRP_DRV_ASSERT(ret_val);
//////            printf("b2g start ret val = %d", ret_val);
////        }
////
////        /***************************************/
////        /* Wait until DRP processing is finish */
////        /***************************************/
////        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
////        {
////            while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
////            {
////                /* DO NOTHING */
////            }
////        }
////
////        /* Set end time of process */
////        PerformSetEndTime(0);
////        printf("Hi1 \n");
////
////
////        /**********************/
////        /* Unload DRP Library */
////        /**********************/
////        ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
////                                                            | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], &drp_lib_id[0]);
////        DRP_DRV_ASSERT(ret_val);
//////        printf("b2g unload ret val = %d", ret_val);
////
//////        /* Clear the current capture state and enable the detection of the next capture completion */
//////        R_BCD_CameraClearCaptureStatus();
//////
//////        /* Capture Start */
//////        R_BCD_CameraCaptureStart();
////
//////        /* Display image processing result */
//////        R_BCD_LcdSwapVideoBuffer();
////
//////        printf("sizeof output of b2g: %li", sizeof(work_bufadr));
////
////
////
////
////
//////        /******************************************************************************************************/
//////        /******************************/
//////        /* Load DRP Library           */
//////        /*        +-----------------+ */
//////        /* tile 0 | 	Sobel		| */
//////        /*        +-----------------+ */
//////        /* tile 1 | 	Sobel		| */
//////        /*        +-----------------+ */
//////        /* tile 2 | 	Sobel		| */
//////        /*        +-----------------+ */
//////        /* tile 3 | 	Sobel		| */
//////        /*        +-----------------+ */
//////        /* tile 4 | 	Sobel		| */
//////        /*        +-----------------+ */
//////        /* tile 5 | 	Sobel		| */
//////        /*        +-----------------+ */
//////        /******************************/
//////        ret_val = R_DK2_Load(&g_drp_lib_sobel[0],
//////        		R_DK2_TILE_0 | R_DK2_TILE_1 | R_DK2_TILE_2 | R_DK2_TILE_3 | R_DK2_TILE_4 | R_DK2_TILE_5,
//////				R_DK2_TILE_PATTERN_1_1_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
//////        DRP_DRV_ASSERT(ret_val);
//////        //        printf("b2g load ret val = %d", ret_val);
//////
//////        /************************/
//////        /* Activate DRP Library */
//////        /************************/
//////        ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
//////																										   | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], 0);
//////        DRP_DRV_ASSERT(ret_val);
//////        //        printf("b2g activate ret val = %d", ret_val);
//////
//////        /* Set start time of process*/
//////        PerformSetStartTime(7);;
//////
//////
//////
//////        /***************************************/
//////        /* Set R_DK2_Start function parameters */
//////        /***************************************/
//////        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//////        {
//////        	/* Set the address of buffer to be read/write by DRP */
//////        	param_sobel[tile_no].src = work_bufadr_bin2med + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//////        			* tile_no);
//////        	//            param_b2g[tile_no].dst = work_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//////        	//                                                                                                            * tile_no);
//////        	param_sobel[tile_no].dst = output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//////        			* tile_no);
//////
//////        	/* Set Image size */
//////        	param_sobel[tile_no].width = R_BCD_CAMERA_WIDTH;
//////        	param_sobel[tile_no].height = R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM;
//////
//////        	/* Set whether to perform top or bottom edge border processing. */
//////        	param_sobel[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
//////        	param_sobel[tile_no].bottom = (tile_no == TILE_5) ? 1 : 0;
//////
//////        	/* Initialize variables to be used in termination judgment of the DRP library */
//////        	drp_lib_status[tile_no] = DRP_NOT_FINISH;
//////
//////        	/*********************/
//////        	/* Start DRP Library */
//////        	/*********************/
//////        	ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_sobel[tile_no], sizeof(r_drp_sobel_t));
//////        	DRP_DRV_ASSERT(ret_val);
//////        	//            printf("b2g start ret val = %d", ret_val);
//////        }
//////
//////        /***************************************/
//////        /* Wait until DRP processing is finish */
//////        /***************************************/
//////        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//////        {
//////        	while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
//////        	{
//////        		/* DO NOTHING */
//////        	}
//////        }
//////
//////        /* Set end time of process */
//////        PerformSetEndTime(7);
//////        printf("Hi1 \n");
//////
//////
//////        /**********************/
//////        /* Unload DRP Library */
//////        /**********************/
//////        ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
//////																										 | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], &drp_lib_id[0]);
//////        DRP_DRV_ASSERT(ret_val);
//////
//////
//////        /******************************************************************************************************/
////
////
////
////
////
////        /******************************************************************************************************/
////        /************************************/
////        /* Load DRP Library                 */
////        /*        +-----------------------+ */
////        /* tile 0 |                       | */
////        /*        +                       + */
////        /* tile 1 | BinarizationAdaptive  | */
////        /*        +                       + */
////        /* tile 2 |                       | */
////        /*        +-----------------------+ */
////        /* tile 3 |                       | */
////        /*        +                       + */
////        /* tile 4 |                       | */
////        /*        |                       | */
////        /* tile 5 |                       | */
////        /*        +-----------------------+ */
////        /************************************/
////
////		/*############    -  BinarizationAdaptive  -    ##############*/
////
////
////
////		/*****************************************/
////		/* Load DRP Library BinarizationAdaptive */
////		/*****************************************/
////		ret_val = R_DK2_Load(&g_drp_lib_binarization_adaptive[0],
////				R_DK2_TILE_0,
////				R_DK2_TILE_PATTERN_3_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
////		DRP_DRV_ASSERT(ret_val);
//////		printf("bin-ad load ret val = %d", ret_val);
////
////		/*****************************************/
////		/* Activate DRP Lib BinarizationAdaptive */
////		/*****************************************/
////		ret_val = R_DK2_Activate(drp_lib_id[TILE_0], 0);
////		DRP_DRV_ASSERT(ret_val);
//////		printf("bin-ad activate ret val = %d", ret_val);
////
////		/* Set start time of process*/
////		PerformSetStartTime(1);
////
////		/****************************************************************/
////		/* Set R_DK2_Start function parameters for BinarizationAdaptive */
////		/****************************************************************/
////
////		param_binarization_adaptive.src        = work_bufadr;     					/* Address of image to be binarized. */
////		param_binarization_adaptive.dst        = work_bufadr_bin2med;       		/* Address to output binarized result. */
//////		param_binarization_adaptive.dst        = output_bufadr;
////		param_binarization_adaptive.width      = (uint16_t)R_BCD_CAMERA_WIDTH;   	/* The horizontal size (pixels) of the image to be binarized. */
////		param_binarization_adaptive.height     = (uint16_t)R_BCD_CAMERA_HEIGHT;  	/* The vertical size (pixels) of the image to be binarized. */
////		param_binarization_adaptive.work       = (uint32_t)&work3[0];            	/* Address of the work buffer used by the library. */
////		param_binarization_adaptive.range      = 0x03;                            	/* A luminance difference to judge whether it is effective average luminance.(8x8 pixel) */
////
////		/* Initialize variables to be used in termination judgment of the DRP application */
////		drp_lib_status[TILE_0] = DRP_NOT_FINISH;
////
////		/******************************************/
////		/* Start DRP Library BinarizationAdaptive */
////		/******************************************/
////		ret_val = R_DK2_Start(drp_lib_id[TILE_0], (void *)&param_binarization_adaptive, sizeof(r_drp_binarization_adaptive_t));
////		DRP_DRV_ASSERT(ret_val);
//////		printf("bin-ad start ret val = %d", ret_val);
////
////
////		/*******************************************************/
////		/* Wait until BinarizationAdaptive processing finished */
////		/*******************************************************/
////		while (drp_lib_status[TILE_0] == DRP_NOT_FINISH);  // BinarizationAdaptive
////
////		/*******************************************/
////		/* Unload DRP library BinarizationAdaptive */
////		/*******************************************/
////		ret_val = R_DK2_Unload(drp_lib_id[TILE_0], &drp_lib_id[TILE_0]);
////		DRP_DRV_ASSERT(ret_val);
//////		printf("bin-ad unload ret val = %d", ret_val);
////
////		/* Set end time of DRP processing */
////		PerformSetEndTime(1);
////		printf("Hi2 \n");
////
//////		/* Clear the current capture state and enable the detection of the next capture completion */
//////		R_BCD_CameraClearCaptureStatus();
//////
//////		/* Capture Start */
//////		R_BCD_CameraCaptureStart();
//////
//////		/* Display image processing result */
//////		R_BCD_LcdSwapVideoBuffer();
////
//////		printf("sizeof output of binarization: %li", sizeof(work_bufadr_bin2med));
////
////		/******************************************************************************************************/
////
////
//////		/******************************************************************************************************/
//////		/******************************/
//////		/* Load DRP Library           */
//////		/*        +-----------------+ */
//////		/* tile 0 |  gaussian blur	| */
//////		/*        +-----------------+ */
//////		/* tile 1 |  gaussian blur	| */
//////		/*        +-----------------+ */
//////		/* tile 2 |  gaussian blur	| */
//////		/*        +-----------------+ */
//////		/* tile 3 |  gaussian blur	| */
//////		/*        +-----------------+ */
//////		/* tile 4 |  gaussian blur	| */
//////		/*        +-----------------+ */
//////		/* tile 5 |  gaussian blur	| */
//////		/*        +-----------------+ */
//////		/******************************/
//////		ret_val = R_DK2_Load(&g_drp_lib_gaussian_blur[0],
//////				R_DK2_TILE_0 | R_DK2_TILE_1 | R_DK2_TILE_2 | R_DK2_TILE_3 | R_DK2_TILE_4 | R_DK2_TILE_5,
//////				R_DK2_TILE_PATTERN_1_1_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
//////		DRP_DRV_ASSERT(ret_val);
//////		//        printf("b2g load ret val = %d", ret_val);
//////
//////		/************************/
//////		/* Activate DRP Library */
//////		/************************/
//////		ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
//////																										   | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], 0);
//////		DRP_DRV_ASSERT(ret_val);
//////		//        printf("b2g activate ret val = %d", ret_val);
//////
//////		/* Set start time of process*/
//////		PerformSetStartTime(6);;
//////
//////
//////
//////		/***************************************/
//////		/* Set R_DK2_Start function parameters */
//////		/***************************************/
//////		for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//////		{
//////			/* Set the address of buffer to be read/write by DRP */
//////			param_gaussian_blur[tile_no].src = work_bufadr_bin2med + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//////					* tile_no);
//////			//        	param_gaussian_blur[tile_no].dst = work_bufadr_bin2med + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//////			//        			* tile_no);
//////			param_gaussian_blur[tile_no].dst = output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//////					* tile_no);
//////
//////			/* Set Image size */
//////			param_gaussian_blur[tile_no].width = R_BCD_CAMERA_WIDTH;
//////			param_gaussian_blur[tile_no].height = R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM;
//////
//////			/* Set whether to perform top or bottom edge border processing. */
//////			param_gaussian_blur[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
//////			param_gaussian_blur[tile_no].bottom = (tile_no == TILE_5) ? 1 : 0;
//////
//////			/* Initialize variables to be used in termination judgment of the DRP library */
//////			drp_lib_status[tile_no] = DRP_NOT_FINISH;
//////
//////			/*********************/
//////			/* Start DRP Library */
//////			/*********************/
//////			ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_gaussian_blur[tile_no], sizeof(r_drp_gaussian_blur_t));
//////			DRP_DRV_ASSERT(ret_val);
//////			//            printf("b2g start ret val = %d", ret_val);
//////		}
//////
//////		/***************************************/
//////		/* Wait until DRP processing is finish */
//////		/***************************************/
//////		for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//////		{
//////			while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
//////			{
//////				/* DO NOTHING */
//////			}
//////		}
//////
//////		/* Set end time of process */
//////		PerformSetEndTime(6);
//////		printf("Hi1 \n");
//////
//////
//////		/**********************/
//////		/* Unload DRP Library */
//////		/**********************/
//////		ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
//////																										 | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], &drp_lib_id[0]);
//////		DRP_DRV_ASSERT(ret_val);
//////
//////
//////		/******************************************************************************************************/
////
////
////
////		/******************************************************************************************************/
////		/**************************/
////		/* Load DRP Library       */
////		/*        +-------------+ */
////		/* tile 0 | Median blur | */
////		/*        +-------------+ */
////		/* tile 1 | Median blur | */
////		/*        +-------------+ */
////		/* tile 2 | Median blur | */
////		/*        +-------------+ */
////		/* tile 3 | Median blur | */
////		/*        +-------------+ */
////		/* tile 4 | Median blur | */
////		/*        +-------------+ */
////		/* tile 5 | Median blur | */
////		/*        +-------------+ */
////		/**************************/
////		ret_val = R_DK2_Load(&g_drp_lib_median_blur[0],
////				R_DK2_TILE_0 | R_DK2_TILE_1 | R_DK2_TILE_2 | R_DK2_TILE_3 | R_DK2_TILE_4 | R_DK2_TILE_5,
////				R_DK2_TILE_PATTERN_1_1_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
////		DRP_DRV_ASSERT(ret_val);
////		/************************/
////		/* Activate DRP Library */
////		/************************/
////		ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
////																										   | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], 0);
////		DRP_DRV_ASSERT(ret_val);
////		/* Set start time of process*/
////		PerformSetStartTime(2);
////		/***************************************/
////		/* Set R_DK2_Start function parameters */
////		/***************************************/
////		for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
////		{
////			/* Set the address of buffer to be read/write by DRP */
////			param_median[tile_no].src = work_bufadr_bin2med + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////					* tile_no);
//////			param_median[tile_no].dst = work_bufadr_med2thin + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//////					* tile_no);
////			param_median[tile_no].dst = output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////								* tile_no);
//////			param_median[tile_no].dst = (uint32_t)&p_work_bufadr_med2thin[0];   + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//////					* tile_no);
//////
//////			R_MMU_VAtoPA((uint32_t)param_median[tile_no].dst, &(param_median[tile_no].dst ));
////
////			/* Set Image size */
////			param_median[tile_no].width = R_BCD_CAMERA_WIDTH;
////			param_median[tile_no].height = R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM;
////			/* Set whether to perform top or bottom edge border processing. */
////			param_median[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
////			param_median[tile_no].bottom = (tile_no == TILE_5) ? 1 : 0;
////			/* Initialize variables to be used in termination judgment of the DRP library */
////			drp_lib_status[tile_no] = DRP_NOT_FINISH;
////			/*********************/
////			/* Start DRP Library */
////			/*********************/
////			ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_median[tile_no], sizeof(r_drp_median_blur_t));
////			DRP_DRV_ASSERT(ret_val);
////		}
////
////		/***************************************/
////		/* Wait until DRP processing is finish */
////		/***************************************/
////		for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
////		{
////			while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
////			{
////				/* DO NOTHING */
////			}
////		}
////
////		/* Set end time of process */
////		PerformSetEndTime(2);
////		/**********************/
////		/* Unload DRP library */
////		/**********************/
////		ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3] |
////				drp_lib_id[TILE_4] | drp_lib_id[TILE_5], &drp_lib_id[TILE_0]);
////		DRP_DRV_ASSERT(ret_val);
////
////
////		//		/* Clear the current capture state and enable the detection of the next capture completion */
////		//		R_BCD_CameraClearCaptureStatus();
////		//
////		//		/* Capture Start */
////		//		R_BCD_CameraCaptureStart();
////
//////		/* Display image processing result */
//////		R_BCD_LcdSwapVideoBuffer();
////
////		printf("Hi3 \n");
////
//////		printf("sizeof output of binarization: %li", sizeof(work_bufadr_bin2med));
////
////		/******************************************************************************************************/
////
////
//////        /******************************************************************************************************/
//////        /******************************/
//////        /* Load DRP Library           */
//////        /*        +-----------------+ */
//////        /* tile 0 |                 | */
//////        /*        +                 + */
//////        /* tile 1 |    Thinning     | */
//////        /*        +                 + */
//////        /* tile 2 |                 | */
//////        /*        +-----------------+ */
//////        /* tile 3 |                 | */
//////        /*        +                 + */
//////        /* tile 4 |    Thinning     | */
//////        /*        +                 + */
//////        /* tile 5 |                 | */
//////        /*        +-----------------+ */
//////        /******************************/
//////        ret_val = R_DK2_Load(&g_drp_lib_thinning[0], R_DK2_TILE_0 | R_DK2_TILE_3,
//////        		R_DK2_TILE_PATTERN_3_3, NULL, &cb_drp_finish, &drp_lib_id[0]);
//////        DRP_DRV_ASSERT(ret_val);
//////
//////        /********************/
//////        /* Activate DRP Lib */
//////        /********************/
//////        ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_3], 0);
//////        DRP_DRV_ASSERT(ret_val);
//////
//////        /* Set start time of process*/
//////        PerformSetStartTime(3);
//////
//////        /***************************************/
//////        /* Set R_DK2_Start function parameters */
//////        /***************************************/
//////        for (tile_no = TILE_0; tile_no <= TILE_3; tile_no += 3)
//////        {
//////        	/* Set Image size */
//////        	param_thinning[tile_no].width = R_BCD_CAMERA_WIDTH;
//////        	param_thinning[tile_no].height = (R_BCD_CAMERA_HEIGHT / 2);
//////
//////        	/* Set Buffer size */
//////        	bufsize_thinning = (uint32_t)(param_thinning[tile_no].width * param_thinning[tile_no].height);
//////
//////        	/* Set the address of buffer to be read/write by DRP */
//////        	param_thinning[tile_no].src = work_bufadr_med2thin + ((tile_no / 3) * bufsize_thinning);
////////        	param_thinning[tile_no].dst = output_bufadr  + ((tile_no / 3) * bufsize_thinning);
//////        	param_thinning[tile_no].dst = output_bufadr  + ((tile_no / 3) * bufsize_thinning);
//////
//////
//////        	/* Set additional information (currently no additional information) */
//////        	param_thinning[tile_no].result =
//////        			(uint32_t)&thinning_result_buf[((tile_no / 3) * (bufsize_thinning + (R_BCD_CAMERA_WIDTH*2) ))*2];
//////        	param_thinning[tile_no].threshold = 0x01;
//////        	param_thinning[tile_no].reverse = 1;
//////
//////        	/* Set whether to perform top or bottom edge border processing. */
//////        	param_thinning[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
//////        	param_thinning[tile_no].bottom = (tile_no == TILE_3) ? 1 : 0;
//////
//////        	param_thinning[tile_no].step = 0;
//////
//////
//////
//////        	/* Initialize variables to be used in termination judgment of the DRP library */
//////        	drp_lib_status[tile_no] = DRP_NOT_FINISH;
//////
//////        	/*********************/
//////        	/* Start DRP Library */
//////        	/*********************/
//////        	ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_thinning[tile_no],
//////        			sizeof(r_drp_thinning_t));
//////        	DRP_DRV_ASSERT(ret_val);
//////        }
//////
//////        /***************************************/
//////        /* Wait until DRP processing is finish */
//////        /***************************************/
//////        for (tile_no = TILE_0; tile_no <= TILE_3; tile_no += 3)
//////        {
//////        	/***************************************/
//////        	/* Wait until DRP processing is finish */
//////        	/***************************************/
//////        	while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
//////        	{
//////        		/* DO NOTHING */
//////        	}
//////        }
//////
//////        /* Set end time of DRP processing */
//////        PerformSetEndTime(3);
//////
//////        /**********************/
//////        /* Unload DRP library */
//////        /**********************/
//////        ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_3] , &drp_lib_id[TILE_0]);
//////        DRP_DRV_ASSERT(ret_val);
//////
//////
//////        /******************************************************************************************************/
////
//////        for(int height = 0 ; height < R_BCD_LCD_HEIGHT; height ++ )
//////        {
//////            for(int width = 0 ; width < R_BCD_LCD_WIDTH ; width ++ )
//////            {
//////                p_output_bufadr[(R_BCD_LCD_WIDTH * height) + width]
//////                                    = 255 - p_work_bufadr_med2thin[(R_BCD_CAMERA_WIDTH * height) + width];
//////            }
//////        }
////
////
//////        R_MMU_VAtoPA((uint32_t)p_output_bufadr, &output_bufadr);
////
////
////
////
////
////
////        /******************************************************************************************************/
////
////
////		/******************************************************************************************************/
////		/************************************/
////        /* Load DRP Library                 */
////        /*        +-----------------------+ */
////        /* tile 0 |                       | */
////        /*        +                       + */
////        /* tile 1 |       		  	      | */
////        /*        +                       + */
////        /* tile 2 |                       | */
////        /*        +-----------------------+ */
////        /* tile 3 |                       | */
////        /*        +     FindContours      + */
////        /* tile 4 |                       | */
////        /*        +-----------------------+ */
////        /* tile 5 |                       | */
////        /*        +-----------------------+ */
////        /************************************/
////
////
////        /*****************************************/
////        /* Load DRP Library BinarizationAdaptive */
////        /*****************************************/
////        ret_val = R_DK2_Load(&g_drp_lib_find_contours[0],
////        		R_DK2_TILE_3,
////				R_DK2_TILE_PATTERN_3_2_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
//////        ret_val = R_DK2_Load(&g_drp_lib_find_contours[0],
//////        		R_DK2_TILE_0,
//////				R_DK2_TILE_PATTERN_2_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
////        DRP_DRV_ASSERT(ret_val);
////        //		printf("bin-ad load ret val = %d", ret_val);
////        printf("load find contours \n");
////
////        /*****************************************/
////        /* Activate DRP Lib BinarizationAdaptive */
////        /*****************************************/
////        ret_val = R_DK2_Activate(drp_lib_id[TILE_3], 0);
//////        ret_val = R_DK2_Activate(drp_lib_id[TILE_3], 0);
////        DRP_DRV_ASSERT(ret_val);
////        //		printf("bin-ad activate ret val = %d", ret_val);
////        printf("activate find contours \n");
////
////        /* Set start time of process*/
////        PerformSetStartTime(3);
////
////
////        /****************************************************************/
////        /* Set R_DK2_Start function parameters for BinarizationAdaptive */
////        /****************************************************************/
////        /* Cast to an appropriate type */
////        param_find_contours.src = output_bufadr;
//////        param_find_contours.src = (uint32_t)&p_output_bufadr[0];
////
////        /* Cast to an appropriate type */
//////        R_MMU_VAtoPA((uint32_t) param_find_contours.src, &(param_find_contours.src));
////
////        /* Cast to an appropriate type */
////        param_find_contours.dst_region = (uint32_t)&g_contours_region_adr[0];
////
////        /* Cast to an appropriate type */
////        R_MMU_VAtoPA((uint32_t) param_find_contours.dst_region, &(param_find_contours.dst_region));
////
////        /* Set Image size */
////        param_find_contours.width = (uint16_t)R_BCD_CAMERA_WIDTH;
////        param_find_contours.height = (uint16_t)R_BCD_CAMERA_HEIGHT;
////
////        /* Set whether to perform top or bottom edge border processing. */
////        /* Cast to an appropriate type */
//////        param_find_contours.work = (uint32_t)&p_frame_ram1[0];
//////        param_find_contours.work = p_frame_ram1;
////
////        /*Error when work 4 is used*/
////        param_find_contours.work = (uint32_t)work_find_contours[0];    /* Address of work area; minimum size = width * height / 4 + 8 */
//////        param_find_contours.work = (uint32_t)work_find_contours;
////
////        /* Cast to an appropriate type */
////        R_MMU_VAtoPA((uint32_t) param_find_contours.work, &(param_find_contours.work));
////
////        /* Cast to an appropriate type */
////        param_find_contours.dst_rect = (uint32_t)&g_contours_rect_adr[0];
////
////        /* Cast to an appropriate type */
////        R_MMU_VAtoPA((uint32_t) param_find_contours.dst_rect, &(param_find_contours.dst_rect));
////
////        //         param_find_contours.dst_region_size = FIND_CONTOURS_NUM;
//////        Dont assign a lower value (eg 100 to dst_region)
//////        param_find_contours.dst_region_size = 500000;
////        param_find_contours.dst_region_size = 0;
////        param_find_contours.dst_rect_size = FIND_CONTOURS_NUM;
//////        param_find_contours.dst_rect_size = 20000;
////        param_find_contours.threshold_width = 50;
////        param_find_contours.threshold_height = 50;
////
////
////        /* Initialize variables to be used in termination judgment of the DRP application */
////        drp_lib_status[TILE_3] = DRP_NOT_FINISH;
////
////        /******************************************/
////        /* Start DRP Library BinarizationAdaptive */
////        /******************************************/
////        ret_val = R_DK2_Start(drp_lib_id[TILE_3], (void *)&param_find_contours, sizeof(r_drp_find_contours_t));
////        DRP_DRV_ASSERT(ret_val);
////        //		printf("bin-ad start ret val = %d", ret_val);
////        printf("start find contours \n");
////
////
////        /*******************************************************/
////        /* Wait until BinarizationAdaptive processing finished */
////        /*******************************************************/
//////        while (drp_lib_status[TILE_3] == DRP_NOT_FINISH);
////
////		while (drp_lib_status[TILE_3] == DRP_NOT_FINISH)
////		{
////			/* DO NOTHING */
//////			printf("***still in loop*** \n");
////		}
////
////        printf("drp finished \n");
////
////        /*******************************************/
////        /* Unload DRP library BinarizationAdaptive */
////        /*******************************************/
////        ret_val = R_DK2_Unload(drp_lib_id[TILE_3], &drp_lib_id[TILE_3]);
////        DRP_DRV_ASSERT(ret_val);
////        //		printf("bin-ad unload ret val = %d", ret_val);
////        printf("unload find contours \n");
////
////        PerformSetEndTime(3);
////
////
////        /******************************************************************************************************/
////
////
////
////        printf("Hi4 \n");
////        uint32_t num_contours = 0;
////        int32_t x, y, length, height;
////        uint8_t  color;
//////        R_BCD_LcdClearGraphicsBuffer();
////        printf("size of g_contours_rect_adr = %i \n",sizeof(g_contours_rect_adr));
////        printf("g_contours_rect_adr[0].x = %i \n",g_contours_rect_adr[0].x);
//////        R_BCD_LcdWriteLine( 100         ,  100          , 200         , 200, color);
//////
//////        /* Write the data(buf) on the cache to physical memory */
//////        R_CACHE_L1DataCleanLine(R_BCD_LcdGetOLVramAddress(), (R_BCD_LCD_WIDTH * R_BCD_LCD_HEIGHT));
//////
//////        /* Write the data(buf) on the cache to physical memory */
//////        R_CACHE_L1DataCleanLine(output_bufadr, ((R_BCD_LCD_WIDTH * R_BCD_LCD_HEIGHT) * 4));
//////
////////        R_BCD_CameraClearCaptureStatus();
//////
////////        R_BCD_LcdSwapGraphicsBuffer();
//////        R_BCD_LcdSwapVideoBuffer();
////
////
////        while ((bcd_drp_check_empty_contours(num_contours)) && (num_contours <= (uint32_t)FIND_CONTOURS_NUM))
////        {
////        	x     = g_contours_rect_adr[num_contours].x;
////        	printf("\n%li x = %li ", num_contours, x);
////        	y     = g_contours_rect_adr[num_contours].y;
////        	printf("\n%li y = %li ", num_contours, y);
////        	length = g_contours_rect_adr[num_contours].width;
////        	printf("\n%li length = %li ", num_contours, length);
////        	height = g_contours_rect_adr[num_contours].height;
////        	printf("\n%li height = %li ", num_contours, height);
////
////        	color = RED;
////        	R_BCD_LcdWriteLine( x          ,  y          , (x + length),  y          , color);
////        	R_BCD_LcdWriteLine((x + length),  y          , (x + length), (y + height), color);
////        	R_BCD_LcdWriteLine( x          , (y + height), (x + length), (y + height), color);
////        	R_BCD_LcdWriteLine( x          ,  y          ,  x          , (y + height), color);
//////        	R_BCD_LcdWriteLine( 100         ,  100          ,  x          , 200, color);
////
////        	num_contours++;
////        }
////
////    	/* Write the data(buf) on the cache to physical memory */
////    	R_CACHE_L1DataCleanLine(R_BCD_LcdGetOLVramAddress(), (R_BCD_LCD_WIDTH * R_BCD_LCD_HEIGHT));
////
////    	/* Write the data(buf) on the cache to physical memory */
////    	R_CACHE_L1DataCleanLine(output_bufadr, ((R_BCD_LCD_WIDTH * R_BCD_LCD_HEIGHT) * 4));
////
////    	//        R_BCD_CameraClearCaptureStatus();
////
////    	//        R_BCD_LcdSwapGraphicsBuffer();
////    	R_BCD_LcdSwapVideoBuffer();
////
////        printf("Hi5 \n");
//
//
//
////		us = PerformGetElapsedTime_us(0);
////		sprintf((void *)&buf[0],"Bayer2Grayscale : %d.%d[ms]", (int)(us / 1000), (int)((us - ((us / 1000) * 1000))
////				/ 100));
////		R_BCD_LcdWriteString(&buf[0], 2, 2, GREEN);
////		us = PerformGetElapsedTime_us(1);
////		sprintf((void *)&buf[0],"binarization : %d.%d[ms]", (int)(us / 1000), (int)((us - ((us / 1000) * 1000))
////				/ 100));
////		R_BCD_LcdWriteString(&buf[0], 2, 32, GREEN);
////		us = PerformGetElapsedTime_us(2);
////		sprintf((void *)&buf[0],"Median blur : %d.%d[ms]", (int)(us / 1000), (int)((us - ((us / 1000) * 1000))
////				/ 100));
////		R_BCD_LcdWriteString(&buf[0], 2, 62, GREEN);
////		//		us = PerformGetElapsedTime_us(3);
////		us = PerformGetElapsedTime_us(3);
////		sprintf((void *)&buf[0],"Find Contours : %d.%d[ms]", (int)(us / 1000), (int)((us - ((us / 1000) * 1000))
////				/ 100));
////		R_BCD_LcdWriteString(&buf[0], 2, 92, GREEN);
////
////
////		/* Write the data(buf) on the cache to physical memory */
////		R_CACHE_L1DataCleanLine(R_BCD_LcdGetOLVramAddress(), (R_BCD_LCD_WIDTH * R_BCD_LCD_HEIGHT));
////
////		/* Write the data(buf) on the cache to physical memory */
////		R_CACHE_L1DataCleanLine(output_bufadr, ((R_BCD_LCD_WIDTH * R_BCD_LCD_HEIGHT) * 4));
////
////		/* Clear the current capture state and enable the detection of the next capture completion */
////		R_BCD_CameraClearCaptureStatus();
////
//////		R_BCD_LcdSwapGraphicsBuffer();
////		R_BCD_LcdSwapVideoBuffer();
//
//    }
//
//    sample_finish:
//
//	return;
//}
//
///**********************************************************************************************************************
//* End of function sample_main
//**********************************************************************************************************************/
//
//
///******************************************************************************
// * Function Name: bcd_drp_check_empty_contours
// * Description  :
// * Arguments    : -
// * Return Value : -
// ******************************************************************************/
//static uint32_t bcd_drp_check_empty_contours(uint32_t i)
//{
//
//    if(g_contours_rect_adr[i].x)
//    {
//        return 1;
//    }
//    else if(g_contours_rect_adr[i].y)
//    {
//        return 1;
//    }
//    else if(g_contours_rect_adr[i].width)
//    {
//        return 1;
//    }
//    else if(g_contours_rect_adr[i].height)
//    {
//        return 1;
//    }
//    else if(g_contours_rect_adr[i].num)
//    {
//        return 1;
//    }
//    else if(g_contours_rect_adr[i].addr)
//    {
//        return 1;
//    }
//    else
//    {
//        return 0;
//    }
//}
///**********************************************************************************************************************
// End of function bcd_drp_check_empty_contours
//
//
//
///* End of File */




/**********************************************************************************************************************
* b2g->bin->find_contours working? DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
* THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
* this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
* Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
**********************************************************************************************************************/

/**********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
**********************************************************************************************************************/
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"

#include "r_typedefs.h"
#include "iodefine.h"
#include "r_cache_lld_rza2m.h"

#include "r_bcd_ae.h"
#include "r_bcd_camera.h"
#include "r_bcd_lcd.h"
#include "draw.h"
#include "perform.h"
#include "r_mmu_lld_rza2m.h"
#include "r_gpio_drv_api.h"

#include "r_dk2_if.h"

//#include "r_drp_simple_isp.h"
#include "r_drp_bayer2grayscale.h"
#include "r_drp_median_blur.h"
//#include "r_drp_corner_harris.h"
#include "r_drp_dilate.h"
#include "r_drp_binarization_adaptive.h"
#include "r_drp_median_blur.h"
#include "r_drp_thinning.h"
#include "r_drp_sobel.h"
#include "r_drp_find_contours.h"
#include "r_drp_dilate.h"
#include "r_drp_erode.h"
//#include "r_drp_prewitt.h"
//#include "r_drp_gaussian_blur.h"
//#include "r_drp_canny_calculate.h"
//#include "r_drp_canny_hysterisis.h"
#include "r_drp_cropping.h"
#include "r_drp_resize_bilinear.h"
#include "r_drp_resize_bilinear_crop_x_t6.h"

/**********************************************************************************************************************
  Local Typedef definitions
 *********************************************************************************************************************/

typedef struct contours_rect_t
{
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
    uint32_t num;
    uint32_t addr;
} contours_rect_t;

typedef struct
{
    uint16_t x;
    uint16_t y;
} contours_region_t;

/**********************************************************************************************************************
Macro definitions
**********************************************************************************************************************/
#define TILE_0          (0)
#define TILE_1          (1)
#define TILE_2          (2)
#define TILE_3          (3)
#define TILE_4          (4)
#define TILE_5          (5)

#define DRP_NOT_FINISH  (0)
#define DRP_FINISH      (1)

#define FIND_CONTOURS_NUM (6)

#define DRP_DRV_ASSERT(x) if ((x) != 0) goto sample_finish

#define LEN(arr) ((int) (sizeof (arr) / sizeof (arr)[0]))

#define WEAK_LEVEL      (0x28)
#define STRONG_LEVEL    (0x58)

#define HYSTERISIS_COUNT  (2)

#define NN_HEIGHT  (32)
#define NN_WIDTH  (32)


/**********************************************************************************************************************
Imported global variables and functions (from other files)
**********************************************************************************************************************/
extern uint8_t g_drp_lib_bayer2grayscale[];
extern uint8_t g_drp_lib_binarization_adaptive[];
//extern uint8_t g_drp_lib_binarization_fixed[];
extern uint8_t g_drp_lib_median_blur[];
extern uint8_t g_drp_lib_thinning[];
extern uint8_t g_drp_lib_dilate[];
extern uint8_t g_drp_lib_erode[];
extern uint8_t g_drp_lib_find_contours[];
extern uint8_t g_drp_lib_sobel[];
//extern uint8_t g_drp_lib_gaussian_blur[];
//extern uint8_t g_drp_lib_canny_calculate[];
//extern uint8_t g_drp_lib_canny_hysterisis[];
extern uint8_t g_drp_lib_cropping[];
extern uint8_t g_drp_lib_resize_bilinear[];
//extern uint8_t g_drp_lib_resize_bilinear_crop_t6[];


/**********************************************************************************************************************
Private global variables and functions
**********************************************************************************************************************/
static uint8_t drp_lib_id[R_DK2_TILE_NUM] = {0};
static volatile uint8_t drp_lib_status[R_DK2_TILE_NUM] = {DRP_NOT_FINISH};
static uint8_t work_buf[R_BCD_CAMERA_WIDTH * R_BCD_CAMERA_HEIGHT] 					__attribute__ ((aligned(32)));
//static uint8_t work_buf_2[R_BCD_CAMERA_WIDTH * R_BCD_CAMERA_HEIGHT] 				__attribute__ ((aligned(32)));
//static uint8_t work_buf_3[R_BCD_CAMERA_WIDTH * R_BCD_CAMERA_HEIGHT] 				__attribute__ ((aligned(32)));
//static uint8_t work_buf_4[R_BCD_CAMERA_WIDTH * R_BCD_CAMERA_HEIGHT] 				__attribute__ ((aligned(32)));
//static uint8_t work_buf_5[R_BCD_CAMERA_WIDTH * R_BCD_CAMERA_HEIGHT] 				__attribute__ ((aligned(32)));
//static uint8_t work_buf_6[R_BCD_CAMERA_WIDTH * R_BCD_CAMERA_HEIGHT] 				__attribute__ ((section("ImageWork_RAM")));


static r_drp_bayer2grayscale_t param_b2g[R_DK2_TILE_NUM]						 	__attribute__ ((section("UNCACHED_BSS")));
static r_drp_binarization_adaptive_t param_binarization_adaptive 					__attribute__ ((section("UNCACHED_BSS")));
static r_drp_median_blur_t param_median[R_DK2_TILE_NUM] 							__attribute__ ((section("UNCACHED_BSS")));
static r_drp_thinning_t param_thinning[2] 										__attribute__ ((section("UNCACHED_BSS")));
static r_drp_dilate_t param_dilate[R_DK2_TILE_NUM]								__attribute__ ((section("UNCACHED_BSS")));
static r_drp_erode_t param_erode[R_DK2_TILE_NUM]                              __attribute__ ((section("UNCACHED_BSS")));
static r_drp_find_contours_t param_find_contours 									__attribute__ ((section("Uncache_BSS")));
contours_region_t g_contours_region_adr[FIND_CONTOURS_NUM + 1]  					__attribute__ ((section("Uncache_IRAM")));
contours_rect_t g_contours_rect_adr[FIND_CONTOURS_NUM + 1] 							__attribute__ ((section("Uncache_IRAM")));
static r_drp_sobel_t param_sobel[R_DK2_TILE_NUM] 									__attribute__ ((section("UNCACHED_BSS")));
//static r_drp_gaussian_blur_t param_gaussian_blur[R_DK2_TILE_NUM] 					__attribute__ ((section("UNCACHED_BSS")));
//static r_drp_canny_calculate_t  param_canny_cal[1]     							__attribute__ ((section("Uncache_IRAM")));
//static r_drp_canny_calculate_t  param_canny_cal     								__attribute__ ((section("Uncache_IRAM")));
static r_drp_cropping_t               param_cropping                               __attribute__ ((section("Uncache_IRAM")));
static r_drp_resize_bilinear_t               param_resize_bilinear                               __attribute__ ((section("Uncache_IRAM")));
static r_drp_resize_bilinear_crop_t        param_resize_bilinear_crop          __attribute__ ((section("Uncache_IRAM")));

//static r_drp_canny_hysterisis_t             param_canny_hyst    					__attribute__ ((section("Uncache_IRAM")));
//static r_drp_prewitt_t param_sobel[R_DK2_TILE_NUM] 								__attribute__ ((section("UNCACHED_BSS")));


static uint8_t frame_RAM_A[R_BCD_CAMERA_HEIGHT * R_BCD_CAMERA_WIDTH]          __attribute__ ((section("Uncache_IRAM")));
static uint8_t frame_RAM_B[R_BCD_CAMERA_HEIGHT * R_BCD_CAMERA_WIDTH]          __attribute__ ((section("Uncache_IRAM")));
static uint8_t frame_RAM_C[R_BCD_CAMERA_HEIGHT * R_BCD_CAMERA_WIDTH]          __attribute__ ((section("Uncache_IRAM")));
static uint8_t frame_RAM_D[R_BCD_CAMERA_HEIGHT * R_BCD_CAMERA_WIDTH]          __attribute__ ((section("Uncache_IRAM")));
//static uint8_t frame_RAM_E[R_BCD_CAMERA_HEIGHT * R_BCD_CAMERA_WIDTH]          __attribute__ ((section("UNCACHED_BSS")));
//static uint8_t frame_RAM_CC[FIND_CONTOURS_NUM][R_BCD_CAMERA_HEIGHT * R_BCD_CAMERA_WIDTH]   __attribute__ ((section("Uncache_IRAM")));   /* cropped character */
static uint8_t frame_RAM_CC[FIND_CONTOURS_NUM][150 * 150]   __attribute__ ((section("Uncache_IRAM")));   /* cropped character */
static uint8_t frame_RAM_CCR[FIND_CONTOURS_NUM][NN_HEIGHT * NN_WIDTH]   __attribute__ ((section("UNCACHED_BSS")));   /* cropped character */

static uint8_t work3[((R_BCD_CAMERA_HEIGHT * R_BCD_CAMERA_WIDTH) / 64) + 2]   __attribute__ ((section("ImageWork_RAM")));  /* Work area for BinarizationAdaptive */
//static uint8_t work4[R_BCD_CAMERA_HEIGHT * R_BCD_CAMERA_WIDTH]   			  __attribute__ ((section("ImageWork_RAM")));  /* Work area for FindContours */
//static uint8_t work2[R_BCD_CAMERA_HEIGHT * R_BCD_CAMERA_WIDTH]                __attribute__ ((section("ImageWork_RAM")));  /* Work area for Canny Hysterisis and Find Conturs */
static uint8_t work_find_contours[R_BCD_CAMERA_HEIGHT * R_BCD_CAMERA_WIDTH]                __attribute__ ((section("ImageWork_RAM")));  /* Work area Find Conturs */
//static uint8_t work_canny_calculate[((R_BCD_CAMERA_HEIGHT +2) * R_BCD_CAMERA_WIDTH)*2]       __attribute__ ((section("ImageWork_RAM")));  /* Work area for Canny Calculate */
//static uint8_t work_canny_hyst[R_BCD_CAMERA_HEIGHT * R_BCD_CAMERA_WIDTH]                __attribute__ ((section("ImageWork_RAM")));  /* Work area for Canny Hysterisis and Find Conturs */
//static uint8_t thinning_result_buf[R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT+(2*3)) * 2] __attribute__ ((section("ImageWork_RAM")));
static void cb_drp_finish(uint8_t id);
//static void write_harris_data(uint8_t *psrc, uint32_t *pdst);
static uint32_t bcd_drp_check_empty_contours(uint32_t i);

/**********************************************************************************************************************
* Function Name: cb_drp_finish
* Description  : This function is a callback function called from the
*              : DRP driver at the finish of the DRP library processing.
* Arguments    : id
*              :   The ID of the DRP library that finished processing.
* Return Value : -
**********************************************************************************************************************/
static void cb_drp_finish(uint8_t id)
{
    uint32_t tile_no;

    /* Change the operation state of the DRP library notified by the argument to finish */
    for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
    {
        if (drp_lib_id[tile_no] == id)
        {
            drp_lib_status[tile_no] = DRP_FINISH;
            break;
        }
    }

    return;
}
/**********************************************************************************************************************
* End of function cb_drp_finish
**********************************************************************************************************************/

/**********************************************************************************************************************
* Function Name: sample_main
* Description  : First function called after initialization is completed
* Arguments    : -
* Return Value : -
**********************************************************************************************************************/
void sample_main(void)
{
    int32_t frame_buf_id;
    uint8_t buf[80];
    int32_t ret_val;
    uint32_t us;
//    uint32_t input_bufadr;
    uint32_t output_bufadr;
//    uint32_t work_bufadr;
//    uint32_t work_bufadr_bin2med;
//    uint32_t work_bufadr_med2thin;
//    uint32_t work_bufadr_med2dilate;
//    uint32_t work_bufadr_med2contours;
//    uint32_t extra_bufadr;
//    uint32_t intermediate_bufadr;
    uint32_t tile_no;
    uint8_t * p_input_bufadr;
    uint8_t * p_output_bufadr;
    uint8_t * p_work_bufadr;
//    uint8_t * p_work_bufadr_bin2med;
//    uint8_t * p_work_bufadr_med2thin;
//    uint8_t * p_work_bufadr_med2dilate;
//    uint8_t * p_extra_bufadr;
//    uint32_t * p_frame_ram1;
//    uint8_t * p_work_bufadr_med2dilate;
//    uint8_t * p_work_bufadr_med2contours;
    uint32_t bufsize_thinning;
//    uint32_t bufsize;
//    uint32_t * p_frame_ram1;
//    uint32_t * p_frame_ram2;
//    uint8_t * p_frame_ram3;
    uint32_t *p_frame_ram_thinning;
//    uint32_t *p_frame_ram_canny_cal;
//    uint32_t *p_frame_ram_canny_hyst;

    uint8_t symbol;
    uint8_t num_valid_char;
    uint8_t valid_char;
    uint16_t  ih;
    uint16_t  iw;
    uint8_t flag;

    /* Initialization of VIN and MIPI driver */
    R_BCD_CameraInit();

    /* Initialization of LCD driver */
    R_BCD_LcdInit();

    /* Capture Start */
    R_BCD_CameraCaptureStart();

    /* Initialize of Performance counter */
    PerformInit();

    /********************************/
    /* Initialization of DRP driver */
    /********************************/
    R_DK2_Initialize();

    /* main loop */
    while (1)
    {
//    	R_BCD_LcdClearGraphicsBuffer();
        /* Wait until camera capture is complete */
        while ((frame_buf_id = R_BCD_CameraGetCaptureStatus()) == R_BCD_CAMERA_NOT_CAPTURED)
        {
            /* DO NOTHING */
        }
        p_input_bufadr  			= R_BCD_CameraGetFrameAddress(frame_buf_id);
        p_output_bufadr 			= R_BCD_LcdGetVramAddress();
        p_work_bufadr   			= (uint32_t *)&work_buf[0];
//        p_frame_ram1 		        = (uint32_t *)&work_buf_2[0];
//        p_frame_ram2 	            = (uint32_t *)&work_buf_3[0];
//        p_work_bufadr_med2dilate 	= (uint8_t *)&work_buf_5[0];


//        /* convert to phisical address */
//        R_MMU_VAtoPA((uint32_t)p_input_bufadr, &input_bufadr);
//
//        /* convert to phisical address */
//        R_MMU_VAtoPA((uint32_t)p_output_bufadr, &output_bufadr);
//
//        /* convert to phisical address */
//        R_MMU_VAtoPA((uint32_t)p_work_bufadr, &work_bufadr);
//
//        /* convert to phisical address */
//        R_MMU_VAtoPA((uint32_t)p_work_bufadr_bin2med, &work_bufadr_bin2med);
//
//        /* convert to phisical address */
//        R_MMU_VAtoPA((uint32_t)p_work_bufadr_med2contours, &work_bufadr_med2contours);
//
//        /* convert to phisical address */
//        R_MMU_VAtoPA((uint32_t)p_work_bufadr_med2dilate, &work_bufadr_med2dilate);
//
//        p_extra_bufadr 				= (uint8_t *)&work2[0];
//        R_MMU_VAtoPA((uint32_t)p_extra_bufadr, &extra_bufadr);




//        printf("sizeof input to b2g: %li", sizeof(input_bufadr));
        printf("Hi0 \n");

        /******************************/
        /* Load DRP Library           */
        /*        +-----------------+ */
        /* tile 0 | Bayer2Grayscale | */
        /*        +-----------------+ */
        /* tile 1 | Bayer2Grayscale | */
        /*        +-----------------+ */
        /* tile 2 | Bayer2Grayscale | */
        /*        +-----------------+ */
        /* tile 3 | Bayer2Grayscale | */
        /*        +-----------------+ */
        /* tile 4 | Bayer2Grayscale | */
        /*        +-----------------+ */
        /* tile 5 | Bayer2Grayscale | */
        /*        +-----------------+ */
        /******************************/
        ret_val = R_DK2_Load(&g_drp_lib_bayer2grayscale[0],
                            R_DK2_TILE_0 | R_DK2_TILE_1 | R_DK2_TILE_2 | R_DK2_TILE_3 | R_DK2_TILE_4 | R_DK2_TILE_5,
                            R_DK2_TILE_PATTERN_1_1_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
        DRP_DRV_ASSERT(ret_val);
//        printf("b2g load ret val = %d", ret_val);

        /************************/
        /* Activate DRP Library */
        /************************/
        ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
                                | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], 0);
        DRP_DRV_ASSERT(ret_val);
//        printf("b2g activate ret val = %d", ret_val);

        /* Set start time of process*/
        PerformSetStartTime(0);;



        /***************************************/
        /* Set R_DK2_Start function parameters */
        /***************************************/
        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
        {
            /* Set the address of buffer to be read/write by DRP */
//            param_b2g[tile_no].src = input_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//                                                                                                            * tile_no);
//            param_b2g[tile_no].dst = work_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//                                                                                                            * tile_no);
////            param_b2g[tile_no].dst = output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////                                                                                                             * tile_no);


        	param_b2g[tile_no].src = p_input_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
        	param_b2g[tile_no].dst = (uint32_t)&frame_RAM_A + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//        	param_b2g[tile_no].dst = p_output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);

        	R_MMU_VAtoPA((uint32_t)param_b2g[tile_no].src, &(param_b2g[tile_no].src));
        	R_MMU_VAtoPA((uint32_t)param_b2g[tile_no].dst, &(param_b2g[tile_no].dst));

            /* Set Image size */
            param_b2g[tile_no].width = R_BCD_CAMERA_WIDTH;
            param_b2g[tile_no].height = R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM;

            /* Set whether to perform top or bottom edge border processing. */
            param_b2g[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
            param_b2g[tile_no].bottom = (tile_no == TILE_5) ? 1 : 0;

            /* Initialize variables to be used in termination judgment of the DRP library */
            drp_lib_status[tile_no] = DRP_NOT_FINISH;

            /*********************/
            /* Start DRP Library */
            /*********************/
            ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_b2g[tile_no], sizeof(r_drp_bayer2grayscale_t));
            DRP_DRV_ASSERT(ret_val);
//            printf("b2g start ret val = %d", ret_val);
        }

        /***************************************/
        /* Wait until DRP processing is finish */
        /***************************************/
        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
        {
            while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
            {
                /* DO NOTHING */
            }
        }

        /* Set end time of process */
        PerformSetEndTime(0);
        printf("Bayer2Grayscale End \n");


        /**********************/
        /* Unload DRP Library */
        /**********************/
        ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
                                                            | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], &drp_lib_id[0]);
        DRP_DRV_ASSERT(ret_val);
//        printf("b2g unload ret val = %d", ret_val);

//        /* Clear the current capture state and enable the detection of the next capture completion */
//        R_BCD_CameraClearCaptureStatus();
//
//        /* Capture Start */
//        R_BCD_CameraCaptureStart();

//        /* Display image processing result */
//        R_BCD_LcdSwapVideoBuffer();

//        printf("sizeof output of b2g: %li", sizeof(work_bufadr));



        /******************************************************************************************************/
        /************************************/
        /* Load DRP Library                 */
        /*        +-----------------------+ */
        /* tile 0 |                       | */
        /*        +                       + */
        /* tile 1 | BinarizationAdaptive  | */
        /*        +                       + */
        /* tile 2 |                       | */
        /*        +-----------------------+ */
        /* tile 3 |                       | */
        /*        +                       + */
        /* tile 4 |                       | */
        /*        |                       | */
        /* tile 5 |                       | */
        /*        +-----------------------+ */
        /************************************/

		/*############    -  BinarizationAdaptive  -    ##############*/



		/*****************************************/
		/* Load DRP Library BinarizationAdaptive */
		/*****************************************/
		ret_val = R_DK2_Load(&g_drp_lib_binarization_adaptive[0],
				R_DK2_TILE_0,
				R_DK2_TILE_PATTERN_3_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
		DRP_DRV_ASSERT(ret_val);
//		printf("bin-ad load ret val = %d", ret_val);

		/*****************************************/
		/* Activate DRP Lib BinarizationAdaptive */
		/*****************************************/
		ret_val = R_DK2_Activate(drp_lib_id[TILE_0], 0);
		DRP_DRV_ASSERT(ret_val);
//		printf("bin-ad activate ret val = %d", ret_val);

		/* Set start time of process*/
		PerformSetStartTime(1);

		/****************************************************************/
		/* Set R_DK2_Start function parameters for BinarizationAdaptive */
		/****************************************************************/

//		param_binarization_adaptive.src        = work_bufadr;     					/* Address of image to be binarized. */
//		param_binarization_adaptive.dst        = work_bufadr_bin2med;       		/* Address to output binarized result. */
//		param_binarization_adaptive.dst        = output_bufadr;

		param_binarization_adaptive.src        = (uint32_t)&frame_RAM_A;     					/* Address of image to be binarized. */
		param_binarization_adaptive.dst        = (uint32_t)&frame_RAM_B;       		/* Address to output binarized result. */
//		param_binarization_adaptive.dst        = p_output_bufadr;

		R_MMU_VAtoPA((uint32_t)param_binarization_adaptive.src , &(param_binarization_adaptive.src));
		R_MMU_VAtoPA((uint32_t)param_binarization_adaptive.dst , &(param_binarization_adaptive.dst));

		param_binarization_adaptive.width      = (uint16_t)R_BCD_CAMERA_WIDTH;   	/* The horizontal size (pixels) of the image to be binarized. */
		param_binarization_adaptive.height     = (uint16_t)R_BCD_CAMERA_HEIGHT;  	/* The vertical size (pixels) of the image to be binarized. */
		param_binarization_adaptive.work       = (uint32_t)&work3[0];            	/* Address of the work buffer used by the library. */
		param_binarization_adaptive.range      = 0x01;                            	/* A luminance difference to judge whether it is effective average luminance.(8x8 pixel) */

		/* Initialize variables to be used in termination judgment of the DRP application */
		drp_lib_status[TILE_0] = DRP_NOT_FINISH;

		/******************************************/
		/* Start DRP Library BinarizationAdaptive */
		/******************************************/
		ret_val = R_DK2_Start(drp_lib_id[TILE_0], (void *)&param_binarization_adaptive, sizeof(r_drp_binarization_adaptive_t));
		DRP_DRV_ASSERT(ret_val);
//		printf("bin-ad start ret val = %d", ret_val);


		/*******************************************************/
		/* Wait until BinarizationAdaptive processing finished */
		/*******************************************************/
		while (drp_lib_status[TILE_0] == DRP_NOT_FINISH);  // BinarizationAdaptive

		/*******************************************/
		/* Unload DRP library BinarizationAdaptive */
		/*******************************************/
		ret_val = R_DK2_Unload(drp_lib_id[TILE_0], &drp_lib_id[TILE_0]);
		DRP_DRV_ASSERT(ret_val);
//		printf("bin-ad unload ret val = %d", ret_val);

		/* Set end time of DRP processing */
		PerformSetEndTime(1);
		printf("BinarizationAdaptive End \n");

		/******************************************************************************************************/


////		/******************************************************************************************************/
////		/******************************/
////		/* Load DRP Library           */
////		/*        +-----------------+ */
////		/* tile 0 |  gaussian blur	| */
////		/*        +-----------------+ */
////		/* tile 1 |  gaussian blur	| */
////		/*        +-----------------+ */
////		/* tile 2 |  gaussian blur	| */
////		/*        +-----------------+ */
////		/* tile 3 |  gaussian blur	| */
////		/*        +-----------------+ */
////		/* tile 4 |  gaussian blur	| */
////		/*        +-----------------+ */
////		/* tile 5 |  gaussian blur	| */
////		/*        +-----------------+ */
////		/******************************/
////		ret_val = R_DK2_Load(&g_drp_lib_gaussian_blur[0],
////				R_DK2_TILE_0 | R_DK2_TILE_1 | R_DK2_TILE_2 | R_DK2_TILE_3 | R_DK2_TILE_4 | R_DK2_TILE_5,
////				R_DK2_TILE_PATTERN_1_1_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
////		DRP_DRV_ASSERT(ret_val);
////		//        printf("b2g load ret val = %d", ret_val);
////
////		/************************/
////		/* Activate DRP Library */
////		/************************/
////		ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
////																										   | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], 0);
////		DRP_DRV_ASSERT(ret_val);
////		//        printf("b2g activate ret val = %d", ret_val);
////
////		/* Set start time of process*/
////		PerformSetStartTime(6);;
////
////
////
////		/***************************************/
////		/* Set R_DK2_Start function parameters */
////		/***************************************/
////		for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
////		{
////			/* Set the address of buffer to be read/write by DRP */
////			param_gaussian_blur[tile_no].src = work_bufadr_bin2med + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////					* tile_no);
////			//        	param_gaussian_blur[tile_no].dst = work_bufadr_bin2med + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////			//        			* tile_no);
////			param_gaussian_blur[tile_no].dst = output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////					* tile_no);
////
////			/* Set Image size */
////			param_gaussian_blur[tile_no].width = R_BCD_CAMERA_WIDTH;
////			param_gaussian_blur[tile_no].height = R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM;
////
////			/* Set whether to perform top or bottom edge border processing. */
////			param_gaussian_blur[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
////			param_gaussian_blur[tile_no].bottom = (tile_no == TILE_5) ? 1 : 0;
////
////			/* Initialize variables to be used in termination judgment of the DRP library */
////			drp_lib_status[tile_no] = DRP_NOT_FINISH;
////
////			/*********************/
////			/* Start DRP Library */
////			/*********************/
////			ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_gaussian_blur[tile_no], sizeof(r_drp_gaussian_blur_t));
////			DRP_DRV_ASSERT(ret_val);
////			//            printf("b2g start ret val = %d", ret_val);
////		}
////
////		/***************************************/
////		/* Wait until DRP processing is finish */
////		/***************************************/
////		for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
////		{
////			while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
////			{
////				/* DO NOTHING */
////			}
////		}
////
////		/* Set end time of process */
////		PerformSetEndTime(6);
////		printf("Hi1 \n");
////
////
////		/**********************/
////		/* Unload DRP Library */
////		/**********************/
////		ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
////																										 | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], &drp_lib_id[0]);
////		DRP_DRV_ASSERT(ret_val);
////
////
////		/******************************************************************************************************/



		/******************************************************************************************************/
		/**************************/
		/* Load DRP Library       */
		/*        +-------------+ */
		/* tile 0 | Median blur | */
		/*        +-------------+ */
		/* tile 1 | Median blur | */
		/*        +-------------+ */
		/* tile 2 | Median blur | */
		/*        +-------------+ */
		/* tile 3 | Median blur | */
		/*        +-------------+ */
		/* tile 4 | Median blur | */
		/*        +-------------+ */
		/* tile 5 | Median blur | */
		/*        +-------------+ */
		/**************************/
		ret_val = R_DK2_Load(&g_drp_lib_median_blur[0],
				R_DK2_TILE_0 | R_DK2_TILE_1 | R_DK2_TILE_2 | R_DK2_TILE_3 | R_DK2_TILE_4 | R_DK2_TILE_5,
				R_DK2_TILE_PATTERN_1_1_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
		DRP_DRV_ASSERT(ret_val);
		/************************/
		/* Activate DRP Library */
		/************************/
		ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
																										   | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], 0);
		DRP_DRV_ASSERT(ret_val);
		/* Set start time of process*/
		PerformSetStartTime(2);
		/***************************************/
		/* Set R_DK2_Start function parameters */
		/***************************************/
		for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
		{
			/* Set the address of buffer to be read/write by DRP */
//			param_median[tile_no].src = work_bufadr_bin2med + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//					* tile_no);
//			param_median[tile_no].dst = work_bufadr_med2dilate + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//					* tile_no);
////			param_median[tile_no].dst = output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////								* tile_no);
////			param_median[tile_no].dst = (uint32_t)&p_work_bufadr_med2thin[0];   + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////					* tile_no);
////			R_MMU_VAtoPA((uint32_t)param_median[tile_no].dst, &(param_median[tile_no].dst ));

			param_median[tile_no].src = (uint32_t)&frame_RAM_B + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
			param_median[tile_no].dst = (uint32_t)&frame_RAM_C + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//			param_median[tile_no].dst = p_output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);

			R_MMU_VAtoPA((uint32_t)param_median[tile_no].src, &(param_median[tile_no].src));
			R_MMU_VAtoPA((uint32_t)param_median[tile_no].dst, &(param_median[tile_no].dst));


			/* Set Image size */
			param_median[tile_no].width = R_BCD_CAMERA_WIDTH;
			param_median[tile_no].height = R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM;
			/* Set whether to perform top or bottom edge border processing. */
			param_median[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
			param_median[tile_no].bottom = (tile_no == TILE_5) ? 1 : 0;
			/* Initialize variables to be used in termination judgment of the DRP library */
			drp_lib_status[tile_no] = DRP_NOT_FINISH;
			/*********************/
			/* Start DRP Library */
			/*********************/
			ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_median[tile_no], sizeof(r_drp_median_blur_t));
			DRP_DRV_ASSERT(ret_val);
		}

		/***************************************/
		/* Wait until DRP processing is finish */
		/***************************************/
		for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
		{
			while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
			{
				/* DO NOTHING */
			}
		}

		/* Set end time of process */
		PerformSetEndTime(2);
		/**********************/
		/* Unload DRP library */
		/**********************/
		ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3] |
				drp_lib_id[TILE_4] | drp_lib_id[TILE_5], &drp_lib_id[TILE_0]);
		DRP_DRV_ASSERT(ret_val);


		//		/* Clear the current capture state and enable the detection of the next capture completion */
		//		R_BCD_CameraClearCaptureStatus();
		//
		//		/* Capture Start */
		//		R_BCD_CameraCaptureStart();

//		/* Display image processing result */
//		R_BCD_LcdSwapVideoBuffer();

		printf("MedianBlur End \n");

//		printf("sizeof output of binarization: %li", sizeof(work_bufadr_bin2med));

		/******************************************************************************************************/


        /******************************************************************************************************/
        /******************************/
        /* Load DRP Library           */
        /*        +-----------------+ */
        /* tile 0 |                 | */
        /*        +                 + */
        /* tile 1 |    Thinning     | */
        /*        +                 + */
        /* tile 2 |                 | */
        /*        +-----------------+ */
        /* tile 3 |                 | */
        /*        +                 + */
        /* tile 4 |    Thinning     | */
        /*        +                 + */
        /* tile 5 |                 | */
        /*        +-----------------+ */
        /******************************/
        ret_val = R_DK2_Load(&g_drp_lib_thinning[0], R_DK2_TILE_0 | R_DK2_TILE_3,
        		R_DK2_TILE_PATTERN_3_3, NULL, &cb_drp_finish, &drp_lib_id[0]);
        DRP_DRV_ASSERT(ret_val);

        /********************/
        /* Activate DRP Lib */
        /********************/
        ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_3], 0);
        DRP_DRV_ASSERT(ret_val);

        /* Set start time of process*/
        PerformSetStartTime(9);

        /***************************************/
        /* Set R_DK2_Start function parameters */
        /***************************************/
        for (tile_no = TILE_0; tile_no <= TILE_3; tile_no += 3)
        {
        	/* Set Image size */
        	param_thinning[tile_no].width = R_BCD_CAMERA_WIDTH;
        	param_thinning[tile_no].height = (R_BCD_CAMERA_HEIGHT / 2);

        	/* Set Buffer size */
        	bufsize_thinning = (uint32_t)(param_thinning[tile_no].width * param_thinning[tile_no].height);

        	/* Set the address of buffer to be read/write by DRP */
//        	param_thinning[tile_no].src = work_bufadr_med2thin + ((tile_no / 3) * bufsize_thinning);
////        	param_thinning[tile_no].dst = output_bufadr  + ((tile_no / 3) * bufsize_thinning);
//        	param_thinning[tile_no].dst = output_bufadr  + ((tile_no / 3) * bufsize_thinning);

        	param_thinning[tile_no].src = (uint32_t)&frame_RAM_C + ((tile_no / 3) * bufsize_thinning);
        	param_thinning[tile_no].dst = (uint32_t)&frame_RAM_A + ((tile_no / 3) * bufsize_thinning);
//        	param_thinning[tile_no].dst = p_output_bufadr + ((tile_no / 3) * bufsize_thinning);

			R_MMU_VAtoPA((uint32_t)param_thinning[tile_no].src, &(param_thinning[tile_no].src));
			R_MMU_VAtoPA((uint32_t)param_thinning[tile_no].dst, &(param_thinning[tile_no].dst));


        	/* Set additional information (currently no additional information) */
        	param_thinning[tile_no].result =
        			(uint32_t)&p_frame_ram_thinning[((tile_no / 3) * (bufsize_thinning + (R_BCD_CAMERA_WIDTH*2) ))*2];
        	R_MMU_VAtoPA((uint32_t)param_thinning[tile_no].result, &(param_thinning[tile_no].result));

        	param_thinning[tile_no].threshold = 0x01;
        	param_thinning[tile_no].reverse = 1;

        	/* Set whether to perform top or bottom edge border processing. */
        	param_thinning[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
        	param_thinning[tile_no].bottom = (tile_no == TILE_3) ? 1 : 0;

        	param_thinning[tile_no].step = 0;

        	/* Initialize variables to be used in termination judgment of the DRP library */
        	drp_lib_status[tile_no] = DRP_NOT_FINISH;

        	/*********************/
        	/* Start DRP Library */
        	/*********************/
        	ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_thinning[tile_no],
        			sizeof(r_drp_thinning_t));
        	DRP_DRV_ASSERT(ret_val);
        }

        /***************************************/
        /* Wait until DRP processing is finish */
        /***************************************/
        for (tile_no = TILE_0; tile_no <= TILE_3; tile_no += 3)
        {
        	/***************************************/
        	/* Wait until DRP processing is finish */
        	/***************************************/
        	while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
        	{
        		/* DO NOTHING */
        	}
        }

        /* Set end time of DRP processing */
        PerformSetEndTime(9);

        /**********************/
        /* Unload DRP library */
        /**********************/
        ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_3] , &drp_lib_id[TILE_0]);
        DRP_DRV_ASSERT(ret_val);


        /******************************************************************************************************/

//        /**Dilate original***********************************************************************************/
//        /**************************/
//        /* Load DRP Library       */
//        /*        +-------------+ */
//        /* tile 0 |   Dilate    | */
//        /*        +-------------+ */
//        /* tile 1 |   Dilate    | */
//        /*        +-------------+ */
//        /* tile 2 |   Dilate    | */
//        /*        +-------------+ */
//        /* tile 3 |   Dilate    | */
//        /*        +-------------+ */
//        /* tile 4 |   Dilate    | */
//        /*        +-------------+ */
//        /* tile 5 |   Dilate    | */
//        /*        +-------------+ */
//        /**************************/
//        ret_val = R_DK2_Load(&g_drp_lib_dilate[0],
//                R_DK2_TILE_0 | R_DK2_TILE_1 | R_DK2_TILE_2 | R_DK2_TILE_3 | R_DK2_TILE_4 | R_DK2_TILE_5,
//                R_DK2_TILE_PATTERN_1_1_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
//        DRP_DRV_ASSERT(ret_val);
//        /************************/
//        /* Activate DRP Library */
//        /************************/
//        ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
//                                                                                                           | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], 0);
//        DRP_DRV_ASSERT(ret_val);
//        /* Set start time of process*/
//        PerformSetStartTime(8);
//        /***************************************/
//        /* Set R_DK2_Start function parameters */
//        /***************************************/
//        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//        {
//            /* Set the address of buffer to be read/write by DRP */
////          param_dilate[tile_no].src = work_bufadr_med2thin + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////                  * tile_no);
////          param_dilate[tile_no].dst = output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////                  * tile_no);
//
//            param_dilate[tile_no].src = (uint32_t)&frame_RAM_A + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//            param_dilate[tile_no].dst = p_output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
////          param_dilate[tile_no].dst = p_work_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
////          param_dilate[tile_no].dst = (uint32_t)&frame_RAM_A + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//
//            R_MMU_VAtoPA((uint32_t)param_dilate[tile_no].src, &(param_dilate[tile_no].src));
//            R_MMU_VAtoPA((uint32_t)param_dilate[tile_no].dst, &(param_dilate[tile_no].dst));
//            /* Set Image size */
//            param_dilate[tile_no].width = R_BCD_CAMERA_WIDTH;
//            param_dilate[tile_no].height = R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM;
//            /* Set whether to perform top or bottom edge border processing. */
//            param_dilate[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
//            param_dilate[tile_no].bottom = (tile_no == TILE_5) ? 1 : 0;
//            /* Initialize variables to be used in termination judgment of the DRP library */
//            drp_lib_status[tile_no] = DRP_NOT_FINISH;
//            /*********************/
//            /* Start DRP Library */
//            /*********************/
//            ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_dilate[tile_no], sizeof(r_drp_dilate_t));
//            DRP_DRV_ASSERT(ret_val);
//        }
//
//        /***************************************/
//        /* Wait until DRP processing is finish */
//        /***************************************/
//        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//        {
//            while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
//            {
//                /* DO NOTHING */
//            }
//        }
//
//        /* Set end time of process */
//        PerformSetEndTime(8);
//        /**********************/
//        /* Unload DRP library */
//        /**********************/
//        ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3] |
//                drp_lib_id[TILE_4] | drp_lib_id[TILE_5], &drp_lib_id[TILE_0]);
//        DRP_DRV_ASSERT(ret_val);
//        /******************************************************************************************************/



//        /**Opening*********************************************************************************************/
//        /******************************************************************************************************/
//        /**Open-Erode1*****************************************************************************************/
//        /**************************/
//        /* Load DRP Library       */
//        /*        +-------------+ */
//        /* tile 0 |   Erode     | */
//        /*        +-------------+ */
//        /* tile 1 |   Erode     | */
//        /*        +-------------+ */
//        /* tile 2 |   Erode     | */
//        /*        +-------------+ */
//        /* tile 3 |   Erode     | */
//        /*        +-------------+ */
//        /* tile 4 |   Erode     | */
//        /*        +-------------+ */
//        /* tile 5 |   Erode     | */
//        /*        +-------------+ */
//        /**************************/
//        ret_val = R_DK2_Load(&g_drp_lib_erode[0],
//                R_DK2_TILE_0 | R_DK2_TILE_1 | R_DK2_TILE_2 | R_DK2_TILE_3 | R_DK2_TILE_4 | R_DK2_TILE_5,
//                R_DK2_TILE_PATTERN_1_1_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
//        DRP_DRV_ASSERT(ret_val);
//        /************************/
//        /* Activate DRP Library */
//        /************************/
//        ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
//                                                                                                           | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], 0);
//        DRP_DRV_ASSERT(ret_val);
//        /* Set start time of process*/
//        PerformSetStartTime(8);
//        /***************************************/
//        /* Set R_DK2_Start function parameters */
//        /***************************************/
//        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//        {
//            /* Set the address of buffer to be read/write by DRP */
////          param_dilate[tile_no].src = work_bufadr_med2thin + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////                  * tile_no);
////          param_dilate[tile_no].dst = output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////                  * tile_no);
//
//            param_erode[tile_no].src = (uint32_t)&frame_RAM_A + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//            param_erode[tile_no].dst = (uint32_t)&frame_RAM_B + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
////          param_dilate[tile_no].dst = p_work_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
////          param_dilate[tile_no].dst = (uint32_t)&frame_RAM_A + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//
//            R_MMU_VAtoPA((uint32_t)param_erode[tile_no].src, &(param_erode[tile_no].src));
//            R_MMU_VAtoPA((uint32_t)param_erode[tile_no].dst, &(param_erode[tile_no].dst));
//            /* Set Image size */
//            param_erode[tile_no].width = R_BCD_CAMERA_WIDTH;
//            param_erode[tile_no].height = R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM;
//            /* Set whether to perform top or bottom edge border processing. */
//            param_erode[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
//            param_erode[tile_no].bottom = (tile_no == TILE_5) ? 1 : 0;
//            /* Initialize variables to be used in termination judgment of the DRP library */
//            drp_lib_status[tile_no] = DRP_NOT_FINISH;
//            /*********************/
//            /* Start DRP Library */
//            /*********************/
//            ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_erode[tile_no], sizeof(r_drp_erode_t));
//            DRP_DRV_ASSERT(ret_val);
//        }
//
//        /***************************************/
//        /* Wait until DRP processing is finish */
//        /***************************************/
//        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//        {
//            while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
//            {
//                /* DO NOTHING */
//            }
//        }
//
//        /* Set end time of process */
//        PerformSetEndTime(8);
//        /**********************/
//        /* Unload DRP library */
//        /**********************/
//        ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3] |
//                drp_lib_id[TILE_4] | drp_lib_id[TILE_5], &drp_lib_id[TILE_0]);
//        DRP_DRV_ASSERT(ret_val);
//        /******************************************************************************************************/
//
//
//
//        /**Open-Erode2*****************************************************************************************/
//        /**************************/
//        /* Load DRP Library       */
//        /*        +-------------+ */
//        /* tile 0 |   Erode     | */
//        /*        +-------------+ */
//        /* tile 1 |   Erode     | */
//        /*        +-------------+ */
//        /* tile 2 |   Erode     | */
//        /*        +-------------+ */
//        /* tile 3 |   Erode     | */
//        /*        +-------------+ */
//        /* tile 4 |   Erode     | */
//        /*        +-------------+ */
//        /* tile 5 |   Erode     | */
//        /*        +-------------+ */
//        /**************************/
//        ret_val = R_DK2_Load(&g_drp_lib_erode[0],
//                R_DK2_TILE_0 | R_DK2_TILE_1 | R_DK2_TILE_2 | R_DK2_TILE_3 | R_DK2_TILE_4 | R_DK2_TILE_5,
//                R_DK2_TILE_PATTERN_1_1_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
//        DRP_DRV_ASSERT(ret_val);
//        /************************/
//        /* Activate DRP Library */
//        /************************/
//        ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
//                                                                                                           | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], 0);
//        DRP_DRV_ASSERT(ret_val);
//        /* Set start time of process*/
//        PerformSetStartTime(8);
//        /***************************************/
//        /* Set R_DK2_Start function parameters */
//        /***************************************/
//        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//        {
//            /* Set the address of buffer to be read/write by DRP */
////          param_dilate[tile_no].src = work_bufadr_med2thin + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////                  * tile_no);
////          param_dilate[tile_no].dst = output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////                  * tile_no);
//
//            param_erode[tile_no].src = (uint32_t)&frame_RAM_B + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//            param_erode[tile_no].dst = (uint32_t)&frame_RAM_C + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
////          param_dilate[tile_no].dst = p_work_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
////          param_dilate[tile_no].dst = (uint32_t)&frame_RAM_A + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//
//            R_MMU_VAtoPA((uint32_t)param_erode[tile_no].src, &(param_erode[tile_no].src));
//            R_MMU_VAtoPA((uint32_t)param_erode[tile_no].dst, &(param_erode[tile_no].dst));
//            /* Set Image size */
//            param_erode[tile_no].width = R_BCD_CAMERA_WIDTH;
//            param_erode[tile_no].height = R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM;
//            /* Set whether to perform top or bottom edge border processing. */
//            param_erode[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
//            param_erode[tile_no].bottom = (tile_no == TILE_5) ? 1 : 0;
//            /* Initialize variables to be used in termination judgment of the DRP library */
//            drp_lib_status[tile_no] = DRP_NOT_FINISH;
//            /*********************/
//            /* Start DRP Library */
//            /*********************/
//            ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_erode[tile_no], sizeof(r_drp_erode_t));
//            DRP_DRV_ASSERT(ret_val);
//        }
//
//        /***************************************/
//        /* Wait until DRP processing is finish */
//        /***************************************/
//        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//        {
//            while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
//            {
//                /* DO NOTHING */
//            }
//        }
//
//        /* Set end time of process */
//        PerformSetEndTime(8);
//        /**********************/
//        /* Unload DRP library */
//        /**********************/
//        ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3] |
//                drp_lib_id[TILE_4] | drp_lib_id[TILE_5], &drp_lib_id[TILE_0]);
//        DRP_DRV_ASSERT(ret_val);
//        /******************************************************************************************************/
//
//
//
//        /**Open-Erode3*****************************************************************************************/
//        /**************************/
//        /* Load DRP Library       */
//        /*        +-------------+ */
//        /* tile 0 |   Erode     | */
//        /*        +-------------+ */
//        /* tile 1 |   Erode     | */
//        /*        +-------------+ */
//        /* tile 2 |   Erode     | */
//        /*        +-------------+ */
//        /* tile 3 |   Erode     | */
//        /*        +-------------+ */
//        /* tile 4 |   Erode     | */
//        /*        +-------------+ */
//        /* tile 5 |   Erode     | */
//        /*        +-------------+ */
//        /**************************/
//        ret_val = R_DK2_Load(&g_drp_lib_erode[0],
//                R_DK2_TILE_0 | R_DK2_TILE_1 | R_DK2_TILE_2 | R_DK2_TILE_3 | R_DK2_TILE_4 | R_DK2_TILE_5,
//                R_DK2_TILE_PATTERN_1_1_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
//        DRP_DRV_ASSERT(ret_val);
//        /************************/
//        /* Activate DRP Library */
//        /************************/
//        ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
//                                                                                                           | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], 0);
//        DRP_DRV_ASSERT(ret_val);
//        /* Set start time of process*/
//        PerformSetStartTime(8);
//        /***************************************/
//        /* Set R_DK2_Start function parameters */
//        /***************************************/
//        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//        {
//            /* Set the address of buffer to be read/write by DRP */
////          param_dilate[tile_no].src = work_bufadr_med2thin + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////                  * tile_no);
////          param_dilate[tile_no].dst = output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////                  * tile_no);
//
//            param_erode[tile_no].src = (uint32_t)&frame_RAM_C + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
////            param_erode[tile_no].dst = p_output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//            param_erode[tile_no].dst = (uint32_t)&frame_RAM_A + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//
//            R_MMU_VAtoPA((uint32_t)param_erode[tile_no].src, &(param_erode[tile_no].src));
//            R_MMU_VAtoPA((uint32_t)param_erode[tile_no].dst, &(param_erode[tile_no].dst));
//            /* Set Image size */
//            param_erode[tile_no].width = R_BCD_CAMERA_WIDTH;
//            param_erode[tile_no].height = R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM;
//            /* Set whether to perform top or bottom edge border processing. */
//            param_erode[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
//            param_erode[tile_no].bottom = (tile_no == TILE_5) ? 1 : 0;
//            /* Initialize variables to be used in termination judgment of the DRP library */
//            drp_lib_status[tile_no] = DRP_NOT_FINISH;
//            /*********************/
//            /* Start DRP Library */
//            /*********************/
//            ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_erode[tile_no], sizeof(r_drp_erode_t));
//            DRP_DRV_ASSERT(ret_val);
//        }
//
//        /***************************************/
//        /* Wait until DRP processing is finish */
//        /***************************************/
//        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//        {
//            while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
//            {
//                /* DO NOTHING */
//            }
//        }
//
//        /* Set end time of process */
//        PerformSetEndTime(8);
//        /**********************/
//        /* Unload DRP library */
//        /**********************/
//        ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3] |
//                drp_lib_id[TILE_4] | drp_lib_id[TILE_5], &drp_lib_id[TILE_0]);
//        DRP_DRV_ASSERT(ret_val);
//        /******************************************************************************************************/
//
//
//        /**Open-Dilate1****************************************************************************************/
//        /**************************/
//        /* Load DRP Library       */
//        /*        +-------------+ */
//        /* tile 0 |   Dilate    | */
//        /*        +-------------+ */
//        /* tile 1 |   Dilate    | */
//        /*        +-------------+ */
//        /* tile 2 |   Dilate    | */
//        /*        +-------------+ */
//        /* tile 3 |   Dilate    | */
//        /*        +-------------+ */
//        /* tile 4 |   Dilate    | */
//        /*        +-------------+ */
//        /* tile 5 |   Dilate    | */
//        /*        +-------------+ */
//        /**************************/
//        ret_val = R_DK2_Load(&g_drp_lib_dilate[0],
//                R_DK2_TILE_0 | R_DK2_TILE_1 | R_DK2_TILE_2 | R_DK2_TILE_3 | R_DK2_TILE_4 | R_DK2_TILE_5,
//                R_DK2_TILE_PATTERN_1_1_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
//        DRP_DRV_ASSERT(ret_val);
//        /************************/
//        /* Activate DRP Library */
//        /************************/
//        ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
//                                                                                                           | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], 0);
//        DRP_DRV_ASSERT(ret_val);
//        /* Set start time of process*/
//        PerformSetStartTime(8);
//        /***************************************/
//        /* Set R_DK2_Start function parameters */
//        /***************************************/
//        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//        {
//            /* Set the address of buffer to be read/write by DRP */
////          param_dilate[tile_no].src = work_bufadr_med2thin + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////                  * tile_no);
////          param_dilate[tile_no].dst = output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////                  * tile_no);
//
//            param_dilate[tile_no].src = (uint32_t)&frame_RAM_A + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//            param_dilate[tile_no].dst = (uint32_t)&frame_RAM_B + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
////          param_dilate[tile_no].dst = p_work_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
////          param_dilate[tile_no].dst = (uint32_t)&frame_RAM_A + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//
//            R_MMU_VAtoPA((uint32_t)param_dilate[tile_no].src, &(param_dilate[tile_no].src));
//            R_MMU_VAtoPA((uint32_t)param_dilate[tile_no].dst, &(param_dilate[tile_no].dst));
//            /* Set Image size */
//            param_dilate[tile_no].width = R_BCD_CAMERA_WIDTH;
//            param_dilate[tile_no].height = R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM;
//            /* Set whether to perform top or bottom edge border processing. */
//            param_dilate[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
//            param_dilate[tile_no].bottom = (tile_no == TILE_5) ? 1 : 0;
//            /* Initialize variables to be used in termination judgment of the DRP library */
//            drp_lib_status[tile_no] = DRP_NOT_FINISH;
//            /*********************/
//            /* Start DRP Library */
//            /*********************/
//            ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_dilate[tile_no], sizeof(r_drp_dilate_t));
//            DRP_DRV_ASSERT(ret_val);
//        }
//
//        /***************************************/
//        /* Wait until DRP processing is finish */
//        /***************************************/
//        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//        {
//            while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
//            {
//                /* DO NOTHING */
//            }
//        }
//
//        /* Set end time of process */
//        PerformSetEndTime(8);
//        /**********************/
//        /* Unload DRP library */
//        /**********************/
//        ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3] |
//                drp_lib_id[TILE_4] | drp_lib_id[TILE_5], &drp_lib_id[TILE_0]);
//        DRP_DRV_ASSERT(ret_val);
//        /******************************************************************************************************/
//
//
//
//        /**Open-Dilate2****************************************************************************************/
//        /**************************/
//        /* Load DRP Library       */
//        /*        +-------------+ */
//        /* tile 0 |   Dilate    | */
//        /*        +-------------+ */
//        /* tile 1 |   Dilate    | */
//        /*        +-------------+ */
//        /* tile 2 |   Dilate    | */
//        /*        +-------------+ */
//        /* tile 3 |   Dilate    | */
//        /*        +-------------+ */
//        /* tile 4 |   Dilate    | */
//        /*        +-------------+ */
//        /* tile 5 |   Dilate    | */
//        /*        +-------------+ */
//        /**************************/
//        ret_val = R_DK2_Load(&g_drp_lib_dilate[0],
//                             R_DK2_TILE_0 | R_DK2_TILE_1 | R_DK2_TILE_2 | R_DK2_TILE_3 | R_DK2_TILE_4 | R_DK2_TILE_5,
//                             R_DK2_TILE_PATTERN_1_1_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
//        DRP_DRV_ASSERT(ret_val);
//        /************************/
//        /* Activate DRP Library */
//        /************************/
//        ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
//                                                                                                           | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], 0);
//        DRP_DRV_ASSERT(ret_val);
//        /* Set start time of process*/
//        PerformSetStartTime(8);
//        /***************************************/
//        /* Set R_DK2_Start function parameters */
//        /***************************************/
//        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//        {
//            /* Set the address of buffer to be read/write by DRP */
//            //          param_dilate[tile_no].src = work_bufadr_med2thin + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//            //                  * tile_no);
//            //          param_dilate[tile_no].dst = output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//            //                  * tile_no);
//
//            param_dilate[tile_no].src = (uint32_t)&frame_RAM_B + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//            param_dilate[tile_no].dst = (uint32_t)&frame_RAM_C + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//            //          param_dilate[tile_no].dst = p_work_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//            //          param_dilate[tile_no].dst = (uint32_t)&frame_RAM_A + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//
//            R_MMU_VAtoPA((uint32_t)param_dilate[tile_no].src, &(param_dilate[tile_no].src));
//            R_MMU_VAtoPA((uint32_t)param_dilate[tile_no].dst, &(param_dilate[tile_no].dst));
//            /* Set Image size */
//            param_dilate[tile_no].width = R_BCD_CAMERA_WIDTH;
//            param_dilate[tile_no].height = R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM;
//            /* Set whether to perform top or bottom edge border processing. */
//            param_dilate[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
//            param_dilate[tile_no].bottom = (tile_no == TILE_5) ? 1 : 0;
//            /* Initialize variables to be used in termination judgment of the DRP library */
//            drp_lib_status[tile_no] = DRP_NOT_FINISH;
//            /*********************/
//            /* Start DRP Library */
//            /*********************/
//            ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_dilate[tile_no], sizeof(r_drp_dilate_t));
//            DRP_DRV_ASSERT(ret_val);
//        }
//
//        /***************************************/
//        /* Wait until DRP processing is finish */
//        /***************************************/
//        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//        {
//            while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
//            {
//                /* DO NOTHING */
//            }
//        }
//
//        /* Set end time of process */
//        PerformSetEndTime(8);
//        /**********************/
//        /* Unload DRP library */
//        /**********************/
//        ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3] |
//                               drp_lib_id[TILE_4] | drp_lib_id[TILE_5], &drp_lib_id[TILE_0]);
//        DRP_DRV_ASSERT(ret_val);
//        /******************************************************************************************************/
//
//
//        /**Open-Dilate3****************************************************************************************/
//        /**************************/
//        /* Load DRP Library       */
//        /*        +-------------+ */
//        /* tile 0 |   Dilate    | */
//        /*        +-------------+ */
//        /* tile 1 |   Dilate    | */
//        /*        +-------------+ */
//        /* tile 2 |   Dilate    | */
//        /*        +-------------+ */
//        /* tile 3 |   Dilate    | */
//        /*        +-------------+ */
//        /* tile 4 |   Dilate    | */
//        /*        +-------------+ */
//        /* tile 5 |   Dilate    | */
//        /*        +-------------+ */
//        /**************************/
//        ret_val = R_DK2_Load(&g_drp_lib_dilate[0],
//                             R_DK2_TILE_0 | R_DK2_TILE_1 | R_DK2_TILE_2 | R_DK2_TILE_3 | R_DK2_TILE_4 | R_DK2_TILE_5,
//                             R_DK2_TILE_PATTERN_1_1_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
//        DRP_DRV_ASSERT(ret_val);
//        /************************/
//        /* Activate DRP Library */
//        /************************/
//        ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
//                                                                                                           | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], 0);
//        DRP_DRV_ASSERT(ret_val);
//        /* Set start time of process*/
//        PerformSetStartTime(8);
//        /***************************************/
//        /* Set R_DK2_Start function parameters */
//        /***************************************/
//        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//        {
//            /* Set the address of buffer to be read/write by DRP */
//            //          param_dilate[tile_no].src = work_bufadr_med2thin + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//            //                  * tile_no);
//            //          param_dilate[tile_no].dst = output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//            //                  * tile_no);
//
//            param_dilate[tile_no].src = (uint32_t)&frame_RAM_C + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//            param_dilate[tile_no].dst = (uint32_t)&frame_RAM_A + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//            //          param_dilate[tile_no].dst = p_work_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//            //          param_dilate[tile_no].dst = (uint32_t)&frame_RAM_A + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//
//            R_MMU_VAtoPA((uint32_t)param_dilate[tile_no].src, &(param_dilate[tile_no].src));
//            R_MMU_VAtoPA((uint32_t)param_dilate[tile_no].dst, &(param_dilate[tile_no].dst));
//            /* Set Image size */
//            param_dilate[tile_no].width = R_BCD_CAMERA_WIDTH;
//            param_dilate[tile_no].height = R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM;
//            /* Set whether to perform top or bottom edge border processing. */
//            param_dilate[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
//            param_dilate[tile_no].bottom = (tile_no == TILE_5) ? 1 : 0;
//            /* Initialize variables to be used in termination judgment of the DRP library */
//            drp_lib_status[tile_no] = DRP_NOT_FINISH;
//            /*********************/
//            /* Start DRP Library */
//            /*********************/
//            ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_dilate[tile_no], sizeof(r_drp_dilate_t));
//            DRP_DRV_ASSERT(ret_val);
//        }
//
//        /***************************************/
//        /* Wait until DRP processing is finish */
//        /***************************************/
//        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//        {
//            while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
//            {
//                /* DO NOTHING */
//            }
//        }
//
//        /* Set end time of process */
//        PerformSetEndTime(8);
//        /**********************/
//        /* Unload DRP library */
//        /**********************/
//        ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3] |
//                               drp_lib_id[TILE_4] | drp_lib_id[TILE_5], &drp_lib_id[TILE_0]);
//        DRP_DRV_ASSERT(ret_val);
//        /******************************************************************************************************/
//        /******************************************************************************************************/
//        /******************************************************************************************************/




        /**Closing*********************************************************************************************/
        /******************************************************************************************************/
        /**Close-Dilate1***************************************************************************************/
        /**************************/
        /* Load DRP Library       */
        /*        +-------------+ */
        /* tile 0 |   Dilate    | */
        /*        +-------------+ */
        /* tile 1 |   Dilate    | */
        /*        +-------------+ */
        /* tile 2 |   Dilate    | */
        /*        +-------------+ */
        /* tile 3 |   Dilate    | */
        /*        +-------------+ */
        /* tile 4 |   Dilate    | */
        /*        +-------------+ */
        /* tile 5 |   Dilate    | */
        /*        +-------------+ */
        /**************************/
        ret_val = R_DK2_Load(&g_drp_lib_dilate[0],
                R_DK2_TILE_0 | R_DK2_TILE_1 | R_DK2_TILE_2 | R_DK2_TILE_3 | R_DK2_TILE_4 | R_DK2_TILE_5,
                R_DK2_TILE_PATTERN_1_1_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
        DRP_DRV_ASSERT(ret_val);
        /************************/
        /* Activate DRP Library */
        /************************/
        ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
                                                                                                           | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], 0);
        DRP_DRV_ASSERT(ret_val);
        /* Set start time of process*/
        PerformSetStartTime(8);
        PerformSetStartTime(20);
        /***************************************/
        /* Set R_DK2_Start function parameters */
        /***************************************/
        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
        {
            /* Set the address of buffer to be read/write by DRP */
//          param_dilate[tile_no].src = work_bufadr_med2thin + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//                  * tile_no);
//          param_dilate[tile_no].dst = output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//                  * tile_no);

            param_dilate[tile_no].src = (uint32_t)&frame_RAM_A + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
            param_dilate[tile_no].dst = (uint32_t)&frame_RAM_B + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//          param_dilate[tile_no].dst = p_work_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//          param_dilate[tile_no].dst = (uint32_t)&frame_RAM_A + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);

            R_MMU_VAtoPA((uint32_t)param_dilate[tile_no].src, &(param_dilate[tile_no].src));
            R_MMU_VAtoPA((uint32_t)param_dilate[tile_no].dst, &(param_dilate[tile_no].dst));
            /* Set Image size */
            param_dilate[tile_no].width = R_BCD_CAMERA_WIDTH;
            param_dilate[tile_no].height = R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM;
            /* Set whether to perform top or bottom edge border processing. */
            param_dilate[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
            param_dilate[tile_no].bottom = (tile_no == TILE_5) ? 1 : 0;
            /* Initialize variables to be used in termination judgment of the DRP library */
            drp_lib_status[tile_no] = DRP_NOT_FINISH;
            /*********************/
            /* Start DRP Library */
            /*********************/
            ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_dilate[tile_no], sizeof(r_drp_dilate_t));
            DRP_DRV_ASSERT(ret_val);
        }

        /***************************************/
        /* Wait until DRP processing is finish */
        /***************************************/
        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
        {
            while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
            {
                /* DO NOTHING */
            }
        }

        /* Set end time of process */
        PerformSetEndTime(8);
        /**********************/
        /* Unload DRP library */
        /**********************/
        ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3] |
                drp_lib_id[TILE_4] | drp_lib_id[TILE_5], &drp_lib_id[TILE_0]);
        DRP_DRV_ASSERT(ret_val);
        /******************************************************************************************************/



        /**Close-Dilate2***************************************************************************************/
        /**************************/
        /* Load DRP Library       */
        /*        +-------------+ */
        /* tile 0 |   Dilate    | */
        /*        +-------------+ */
        /* tile 1 |   Dilate    | */
        /*        +-------------+ */
        /* tile 2 |   Dilate    | */
        /*        +-------------+ */
        /* tile 3 |   Dilate    | */
        /*        +-------------+ */
        /* tile 4 |   Dilate    | */
        /*        +-------------+ */
        /* tile 5 |   Dilate    | */
        /*        +-------------+ */
        /**************************/
        ret_val = R_DK2_Load(&g_drp_lib_dilate[0],
                             R_DK2_TILE_0 | R_DK2_TILE_1 | R_DK2_TILE_2 | R_DK2_TILE_3 | R_DK2_TILE_4 | R_DK2_TILE_5,
                             R_DK2_TILE_PATTERN_1_1_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
        DRP_DRV_ASSERT(ret_val);
        /************************/
        /* Activate DRP Library */
        /************************/
        ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
                                                                                                           | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], 0);
        DRP_DRV_ASSERT(ret_val);
        /* Set start time of process*/
        PerformSetStartTime(8);
        /***************************************/
        /* Set R_DK2_Start function parameters */
        /***************************************/
        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
        {
            /* Set the address of buffer to be read/write by DRP */
            //          param_dilate[tile_no].src = work_bufadr_med2thin + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
            //                  * tile_no);
            //          param_dilate[tile_no].dst = output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
            //                  * tile_no);

            param_dilate[tile_no].src = (uint32_t)&frame_RAM_B + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
            param_dilate[tile_no].dst = (uint32_t)&frame_RAM_C + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
            //          param_dilate[tile_no].dst = p_work_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
            //          param_dilate[tile_no].dst = (uint32_t)&frame_RAM_A + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);

            R_MMU_VAtoPA((uint32_t)param_dilate[tile_no].src, &(param_dilate[tile_no].src));
            R_MMU_VAtoPA((uint32_t)param_dilate[tile_no].dst, &(param_dilate[tile_no].dst));
            /* Set Image size */
            param_dilate[tile_no].width = R_BCD_CAMERA_WIDTH;
            param_dilate[tile_no].height = R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM;
            /* Set whether to perform top or bottom edge border processing. */
            param_dilate[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
            param_dilate[tile_no].bottom = (tile_no == TILE_5) ? 1 : 0;
            /* Initialize variables to be used in termination judgment of the DRP library */
            drp_lib_status[tile_no] = DRP_NOT_FINISH;
            /*********************/
            /* Start DRP Library */
            /*********************/
            ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_dilate[tile_no], sizeof(r_drp_dilate_t));
            DRP_DRV_ASSERT(ret_val);
        }

        /***************************************/
        /* Wait until DRP processing is finish */
        /***************************************/
        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
        {
            while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
            {
                /* DO NOTHING */
            }
        }

        /* Set end time of process */
        PerformSetEndTime(8);
        /**********************/
        /* Unload DRP library */
        /**********************/
        ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3] |
                               drp_lib_id[TILE_4] | drp_lib_id[TILE_5], &drp_lib_id[TILE_0]);
        DRP_DRV_ASSERT(ret_val);
        /******************************************************************************************************/


        /**Close-Dilate3***************************************************************************************/
        /**************************/
        /* Load DRP Library       */
        /*        +-------------+ */
        /* tile 0 |   Dilate    | */
        /*        +-------------+ */
        /* tile 1 |   Dilate    | */
        /*        +-------------+ */
        /* tile 2 |   Dilate    | */
        /*        +-------------+ */
        /* tile 3 |   Dilate    | */
        /*        +-------------+ */
        /* tile 4 |   Dilate    | */
        /*        +-------------+ */
        /* tile 5 |   Dilate    | */
        /*        +-------------+ */
        /**************************/
        ret_val = R_DK2_Load(&g_drp_lib_dilate[0],
                             R_DK2_TILE_0 | R_DK2_TILE_1 | R_DK2_TILE_2 | R_DK2_TILE_3 | R_DK2_TILE_4 | R_DK2_TILE_5,
                             R_DK2_TILE_PATTERN_1_1_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
        DRP_DRV_ASSERT(ret_val);
        /************************/
        /* Activate DRP Library */
        /************************/
        ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
                                                                                                           | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], 0);
        DRP_DRV_ASSERT(ret_val);
        /* Set start time of process*/
        PerformSetStartTime(8);
        /***************************************/
        /* Set R_DK2_Start function parameters */
        /***************************************/
        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
        {
            /* Set the address of buffer to be read/write by DRP */
            //          param_dilate[tile_no].src = work_bufadr_med2thin + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
            //                  * tile_no);
            //          param_dilate[tile_no].dst = output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
            //                  * tile_no);

            param_dilate[tile_no].src = (uint32_t)&frame_RAM_C + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
            param_dilate[tile_no].dst = (uint32_t)&frame_RAM_A + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
            //          param_dilate[tile_no].dst = p_work_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
            //          param_dilate[tile_no].dst = (uint32_t)&frame_RAM_A + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);

            R_MMU_VAtoPA((uint32_t)param_dilate[tile_no].src, &(param_dilate[tile_no].src));
            R_MMU_VAtoPA((uint32_t)param_dilate[tile_no].dst, &(param_dilate[tile_no].dst));
            /* Set Image size */
            param_dilate[tile_no].width = R_BCD_CAMERA_WIDTH;
            param_dilate[tile_no].height = R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM;
            /* Set whether to perform top or bottom edge border processing. */
            param_dilate[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
            param_dilate[tile_no].bottom = (tile_no == TILE_5) ? 1 : 0;
            /* Initialize variables to be used in termination judgment of the DRP library */
            drp_lib_status[tile_no] = DRP_NOT_FINISH;
            /*********************/
            /* Start DRP Library */
            /*********************/
            ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_dilate[tile_no], sizeof(r_drp_dilate_t));
            DRP_DRV_ASSERT(ret_val);
        }

        /***************************************/
        /* Wait until DRP processing is finish */
        /***************************************/
        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
        {
            while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
            {
                /* DO NOTHING */
            }
        }

        /* Set end time of process */
        PerformSetEndTime(8);
        /**********************/
        /* Unload DRP library */
        /**********************/
        ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3] |
                               drp_lib_id[TILE_4] | drp_lib_id[TILE_5], &drp_lib_id[TILE_0]);
        DRP_DRV_ASSERT(ret_val);
        /******************************************************************************************************/


//        /**Dilate4*********************************************************************************************/
//        /**************************/
//        /* Load DRP Library       */
//        /*        +-------------+ */
//        /* tile 0 |   Dilate    | */
//        /*        +-------------+ */
//        /* tile 1 |   Dilate    | */
//        /*        +-------------+ */
//        /* tile 2 |   Dilate    | */
//        /*        +-------------+ */
//        /* tile 3 |   Dilate    | */
//        /*        +-------------+ */
//        /* tile 4 |   Dilate    | */
//        /*        +-------------+ */
//        /* tile 5 |   Dilate    | */
//        /*        +-------------+ */
//        /**************************/
//        ret_val = R_DK2_Load(&g_drp_lib_dilate[0],
//                             R_DK2_TILE_0 | R_DK2_TILE_1 | R_DK2_TILE_2 | R_DK2_TILE_3 | R_DK2_TILE_4 | R_DK2_TILE_5,
//                             R_DK2_TILE_PATTERN_1_1_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
//        DRP_DRV_ASSERT(ret_val);
//        /************************/
//        /* Activate DRP Library */
//        /************************/
//        ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
//                                                                                                           | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], 0);
//        DRP_DRV_ASSERT(ret_val);
//        /* Set start time of process*/
//        PerformSetStartTime(8);
//        /***************************************/
//        /* Set R_DK2_Start function parameters */
//        /***************************************/
//        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//        {
//            /* Set the address of buffer to be read/write by DRP */
//            //          param_dilate[tile_no].src = work_bufadr_med2thin + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//            //                  * tile_no);
//            //          param_dilate[tile_no].dst = output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//            //                  * tile_no);
//
//            param_dilate[tile_no].src = (uint32_t)&frame_RAM_A + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//            param_dilate[tile_no].dst = (uint32_t)&frame_RAM_B + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//            //          param_dilate[tile_no].dst = p_work_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//            //          param_dilate[tile_no].dst = (uint32_t)&frame_RAM_A + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//
//            R_MMU_VAtoPA((uint32_t)param_dilate[tile_no].src, &(param_dilate[tile_no].src));
//            R_MMU_VAtoPA((uint32_t)param_dilate[tile_no].dst, &(param_dilate[tile_no].dst));
//            /* Set Image size */
//            param_dilate[tile_no].width = R_BCD_CAMERA_WIDTH;
//            param_dilate[tile_no].height = R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM;
//            /* Set whether to perform top or bottom edge border processing. */
//            param_dilate[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
//            param_dilate[tile_no].bottom = (tile_no == TILE_5) ? 1 : 0;
//            /* Initialize variables to be used in termination judgment of the DRP library */
//            drp_lib_status[tile_no] = DRP_NOT_FINISH;
//            /*********************/
//            /* Start DRP Library */
//            /*********************/
//            ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_dilate[tile_no], sizeof(r_drp_dilate_t));
//            DRP_DRV_ASSERT(ret_val);
//        }
//
//        /***************************************/
//        /* Wait until DRP processing is finish */
//        /***************************************/
//        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//        {
//            while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
//            {
//                /* DO NOTHING */
//            }
//        }
//
//        /* Set end time of process */
//        PerformSetEndTime(8);
//        /**********************/
//        /* Unload DRP library */
//        /**********************/
//        ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3] |
//                               drp_lib_id[TILE_4] | drp_lib_id[TILE_5], &drp_lib_id[TILE_0]);
//        DRP_DRV_ASSERT(ret_val);
//        /******************************************************************************************************/



        /**Close-Erode1*****************************************************************************************/
        /**************************/
        /* Load DRP Library       */
        /*        +-------------+ */
        /* tile 0 |   Erode     | */
        /*        +-------------+ */
        /* tile 1 |   Erode     | */
        /*        +-------------+ */
        /* tile 2 |   Erode     | */
        /*        +-------------+ */
        /* tile 3 |   Erode     | */
        /*        +-------------+ */
        /* tile 4 |   Erode     | */
        /*        +-------------+ */
        /* tile 5 |   Erode     | */
        /*        +-------------+ */
        /**************************/
        ret_val = R_DK2_Load(&g_drp_lib_erode[0],
                R_DK2_TILE_0 | R_DK2_TILE_1 | R_DK2_TILE_2 | R_DK2_TILE_3 | R_DK2_TILE_4 | R_DK2_TILE_5,
                R_DK2_TILE_PATTERN_1_1_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
        DRP_DRV_ASSERT(ret_val);
        /************************/
        /* Activate DRP Library */
        /************************/
        ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
                                                                                                           | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], 0);
        DRP_DRV_ASSERT(ret_val);
        /* Set start time of process*/
        PerformSetStartTime(8);
        /***************************************/
        /* Set R_DK2_Start function parameters */
        /***************************************/
        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
        {
            /* Set the address of buffer to be read/write by DRP */
//          param_dilate[tile_no].src = work_bufadr_med2thin + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//                  * tile_no);
//          param_dilate[tile_no].dst = output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//                  * tile_no);

            param_erode[tile_no].src = (uint32_t)&frame_RAM_A + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
            param_erode[tile_no].dst = (uint32_t)&frame_RAM_B + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//          param_dilate[tile_no].dst = p_work_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//          param_dilate[tile_no].dst = (uint32_t)&frame_RAM_A + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);

            R_MMU_VAtoPA((uint32_t)param_erode[tile_no].src, &(param_erode[tile_no].src));
            R_MMU_VAtoPA((uint32_t)param_erode[tile_no].dst, &(param_erode[tile_no].dst));
            /* Set Image size */
            param_erode[tile_no].width = R_BCD_CAMERA_WIDTH;
            param_erode[tile_no].height = R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM;
            /* Set whether to perform top or bottom edge border processing. */
            param_erode[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
            param_erode[tile_no].bottom = (tile_no == TILE_5) ? 1 : 0;
            /* Initialize variables to be used in termination judgment of the DRP library */
            drp_lib_status[tile_no] = DRP_NOT_FINISH;
            /*********************/
            /* Start DRP Library */
            /*********************/
            ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_erode[tile_no], sizeof(r_drp_erode_t));
            DRP_DRV_ASSERT(ret_val);
        }

        /***************************************/
        /* Wait until DRP processing is finish */
        /***************************************/
        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
        {
            while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
            {
                /* DO NOTHING */
            }
        }

        /* Set end time of process */
        PerformSetEndTime(8);
        /**********************/
        /* Unload DRP library */
        /**********************/
        ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3] |
                drp_lib_id[TILE_4] | drp_lib_id[TILE_5], &drp_lib_id[TILE_0]);
        DRP_DRV_ASSERT(ret_val);
        /******************************************************************************************************/



        /**Close-Erode2****************************************************************************************/
        /**************************/
        /* Load DRP Library       */
        /*        +-------------+ */
        /* tile 0 |   Erode     | */
        /*        +-------------+ */
        /* tile 1 |   Erode     | */
        /*        +-------------+ */
        /* tile 2 |   Erode     | */
        /*        +-------------+ */
        /* tile 3 |   Erode     | */
        /*        +-------------+ */
        /* tile 4 |   Erode     | */
        /*        +-------------+ */
        /* tile 5 |   Erode     | */
        /*        +-------------+ */
        /**************************/
        ret_val = R_DK2_Load(&g_drp_lib_erode[0],
                R_DK2_TILE_0 | R_DK2_TILE_1 | R_DK2_TILE_2 | R_DK2_TILE_3 | R_DK2_TILE_4 | R_DK2_TILE_5,
                R_DK2_TILE_PATTERN_1_1_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
        DRP_DRV_ASSERT(ret_val);
        /************************/
        /* Activate DRP Library */
        /************************/
        ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
                                                                                                           | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], 0);
        DRP_DRV_ASSERT(ret_val);
        /* Set start time of process*/
        PerformSetStartTime(8);
        /***************************************/
        /* Set R_DK2_Start function parameters */
        /***************************************/
        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
        {
            /* Set the address of buffer to be read/write by DRP */
//          param_dilate[tile_no].src = work_bufadr_med2thin + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//                  * tile_no);
//          param_dilate[tile_no].dst = output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//                  * tile_no);

            param_erode[tile_no].src = (uint32_t)&frame_RAM_B + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
            param_erode[tile_no].dst = (uint32_t)&frame_RAM_C + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//          param_dilate[tile_no].dst = p_work_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//          param_dilate[tile_no].dst = (uint32_t)&frame_RAM_A + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);

            R_MMU_VAtoPA((uint32_t)param_erode[tile_no].src, &(param_erode[tile_no].src));
            R_MMU_VAtoPA((uint32_t)param_erode[tile_no].dst, &(param_erode[tile_no].dst));
            /* Set Image size */
            param_erode[tile_no].width = R_BCD_CAMERA_WIDTH;
            param_erode[tile_no].height = R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM;
            /* Set whether to perform top or bottom edge border processing. */
            param_erode[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
            param_erode[tile_no].bottom = (tile_no == TILE_5) ? 1 : 0;
            /* Initialize variables to be used in termination judgment of the DRP library */
            drp_lib_status[tile_no] = DRP_NOT_FINISH;
            /*********************/
            /* Start DRP Library */
            /*********************/
            ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_erode[tile_no], sizeof(r_drp_erode_t));
            DRP_DRV_ASSERT(ret_val);
        }

        /***************************************/
        /* Wait until DRP processing is finish */
        /***************************************/
        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
        {
            while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
            {
                /* DO NOTHING */
            }
        }

        /* Set end time of process */
        PerformSetEndTime(8);
        /**********************/
        /* Unload DRP library */
        /**********************/
        ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3] |
                drp_lib_id[TILE_4] | drp_lib_id[TILE_5], &drp_lib_id[TILE_0]);
        DRP_DRV_ASSERT(ret_val);
        /******************************************************************************************************/



        /**Close-Erode3****************************************************************************************/
        /**************************/
        /* Load DRP Library       */
        /*        +-------------+ */
        /* tile 0 |   Erode     | */
        /*        +-------------+ */
        /* tile 1 |   Erode     | */
        /*        +-------------+ */
        /* tile 2 |   Erode     | */
        /*        +-------------+ */
        /* tile 3 |   Erode     | */
        /*        +-------------+ */
        /* tile 4 |   Erode     | */
        /*        +-------------+ */
        /* tile 5 |   Erode     | */
        /*        +-------------+ */
        /**************************/
        ret_val = R_DK2_Load(&g_drp_lib_erode[0],
                R_DK2_TILE_0 | R_DK2_TILE_1 | R_DK2_TILE_2 | R_DK2_TILE_3 | R_DK2_TILE_4 | R_DK2_TILE_5,
                R_DK2_TILE_PATTERN_1_1_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
        DRP_DRV_ASSERT(ret_val);
        /************************/
        /* Activate DRP Library */
        /************************/
        ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
                                                                                                           | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], 0);
        DRP_DRV_ASSERT(ret_val);
        /* Set start time of process*/
        PerformSetStartTime(8);
        /***************************************/
        /* Set R_DK2_Start function parameters */
        /***************************************/
        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
        {
            /* Set the address of buffer to be read/write by DRP */
//          param_dilate[tile_no].src = work_bufadr_med2thin + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//                  * tile_no);
//          param_dilate[tile_no].dst = output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
//                  * tile_no);

            param_erode[tile_no].src = (uint32_t)&frame_RAM_C + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//            param_erode[tile_no].dst = p_output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
            param_erode[tile_no].dst = (uint32_t)&frame_RAM_A + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);

            R_MMU_VAtoPA((uint32_t)param_erode[tile_no].src, &(param_erode[tile_no].src));
            R_MMU_VAtoPA((uint32_t)param_erode[tile_no].dst, &(param_erode[tile_no].dst));
            /* Set Image size */
            param_erode[tile_no].width = R_BCD_CAMERA_WIDTH;
            param_erode[tile_no].height = R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM;
            /* Set whether to perform top or bottom edge border processing. */
            param_erode[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
            param_erode[tile_no].bottom = (tile_no == TILE_5) ? 1 : 0;
            /* Initialize variables to be used in termination judgment of the DRP library */
            drp_lib_status[tile_no] = DRP_NOT_FINISH;
            /*********************/
            /* Start DRP Library */
            /*********************/
            ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_erode[tile_no], sizeof(r_drp_erode_t));
            DRP_DRV_ASSERT(ret_val);
        }

        /***************************************/
        /* Wait until DRP processing is finish */
        /***************************************/
        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
        {
            while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
            {
                /* DO NOTHING */
            }
        }

        /* Set end time of process */
        PerformSetEndTime(8);
        PerformSetEndTime(20);
        /**********************/
        /* Unload DRP library */
        /**********************/
        ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3] |
                drp_lib_id[TILE_4] | drp_lib_id[TILE_5], &drp_lib_id[TILE_0]);
        DRP_DRV_ASSERT(ret_val);
        /******************************************************************************************************/



//        /**Erode4*********************************************************************************************/
//        /**************************/
//        /* Load DRP Library       */
//        /*        +-------------+ */
//        /* tile 0 |   Erode     | */
//        /*        +-------------+ */
//        /* tile 1 |   Erode     | */
//        /*        +-------------+ */
//        /* tile 2 |   Erode     | */
//        /*        +-------------+ */
//        /* tile 3 |   Erode     | */
//        /*        +-------------+ */
//        /* tile 4 |   Erode     | */
//        /*        +-------------+ */
//        /* tile 5 |   Erode     | */
//        /*        +-------------+ */
//        /**************************/
//        ret_val = R_DK2_Load(&g_drp_lib_erode[0],
//                R_DK2_TILE_0 | R_DK2_TILE_1 | R_DK2_TILE_2 | R_DK2_TILE_3 | R_DK2_TILE_4 | R_DK2_TILE_5,
//                R_DK2_TILE_PATTERN_1_1_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
//        DRP_DRV_ASSERT(ret_val);
//        /************************/
//        /* Activate DRP Library */
//        /************************/
//        ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
//                                                                                                           | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], 0);
//        DRP_DRV_ASSERT(ret_val);
//        /* Set start time of process*/
//        PerformSetStartTime(8);
//        /***************************************/
//        /* Set R_DK2_Start function parameters */
//        /***************************************/
//        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//        {
//            /* Set the address of buffer to be read/write by DRP */
////          param_dilate[tile_no].src = work_bufadr_med2thin + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////                  * tile_no);
////          param_dilate[tile_no].dst = output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////                  * tile_no);
//
//            param_erode[tile_no].src = (uint32_t)&frame_RAM_B + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//            param_erode[tile_no].dst = p_output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
////          param_dilate[tile_no].dst = p_work_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
////          param_dilate[tile_no].dst = (uint32_t)&frame_RAM_A + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//
//            R_MMU_VAtoPA((uint32_t)param_erode[tile_no].src, &(param_erode[tile_no].src));
//            R_MMU_VAtoPA((uint32_t)param_erode[tile_no].dst, &(param_erode[tile_no].dst));
//            /* Set Image size */
//            param_erode[tile_no].width = R_BCD_CAMERA_WIDTH;
//            param_erode[tile_no].height = R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM;
//            /* Set whether to perform top or bottom edge border processing. */
//            param_erode[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
//            param_erode[tile_no].bottom = (tile_no == TILE_5) ? 1 : 0;
//            /* Initialize variables to be used in termination judgment of the DRP library */
//            drp_lib_status[tile_no] = DRP_NOT_FINISH;
//            /*********************/
//            /* Start DRP Library */
//            /*********************/
//            ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_erode[tile_no], sizeof(r_drp_erode_t));
//            DRP_DRV_ASSERT(ret_val);
//        }
//
//        /***************************************/
//        /* Wait until DRP processing is finish */
//        /***************************************/
//        for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//        {
//            while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
//            {
//                /* DO NOTHING */
//            }
//        }
//
//        /* Set end time of process */
//        PerformSetEndTime(8);
//        /**********************/
//        /* Unload DRP library */
//        /**********************/
//        ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3] |
//                drp_lib_id[TILE_4] | drp_lib_id[TILE_5], &drp_lib_id[TILE_0]);
//        DRP_DRV_ASSERT(ret_val);
//        /******************************************************************************************************/



        /******************************************************************************************************/
        /******************************/
        /* Load DRP Library           */
        /*        +-----------------+ */
        /* tile 0 |                 | */
        /*        +                 + */
        /* tile 1 |    Thinning     | */
        /*        +                 + */
        /* tile 2 |                 | */
        /*        +-----------------+ */
        /* tile 3 |                 | */
        /*        +                 + */
        /* tile 4 |    Thinning     | */
        /*        +                 + */
        /* tile 5 |                 | */
        /*        +-----------------+ */
        /******************************/
        ret_val = R_DK2_Load(&g_drp_lib_thinning[0], R_DK2_TILE_0 | R_DK2_TILE_3,
                R_DK2_TILE_PATTERN_3_3, NULL, &cb_drp_finish, &drp_lib_id[0]);
        DRP_DRV_ASSERT(ret_val);

        /********************/
        /* Activate DRP Lib */
        /********************/
        ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_3], 0);
        DRP_DRV_ASSERT(ret_val);

        /* Set start time of process*/
        PerformSetStartTime(19);

        /***************************************/
        /* Set R_DK2_Start function parameters */
        /***************************************/
        for (tile_no = TILE_0; tile_no <= TILE_3; tile_no += 3)
        {
            /* Set Image size */
            param_thinning[tile_no].width = R_BCD_CAMERA_WIDTH;
            param_thinning[tile_no].height = (R_BCD_CAMERA_HEIGHT / 2);

            /* Set Buffer size */
            bufsize_thinning = (uint32_t)(param_thinning[tile_no].width * param_thinning[tile_no].height);

            /* Set the address of buffer to be read/write by DRP */
//          param_thinning[tile_no].src = work_bufadr_med2thin + ((tile_no / 3) * bufsize_thinning);
////            param_thinning[tile_no].dst = output_bufadr  + ((tile_no / 3) * bufsize_thinning);
//          param_thinning[tile_no].dst = output_bufadr  + ((tile_no / 3) * bufsize_thinning);

            param_thinning[tile_no].src = (uint32_t)&frame_RAM_A + ((tile_no / 3) * bufsize_thinning);
//            param_thinning[tile_no].dst = (uint32_t)&frame_RAM_B + ((tile_no / 3) * bufsize_thinning);
            param_thinning[tile_no].dst = p_output_bufadr + ((tile_no / 3) * bufsize_thinning);

            R_MMU_VAtoPA((uint32_t)param_thinning[tile_no].src, &(param_thinning[tile_no].src));
            R_MMU_VAtoPA((uint32_t)param_thinning[tile_no].dst, &(param_thinning[tile_no].dst));


            /* Set additional information (currently no additional information) */
            param_thinning[tile_no].result =
                    (uint32_t)&p_frame_ram_thinning[((tile_no / 3) * (bufsize_thinning + (R_BCD_CAMERA_WIDTH*2) ))*2];
            R_MMU_VAtoPA((uint32_t)param_thinning[tile_no].result, &(param_thinning[tile_no].result));

            param_thinning[tile_no].threshold = 0x01;
            param_thinning[tile_no].reverse = 1;

            /* Set whether to perform top or bottom edge border processing. */
            param_thinning[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
            param_thinning[tile_no].bottom = (tile_no == TILE_3) ? 1 : 0;

            param_thinning[tile_no].step = 1;

            /* Initialize variables to be used in termination judgment of the DRP library */
            drp_lib_status[tile_no] = DRP_NOT_FINISH;

            /*********************/
            /* Start DRP Library */
            /*********************/
            ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_thinning[tile_no],
                    sizeof(r_drp_thinning_t));
            DRP_DRV_ASSERT(ret_val);
        }

        /***************************************/
        /* Wait until DRP processing is finish */
        /***************************************/
        for (tile_no = TILE_0; tile_no <= TILE_3; tile_no += 3)
        {
            /***************************************/
            /* Wait until DRP processing is finish */
            /***************************************/
            while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
            {
                /* DO NOTHING */
            }
        }

        /* Set end time of DRP processing */
        PerformSetEndTime(19);

        /**********************/
        /* Unload DRP library */
        /**********************/
        ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_3] , &drp_lib_id[TILE_0]);
        DRP_DRV_ASSERT(ret_val);


        /******************************************************************************************************/





//		/******************************************************************************************************/
//		/******************************/
//		/* Load DRP Library           */
//		/*        +-----------------+ */
//		/* tile 0 | 	Sobel		| */
//		/*        +-----------------+ */
//		/* tile 1 | 	Sobel		| */
//		/*        +-----------------+ */
//		/* tile 2 | 	Sobel		| */
//		/*        +-----------------+ */
//		/* tile 3 | 	Sobel		| */
//		/*        +-----------------+ */
//		/* tile 4 | 	Sobel		| */
//		/*        +-----------------+ */
//		/* tile 5 | 	Sobel		| */
//		/*        +-----------------+ */
//		/******************************/
//		ret_val = R_DK2_Load(&g_drp_lib_sobel[0],
//				R_DK2_TILE_0 | R_DK2_TILE_1 | R_DK2_TILE_2 | R_DK2_TILE_3 | R_DK2_TILE_4 | R_DK2_TILE_5,
//				R_DK2_TILE_PATTERN_1_1_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
//		DRP_DRV_ASSERT(ret_val);
//		//        printf("b2g load ret val = %d", ret_val);
//
//		/************************/
//		/* Activate DRP Library */
//		/************************/
//		ret_val = R_DK2_Activate(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
//																										   | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], 0);
//		DRP_DRV_ASSERT(ret_val);
//		//        printf("b2g activate ret val = %d", ret_val);
//
//		/* Set start time of process*/
//		PerformSetStartTime(7);;
//
//
//
//		/***************************************/
//		/* Set R_DK2_Start function parameters */
//		/***************************************/
//		for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//		{
//			/* Set the address of buffer to be read/write by DRP */
////			param_sobel[tile_no].src = work_bufadr_med2dilate + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////					* tile_no);
////			//            param_b2g[tile_no].dst = work_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////			//                                                                                                            * tile_no);
////			param_sobel[tile_no].dst = output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))
////					* tile_no);
//
//
//		    param_sobel[tile_no].src = (uint32_t)&frame_RAM_A + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
////			param_sobel[tile_no].src = p_work_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//			param_sobel[tile_no].dst = p_output_bufadr + ((R_BCD_CAMERA_WIDTH * (R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM))* tile_no);
//
//			R_MMU_VAtoPA((uint32_t)param_sobel[tile_no].src, &(param_sobel[tile_no].src));
//			R_MMU_VAtoPA((uint32_t)param_sobel[tile_no].dst, &(param_sobel[tile_no].dst));
//
//
//			/* Set Image size */
//			param_sobel[tile_no].width = R_BCD_CAMERA_WIDTH;
//			param_sobel[tile_no].height = R_BCD_CAMERA_HEIGHT / R_DK2_TILE_NUM;
//
//			/* Set whether to perform top or bottom edge border processing. */
//			param_sobel[tile_no].top = (tile_no == TILE_0) ? 1 : 0;
//			param_sobel[tile_no].bottom = (tile_no == TILE_5) ? 1 : 0;
//
//			/* Initialize variables to be used in termination judgment of the DRP library */
//			drp_lib_status[tile_no] = DRP_NOT_FINISH;
//
//			/*********************/
//			/* Start DRP Library */
//			/*********************/
//			ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_sobel[tile_no], sizeof(r_drp_sobel_t));
//			DRP_DRV_ASSERT(ret_val);
////			ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_sobel[tile_no], sizeof(r_drp_prewitt_t));
////			DRP_DRV_ASSERT(ret_val);
//			//            printf("b2g start ret val = %d", ret_val);
//		}
//
//		/***************************************/
//		/* Wait until DRP processing is finish */
//		/***************************************/
//		for (tile_no = 0; tile_no < R_DK2_TILE_NUM; tile_no++)
//		{
//			while (drp_lib_status[tile_no] == DRP_NOT_FINISH)
//			{
//				/* DO NOTHING */
//			}
//		}
//
//		/* Set end time of process */
//		PerformSetEndTime(7);
//		printf("Sobel End \n");
//
//
//		/**********************/
//		/* Unload DRP Library */
//		/**********************/
//		ret_val = R_DK2_Unload(drp_lib_id[TILE_0] | drp_lib_id[TILE_1] | drp_lib_id[TILE_2] | drp_lib_id[TILE_3]
//																										 | drp_lib_id[TILE_4] | drp_lib_id[TILE_5], &drp_lib_id[0]);
//		DRP_DRV_ASSERT(ret_val);
//
//
//		/******************************************************************************************************/


//		/***********************************/
//		/* Load DRP Library                */
//		/*        +----------------------+ */
//		/* tile 0 |                      | */
//		/*        +   Canny Calculate    + */
//		/* tile 1 |                      | */
//		/*        +----------------------+ */
//		/* tile 2 | 					 | */
//		/*        +----------------------+ */
//		/* tile 3 | 					 | */
//		/*        +----------------------+ */
//		/* tile 4 |                      | */
//		/*        +----------------------+ */
//		/* tile 5 |                      | */
//		/*        +----------------------+ */
//		/***********************************/
//
//		/* Set start time of process*/
//		PerformSetStartTime(8);
//
//
//		/*##################################*/
//		/* load DRP Library Canny Calculate */
//		/*##################################*/
//
//		ret_val = R_DK2_Load(&g_drp_lib_canny_calculate[0],
//							 R_DK2_TILE_0,
//							 R_DK2_TILE_PATTERN_2_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
//		DRP_DRV_ASSERT(ret_val);
//
//		/*##################################*/
//		/* Activate DRP Lib Canny Calculate */
//		/*##################################*/
//		ret_val = R_DK2_Activate(drp_lib_id[TILE_0], 0);
//		DRP_DRV_ASSERT(ret_val);
//
//
//		/***************************************/
//		/* Set R_DK2_Start function parameters */
//		/***************************************/
////		tile_no = TILE_0;
//
//		/* Set Image size */
//		param_canny_cal.width  = R_BCD_CAMERA_WIDTH;
//		param_canny_cal.height = R_BCD_CAMERA_HEIGHT;
//
//		/* Set Buffer size */
////		bufsize = (uint32_t)(param_canny_cal.width * param_canny_cal.height);
//
//		/* Set the address of buffer to be read/write by DRP */
////		param_canny_cal.src = work_bufadr_med2thin;
////		param_canny_cal.dst = work_bufadr_med2contours;
////		R_MMU_VAtoPA((uint32_t)param_canny_cal[tile_no].src, &(param_canny_cal[tile_no].src ));
////		R_MMU_VAtoPA((uint32_t)param_canny_cal[tile_no].dst, &(param_canny_cal[tile_no].dst ));
//
//
//		param_canny_cal.src = (uint32_t)&frame_RAM_D;
//		param_canny_cal.dst = (uint32_t)&frame_RAM_E;
//
//		R_MMU_VAtoPA((uint32_t)param_canny_cal.src, &(param_canny_cal.src));
//		R_MMU_VAtoPA((uint32_t)param_canny_cal.dst, &(param_canny_cal.dst));
//
//		/* Set additional information (currently no additional information) */
//		param_canny_cal.work = (uint32_t)&p_frame_ram_canny_cal[0];
////		param_canny_cal.work = (uint32_t)&p_frame_ram1[0];
//		R_MMU_VAtoPA((uint32_t)param_canny_cal.work, &(param_canny_cal.work ));
//
//		param_canny_cal.threshold_high = STRONG_LEVEL;
//		param_canny_cal.threshold_low = WEAK_LEVEL;
//
//		/* Set whether to perform top or bottom edge border processing. */
//		param_canny_cal.top    = (tile_no == TILE_0) ? 1 : 0;
//		param_canny_cal.bottom = (tile_no == TILE_0) ? 1 : 0;
//
//		/* Initialize variables to be used in termination judgment of the DRP library */
//		drp_lib_status[tile_no] = DRP_NOT_FINISH;
//
//		/*********************/
//		/* Start DRP Library */
//		/*********************/
//		ret_val = R_DK2_Start(drp_lib_id[TILE_0], (void *)&param_canny_cal, sizeof(r_drp_canny_calculate_t));
//		DRP_DRV_ASSERT(ret_val);
//
//		/***************************************/
//		/* Wait until DRP processing is finish */
//		/***************************************/
//		while (drp_lib_status[TILE_0] == DRP_NOT_FINISH);
//
//		/**********************/
//		/* Unload DRP library */
//		/**********************/
//		ret_val = R_DK2_Unload(drp_lib_id[TILE_0], &drp_lib_id[TILE_0]);
//		DRP_DRV_ASSERT(ret_val);
//
//		/* Set end time of DRP processing */
//		PerformSetEndTime(8);
//
//		printf("Hi4 \n");
//
//
////		ret_val = R_DK2_Load(&g_drp_lib_canny_calculate[0],
////							 R_DK2_TILE_0,
////							 R_DK2_TILE_PATTERN_2_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
////		DRP_DRV_ASSERT(ret_val);
////
////		/*##################################*/
////		/* Activate DRP Lib Canny Calculate */
////		/*##################################*/
////		ret_val = R_DK2_Activate(drp_lib_id[TILE_0], 0);
////		DRP_DRV_ASSERT(ret_val);
////
////		PerformSetStartTime(3);
////
////		/***************************************/
////		/* Set R_DK2_Start function parameters */
////		/***************************************/
////		tile_no = TILE_0;
////
////		/* Set Image size */
////		param_canny_cal[tile_no].width  = R_BCD_CAMERA_WIDTH;
////		param_canny_cal[tile_no].height = R_BCD_CAMERA_HEIGHT;
////
////		/* Set Buffer size */
////		bufsize = (uint32_t)(param_canny_cal[tile_no].width * param_canny_cal[tile_no].height);
////
////		/* Set the address of buffer to be read/write by DRP */
////		param_canny_cal[tile_no].src = work_bufadr_med2thin;
////		param_canny_cal[tile_no].dst = work_bufadr_med2contours;
//////		R_MMU_VAtoPA((uint32_t)param_canny_cal[tile_no].src, &(param_canny_cal[tile_no].src ));
//////		R_MMU_VAtoPA((uint32_t)param_canny_cal[tile_no].dst, &(param_canny_cal[tile_no].dst ));
////
////		/* Set additional information (currently no additional information) */
//////		param_canny_cal[tile_no].work = (uint32_t)p_frame_ram1[0];
////		param_canny_cal[tile_no].work = (uint32_t)&p_frame_ram1[(tile_no * (bufsize + (R_BCD_CAMERA_WIDTH*2) ))*2];
////		R_MMU_VAtoPA((uint32_t)param_canny_cal[tile_no].work, &(param_canny_cal[tile_no].work ));
////
////		param_canny_cal[tile_no].threshold_high = STRONG_LEVEL;
////		param_canny_cal[tile_no].threshold_low = WEAK_LEVEL;
////
////		/* Set whether to perform top or bottom edge border processing. */
////		param_canny_cal[tile_no].top    = (tile_no == TILE_0) ? 1 : 0;
////		param_canny_cal[tile_no].bottom = (tile_no == TILE_0) ? 1 : 0;
////
////		/* Initialize variables to be used in termination judgment of the DRP library */
////		drp_lib_status[tile_no] = DRP_NOT_FINISH;
////
////		/*********************/
////		/* Start DRP Library */
////		/*********************/
////		ret_val = R_DK2_Start(drp_lib_id[tile_no], (void *)&param_canny_cal[tile_no / 2], sizeof(r_drp_canny_calculate_t));
////		DRP_DRV_ASSERT(ret_val);
////
////		/***************************************/
////		/* Wait until DRP processing is finish */
////		/***************************************/
////		while (drp_lib_status[TILE_0] == DRP_NOT_FINISH);
////
////		/**********************/
////		/* Unload DRP library */
////		/**********************/
////		ret_val = R_DK2_Unload(drp_lib_id[TILE_0], &drp_lib_id[TILE_0]);
////		DRP_DRV_ASSERT(ret_val);
////
////		/* Set end time of DRP processing */
////		PerformSetEndTime(3);
//
//
//
//
//		/*******************************/
//		/* Load DRP Library            */
//		/*        +------------------+ */
//		/* tile 0 |                  | */
//		/*        +                  + */
//		/* tile 1 |                  | */
//		/*        +                  + */
//		/* tile 2 |                  | */
//		/*        + Canny Hysterisis + */
//		/* tile 3 |                  | */
//		/*        +                  + */
//		/* tile 4 |                  | */
//		/*        +                  + */
//		/* tile 5 |                  | */
//		/*        +------------------+ */
//		/*******************************/
//
//		/* Set start time of Canny Hyst process */
//		PerformSetStartTime(4);
//
//		ret_val = R_DK2_Load(&g_drp_lib_canny_hysterisis[0],
//							 R_DK2_TILE_0,
//							 R_DK2_TILE_PATTERN_6, NULL, &cb_drp_finish, &drp_lib_id[0]);
//		DRP_DRV_ASSERT(ret_val);
//
//		printf("CH load \n");
//
//		/************************/
//		/* Activate DRP Library */
//		/************************/
//		ret_val = R_DK2_Activate(drp_lib_id[TILE_0], 0);
//		DRP_DRV_ASSERT(ret_val);
//
//		printf("CH activate \n");
//
//		/***************************************/
//		/* Set R_DK2_Start function parameters */
//		/***************************************/
//		/* Set Image size */
//		param_canny_hyst.width = R_BCD_CAMERA_WIDTH;
//		param_canny_hyst.height = R_BCD_CAMERA_HEIGHT;
//
//		/* Set the address of buffer to be read/write by DRP */
//		param_canny_hyst.src = work_bufadr_med2contours;
//		param_canny_hyst.dst = output_bufadr;
////		R_MMU_VAtoPA((uint32_t)param_canny_hyst.src, &(param_canny_hyst.src ));
////		R_MMU_VAtoPA((uint32_t)param_canny_hyst.dst, &(param_canny_hyst.dst ));
//
//		param_canny_hyst.src = (uint32_t)&frame_RAM_E;
//		param_canny_hyst.dst = (uint32_t)&p_output_bufadr;
//
//		R_MMU_VAtoPA((uint32_t)param_canny_hyst.src, &(param_canny_hyst.src));
//		R_MMU_VAtoPA((uint32_t)param_canny_hyst.dst, &(param_canny_hyst.dst));
//
//		/* Set additional information (currently no additional information) */
//		param_canny_hyst.work = (uint32_t)&p_frame_ram_canny_hyst[0];
////		param_canny_hyst.work = (uint32_t)&p_frame_ram2[0];
//		R_MMU_VAtoPA((uint32_t)param_canny_hyst.work, &(param_canny_hyst.work ));
//		param_canny_hyst.iterations = HYSTERISIS_COUNT;
//
//		/* Initialize variables to be used in termination judgment of the DRP library */
//		drp_lib_status[TILE_0] = DRP_NOT_FINISH;
//
//		/*********************/
//		/* Start DRP Library */
//		/*********************/
//		ret_val = R_DK2_Start(drp_lib_id[TILE_0], (void *)&param_canny_hyst, sizeof(r_drp_canny_hysterisis_t));
//		DRP_DRV_ASSERT(ret_val);
//
//		printf("CH start \n");
//
//		/***************************************/
//		/* Wait until DRP processing is finish */
//		/***************************************/
//		while (drp_lib_status[TILE_0] == DRP_NOT_FINISH)
//		{
//			printf("in loop \n");
//		}
//
//		/**********************/
//		/* Unload DRP Library */
//		/**********************/
//		ret_val = R_DK2_Unload(drp_lib_id[TILE_0], &drp_lib_id[TILE_0]);
//		DRP_DRV_ASSERT(ret_val);
//
//		printf("CH unload \n");
//
//		/* Set end time of DRP processing */
//		PerformSetEndTime(4);
//
//		printf("Hi5 \n");
//
//
//		/******************************************************************************************************/


		/******************************************************************************************************/
		/************************************/
        /* Load DRP Library                 */
        /*        +-----------------------+ */
        /* tile 0 |                       | */
        /*        +                       + */
        /* tile 1 |       		  	      | */
        /*        +                       + */
        /* tile 2 |                       | */
        /*        +-----------------------+ */
        /* tile 3 |                       | */
        /*        +     FindContours      + */
        /* tile 4 |                       | */
        /*        +-----------------------+ */
        /* tile 5 |                       | */
        /*        +-----------------------+ */
        /************************************/


        /*****************************************/
        /* Load DRP Library BinarizationAdaptive */
        /*****************************************/
        ret_val = R_DK2_Load(&g_drp_lib_find_contours[0],
        		R_DK2_TILE_3,
				R_DK2_TILE_PATTERN_3_2_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
//        ret_val = R_DK2_Load(&g_drp_lib_find_contours[0],
//        		R_DK2_TILE_0,
//				R_DK2_TILE_PATTERN_2_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
        DRP_DRV_ASSERT(ret_val);
        //		printf("bin-ad load ret val = %d", ret_val);
        printf("load find contours \n");

        /*****************************************/
        /* Activate DRP Lib BinarizationAdaptive */
        /*****************************************/
        ret_val = R_DK2_Activate(drp_lib_id[TILE_3], 0);
//        ret_val = R_DK2_Activate(drp_lib_id[TILE_3], 0);
        DRP_DRV_ASSERT(ret_val);
        //		printf("bin-ad activate ret val = %d", ret_val);
        printf("activate find contours \n");

        /* Set start time of process*/
        PerformSetStartTime(3);


        /****************************************************************/
        /* Set R_DK2_Start function parameters for FindContours */
        /****************************************************************/
        param_find_contours.src = p_output_bufadr;
//        param_find_contours.src = (uint32_t)&frame_RAM_B;

        /* Cast to an appropriate type */
        R_MMU_VAtoPA((uint32_t) param_find_contours.src, &(param_find_contours.src));


        /* Cast to an appropriate type */
        param_find_contours.dst_region = (uint32_t)&g_contours_region_adr[0];

        /* Cast to an appropriate type */
        R_MMU_VAtoPA((uint32_t) param_find_contours.dst_region, &(param_find_contours.dst_region));

        /* Set Image size */
        param_find_contours.width = (uint16_t)R_BCD_CAMERA_WIDTH;
        param_find_contours.height = (uint16_t)R_BCD_CAMERA_HEIGHT;

        /* Set whether to perform top or bottom edge border processing. */
        /* Cast to an appropriate type */
//        param_find_contours.work = (uint32_t)&p_frame_ram1[0];
//        param_find_contours.work = p_frame_ram1;

        /*Error when work 4 is used*/
        param_find_contours.work = (uint32_t)&work_find_contours[0];    /* Address of work area; minimum size = width * height / 4 + 8 */
//        param_find_contours.work = (uint32_t)work_find_contours;

        /* Cast to an appropriate type */
        R_MMU_VAtoPA((uint32_t) param_find_contours.work, &(param_find_contours.work));

        /* Cast to an appropriate type */
        param_find_contours.dst_rect = (uint32_t)&g_contours_rect_adr[0];

        /* Cast to an appropriate type */
        R_MMU_VAtoPA((uint32_t) param_find_contours.dst_rect, &(param_find_contours.dst_rect));

        //         param_find_contours.dst_region_size = FIND_CONTOURS_NUM;
//        Dont assign a lower value (eg 100 to dst_region)
//        param_find_contours.dst_region_size = 500000;
        param_find_contours.dst_region_size = 0;
        param_find_contours.dst_rect_size = FIND_CONTOURS_NUM;
//        param_find_contours.dst_rect_size = 20000;
        param_find_contours.threshold_width = 40;
        param_find_contours.threshold_height = 40;


        /* Initialize variables to be used in termination judgment of the DRP application */
        drp_lib_status[TILE_3] = DRP_NOT_FINISH;

        /******************************************/
        /* Start DRP Library BinarizationAdaptive */
        /******************************************/
        ret_val = R_DK2_Start(drp_lib_id[TILE_3], (void *)&param_find_contours, sizeof(r_drp_find_contours_t));
        DRP_DRV_ASSERT(ret_val);
        //		printf("bin-ad start ret val = %d", ret_val);
        printf("start find contours \n");


        /*******************************************************/
        /* Wait until BinarizationAdaptive processing finished */
        /*******************************************************/
//        while (drp_lib_status[TILE_3] == DRP_NOT_FINISH);

		while (drp_lib_status[TILE_3] == DRP_NOT_FINISH)
		{
			/* DO NOTHING */
//			printf("***still in loop*** \n");
		}

        printf("drp finished \n");

        /*******************************************/
        /* Unload DRP library BinarizationAdaptive */
        /*******************************************/
        ret_val = R_DK2_Unload(drp_lib_id[TILE_3], &drp_lib_id[TILE_3]);
        DRP_DRV_ASSERT(ret_val);
        //		printf("bin-ad unload ret val = %d", ret_val);
        printf("unload find contours \n");

        PerformSetEndTime(3);


        /******************************************************************************************************/


//        for (ih = 1; ih <= R_BCD_CAMERA_WIDTH; ih ++)
//        {
//            for (iw = 1; iw <= R_BCD_CAMERA_HEIGHT; iw ++)
//            {
//                p_output_bufadr[ih*iw] = frame_RAM_B[ih*iw];
//          }
//        }

//        /* convert to physical address */
//        R_MMU_VAtoPA((uint32_t)p_output_bufadr, &p_output_bufadr);



        printf("FindContour End \n");
        uint32_t num_contours = 0;
        int32_t x, y, length, height;
        uint8_t  color;
//        R_BCD_LcdClearGraphicsBuffer();
//        printf("size of g_contours_rect_adr = %i \n",sizeof(g_contours_rect_adr));
        printf("g_contours_rect_adr[0].x = %i ",g_contours_rect_adr[0].x);
//        R_BCD_LcdWriteLine( 100         ,  100          , 200         , 200, color);
//
//        /* Write the data(buf) on the cache to physical memory */
//        R_CACHE_L1DataCleanLine(R_BCD_LcdGetOLVramAddress(), (R_BCD_LCD_WIDTH * R_BCD_LCD_HEIGHT));
//
//        /* Write the data(buf) on the cache to physical memory */
//        R_CACHE_L1DataCleanLine(output_bufadr, ((R_BCD_LCD_WIDTH * R_BCD_LCD_HEIGHT) * 4));
//
////        R_BCD_CameraClearCaptureStatus();
//
////        R_BCD_LcdSwapGraphicsBuffer();
//        R_BCD_LcdSwapVideoBuffer();


        while ((bcd_drp_check_empty_contours(num_contours)) && (num_contours <= (uint32_t)FIND_CONTOURS_NUM))
        {
        	x     = g_contours_rect_adr[num_contours].x;
        	printf("\n%li x = %li ", num_contours, x);
        	y     = g_contours_rect_adr[num_contours].y;
        	printf("\n%li y = %li ", num_contours, y);
        	length = g_contours_rect_adr[num_contours].width;
        	printf("\n%li length = %li ", num_contours, length);
        	height = g_contours_rect_adr[num_contours].height;
        	printf("\n%li height = %li ", num_contours, height);

        	color = RED;
        	R_BCD_LcdWriteLine( x          ,  y          , (x + length),  y          , color);
        	R_BCD_LcdWriteLine((x + length),  y          , (x + length), (y + height), color);
        	R_BCD_LcdWriteLine( x          , (y + height), (x + length), (y + height), color);
        	R_BCD_LcdWriteLine( x          ,  y          ,  x          , (y + height), color);


        	num_contours++;
        }



    	/* Write the data(buf) on the cache to physical memory */
    	R_CACHE_L1DataCleanLine(R_BCD_LcdGetOLVramAddress(), (R_BCD_LCD_WIDTH * R_BCD_LCD_HEIGHT));

    	/* Write the data(buf) on the cache to physical memory */
    	R_CACHE_L1DataCleanLine(p_output_bufadr, ((R_BCD_LCD_WIDTH * R_BCD_LCD_HEIGHT) * 4));

    	//        R_BCD_CameraClearCaptureStatus();

//    	        R_BCD_LcdSwapGraphicsBuffer();
    	R_BCD_LcdSwapVideoBuffer();

    	printf("\nContour Drawing End \n");

    	printf("num_contours = %li\n", num_contours);


        /******************************************************************************************************/


//    	/******************************************************************************************************/
//    	if(num_contours > 0){
//
//            /************************************/
//            /* Load DRP Library                 */
//            /*        +-----------------------+ */
//            /* tile 0 |      Cropping         | */
//            /*        +-----------------------+ */
//            /* tile 1 |                       | */
//            /*        +-----------------------+ */
//            /* tile 2 |                       | */
//            /*        +-----------------------+ */
//            /* tile 3 |                       | */
//            /*        +-----------------------+ */
//            /* tile 4 |                       | */
//            /*        +-----------------------+ */
//            /* tile 5 |                       | */
//            /*        +-----------------------+ */
//            /************************************/
//
//            /*****************************************/
//            /* Load DRP Library Cropping */
//            /*****************************************/
//            ret_val = R_DK2_Load(&g_drp_lib_find_contours[0],
//                    R_DK2_TILE_0,
//                    R_DK2_TILE_PATTERN_1_1_1_1_1_1, NULL, &cb_drp_finish, &drp_lib_id[0]);
//            DRP_DRV_ASSERT(ret_val);
//            printf("load cropping \n");
//
//            /*****************************************/
//            /* Activate DRP Library Cropping */
//            /*****************************************/
//            ret_val = R_DK2_Activate(drp_lib_id[TILE_0], 0);
//            DRP_DRV_ASSERT(ret_val);
//            printf("activate cropping \n");
//
//            /* Set start time of process*/
//            PerformSetStartTime(12);
//
//
//    	    for(symbol=0 ; symbol < num_contours ; symbol++)
//    	    {
//    	        param_cropping.src = p_output_bufadr;
////    	        param_cropping.src = (uint32_t)&frame_RAM_B;
//    	        R_MMU_VAtoPA((uint32_t) param_cropping.src, &(param_cropping.src));
//
//    	        param_cropping.dst = (uint32_t)&frame_RAM_CC[symbol][0];
////    	        param_cropping.dst = (uint32_t)&frame_RAM_D;
////    	        param_cropping.src = p_output_bufadr;
//    	        R_MMU_VAtoPA((uint32_t) param_cropping.dst, &(param_cropping.dst));
//
//    	        param_cropping.src_width = (uint16_t)R_BCD_CAMERA_WIDTH;
//    	        param_cropping.src_height = (uint16_t)R_BCD_CAMERA_HEIGHT;
//
//    	        param_cropping.offset_x = (uint16_t)g_contours_rect_adr[symbol].x;
//    	        param_cropping.offset_y = (uint16_t)g_contours_rect_adr[symbol].y;
//                param_cropping.dst_width = (uint16_t)g_contours_rect_adr[symbol].width;
//                param_cropping.dst_height = (uint16_t)g_contours_rect_adr[symbol].height;
//
//                /* Initialize variables to be used in termination judgment of the DRP application */
//                drp_lib_status[TILE_0] = DRP_NOT_FINISH;
//
//                /******************************************/
//                /* Start DRP Library BinarizationAdaptive */
//                /******************************************/
//                ret_val = R_DK2_Start(drp_lib_id[TILE_0], (void *)&param_cropping, sizeof(r_drp_cropping_t));
//                DRP_DRV_ASSERT(ret_val);
//                //      printf("bin-ad start ret val = %d", ret_val);
//                printf("\nsymbol = %li ", symbol);
//                printf("\nstart cropping \n");
//
//    	    }
//
//            /*******************************************************/
//            /* Wait until Cropping processing finished */
//            /*******************************************************/
//
//            while (drp_lib_status[TILE_0] == DRP_NOT_FINISH)
//            {
//                /* DO NOTHING */
////                  printf("***still in loop*** \n");
//            }
//
//            printf("cropping drp finished \n");
//
//            /*******************************************/
//            /* Unload DRP library Cropping */
//            /*******************************************/
//            ret_val = R_DK2_Unload(drp_lib_id[TILE_0], &drp_lib_id[TILE_0]);
//            DRP_DRV_ASSERT(ret_val);
//
//            printf("unload cropping \n");
//
//            PerformSetEndTime(12);
//
//    	}
//    	/******************************************************************************************************/



//    	/******************************************************************************************************/
//    	if(num_contours > 0){
//
//    	    num_valid_char = 0;
//
//    	    for(symbol=0 ; symbol < num_contours ; symbol++)
//    	    {
//
//                /************************************/
//                /* Load DRP Library                 */
//                /*        +-----------------------+ */
//                /* tile 0 |                       | */
//                /*        +                       + */
//                /* tile 1 |                       | */
//                /*        +                       + */
//                /* tile 2 |                       | */
//                /*        +  ResizeBilinearCrop   + */
//                /* tile 3 |                       | */
//                /*        +                       + */
//                /* tile 4 |                       | */
//                /*        +                       + */
//                /* tile 5 |                       | */
//                /*        +-----------------------+ */
//                /************************************/
//
//                /*****************************************/
//                /* Load DRP Library Cropping */
//                /*****************************************/
//                ret_val = R_DK2_Load(&g_drp_lib_resize_bilinear_crop_t6[0],
//                                     R_DK2_TILE_0,
//                                     R_DK2_TILE_PATTERN_6, NULL, &cb_drp_finish, &drp_lib_id[0]);
//                DRP_DRV_ASSERT(ret_val);
//                printf("load ResizeBilinearCrop \n");
//
//                /*****************************************/
//                /* Activate DRP Library Cropping */
//                /*****************************************/
//                ret_val = R_DK2_Activate(drp_lib_id[TILE_0], 0);
//                DRP_DRV_ASSERT(ret_val);
//                printf("activate ResizeBilinearCrop \n");
//
//                /* Set start time of process*/
////                PerformSetStartTime(12);
//
//
//
//
//    	        printf("symbol start %i \n", symbol);
//    	        printf("g_contours_rect_adr[%i].height = %i \n", symbol, g_contours_rect_adr[symbol].height);
//    	        printf("g_contours_rect_adr[%i].width = %i \n", symbol, g_contours_rect_adr[symbol].width);
//
//    	        flag = 0;
//
//    	        if ((g_contours_rect_adr[symbol].width < 120) && (g_contours_rect_adr[symbol].height < 120) &&
//    	            (g_contours_rect_adr[symbol].width != 0)  && (g_contours_rect_adr[symbol].height != 0))
//    	        {
//    	            printf("num_valid_char = %li\n", num_valid_char);
//    	            printf("index of valid symbol = %li\n", symbol);
//
//    	            printf("Before source \n");
//    	            param_resize_bilinear_crop.src = p_output_bufadr;
////    	            param_resize_bilinear_crop.src = (uint32_t)&frame_RAM_B;
//    	            R_MMU_VAtoPA((uint32_t) param_resize_bilinear_crop.src, &(param_resize_bilinear_crop.src));
//
//    	            printf("Before dst \n");
//    	            param_resize_bilinear_crop.dst = (uint32_t)&frame_RAM_CCR[num_valid_char][0];
//    	            //              param_cropping.dst = (uint32_t)&frame_RAM_D;
//    	            //              param_cropping.src = p_output_bufadr;
//    	            R_MMU_VAtoPA((uint32_t) param_resize_bilinear_crop.dst, &(param_resize_bilinear_crop.dst));
//
//    	            printf("Before params \n");
//
//    	            param_resize_bilinear_crop.src_width = (uint16_t)R_BCD_CAMERA_WIDTH;
//    	            param_resize_bilinear_crop.src_height = (uint16_t)R_BCD_CAMERA_HEIGHT;
//
//    	            param_resize_bilinear_crop.src_window_x = (uint16_t)g_contours_rect_adr[symbol].x;
//    	            param_resize_bilinear_crop.src_window_y = (uint16_t)g_contours_rect_adr[symbol].y;
//    	            param_resize_bilinear_crop.src_window_width = (uint16_t)g_contours_rect_adr[symbol].width;
//    	            param_resize_bilinear_crop.src_window_height = (uint16_t)g_contours_rect_adr[symbol].height;
//
//    	            param_resize_bilinear_crop.dst_width = 32;
//    	            param_resize_bilinear_crop.dst_height = 32;
//
//    	            /* Initialize variables to be used in termination judgment of the DRP application */
//    	            drp_lib_status[TILE_0] = DRP_NOT_FINISH;
//
//    	            printf("Before start \n");
//
//                    /******************************************/
//                    /* Start DRP Library Resize Bilinear Crop */
//                    /******************************************/
//                    ret_val = R_DK2_Start(drp_lib_id[TILE_0], (void *)&param_resize_bilinear_crop, sizeof(r_drp_resize_bilinear_crop_t));
//                    DRP_DRV_ASSERT(ret_val);
//                    //      printf("bin-ad start ret val = %d", ret_val);
//                    printf("after start ResizeBilinearCrop \n");
//
//                    num_valid_char++;
//
//    	            flag = 1;
//
//
//    	        }
//
//    	        printf("symbol end %i \n", symbol);
//
//
//
//
//    	        /*******************************************************/
//    	        /* Wait until Cropping processing finished */
//    	        /*******************************************************/
//
//    	        while (drp_lib_status[TILE_0] == DRP_NOT_FINISH && flag == 1)
//    	        {
//    	            /* DO NOTHING */
//    	            printf("***still in loop*** \n");
//    	        }
//
//    	        /*******************************************/
//    	        /* Unload DRP library Cropping */
//    	        /*******************************************/
//    	        ret_val = R_DK2_Unload(drp_lib_id[TILE_0], &drp_lib_id[TILE_0]);
//    	        DRP_DRV_ASSERT(ret_val);
//
//    	        printf("ResizeBilinearCrop unload \n");
//
//    	        //                  PerformSetEndTime(12);
//    	    }
//
//
//
//    	}
//    	/******************************************************************************************************/


    	printf("**********************************************************\n");


//    	for(int p = 0; p < 35*35; p++)
//    	{
//    	    printf("frame_RAM_CCR[0][%li] = %li\n", p, frame_RAM_CCR[0][p]);
//    	}


//        for (valid_char = 0; valid_char < num_valid_char; valid_char++) {
//            for (ih = 0; ih < R_BCD_CAMERA_WIDTH; ih ++)
//            {
//                for (iw = 0; iw < R_BCD_CAMERA_HEIGHT; iw ++)
//                {
//                	        p_output_bufadr[ih*iw] = frame_RAM_CC[0][ih*iw];
////                    p_output_bufadr[(valid_char+1)*ih*iw] = frame_RAM_CCR[valid_char][ih*iw];
//                }
//            }
//        }

//        for (ih = 0; ih < R_BCD_CAMERA_WIDTH; ih ++)
//        {
//            for (iw = 0; iw < R_BCD_CAMERA_HEIGHT; iw ++)
//            {
////                    p_output_bufadr[ih*iw] = frame_RAM_CC[2][ih*iw];
//                p_output_bufadr[ih*iw] = frame_RAM_B[ih*iw];
////                    p_output_bufadr[(valid_char+1)*ih*iw] = frame_RAM_CCR[valid_char][ih*iw];
//            }
//        }


//    	/******************************************************************************************************/
//    	if(num_contours > 0){
//
//    	    /************************************/
//    	    /* Load DRP Library                 */
//    	    /*        +-----------------------+ */
//    	    /* tile 0 |                       | */
//    	    /*        +                       + */
//    	    /* tile 1 |                       | */
//    	    /*        +                       + */
//    	    /* tile 2 |                       | */
//    	    /*        +    Resize Bilinear    + */
//    	    /* tile 3 |                       | */
//    	    /*        +                       + */
//    	    /* tile 4 |                       | */
//    	    /*        +                       + */
//    	    /* tile 5 |                       | */
//    	    /*        +-----------------------+ */
//    	    /************************************/
//
//    	    /*****************************************/
//    	    /* Load DRP Library Resize Bilinear */
//    	    /*****************************************/
//    	    ret_val = R_DK2_Load(&g_drp_lib_resize_bilinear[0],
//    	                         R_DK2_TILE_0,
//    	                         R_DK2_TILE_PATTERN_6, NULL, &cb_drp_finish, &drp_lib_id[0]);
//    	    DRP_DRV_ASSERT(ret_val);
//    	    printf("load Resize Bilinear \n");
//
//    	    /*****************************************/
//    	    /* Activate DRP Library Resize Bilinear */
//    	    /*****************************************/
//    	    ret_val = R_DK2_Activate(drp_lib_id[TILE_0], 0);
//    	    DRP_DRV_ASSERT(ret_val);
//    	    printf("activate Resize Bilinear \n");
//
//    	    /* Set start time of process*/
//    	    PerformSetStartTime(15);
//
//
//    	    for(symbol=0 ; symbol < num_contours ; symbol++)
//    	    {
//    	        //              param_cropping.src = p_output_bufadr;
//    	        param_resize_bilinear.src = (uint32_t)&frame_RAM_CC[symbol][0];
//    	        R_MMU_VAtoPA((uint32_t) param_resize_bilinear.src, &(param_resize_bilinear.src));
//
//    	        param_resize_bilinear.dst = (uint32_t)&frame_RAM_CCR[symbol][0];
//    	        //              param_cropping.dst = (uint32_t)&frame_RAM_D;
//    	        R_MMU_VAtoPA((uint32_t) param_resize_bilinear.dst, &(param_resize_bilinear.dst));
//
//    	        param_resize_bilinear.src_width = (uint16_t)g_contours_rect_adr[symbol].width;
//    	        param_resize_bilinear.src_height = (uint16_t)g_contours_rect_adr[symbol].height;
//
//    	        param_resize_bilinear.dst_width = 32;
//    	        param_resize_bilinear.dst_height = 32;
//
//    	        /* Initialize variables to be used in termination judgment of the DRP application */
//    	        drp_lib_status[TILE_0] = DRP_NOT_FINISH;
//
//    	        /******************************************/
//    	        /* Start DRP Library BinarizationAdaptive */
//    	        /******************************************/
//    	        ret_val = R_DK2_Start(drp_lib_id[TILE_0], (void *)&param_resize_bilinear, sizeof(r_drp_resize_bilinear_t));
//    	        DRP_DRV_ASSERT(ret_val);
//    	        //      printf("bin-ad start ret val = %d", ret_val);
//    	        printf("start Resize Bilinear \n");
//
//
//    	    }
//
//    	    /*******************************************************/
//    	    /* Wait until Resize Bilinear processing finished */
//    	    /*******************************************************/
//
//    	    while (drp_lib_status[TILE_0] == DRP_NOT_FINISH)
//    	    {
//    	        /* DO NOTHING */
//    	        //                  printf("***still in loop*** \n");
//    	    }
//
//    	    printf("cropping Resize Bilinear \n");
//
//    	    /*******************************************/
//    	    /* Unload DRP library Resize Bilinear */
//    	    /*******************************************/
//    	    ret_val = R_DK2_Unload(drp_lib_id[TILE_0], &drp_lib_id[TILE_0]);
//    	    DRP_DRV_ASSERT(ret_val);
//
//    	    printf("unload Resize Bilinear \n");
//
//    	    PerformSetEndTime(15);
//
//    	}
//    	/******************************************************************************************************/
//
//
//    	for(symbol=0 ; symbol < num_contours ; symbol++)
//    	{
//            for (ih = 0; ih < 32; ih ++)
//            {
//                for (iw = 0; iw < 32; iw ++)
//                {
//                    p_output_bufadr[(symbol+1)*ih*iw] = frame_RAM_CCR[symbol][ih*iw];
////                    memcpy(p_output_bufadr[], frame_RAM_CCR[symbol][0], sizeof(frame_RAM_CCR));
////                    p_output_bufadr[(((uint16_t)ih + (uint16_t)(ccn + 3) * (uint16_t)NN_IN_HEIGHT) * (uint16_t)R_BCD_CAMERA_WIDTH  + (uint16_t)618 + (uint16_t)iw) * (uint16_t)4 + (uint16_t)2] = frame_RAM_CCR[ccn][(uint16_t)ih * (uint16_t)NN_IN_WIDTH + (uint16_t)iw];
////                    p_output_bufadr[(((uint16_t)ih + (uint16_t)(ccn + 3) * (uint16_t)NN_IN_HEIGHT) * (uint16_t)R_BCD_CAMERA_WIDTH  + (uint16_t)618 + (uint16_t)iw) * (uint16_t)4 + (uint16_t)3] = frame_RAM_CCR[ccn][(uint16_t)ih * (uint16_t)NN_IN_WIDTH + (uint16_t)iw];
//                }
//            }
//    	}



        us = PerformGetElapsedTime_us(0);
        sprintf((void *)&buf[0],"Bayer2Grayscale : %d.%d[ms]", (int)(us / 1000), (int)((us - ((us / 1000) * 1000))
                / 100));
        R_BCD_LcdWriteString(&buf[0], 2, 2, GREEN);
//      R_BCD_LcdWriteString(&buf[0], 642, 482, GREEN);

        us = PerformGetElapsedTime_us(1);
        sprintf((void *)&buf[0],"binarization : %d.%d[ms]", (int)(us / 1000), (int)((us - ((us / 1000) * 1000))
                / 100));
        R_BCD_LcdWriteString(&buf[0], 2, 32, GREEN);

        us = PerformGetElapsedTime_us(2);
        sprintf((void *)&buf[0],"Median blur : %d.%d[ms]", (int)(us / 1000), (int)((us - ((us / 1000) * 1000))
                / 100));
        R_BCD_LcdWriteString(&buf[0], 2, 62, GREEN);

        us = PerformGetElapsedTime_us(9);
        sprintf((void *)&buf[0],"Thinning : %d.%d[ms]", (int)(us / 1000), (int)((us - ((us / 1000) * 1000))
                / 100));
        R_BCD_LcdWriteString(&buf[0], 2, 92, GREEN);

        us = PerformGetElapsedTime_us(20);
        sprintf((void *)&buf[0],"Closing : %d.%d[ms]", (int)(us / 1000), (int)((us - ((us / 1000) * 1000))
                / 100));
        R_BCD_LcdWriteString(&buf[0], 2, 122, GREEN);

        us = PerformGetElapsedTime_us(3);
        sprintf((void *)&buf[0],"Find Contours : %d.%d[ms]", (int)(us / 1000), (int)((us - ((us / 1000) * 1000))
                / 100));
        R_BCD_LcdWriteString(&buf[0], 2, 152, GREEN);


		/* Write the data(buf) on the cache to physical memory */
		R_CACHE_L1DataCleanLine(R_BCD_LcdGetOLVramAddress(), (R_BCD_LCD_WIDTH * R_BCD_LCD_HEIGHT));

		/* Write the data(buf) on the cache to physical memory */
		R_CACHE_L1DataCleanLine(output_bufadr, ((R_BCD_LCD_WIDTH * R_BCD_LCD_HEIGHT) * 4));

		/* Clear the current capture state and enable the detection of the next capture completion */
		R_BCD_CameraClearCaptureStatus();

//		R_BCD_LcdSwapGraphicsBuffer();
		R_BCD_LcdSwapVideoBuffer();

		R_BCD_LcdClearGraphicsBuffer();

    }

    sample_finish:

	return;
}

////        /* Display image processing result */
////        R_BCD_LcdSwapVideoBuffer();
//
//
////        /* Display image processing result */
////        R_BCD_LcdSwapVideoBuffer();
//
////        /* Write the data(buf) on the cache to physical memory */
////        R_CACHE_L1DataCleanLine(R_BCD_LcdGetOLVramAddress(), (R_BCD_LCD_WIDTH * R_BCD_LCD_HEIGHT));
//
//        /* Write the data(buf) on the cache to physical memory */
////        R_CACHE_L1DataCleanLine(output_bufadr, ((R_BCD_LCD_WIDTH * R_BCD_LCD_HEIGHT) * 4));
//
//        /* Display overlay buffer written processing time */
////        R_BCD_LcdSwapGraphicsBuffer();
//
////        R_BCD_LcdClearGraphicsBuffer();
////
////        /* Clear the current capture state and enable the detection of the next capture completion */
////        R_BCD_CameraClearCaptureStatus();
////
////        /* Capture Start */
////        R_BCD_CameraCaptureStart();
////
////        /* Display image processing result */
//        R_BCD_LcdSwapVideoBuffer();
//
//		/* Display time taken for image processing */
////        R_BCD_LcdClearGraphicsBuffer();
//		us = PerformGetElapsedTime_us(0);
//		sprintf((void *)&buf[0],"Bayer2Grayscale : %d.%d[ms]", (int)(us / 1000), (int)((us - ((us / 1000) * 1000))
//				/ 100));
//		R_BCD_LcdWriteString(&buf[0], 2, 2, GREEN);
//		us = PerformGetElapsedTime_us(1);
//		sprintf((void *)&buf[0],"binarization : %d.%d[ms]", (int)(us / 1000), (int)((us - ((us / 1000) * 1000))
//				/ 100));
//		R_BCD_LcdWriteString(&buf[0], 2, 32, GREEN);
//		us = PerformGetElapsedTime_us(2);
//		sprintf((void *)&buf[0],"Median blur : %d.%d[ms]", (int)(us / 1000), (int)((us - ((us / 1000) * 1000))
//				/ 100));
//		R_BCD_LcdWriteString(&buf[0], 2, 62, GREEN);
//		us = PerformGetElapsedTime_us(3);
//		sprintf((void *)&buf[0],"Find Contours : %d.%d[ms]", (int)(us / 1000), (int)((us - ((us / 1000) * 1000))
//				/ 100));
//		R_BCD_LcdWriteString(&buf[0], 2, 92, GREEN);
//		/* Write the data(buf) on the cache to physical memory */
//		R_CACHE_L1DataCleanLine(R_BCD_LcdGetOLVramAddress(), (R_BCD_LCD_WIDTH * R_BCD_LCD_HEIGHT));
//
//		/* Write the data(buf) on the cache to physical memory */
//		R_CACHE_L1DataCleanLine(R_BCD_LcdGetOLVramAddress(), ((R_BCD_LCD_WIDTH * R_BCD_LCD_HEIGHT) / 2));
//
//		/* Display overlay buffer written processing time */
//		R_BCD_LcdSwapGraphicsBuffer();
//
//    }
//
//sample_finish:
//
//    return;
//}
/**********************************************************************************************************************
* End of function sample_main
**********************************************************************************************************************/


/******************************************************************************
 * Function Name: bcd_drp_check_empty_contours
 * Description  :
 * Arguments    : -
 * Return Value : -
 ******************************************************************************/
static uint32_t bcd_drp_check_empty_contours(uint32_t i)
{

    if(g_contours_rect_adr[i].x)
    {
        return 1;
    }
    else if(g_contours_rect_adr[i].y)
    {
        return 1;
    }
    else if(g_contours_rect_adr[i].width)
    {
        return 1;
    }
    else if(g_contours_rect_adr[i].height)
    {
        return 1;
    }
    else if(g_contours_rect_adr[i].num)
    {
        return 1;
    }
    else if(g_contours_rect_adr[i].addr)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
/**********************************************************************************************************************
// End of function bcd_drp_check_empty_contours



/* End of File */
