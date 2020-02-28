; **************************************************************************** ;
;                                                                              ;
;    Project: project_files                                   ::::::::             ;
;    Members: dvoort, prmerku                           :+:    :+:             ;
;    Copyright: 2020                                   +:+                     ;
;                                                     +#+                      ;
;                                                    +#+                       ;
;                                                   #+#    #+#                 ;
;    while (!(succeed = try()));                   ########   odam.nl          ;
;                                                                              ;
; **************************************************************************** ;

%include "macros.s"

section .text
	global FN_LABEL(ft_strcpy)

FN_LABEL(ft_strcpy):
	mov			r10,		rdi									; Store our destination string for the return value
	mov			rax,		-16									; Initialize to -16 since we increase by 16 first round
	mov			rcx,		rsi									; Move source to RCX for SSE4.2
	pxor		xmm0,		xmm0								; Zero out XMM0 for PCMPISTRI mask
	jmp			strlen_loop										; Jump to the strlen loop, skipping the first copy
																;
strlen_cpy:														;
	movdqu		oword [rdi + rax],	xmm1						; Copy 16 bytes from source to destination
																;
strlen_loop:													;
	add			rax,				16							; Move 16 bytes forward
	movdqu		xmm1,				oword [rsi + rax]			; Load the data from our source string
	pcmpistri	xmm0,				xmm1,	SSE42_EQUAL_EACH	; Check if this string contains a zero-byte
	jnz			strlen_cpy										; If not, copy to dest and jump back to looping
																;
	add			rsi,				rax							; Increment our offset in the source string
	add			rdi,				rax							; Increment our offset in the destination string
																;
remainder_loop:													;
	lodsb														; Load char from source into al, increase offset
	stosb														; Store char into destination from al, increase offset
	test		al,		al										; Check if the character was a string terminator
	jne			remainder_loop									; If not, keep copying characters
																;
	mov			rax,		r10									; Load the original destination string
	ret															; And return the destination string
