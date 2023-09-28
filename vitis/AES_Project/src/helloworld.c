/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */


#include "platform.h"
#include "aes_ip.h"
#include "xparameters.h"
#include "xil_io.h"


int main()
{
	u32 result;
    init_platform();
    //Data
    AES_IP_mWriteReg(XPAR_AES_IP_0_S00_AXI_BASEADDR, AES_IP_S00_AXI_SLV_REG0_OFFSET, 0xe0370734);
    AES_IP_mWriteReg(XPAR_AES_IP_0_S00_AXI_BASEADDR, AES_IP_S00_AXI_SLV_REG1_OFFSET, 0x313198a2);
    AES_IP_mWriteReg(XPAR_AES_IP_0_S00_AXI_BASEADDR, AES_IP_S00_AXI_SLV_REG2_OFFSET, 0x885a308d);
    AES_IP_mWriteReg(XPAR_AES_IP_0_S00_AXI_BASEADDR, AES_IP_S00_AXI_SLV_REG3_OFFSET, 0x3243f6a8);
    //Key
    AES_IP_mWriteReg(XPAR_AES_IP_0_S00_AXI_BASEADDR, AES_IP_S00_AXI_SLV_REG4_OFFSET, 0x09cf4f3c);
	AES_IP_mWriteReg(XPAR_AES_IP_0_S00_AXI_BASEADDR, AES_IP_S00_AXI_SLV_REG5_OFFSET, 0xabf71588);
	AES_IP_mWriteReg(XPAR_AES_IP_0_S00_AXI_BASEADDR, AES_IP_S00_AXI_SLV_REG6_OFFSET, 0x28aed2a6);
	AES_IP_mWriteReg(XPAR_AES_IP_0_S00_AXI_BASEADDR, AES_IP_S00_AXI_SLV_REG7_OFFSET, 0x2b7e1516);
	//Result
	result = AES_IP_mReadReg(XPAR_AES_IP_0_S00_AXI_BASEADDR, AES_IP_S00_AXI_SLV_REG15_OFFSET+4);

	xil_printf("\n%d\n", result);
    cleanup_platform();
    return 0;
}