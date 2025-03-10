// SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause
/* Copyright (c) 2020 Facebook */
#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

#ifndef SEC
#define SEC(NAME) __attribute__((section(NAME), used))
#endif

char LICENSE[] SEC("license") = "Dual BSD/GPL";
int my_pid = 0;

SEC("tracepoint/syscalls/sys_enter_accept")
int handle_tp(void *ctx)
{
	int pid = bpf_get_current_pid_tgid() >> 32;

	char comm[16] = {0};
	bpf_get_current_comm(&comm, sizeof(comm));


	bpf_printk("accept from %s, %d.\n", comm, pid);

	return 0;
}
