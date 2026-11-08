// SPDX-License-Identifier: GPL-2.0-only
/*
 * Early console for TI-SoCs UART
 *
 * Copyright (C) 2026 Nhat Tran <nhat.tranminhk2@gmail.com>
 */

#include <linux/console.h>
#include <linux/io.h>
#include <linux/serial_core.h>

#define TISOC_UART_THR		0x00
#define TISOC_UART_LSR		0x14
#define TISOC_UART_LSR_TXFIFOE	BIT(5)

static void tisoc_early_putc(struct uart_port *port, unsigned char c)
{
	while (!(readl(port->membase + TISOC_UART_LSR) &
		 TISOC_UART_LSR_TXFIFOE))
		cpu_relax();

	writel(c, port->membase + TISOC_UART_THR);
}

static void tisoc_early_write(struct console *con, const char *s,
			      unsigned int n)
{
	struct earlycon_device *dev = con->data;

	uart_console_write(&dev->port, s, n, tisoc_early_putc);
}

static int __init tisoc_early_setup(struct earlycon_device *dev,
				    const char *opt)
{
	if (!dev->port.membase)
		return -ENODEV;

	dev->con->write = tisoc_early_write;

	return 0;
}
OF_EARLYCON_DECLARE(tisoc, "ti,tisoc-uart", tisoc_early_setup);
