; **************************************************************************** ;
;                                                                              ;
;    Project: custom_libc                                 ::::::::             ;
;    Members: dvoort, prmerku                           :+:    :+:             ;
;    Copyright: 2020                                   +:+                     ;
;                                                     +#+                      ;
;                                                    +#+                       ;
;                                                   #+#    #+#                 ;
;    while (!(succeed = try()));                   ########   odam.nl          ;
;                                                                              ;
; **************************************************************************** ;

%include "macros.asm"

section .text
	global FN_LABEL(ft_memcpy)

FN_LABEL(ft_mempcy):
	xor		ecx, ecx				;clear rcx register
	xor		eax, eax				;clear rax register
	cmp		rdi, rsi				;cmp dst string to src string
	je		.return					;if equal return

.loop:
	mov		al, byte [rsi + rcx]	;copy byte from src to a tmp location
	mov		byte [rdi + rcx], al	;copy from tmp location to dst byte
	cmp		rdx, 0x0				;check if 3rd parameter is 0
	jz		.return					;if yes return

	inc		rcx						;increment index of strings by 1
	dec		rdx						;decrement 3rd parameter by 1
	jmp		.loop					;jump back to loop

.return:
	mov		rax, rdi				;move dst to the return register
	ret								;return dst
