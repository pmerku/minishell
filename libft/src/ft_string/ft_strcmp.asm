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
	global FN_LABEL(ft_strcmp)

FN_LABEL(ft_strcmp):
	xor		eax, eax

.loop:
	cmp		byte [rdi], 0x0
	jz		.return
	mov		dl, byte [rdi]
	cmp		byte [rsi], dl
	jne		.return

	inc		rdi
	inc		rsi
	jmp		.loop

.return:
	movzx	rax, byte [rdi]
	movzx	rsi, byte [rsi]
	sub		rax, rsi
	ret
