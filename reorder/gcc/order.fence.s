	.file	"ordering.cpp"
	.text
	.align 2
.globl _ZN15MersenneTwister7integerEv
	.type	_ZN15MersenneTwister7integerEv, @function
_ZN15MersenneTwister7integerEv:
.LFB17:
	pushq	%rbp
.LCFI0:
	movq	%rsp, %rbp
.LCFI1:
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rax
	movl	2496(%rax), %eax
	movl	%eax, -20(%rbp)
	movq	-40(%rbp), %rax
	movl	2496(%rax), %eax
	addl	$1, %eax
	movl	%eax, -16(%rbp)
	cmpl	$623, -16(%rbp)
	jle	.L2
	movl	$0, -16(%rbp)
.L2:
	movq	-40(%rbp), %rax
	movl	2496(%rax), %eax
	addl	$397, %eax
	movl	%eax, -12(%rbp)
	cmpl	$623, -12(%rbp)
	jle	.L4
	subl	$624, -12(%rbp)
.L4:
	movl	-20(%rbp), %eax
	movq	-40(%rbp), %rdx
	cltq
	movl	(%rdx,%rax,4), %eax
	movl	%eax, %ecx
	andl	$-2147483648, %ecx
	movl	-16(%rbp), %eax
	movq	-40(%rbp), %rdx
	cltq
	movl	(%rdx,%rax,4), %eax
	andl	$2147483647, %eax
	orl	%ecx, %eax
	movl	%eax, -8(%rbp)
	movl	-12(%rbp), %eax
	movq	-40(%rbp), %rdx
	cltq
	movl	(%rdx,%rax,4), %edx
	movl	-8(%rbp), %eax
	shrl	%eax
	xorl	%eax, %edx
	movl	-8(%rbp), %eax
	andl	$1, %eax
	imull	$-1727483681, %eax, %eax
	xorl	%edx, %eax
	movl	%eax, -4(%rbp)
	movq	-40(%rbp), %rax
	movl	2496(%rax), %eax
	movq	-40(%rbp), %rcx
	movslq	%eax,%rdx
	movl	-4(%rbp), %eax
	movl	%eax, (%rcx,%rdx,4)
	movq	-40(%rbp), %rdx
	movl	-16(%rbp), %eax
	movl	%eax, 2496(%rdx)
	movl	-4(%rbp), %eax
	shrl	$11, %eax
	xorl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	sall	$7, %eax
	andl	$-1658038656, %eax
	xorl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	sall	$15, %eax
	andl	$-272236544, %eax
	xorl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	shrl	$18, %eax
	xorl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	leave
	ret
.LFE17:
	.size	_ZN15MersenneTwister7integerEv, .-_ZN15MersenneTwister7integerEv
.globl __gxx_personality_v0
	.align 2
.globl _ZN15MersenneTwisterC1Ej
	.type	_ZN15MersenneTwisterC1Ej, @function
_ZN15MersenneTwisterC1Ej:
.LFB16:
	pushq	%rbp
.LCFI2:
	movq	%rsp, %rbp
.LCFI3:
	subq	$32, %rsp
.LCFI4:
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L8
.L9:
	movl	-8(%rbp), %eax
	movq	-24(%rbp), %rcx
	movslq	%eax,%rdx
	movl	-28(%rbp), %eax
	movl	%eax, (%rcx,%rdx,4)
	addl	$1, -8(%rbp)
.L8:
	cmpl	$623, -8(%rbp)
	jle	.L9
	movq	-24(%rbp), %rax
	movl	$0, 2496(%rax)
	movl	$0, -4(%rbp)
	jmp	.L11
.L12:
	movq	-24(%rbp), %rdi
	call	_ZN15MersenneTwister7integerEv
	addl	$1, -4(%rbp)
.L11:
	cmpl	$62399, -4(%rbp)
	jle	.L12
	leave
	ret
.LFE16:
	.size	_ZN15MersenneTwisterC1Ej, .-_ZN15MersenneTwisterC1Ej
	.align 2
.globl _ZN15MersenneTwisterC2Ej
	.type	_ZN15MersenneTwisterC2Ej, @function
_ZN15MersenneTwisterC2Ej:
.LFB15:
	pushq	%rbp
.LCFI5:
	movq	%rsp, %rbp
.LCFI6:
	subq	$32, %rsp
.LCFI7:
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L16
.L17:
	movl	-8(%rbp), %eax
	movq	-24(%rbp), %rcx
	movslq	%eax,%rdx
	movl	-28(%rbp), %eax
	movl	%eax, (%rcx,%rdx,4)
	addl	$1, -8(%rbp)
.L16:
	cmpl	$623, -8(%rbp)
	jle	.L17
	movq	-24(%rbp), %rax
	movl	$0, 2496(%rax)
	movl	$0, -4(%rbp)
	jmp	.L19
.L20:
	movq	-24(%rbp), %rdi
	call	_ZN15MersenneTwister7integerEv
	addl	$1, -4(%rbp)
.L19:
	cmpl	$62399, -4(%rbp)
	jle	.L20
	leave
	ret
.LFE15:
	.size	_ZN15MersenneTwisterC2Ej, .-_ZN15MersenneTwisterC2Ej
	.align 2
.globl _Z11thread2FuncPv
	.type	_Z11thread2FuncPv, @function
_Z11thread2FuncPv:
.LFB19:
	pushq	%rbp
.LCFI8:
	movq	%rsp, %rbp
.LCFI9:
	subq	$2528, %rsp
.LCFI10:
	movq	%rdi, -2520(%rbp)
	leaq	-2512(%rbp), %rdi
	movl	$2, %esi
	call	_ZN15MersenneTwisterC1Ej
.L24:
	movl	$beginSema2, %edi
	call	sem_wait
.L25:
	leaq	-2512(%rbp), %rdi
	call	_ZN15MersenneTwister7integerEv
	andl	$7, %eax
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	jne	.L25
	movl	$1, Y(%rip)
#APP
	mfence
#NO_APP
	movl	X(%rip), %eax
	movl	%eax, r2(%rip)
	movl	$endSema, %edi
	call	sem_post
	jmp	.L24
.LFE19:
	.size	_Z11thread2FuncPv, .-_Z11thread2FuncPv
	.align 2
.globl _Z11thread1FuncPv
	.type	_Z11thread1FuncPv, @function
_Z11thread1FuncPv:
.LFB18:
	pushq	%rbp
.LCFI11:
	movq	%rsp, %rbp
.LCFI12:
	subq	$2528, %rsp
.LCFI13:
	movq	%rdi, -2520(%rbp)
	leaq	-2512(%rbp), %rdi
	movl	$1, %esi
	call	_ZN15MersenneTwisterC1Ej
.L29:
	movl	$beginSema1, %edi
	call	sem_wait
.L30:
	leaq	-2512(%rbp), %rdi
	call	_ZN15MersenneTwister7integerEv
	andl	$7, %eax
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	jne	.L30
	movl	$1, X(%rip)
#APP
	mfence
#NO_APP
	movl	Y(%rip), %eax
	movl	%eax, r1(%rip)
	movl	$endSema, %edi
	call	sem_post
	jmp	.L29
.LFE18:
	.size	_Z11thread1FuncPv, .-_Z11thread1FuncPv
	.section	.rodata
	.align 8
.LC0:
	.string	"%d reorders detected after %d iterations\n"
	.text
	.align 2
.globl main
	.type	main, @function
main:
.LFB20:
	pushq	%rbp
.LCFI14:
	movq	%rsp, %rbp
.LCFI15:
	subq	$32, %rsp
.LCFI16:
	movl	$0, %edx
	movl	$0, %esi
	movl	$beginSema1, %edi
	call	sem_init
	movl	$0, %edx
	movl	$0, %esi
	movl	$beginSema2, %edi
	call	sem_init
	movl	$0, %edx
	movl	$0, %esi
	movl	$endSema, %edi
	call	sem_init
	leaq	-16(%rbp), %rdi
	movl	$0, %ecx
	movl	$_Z11thread1FuncPv, %edx
	movl	$0, %esi
	call	pthread_create
	leaq	-24(%rbp), %rdi
	movl	$0, %ecx
	movl	$_Z11thread2FuncPv, %edx
	movl	$0, %esi
	call	pthread_create
	movl	$0, -8(%rbp)
	movl	$1, -4(%rbp)
.L34:
	movl	$0, X(%rip)
	movl	$0, Y(%rip)
	movl	$beginSema1, %edi
	call	sem_post
	movl	$beginSema2, %edi
	call	sem_post
	movl	$endSema, %edi
	call	sem_wait
	movl	$endSema, %edi
	call	sem_wait
	movl	r1(%rip), %eax
	testl	%eax, %eax
	jne	.L35
	movl	r2(%rip), %eax
	testl	%eax, %eax
	jne	.L35
	addl	$1, -8(%rbp)
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
.L35:
	addl	$1, -4(%rbp)
	jmp	.L34
.LFE20:
	.size	main, .-main
.globl beginSema1
	.bss
	.align 32
	.type	beginSema1, @object
	.size	beginSema1, 32
beginSema1:
	.zero	32
.globl beginSema2
	.align 32
	.type	beginSema2, @object
	.size	beginSema2, 32
beginSema2:
	.zero	32
.globl endSema
	.align 32
	.type	endSema, @object
	.size	endSema, 32
endSema:
	.zero	32
.globl X
	.align 4
	.type	X, @object
	.size	X, 4
X:
	.zero	4
.globl Y
	.align 4
	.type	Y, @object
	.size	Y, 4
Y:
	.zero	4
.globl r1
	.align 4
	.type	r1, @object
	.size	r1, 4
r1:
	.zero	4
.globl r2
	.align 4
	.type	r2, @object
	.size	r2, 4
r2:
	.zero	4
	.section	.eh_frame,"a",@progbits
.Lframe1:
	.long	.LECIE1-.LSCIE1
.LSCIE1:
	.long	0x0
	.byte	0x1
	.string	"zPR"
	.uleb128 0x1
	.sleb128 -8
	.byte	0x10
	.uleb128 0x6
	.byte	0x3
	.long	__gxx_personality_v0
	.byte	0x3
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x90
	.uleb128 0x1
	.align 8
.LECIE1:
.LSFDE1:
	.long	.LEFDE1-.LASFDE1
.LASFDE1:
	.long	.LASFDE1-.Lframe1
	.long	.LFB17
	.long	.LFE17-.LFB17
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI0-.LFB17
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI1-.LCFI0
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE1:
.LSFDE3:
	.long	.LEFDE3-.LASFDE3
.LASFDE3:
	.long	.LASFDE3-.Lframe1
	.long	.LFB16
	.long	.LFE16-.LFB16
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI2-.LFB16
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI3-.LCFI2
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE3:
.LSFDE5:
	.long	.LEFDE5-.LASFDE5
.LASFDE5:
	.long	.LASFDE5-.Lframe1
	.long	.LFB15
	.long	.LFE15-.LFB15
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI5-.LFB15
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI6-.LCFI5
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE5:
.LSFDE7:
	.long	.LEFDE7-.LASFDE7
.LASFDE7:
	.long	.LASFDE7-.Lframe1
	.long	.LFB19
	.long	.LFE19-.LFB19
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI8-.LFB19
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI9-.LCFI8
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE7:
.LSFDE9:
	.long	.LEFDE9-.LASFDE9
.LASFDE9:
	.long	.LASFDE9-.Lframe1
	.long	.LFB18
	.long	.LFE18-.LFB18
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI11-.LFB18
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI12-.LCFI11
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE9:
.LSFDE11:
	.long	.LEFDE11-.LASFDE11
.LASFDE11:
	.long	.LASFDE11-.Lframe1
	.long	.LFB20
	.long	.LFE20-.LFB20
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI14-.LFB20
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI15-.LCFI14
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE11:
	.ident	"GCC: (GNU) 4.1.2 20080704 (Red Hat 4.1.2-46)"
	.section	.note.GNU-stack,"",@progbits
