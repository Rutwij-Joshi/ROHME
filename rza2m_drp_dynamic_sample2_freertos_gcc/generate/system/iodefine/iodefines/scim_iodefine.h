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
* Rev: 3.01
* Description : IO define header
*******************************************************************************/

#ifndef SCIM_IODEFINE_H
#define SCIM_IODEFINE_H

struct st_scim
{
    union
    {
        unsigned char BYTE;
        struct
        {
            unsigned char CKS:2;
            unsigned char MP:1;
            unsigned char STOP:1;
            unsigned char PM:1;
            unsigned char PE:1;
            unsigned char CHR:1;
            unsigned char CM:1;
        } BIT;
    } SMR;
    union
    {
        unsigned char BYTE;
        struct
        {
            unsigned char BRR:8;
        } BIT;
    } BRR;
    union
    {
        unsigned char BYTE;
        struct
        {
            unsigned char CKE:2;
            unsigned char TEIE:1;
            unsigned char MPIE:1;
            unsigned char RE:1;
            unsigned char TE:1;
            unsigned char RIE:1;
            unsigned char TIE:1;
        } BIT;
    } SCR;
    union
    {
        unsigned char BYTE;
        struct
        {
            unsigned char TDR:8;
        } BIT;
    } TDR;
    union
    {
        unsigned char BYTE;
        struct
        {
            unsigned char MPBT:1;
            unsigned char MPB:1;
            unsigned char TEND:1;
            unsigned char PER:1;
            unsigned char FER:1;
            unsigned char ORER:1;
            unsigned char RDRF:1;
            unsigned char TDRE:1;
        } BIT;
    } SSR;
    union
    {
        unsigned char BYTE;
        struct
        {
            unsigned char RDR:8;
        } BIT;
    } RDR;
    union
    {
        unsigned char BYTE;
        struct
        {
            unsigned char SMIF:1;
            unsigned char :1;
            unsigned char SINV:1;
            unsigned char SDIR:1;
            unsigned char CHR1:1;
            unsigned char :2;
            unsigned char BCP2:1;
        } BIT;
    } SCMR;
    union
    {
        unsigned char BYTE;
        struct
        {
            unsigned char ACS0:1;
            unsigned char :1;
            unsigned char BRME:1;
            unsigned char :1;
            unsigned char ABCS:1;
            unsigned char NFEN:1;
            unsigned char BGDM:1;
            unsigned char RXDESEL:1;
        } BIT;
    } SEMR;
    union
    {
        unsigned char BYTE;
        struct
        {
            unsigned char NFCS:3;
            unsigned char :5;
        } BIT;
    } SNFR;
    char           wk0[4];
    union
    {
        unsigned char BYTE;
        struct
        {
            unsigned char :1;
            unsigned char CTSE:1;
            unsigned char :1;
            unsigned char :1;
            unsigned char :1;
            unsigned char :1;
            unsigned char :1;
            unsigned char :1;
        } BIT;
    } SECR;
    union
    {
        struct
        {
            union
            {
                unsigned short WORD;
                struct
                {
                    unsigned short TDRHL:16;
                } BIT;
            } TDRHL;
        }W;
        struct
        {
            union
            {
                unsigned char BYTE;
                struct
                {
                    unsigned char TDRH:8;
                } BIT;
            } TDRH;
            union
            {
                unsigned char BYTE;
                struct
                {
                    unsigned char TDRL:8;
                } BIT;
            } TDRL;
        }B;
    } TDRHL;
    union
    {
        struct
        {
            union
            {
                unsigned short WORD;
                struct
                {
                    unsigned short RDRHL:16;
                } BIT;
            } RDRHL;
        }W;
        struct
        {
            union
            {
                unsigned char BYTE;
                struct
                {
                    unsigned char RDRH:8;
                } BIT;
            } RDRH;
            union
            {
                unsigned char BYTE;
                struct
                {
                    unsigned char RDRL:8;
                } BIT;
            } RDRL;
        }B;
    } RDRHL;
    union
    {
        unsigned char BYTE;
        struct
        {
            unsigned char MDDR:8;
        } BIT;
    } MDDR;
};

#define SCIM0     (*(volatile struct st_scim      *)0xE800B000)
#define SCIM1     (*(volatile struct st_scim      *)0xE800B800)

#endif
