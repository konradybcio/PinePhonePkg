//
//  Copyright (c) 2012, ARM Limited. All rights reserved.
//
//  This program and the accompanying materials
//  are licensed and made available under the terms and conditions of the BSD License
//  which accompanies this distribution.  The full text of the license may be found at
//  http://opensource.org/licenses/bsd-license.php
//
//  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
//  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
//
//

    EXPORT ArmCallSmc
    EXPORT __sunxi_smc_call


    AREA   ArmSmc, CODE, READONLY

ArmCallSmc
    push    {r1}
    mov     r1, r0
    ldr     r0,[r1]
    smc     #0
    str     r0,[r1]
    pop     {r1}
    bx      lr

__sunxi_smc_call
  	stmfd	sp!, {r4-r12, lr}	//save reg state
	  smc #0
	  ldmfd	sp!, {r4-r12, pc}	//restore saved regs and return

    END
