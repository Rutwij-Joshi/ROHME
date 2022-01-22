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
* System Name : [RZ/A2M] DRPダイナミックローディングサンプルプログラム2
* File Name   : readme-j.txt
*******************************************************************************/
/*******************************************************************************
*
* History     : Sep. 30,2020 Rev.1.00.00    新規作成
*******************************************************************************/

1. はじめに

  本サンプルコードは、RZ/A2Mグループ R7S921058を搭載したGR-MANGO Rev.B ボードを
  使用して動作確認しています。
  お客様のソフトウエア開発時に技術参考資料としてご利用ください。

  ****************************** ご 注 意 ******************************
   本サンプルコードはすべて参考資料であり、その動作を保証するもの
   ではありません。実際のシステムに組み込む場合はシステム全体で
   十分に評価し、お客様の責任において適用可否を判断してください。
  ****************************** ご 注 意 ******************************


2. 動作確認環境

  サンプルコードは以下の環境で動作を確認しています。

    CPU          : RZ/A2M
    ボード       : GR-MANGO Rev.B ボード
    コンパイラ   : GNU ARM Embedded 6.3.1.20170620
    統合開発環境 : e2 studio Version 7.8.0.
    カメラ       : Raspberry Pi Camera V2
    モニタ       : Full-WXGA(1366*768)を表示可能なモニタ


3. サンプルコードの内容

  本サンプルコードは、以下の処理を行います。

    DRP基本動作サンプルプログラム
      MIPIカメラからの入力画像を、
      DRP Libraryを使ってグレースケール画像へ変換して、Displayに出力します。

    DRP並列動作サンプルプログラム
      MIPIカメラからの入力画像を、
      DRP Libraryの並列動作機能を使って高速にグレースケール画像へ変換して、Displayに出力します。

    DRPダイナミックローディングサンプルプログラム1
      MIPIカメラからの入力画像に対し、
      DRP Libraryを動的に切り替えながらCanny法でエッジを検出し、結果をDisplayに出力します。

    DRPダイナミックローディングサンプルプログラム2
      MIPIカメラからの入力画像に対し、
      DRP Libraryを動的に切り替えながらHarrisコーナー検出を行い、結果をDisplayに出力します。

    DRPダイナミックローディングサンプルプログラム3
      MIPIカメラからの入力画像に対し、DRP Libraryを動的に切り替えながらCanny法でエッジ検出した後、
      FindContoursにより輪郭情報を抽出。結果をディスプレイに表示します。

    DRP Simple ISPサンプルプログラム1
      MIPIカメラからの入力画像に対し、
      DRP Libraryを使用して色の補正やノイズ除去を行い、色再現性の高い画像をDisplayに出力します。

    アプリケーションプログラムは、ローダプログラムによりOctaメモリコントローラのレジスタ設定処理を
    行った後に、ローダプログラムから実行されます。
    ローダプログラムは、以下のフォルダに格納しています。
      [rza2m_cam_and_disp_sample_freertos_gcc\generate\gr_mango_boot\mbed_sf_boot.c]

4. サンプルコードの動作確認条件

  (1) ブートモード
    - ブートモード6
      OctaFlash空間に接続されたOctaFlash(SPIモード)からブートします。
      ※上記以外のブートモードを設定した場合、プログラムは動作しません。

  (2) 動作周波数
    RZ/A2M CPUボード上のRZ/A2Mの各クロックが以下の周波数となるように、
    RZ/A2Mのクロックパルス発振器を設定しています。
    (RZ/A2Mのクロックモード1で、EXTAL端子に24MHzのクロックが
    入力されている状態での周波数です。)
      - CPUクロック(Iφ)     : 528MHz
      - 画像処理(Gφ)        : 264MHz
      - 内部バスクロック(Bφ): 132MHz
      - 周辺クロック1(P1φ)  :  66MHz
      - 周辺クロック0(P0φ)  :  33MHz
      - OM_CK/OM_CK#         : 132MHz
      - CKIO                 : 132MHz

  (3) OctaFlash（OctaFlash: 128Mbit、OctaRam: 128Mbit）
    - メーカ  : Macronix社
    - 型名    : MX25UW12845GXDI00

  (4) キャッシュの設定
    L1およびL2キャッシュの初期設定をMMUを設定することにより行っています。
    L1キャッシュおよびL2キャッシュの有効または無効の領域については、
    RZ/A2M初期設定例のアプリケーションノートの「MMUの設定」を参照してください。


5. サンプルコードの動作手順

  本サンプルコードを動作させる場合は、以下の手順に従ってください。

  (1) サンプルコードのセットアップ
    サンプルコードのディレクトリをホストPCの
    e2 studioワークスペースディレクトリ(例: "C:\e2studio_Workspace")にコピーします。

    サンプルコードのディレクトリ :
      DRP基本動作サンプルプログラム
        rza2m_drp_basic_sample_freertos_gcc
      DRP並列動作サンプルプログラム
        rza2m_drp_parallel_sample_freertos_gcc
      DRPダイナミックローディングサンプルプログラム1
        rza2m_drp_dynamic_sample1_freertos_gcc
      DRPダイナミックローディングサンプルプログラム2
        rza2m_drp_dynamic_sample2_freertos_gcc
      DRPダイナミックローディングサンプルプログラム3
        rza2m_drp_dynamic_sample3_freertos_gcc
      DRP Simple ISPサンプルプログラム1
        rza2m_drp_simple_isp_sample1_freertos_gcc

  (2) 統合開発環境の起動
    統合開発環境e2 studioを起動します。

  (3) アプリケーションプログラムのビルド
    e2 studioメニューより、サンプルコードのプロジェクトをインポートした後、
    プロジェクトをビルドし、実行ファイルを生成します。

    サンプルコードのプロジェクト名 :
      DRP基本動作サンプルプログラム
        rza2m_drp_basic_sample_freertos_gcc
      DRP並列動作サンプルプログラム
        rza2m_drp_parallel_sample_freertos_gcc
      DRPダイナミックローディングサンプルプログラム1
        rza2m_drp_dynamic_sample1_freertos_gcc
      DRPダイナミックローディングサンプルプログラム2
        rza2m_drp_dynamic_sample2_freertos_gcc
      DRPダイナミックローディングサンプルプログラム3
        rza2m_drp_dynamic_sample3_freertos_gcc
      DRP Simple ISPサンプルプログラム1
        rza2m_drp_simple_isp_sample1_freertos_gcc

  (4) サンプルコードのダウンロード
    GR-MANGOのCN1とPCをUSBケーブルで接続します。
    PCはGR-MANGOをMBEDドライブとして認識するので、生成したバイナリファイルを
    MBEDドライブへドラッグ&ドロップします。

  (5) サンプルコードの実行
    GR-MANGOのCN13にカメラを接続します。また、CN9とディスプレイをHDMIケーブルで接続します。
    サンプルコードのダウンロード完了を確認し、GR-MANGOのResetボタンを押下します。


以上

