	.file	"grading1.cpp"
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.rodata
.LC0:
	.string	"Grade is "
	.text
	.globl	main
	.type	main, @function
main:
.LFB971:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 3, -24
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	_Z9getScoresv
	movq	-48(%rbp), %rax
	movq	%rax, (%rsp)
	movq	-40(%rbp), %rax
	movq	%rax, 8(%rsp)
	movq	-32(%rbp), %rax
	movq	%rax, 16(%rsp)
	movq	-24(%rbp), %rax
	movq	%rax, 24(%rsp)
	call	_Z12overallGrade6Record
	movsbl	%al, %ebx
	movl	$.LC0, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	%ebx, %esi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	call	_ZNSolsEPFRSoS_E
	movl	$0, %eax
	addq	$72, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE971:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC1:
	.string	"Enter scores in this order: 2 quizzes, midterm, final: "
	.text
	.globl	_Z9getScoresv
	.type	_Z9getScoresv, @function
_Z9getScoresv:
.LFB972:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	$.LC1, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	movl	$_ZSt3cin, %edi
	call	_ZNSirsERd
	movq	-8(%rbp), %rdx
	addq	$8, %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSirsERd
	movq	-8(%rbp), %rdx
	addq	$16, %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSirsERd
	movq	-8(%rbp), %rdx
	addq	$24, %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZNSirsERd
	nop
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE972:
	.size	_Z9getScoresv, .-_Z9getScoresv
	.globl	_Z11letterEquivd
	.type	_Z11letterEquivd, @function
_Z11letterEquivd:
.LFB973:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movsd	%xmm0, -8(%rbp)
	movsd	-8(%rbp), %xmm0
	ucomisd	.LC2(%rip), %xmm0
	jb	.L19
	movl	$65, %eax
	jmp	.L8
.L19:
	movsd	-8(%rbp), %xmm0
	ucomisd	.LC3(%rip), %xmm0
	jb	.L20
	movl	$66, %eax
	jmp	.L8
.L20:
	movsd	-8(%rbp), %xmm0
	ucomisd	.LC4(%rip), %xmm0
	jb	.L21
	movl	$67, %eax
	jmp	.L8
.L21:
	movsd	-8(%rbp), %xmm0
	ucomisd	.LC5(%rip), %xmm0
	jb	.L22
	movl	$68, %eax
	jmp	.L8
.L22:
	movl	$70, %eax
.L8:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE973:
	.size	_Z11letterEquivd, .-_Z11letterEquivd
	.globl	_Z12overallGrade6Record
	.type	_Z12overallGrade6Record, @function
_Z12overallGrade6Record:
.LFB974:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$24, %rsp
	movsd	16(%rbp), %xmm0
	movsd	.LC6(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movapd	%xmm0, %xmm1
	movsd	24(%rbp), %xmm0
	movsd	.LC6(%rip), %xmm2
	divsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	movsd	.LC7(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, -8(%rbp)
	movsd	-8(%rbp), %xmm1
	movsd	.LC8(%rip), %xmm0
	mulsd	%xmm0, %xmm1
	movsd	32(%rbp), %xmm2
	movsd	.LC9(%rip), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm0, %xmm1
	movsd	40(%rbp), %xmm2
	movsd	.LC10(%rip), %xmm0
	mulsd	%xmm2, %xmm0
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -24(%rbp)
	movsd	-24(%rbp), %xmm0
	call	_Z11letterEquivd
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE974:
	.size	_Z12overallGrade6Record, .-_Z12overallGrade6Record
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB985:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	cmpl	$1, -4(%rbp)
	jne	.L25
	cmpl	$65535, -8(%rbp)
	jne	.L25
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	call	__cxa_atexit
.L25:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE985:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I_main, @function
_GLOBAL__sub_I_main:
.LFB986:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$65535, %esi
	movl	$1, %edi
	call	_Z41__static_initialization_and_destruction_0ii
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE986:
	.size	_GLOBAL__sub_I_main, .-_GLOBAL__sub_I_main
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I_main
	.section	.rodata
	.align 8
.LC2:
	.long	0
	.long	1079410688
	.align 8
.LC3:
	.long	0
	.long	1079246848
	.align 8
.LC4:
	.long	0
	.long	1079083008
	.align 8
.LC5:
	.long	0
	.long	1078853632
	.align 8
.LC6:
	.long	0
	.long	1076101120
	.align 8
.LC7:
	.long	0
	.long	1073741824
	.align 8
.LC8:
	.long	0
	.long	1077477376
	.align 8
.LC9:
	.long	0
	.long	1070596096
	.align 8
.LC10:
	.long	0
	.long	1071644672
	.hidden	__dso_handle
	.ident	"GCC: (GNU) 4.8.3 20140911 (Red Hat 4.8.3-7)"
	.section	.note.GNU-stack,"",@progbits
