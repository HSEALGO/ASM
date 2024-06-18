global func1, func2, func3, dfunc1, dfunc2, dfunc3

section .rodata
	f2const1 dq -2.0
	f2const2 dq 14.0
	f3const0 dq -1.0
	f3const1 dq 1.0
	f3const2 dq 2.0
	f3const3 dq 6.0
	df1const1 dq 1.0
	

section .text

;f1(x) = ln(x)
func1:
	push ebp
	mov ebp, esp
	
	%define x ebp + 8

	fld1
	fld qword[x]
	fyl2x
	fldln2
	fmul
	
	%undef x

	mov esp, ebp
	pop ebp

	ret

;f2(x) = -2*x + 8
func2:
	push ebp
	mov ebp, esp

	%define x ebp + 8

	fld qword[x]
	fld qword[f2const1]
	fmul

	fld qword[f2const2]
	fadd
	
	%undef x

	mov esp, ebp
	pop ebp

	ret

;f3(x) = 1/(2 - x) + 6
func3:
	push ebp
	mov ebp, esp
	
	%define x ebp+8
	
	fld qword[f3const0]
	fld qword[x]
	fmul
	fld qword[f3const2]
	fadd
	fst st1
	fld qword[f3const1]
	fdiv st0, st1
	fld qword[f3const3]
	fadd

	%undef x

	mov esp, ebp
	pop ebp

	ret

;f1'(x) = 1/x
dfunc1:
	push ebp
	mov ebp, esp

	%define x ebp+8

	fld qword[df1const1]
	fld qword[x]
	fdiv

	%undef x

	mov esp, ebp
	pop ebp

	ret

;f2'(x) = -2
dfunc2:
	push ebp
	mov ebp, esp

	fld qword[f2const1]

	mov esp, ebp
	pop ebp

	ret

;f3'(x) = 1/(-x + 2)^2
dfunc3:
	push ebp
	mov ebp, esp

	%define x ebp+8

	fld qword[f3const0]
	fld qword[x]
	fmul
	fld qword[f3const2]
	fadd
	fmul st0, st0
	fst st1
	fld qword[f3const1]
	fdiv st0, st1

	%undef x

	mov esp, ebp
	pop ebp

	ret

