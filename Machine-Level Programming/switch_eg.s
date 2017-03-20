	.file	"switch_eg.c"
	.text
	.globl	switch_eg
	.type	switch_eg, @function
switch_eg:
.LFB0:
	.cfi_startproc
	cmpl	$4, %edi
	ja	.L2
	movl	%edi, %edi
	jmp	*.L4(,%rdi,8)
	.section	.rodata
	.align 8
	.align 4
.L4:
	.quad	.L3
	.quad	.L9
	.quad	.L6
	.quad	.L7
	.quad	.L8
	.text
.L3:
	movl	$1, %eax
	ret
.L6:
	movl	$3, %eax
	ret
.L7:
	movl	$10, %eax
	ret
.L8:
	movl	$6, %eax
	ret
.L2:
	movl	$0, %eax
	ret
.L9:
	movl	$2, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	switch_eg, .-switch_eg
	.ident	"GCC: (Debian 4.9.2-10) 4.9.2"
	.section	.note.GNU-stack,"",@progbits
