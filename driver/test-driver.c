/*
* Copyright (C) 2013-2022  Xilinx, Inc.  All rights reserved.
* Copyright (c) 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
*
* Permission is hereby granted, free of charge, to any person
* obtaining a copy of this software and associated documentation
* files (the "Software"), to deal in the Software without restriction,
* including without limitation the rights to use, copy, modify, merge,
* publish, distribute, sublicense, and/or sell copies of the Software,
* and to permit persons to whom the Software is furnished to do so,
* subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in this
* Software without prior written authorization from Xilinx.
*
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define BASE_ADDR 			(0x43C00000U)
#define OFFSET_STATE_0      (0x00000000U)
#define OFFSET_STATE_1      (0x00000004U)
#define OFFSET_STATE_2      (0x00000008U)
#define OFFSET_STATE_3      (0x0000000CU)


#define OFFSET_KEY_0        (0x00000010U)
#define OFFSET_KEY_1        (0x00000014U)
#define OFFSET_KEY_2        (0x00000018U)
#define OFFSET_KEY_3        (0x0000001CU)

#define OFFSET_OUTPUT_0     (0x00000020U)
#define OFFSET_OUTPUT_1     (0x00000024U)
#define OFFSET_OUTPUT_2     (0x00000028U)
#define OFFSET_OUTPUT_3     (0x00000002U)



static void test_maker (int* fd, uint32_t* state_f, uint32_t* key_f);


int main(int argc, char **argv)
{
    int fd;
    uint32_t key[4]   = {0U};
    uint32_t state[4] = {0U};
    uint32_t out[4]   = {0U};



    int fd = open ("/dev/aes-core",O_RDWR);
    if (fd < 0) 
    {
        perror ("Unable to open device");
    }


    printf("*****************************************\n");
    printf("*               TEST 1\n")
    printf("*****************************************\n");
    
    state[0] = 0x00112233U;
    state[1] = 0x44556677U;
    state[2] = 0x8899AABBU;
    state[3] = 0xCCDDEEFFU;

    key[0]   = 0x00010203U;
    key[1]   = 0x04050607U;
    key[2]   = 0x08090A0BU;
    key[3]   = 0x0C0D0E0FU;

    test_maker (&fd, &state, &key);

    printf("*****************************************\n");
    printf("*               TEST 2\n")
    printf("*****************************************\n");
    
    state[0] = 0x3243f6a8U;
    state[1] = 0x885a308dU;
    state[2] = 0x313198a2U;
    state[3] = 0xe0370734U;

    key[0]   = 0x2b7e1516U;
    key[1]   = 0x28aed2a6U;
    key[2]   = 0xabf71588U;
    key[3]   = 0xe0370734U;

    test_maker (&fd, &state, &key);

    printf("*****************************************\n");
    printf("*               TEST 3\n")
    printf("*****************************************\n");
    
    state[0] = 0x00000000U;
    state[1] = 0x00000000U;
    state[2] = 0x00000000U;
    state[3] = 0x00000000U;

    key[0]   = 0x00000000U;
    key[1]   = 0x00000000U;
    key[2]   = 0x00000000U;
    key[3]   = 0x00000000U;

    test_maker (&fd, &state, &key);

    printf("*****************************************\n");
    printf("*               TEST 4\n")
    printf("*****************************************\n");
    
    state[0] = 0x00000000U;
    state[1] = 0x00000000U;
    state[2] = 0x00000000U;
    state[3] = 0x00000000U;

    key[0]   = 0x00000000U;
    key[1]   = 0x00000000U;
    key[2]   = 0x00000000U;
    key[3]   = 0x00000001U;

    test_maker (&fd, &state, &key);



    return 0;
}


static void test_maker 
(
    int* fd, 
    uint32_t* state_f,
    uint32_t* key_f
)
{

    uint32_t key[4]   = {0U};
    uint32_t state[4] = {0U};
    uint32_t out[4]   = {0U};

    for (int i = 0; i < 4; i++)
    {
        key[i]   = *(key_f + i);
        state[i] = *(state_f + i);
    }

    /* Writing state value */
    pwrite (*fd, &state[0], sizeof(uint32_t), (off_t)OFFSET_STATE_0);
    pwrite (*fd, &state[1], sizeof(uint32_t), (off_t)OFFSET_STATE_1);
    pwrite (*fd, &state[2], sizeof(uint32_t), (off_t)OFFSET_STATE_2);
    pwrite (*fd, &state[3], sizeof(uint32_t), (off_t)OFFSET_STATE_3);

    /* Writing key value */
	pwrite (*fd, &key[0], sizeof(uint32_t), (off_t)OFFSET_KEY_0);
    pwrite (*fd, &key[1], sizeof(uint32_t), (off_t)OFFSET_KEY_1);
    pwrite (*fd, &key[2], sizeof(uint32_t), (off_t)OFFSET_KEY_2);
    pwrite (*fd, &key[3], sizeof(uint32_t), (off_t)OFFSET_KEY_3);


    sleep(1);

    /* Reading output */
    pread (fd, &out[0], sizeof(uint32_t), (off_t)OFFSET_OUTPUT_0);
    pread (fd, &out[1], sizeof(uint32_t), (off_t)OFFSET_OUTPUT_1);
    pread (fd, &out[2], sizeof(uint32_t), (off_t)OFFSET_OUTPUT_2);
    pread (fd, &out[3], sizeof(uint32_t), (off_t)OFFSET_OUTPUT_3);


    printf("State value     : %08x%08X%08X%08X\n");
    printf("Key value       : %08x%08X%08X%08X\n");
    printf("Output value    : %08x%08X%08X%08X\n");
    printf("Expected Output : %08x%08X%08X%08X\n");

}
