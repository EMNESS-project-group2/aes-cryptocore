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
#include "aes_axi_ip_if.h"
#include "xparameters.h"
#include "xil_io.h"


int main()
{
	u32 result;
	u32 result1;
	u32 result2;
	u32 result3;

	u32 state1;
	u32 state2;
	u32 state3;
	u32 state4;

    u32 key1;
	u32 key2;
	u32 key3;
	u32 key4;


    init_platform();

    /** Input parameters */

    //Data
    AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG0_OFFSET, 0x00112233);
    AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG1_OFFSET, 0x44556677);
    AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG2_OFFSET, 0x8899AABB);
    AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG3_OFFSET, 0xCCDDEEFF);
    //Key
    AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG4_OFFSET, 0x00010203);
	AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG5_OFFSET, 0x04050607);
	AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG6_OFFSET, 0x08090A0B);
	AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG7_OFFSET, 0x0C0D0E0F);

    for (int i = 0; i < 10000000; i++);
    /* Result */
	result = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG8_OFFSET);
	result1 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG9_OFFSET);
	result2 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG10_OFFSET);
	result3 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG11_OFFSET);

	state1 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG0_OFFSET);
	state2 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG1_OFFSET);
	state3 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG2_OFFSET);
	state4 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG3_OFFSET);

    key1 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG4_OFFSET);
	key2 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG5_OFFSET);
	key3 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG6_OFFSET);
	key4 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG7_OFFSET);


	xil_printf("\n\nResult Test 1   : %08X%08X%08X%08X", result3, result2, result1, result);


    xil_printf("\nExpected Result : 69c4e0d86a7b0430d8cdb78070b4c55a");


	xil_printf("\nstate: %08X%08X%08X%08X", state4, state3, state2, state1);


	xil_printf("\nkey: %08X%08X%08X%08X", key4, key3, key2, key1);


    /** -------------------------------------------------- Test 2 --------------------------------------------------*/


        //Data
    AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG0_OFFSET, 0x3243f6a8);
    AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG1_OFFSET, 0x885a308d);
    AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG2_OFFSET, 0x313198a2);
    AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG3_OFFSET, 0xe0370734);
    //Key
    AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG4_OFFSET, 0x2b7e1516);
	AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG5_OFFSET, 0x28aed2a6);
	AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG6_OFFSET, 0xabf71588);
	AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG7_OFFSET, 0xe0370734);

    for (int i = 0; i < 10000000; i++);
    /* Result */
	result = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG8_OFFSET);
	result1 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG9_OFFSET);
	result2 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG10_OFFSET);
	result3 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG11_OFFSET);

	state1 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG0_OFFSET);
	state2 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG1_OFFSET);
	state3 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG2_OFFSET);
	state4 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG3_OFFSET);

    key1 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG4_OFFSET);
	key2 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG5_OFFSET);
	key3 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG6_OFFSET);
	key4 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG7_OFFSET);


	xil_printf("\n\nResult Test 2   : %08X%08X%08X%08X", result3, result2, result1, result);


    xil_printf("\nExpected Result : 3925841d02dc09fbdc118597196a0b32");


	xil_printf("\nstate: %08X%08X%08X%08X", state4, state3, state2, state1);


	xil_printf("\nkey: %08X%08X%08X%08X", key4, key3, key2, key1);


    /** -------------------------------------------------- Test 3 --------------------------------------------------*/


            //Data
    AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG0_OFFSET, 0x00000000);
    AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG1_OFFSET, 0x00000000);
    AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG2_OFFSET, 0x00000000);
    AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG3_OFFSET, 0x00000000);
    //Key
    AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG4_OFFSET, 0x00000000);
	AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG5_OFFSET, 0x00000000);
	AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG6_OFFSET, 0x00000000);
	AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG7_OFFSET, 0x00000000);

    for (int i = 0; i < 10000000; i++);
    /* Result */
	result = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG8_OFFSET);
	result1 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG9_OFFSET);
	result2 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG10_OFFSET);
	result3 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG11_OFFSET);

	state1 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG0_OFFSET);
	state2 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG1_OFFSET);
	state3 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG2_OFFSET);
	state4 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG3_OFFSET);

    key1 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG4_OFFSET);
	key2 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG5_OFFSET);
	key3 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG6_OFFSET);
	key4 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG7_OFFSET);


	xil_printf("\n\nResult Test 2   : %08X%08X%08X%08X", result3, result2, result1, result);


    xil_printf("\nExpected Result : 66e94bd4ef8a2c3b884cfa59ca342b2e");


	xil_printf("\nstate: %08X%08X%08X%08X", state4, state3, state2, state1);


	xil_printf("\nkey: %08X%08X%08X%08X", key4, key3, key2, key1);

    /** -------------------------------------------------- Test 4 --------------------------------------------------*/

            //Data
    AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG0_OFFSET, 0x00000000);
    AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG1_OFFSET, 0x00000000);
    AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG2_OFFSET, 0x00000000);
    AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG3_OFFSET, 0x00000000);
    //Key
    AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG4_OFFSET, 0x00000000);
	AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG5_OFFSET, 0x00000000);
	AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG6_OFFSET, 0x00000000);
	AES_AXI_IP_IF_mWriteReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG7_OFFSET, 0x00000001);

    for (int i = 0; i < 10000000; i++);
    /* Result */
	result = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG8_OFFSET);
	result1 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG9_OFFSET);
	result2 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG10_OFFSET);
	result3 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG11_OFFSET);

	state1 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG0_OFFSET);
	state2 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG1_OFFSET);
	state3 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG2_OFFSET);
	state4 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG3_OFFSET);

    key1 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG4_OFFSET);
	key2 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG5_OFFSET);
	key3 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG6_OFFSET);
	key4 = AES_AXI_IP_IF_mReadReg(XPAR_AES_AXI_IP_IF_0_S00_AXI_BASEADDR, AES_AXI_IP_IF_S00_AXI_SLV_REG7_OFFSET);


	xil_printf("\n\nResult Test 2   : %08X%08X%08X%08X", result3, result2, result1, result);


    xil_printf("\nExpected Result : 0545aad56da2a97c3663d1432a3d1c84");


	xil_printf("\nstate: %08X%08X%08X%08X", state4, state3, state2, state1);


	xil_printf("\nkey: %08X%08X%08X%08X", key4, key3, key2, key1);

    cleanup_platform();
    return 0;
}
