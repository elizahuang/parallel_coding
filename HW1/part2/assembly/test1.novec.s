	.text
	.def	 @feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"test1.cpp"
	.def	 _Z5test1PfS_S_i;
	.scl	2;
	.type	32;
	.endef
	.section	.rdata,"dr"
	.p2align	3               # -- Begin function _Z5test1PfS_S_i
.LCPI0_0:
	.quad	4472406533629990549     # double 1.0000000000000001E-9
	.text
	.globl	_Z5test1PfS_S_i
	.p2align	4, 0x90
_Z5test1PfS_S_i:                        # @_Z5test1PfS_S_i
.seh_proc _Z5test1PfS_S_i
# %bb.0:
	pushq	%rsi
	.seh_pushreg 6
	pushq	%rdi
	.seh_pushreg 7
	pushq	%rbx
	.seh_pushreg 3
	subq	$80, %rsp
	.seh_stackalloc 80
	movaps	%xmm6, 64(%rsp)         # 16-byte Spill
	.seh_savexmm 6, 64
	.seh_endprologue
	movq	%r8, %rsi
	movq	%rdx, %rdi
	movq	%rcx, %rbx
	leaq	48(%rsp), %rdx
	movl	$4, %ecx
	callq	clock_gettime
	testl	%eax, %eax
	jne	.LBB0_7
# %bb.1:
	xorl	%eax, %eax
	.p2align	4, 0x90
.LBB0_2:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_3 Depth 2
	xorl	%ecx, %ecx
	.p2align	4, 0x90
.LBB0_3:                                #   Parent Loop BB0_2 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movss	(%rbx,%rcx,4), %xmm0    # xmm0 = mem[0],zero,zero,zero
	addss	(%rdi,%rcx,4), %xmm0
	movss	%xmm0, (%rsi,%rcx,4)
	movss	4(%rbx,%rcx,4), %xmm0   # xmm0 = mem[0],zero,zero,zero
	addss	4(%rdi,%rcx,4), %xmm0
	movss	%xmm0, 4(%rsi,%rcx,4)
	movss	8(%rbx,%rcx,4), %xmm0   # xmm0 = mem[0],zero,zero,zero
	addss	8(%rdi,%rcx,4), %xmm0
	movss	%xmm0, 8(%rsi,%rcx,4)
	movss	12(%rbx,%rcx,4), %xmm0  # xmm0 = mem[0],zero,zero,zero
	addss	12(%rdi,%rcx,4), %xmm0
	movss	%xmm0, 12(%rsi,%rcx,4)
	addq	$4, %rcx
	cmpq	$1024, %rcx             # imm = 0x400
	jne	.LBB0_3
# %bb.4:                                #   in Loop: Header=BB0_2 Depth=1
	addl	$1, %eax
	cmpl	$20000000, %eax         # imm = 0x1312D00
	jne	.LBB0_2
# %bb.5:
	leaq	32(%rsp), %rdx
	movl	$4, %ecx
	callq	clock_gettime
	testl	%eax, %eax
	jne	.LBB0_7
# %bb.6:
	movq	32(%rsp), %rax
	movq	40(%rsp), %rcx
	subq	48(%rsp), %rax
	subq	56(%rsp), %rcx
	xorps	%xmm0, %xmm0
	cvtsi2sdq	%rcx, %xmm0
	movabsq	$.LCPI0_0, %rcx
	mulsd	(%rcx), %xmm0
	movabsq	$.L.str, %rdx
	xorps	%xmm6, %xmm6
	cvtsi2sdq	%rax, %xmm6
	addsd	%xmm0, %xmm6
	movabsq	$_ZSt4cout, %rsi
	movl	$47, %r8d
	movq	%rsi, %rcx
	callq	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movq	%rsi, %rcx
	movapd	%xmm6, %xmm1
	callq	_ZNSo9_M_insertIdEERSoT_
	movq	%rax, %rsi
	movabsq	$.L.str.1, %rdx
	movl	$8, %r8d
	movq	%rax, %rcx
	callq	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movq	%rsi, %rcx
	movl	$1024, %edx             # imm = 0x400
	callq	_ZNSolsEi
	movq	%rax, %rsi
	movabsq	$.L.str.2, %rdx
	movl	$5, %r8d
	movq	%rax, %rcx
	callq	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movq	%rsi, %rcx
	movl	$20000000, %edx         # imm = 0x1312D00
	callq	_ZNSolsEi
	movabsq	$.L.str.3, %rdx
	movl	$2, %r8d
	movq	%rax, %rcx
	callq	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movaps	64(%rsp), %xmm6         # 16-byte Reload
	addq	$80, %rsp
	popq	%rbx
	popq	%rdi
	popq	%rsi
	retq
.LBB0_7:
	movabsq	$.L.str.4, %rcx
	movabsq	$.L__PRETTY_FUNCTION__._ZL7gettimev, %r8
	movabsq	$.L.str.5, %r9
	movl	$75, %edx
	callq	__assert_func
	ud2
	.seh_handlerdata
	.text
	.seh_endproc
                                        # -- End function
	.def	 _GLOBAL__sub_I_test1.cpp;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90         # -- Begin function _GLOBAL__sub_I_test1.cpp
_GLOBAL__sub_I_test1.cpp:               # @_GLOBAL__sub_I_test1.cpp
.seh_proc _GLOBAL__sub_I_test1.cpp
# %bb.0:
	pushq	%rsi
	.seh_pushreg 6
	subq	$32, %rsp
	.seh_stackalloc 32
	.seh_endprologue
	movabsq	$_ZStL8__ioinit, %rsi
	movq	%rsi, %rcx
	callq	_ZNSt8ios_base4InitC1Ev
	movabsq	$_ZNSt8ios_base4InitD1Ev, %rcx
	movabsq	$__dso_handle, %r8
	movabsq	$__imp___cxa_atexit, %rax
	movq	%rsi, %rdx
	addq	$32, %rsp
	popq	%rsi
	rex64 jmpq	*(%rax)         # TAILCALL
	.seh_handlerdata
	.text
	.seh_endproc
                                        # -- End function
	.lcomm	_ZStL8__ioinit,1        # @_ZStL8__ioinit
	.section	.rdata,"dr"
.L.str:                                 # @.str
	.asciz	"Elapsed execution time of the loop in test1():\n"

.L.str.1:                               # @.str.1
	.asciz	"sec (N: "

.L.str.2:                               # @.str.2
	.asciz	", I: "

.L.str.3:                               # @.str.3
	.asciz	")\n"

.L.str.4:                               # @.str.4
	.asciz	"./fasttime.h"

.L__PRETTY_FUNCTION__._ZL7gettimev:     # @__PRETTY_FUNCTION__._ZL7gettimev
	.asciz	"fasttime_t gettime()"

.L.str.5:                               # @.str.5
	.asciz	"r == 0"

	.section	.ctors,"dw"
	.p2align	3
	.quad	_GLOBAL__sub_I_test1.cpp

	.addrsig
	.addrsig_sym _GLOBAL__sub_I_test1.cpp
	.addrsig_sym _ZStL8__ioinit
	.addrsig_sym __dso_handle
	.addrsig_sym _ZSt4cout
