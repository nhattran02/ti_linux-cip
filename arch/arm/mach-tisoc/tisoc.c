// SPDX-License-Identifier: GPL-2.0-only
/*
 * Device Tree support for TI SoCs
 * Copyright (C) 2026 Nhat Tran <nhat.tranminhk2@gmail.com>
 * 
 */

#include <asm/mach/arch.h>

static const char * const tisoc_board_dt_compat[] = {
	"ti,tisoc",
	NULL,
};

DT_MACHINE_START(TISOC_DT, "TI-SoCs Cortex-A8 (Device Tree)")
	.dt_compat	= tisoc_board_dt_compat,
MACHINE_END
