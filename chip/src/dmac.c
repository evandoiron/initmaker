/*
 * dmac.c
 * dma controller for SAMD51
 * 
 * Copyright � Alkgrove 2018
 *
 * @par Redistribution and use in source and binary forms, with or without modification, are permitted 
 * provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions 
 * and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions 
 * and the following disclaimer in the documentation and/or other materials provided with the 
 * distribution. 
 * 3. Neither the name of the copyright holder nor the names of its contributors may be 
 * used to endorse or promote products derived from this software without specific prior written 
 * permission.
 * 
 * @par THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER 
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF 
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#ifdef DEBUG
#include <stdio.h>
#endif
#include "sam.h"

__attribute__((__aligned__(16))) 
DmacDescriptor base_dma_descriptor[DMAC_BASE_COUNT] = {0};
__attribute__((__aligned__(16)))
DmacDescriptor base_dma_write_back[DMAC_BASE_COUNT] = {0};

DmacDescriptor *get_base_DMA_descriptor(uint8_t channel)
{
	return &base_dma_descriptor[channel];
}

DmacDescriptor *get_base_DMA_writeback_descriptor(uint8_t channel)
{
	return &base_dma_write_back[channel];
}

#ifdef DEBUG
/* 
 * Print descriptor
 * Print descriptors in link list until null pointer or ep (end pointer is reached)
 * ep is provided to stop printing a circular list
 */

void print_descriptor(DmacDescriptor *p, DmacDescriptor *ep)
{
    DmacDescriptor *next;
    int i = 1;
    const char *beat[] = {"Byte", "Halfword", "Word", "Invalid"};
    const char *blockact[] = {"NOACT", "INT", "SUSPEND", "BOTH"};
    const char *evosel[] = {"Disable", "Block", "Invalid", "Beat"};
    unsigned int btctrl;
    do {
        next = (DmacDescriptor *) p->DESCADDR.reg;
        printf("Descriptor #%d\r\n", i++);
    	printf(" SRC %08X\r\n", (unsigned int) p->SRCADDR.reg);
    	printf(" DST %08X\r\n",  (unsigned int) p->DSTADDR.reg);
    	printf(" DESC %08X\r\n", (unsigned int) next);
    	printf(" BTCNT %08X (%d)\r\n",  p->BTCNT.reg, p->BTCNT.reg);
    	btctrl = (unsigned int) p->BTCTRL.reg;
    	printf(" BTCTRL %08X\r\n", btctrl);	
    	printf("   STEPSIZE %1X\r\n", 1 << ((btctrl & DMAC_BTCTRL_STEPSIZE_Msk) >> DMAC_BTCTRL_STEPSIZE_Pos));
    	printf("   Step Select %s\r\n", (btctrl & DMAC_BTCTRL_STEPSEL) ? "SRC" : "DST");
    	printf("   DST INC %s\r\n", (btctrl & DMAC_BTCTRL_DSTINC) ? "enabled" : "disabled");
    	printf("   SRC INC %s\r\n", (btctrl & DMAC_BTCTRL_SRCINC) ? "enabled" : "disabled");
    	printf("   Beat Size %s\r\n", beat[((btctrl & DMAC_BTCTRL_BEATSIZE_Msk) >> DMAC_BTCTRL_BEATSIZE_Pos)]);
    	printf("   Block Action %s\r\n", blockact[((btctrl & DMAC_BTCTRL_BLOCKACT_Msk) >> DMAC_BTCTRL_BLOCKACT_Pos)]);
    	printf("   Event Out Select %s\r\n", evosel[((btctrl & DMAC_BTCTRL_EVOSEL_Msk) >> DMAC_BTCTRL_EVOSEL_Pos)]);
    	printf("   Descriptor %s\r\n", (btctrl & DMAC_BTCTRL_VALID) ? "Valid" : "Invalid");    	
    	p = next;
    } while ((next != ep) && (next != 0));
	
}	
#endif