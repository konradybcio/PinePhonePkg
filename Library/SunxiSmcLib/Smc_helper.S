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

.text
.align 3

GCC_ASM_EXPORT(ArmCallSmc)
GCC_ASM_EXPORT(__sunxi_smc_call)

/* Code from https://github.com/ARM-software/arm-enterprise-acs/blob/master/mpam/platform/pal_uefi_acpi_override/src/AArch64/arm_smc.S */
ASM_PFX(ArmCallSmc):
  // Push x0 on the stack - The stack must always be quad-word aligned
  str   x0, [sp, #-16]!

  // Load the SMC arguments values into the appropriate registers
  ldp   x6, x7, [x0, #48]
  ldp   x4, x5, [x0, #32]
  ldp   x2, x3, [x0, #16]
  ldp   x0, x1, [x0, #0]

  smc   #0

  // Pop the ARM_SMC_ARGS structure address from the stack into x9
  ldr   x9, [sp], #16

  // Store the SMC returned values into the ARM_SMC_ARGS structure.
  // A SMC call can return up to 4 values - we do not need to store back x4-x7.
  stp   x2, x3, [x9, #16]
  stp   x0, x1, [x9, #0]

  mov   x0, x9

  ret
/* End code from https://github.com/ARM-software/arm-enterprise-acs/blob/master/mpam/platform/pal_uefi_acpi_override/src/AArch64/arm_smc.S */

ASM_PFX(__sunxi_smc_call):
	//stmfd	sp!, {r4-r12, lr}	 //save reg state
	stp	x4, x5, [sp, 16]!
        stp     x6, x7, [sp, 16]!
        stp     x8, x9, [sp, 16]!
        stp     x10, x11, [sp, 16]!
        stp     x12, lr, [sp, 16]!
	smc #0

	//ldmfd	sp!, {r4-r12, pc} //restore saved regs and return
	ldp	x4, x5, [sp, 16]!
	ldp     x6, x7, [sp, 16]
	ldp     x8, x9, [sp, 16]
	ldp     x10, x11, [sp, 16]
	ldr     x12, [sp, 16] //what to do with pc yikes
	mov	lr, x12
	ret
