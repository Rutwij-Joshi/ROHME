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
* Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* System Name : [RZ/A2M] DRP Dynamic Loading Sample Program 2
* File Name   : readme-e.txt
*******************************************************************************/
/*******************************************************************************
*
* History     : Sep. 30,2020 Rev.1.00.00    First edition issued
*******************************************************************************/

1. Before Use

  This sample code has been tested using the GR-MANGO Rev.B board
  with the RZ/A2M group R7S921058. 
  Use this readme file, the application note, and the sample code as a reference 
  for your software development.


  ****************************** CAUTION ******************************
   This sample code are all reference, and no one to guarantee the 
   operation. Please use this sample code for the technical 
   reference when customers develop software.
  ****************************** CAUTION ******************************


2. System Verification

  This sample code was developed and tested with the following components:

    CPU                                 : RZ/A2M
    Board                               : GR-MANGO Rev.B board
                                          HDMI board output (Control IC: Low Power HDMI Transmitter EP952)
    Compiler                            : GNU ARM Embedded 6.3.1.20170620
    Integrated development environment  : e2 studio Version 7.8.0.
    Camera                              : Raspberry Pi Camera V2
    Monitor                             : Monitor compatible with Full-WXGA(1366*768) resolution

3. About Sample Code

  These sample code operate as described below:

    DRP Basic Operation Sample Program
      Converts the input image from MIPI camera to grayscale image
      using DRP Library and outputs to display.

    DRP Parallel Operation Sample Program
      Converts the input image from MIPI camera to grayscale image at high speed
      using parallel operation function of DRP Library and outputs to display.

    DRP Dynamic Loading Sample Program 1
      Detects the edges of the input image from MIPI camera
      by Canny method using DRP Library and outputs to display.

    DRP Dynamic Loading Sample Program 2
      Detects the corners of the input image from MIPI camera
      by the Harris corner detector using DRP Library and outputs to display.

    DRP Dynamic Loading Sample Program 3
      After detecting the edges of the input image from MIPI camera
      by Canny method using DRP Library, performs contour detection using findcontours application.
      The results output to display.

    DRP Simple ISP Sample Program 1
      Correct the color and noise of the input image from MIPI camera using DRP Library,
      and the image with high color reproducibility is output to the Display.

    The application program is executed by the loader program after performing the register setting processing of 
    the SPI multi I/O bus controller (SPIBSC) and the serial flash memory by the loader program.
    The loader program is stored in the following folder.
      ["Project name"\bootloader\rza2_qspi_flash_ddr_bootloader.elf]

    This loader program conforms to the specification of Macronix MX25L51245G. When using another serial flash memory, 
    change the source code of the loader program project [rza2m_sflash_boot_loader_gcc] that is included in 
    "RZ/A2M Group Example of Booting from Serial Flash Memory" application note according to the specifications of 
    the flash memory, and then generate the new load module. The project debug configuration uses the loader program
    after changing the file name of the generated load module to "rza2_qspi_flash_ddr_bootloader.elf".


4. Operation Confirmation Conditions

  (1) Boot mode
    - Boot mode 6
      Boot from OctaFlash(SPI mode) connected to OctaFlash space.
      * The program can not be operated if the boot mode except the above is specified.

  (2) Operating frequency
      The RZ/A2M clock pulse oscillator module is set to ensure that the RZ/A2M clocks on the CPU board
      board have the following frequencies:
      (The frequencies indicate the values in the state that the clock with 24MHz
      is input to the EXTAL pin in RZ/A2M clock mode 1.)
      - CPU clock (I clock)                 : 528MHz
      - Image processing clock (G clock)    : 264MHz
      - Internal bus clock (B clock)        : 132MHz
      - Peripheral clock1 (P1 clock)        :  66MHz
      - Peripheral clock0 (P0 clock)        :  33MHz
      - OM_CK/OM_CK#                        : 132MHz
      - CKIO                                : 132MHz

  (3) OctaFlash (connected to OctaFlash space) used
    - Manufacturer  : Macronix Inc.
    - Product No.   : MX25UW12845GXDIO0

  (4) Setting for cache
      Initial setting for the L1 and L2 caches is executed by the MMU. 
      Refer to the "RZ/A2M group Example of Initialization" application note about "Setting for MMU" for 
      the valid/invalid area of L1 and L2 caches.


5. Operational Procedure

  Use the following procedure to execute these sample code.

  (1) Setting up sample code
    Copy the sample code directory to the e2 studio workspace directory
    in the host PC (eg: "C:\e2studio_Workspace").

    Sample code directories:
      DRP Basic Operation Sample Program
        rza2m_drp_basic_sample_freertos_gcc
      DRP Parallel Operation Sample Program
        rza2m_drp_parallel_sample_freertos_gcc
      DRP Dynamic Loading Sample Program 1
        rza2m_drp_dynamic_sample1_freertos_gcc
      DRP Dynamic Loading Sample Program 2
        rza2m_drp_dynamic_sample2_freertos_gcc
      DRP Dynamic Loading Sample Program 3
        rza2m_drp_dynamic_sample3_freertos_gcc
      DRP Simple ISP Sample Program 1
        rza2m_drp_simple_isp_sample1_freertos_gcc

  (2) Activating integrated development environment
    Activate the integrated development environment e2 studio.

  (3) Building application program
    After importing project of sample code by the e2 studio menu, build the project 
    and generate the executable file.

    Project names of sample code:
      DRP Basic Operation Sample Program
        rza2m_drp_basic_sample_freertos_gcc
      DRP Parallel Operation Sample Program
        rza2m_drp_parallel_sample_freertos_gcc
      DRP Dynamic Loading Sample Program 1
        rza2m_drp_dynamic_sample1_freertos_gcc
      DRP Dynamic Loading Sample Program 2
        rza2m_drp_dynamic_sample2_freertos_gcc
      DRP Dynamic Loading Sample Program 3
        rza2m_drp_dynamic_sample3_freertos_gcc
      DRP Simple ISP Sample Program 1
        rza2m_drp_simple_isp_sample1_freertos_gcc

  (4) Downloading sample code
    Connect GR-MANGO CN1 and PC via USB cable.
    PC detects the GR-MANGO as MBED drive.
    Drag-and-drop the binary file to the MBED drive.

  (5) Executing sample code
    Connect the camera to GR-MANGO CN13, and connect display to CN9 via HDMI cable.
    Ensure that complete to download program, and push reset button on GR-PEACH.

/* End of File */
