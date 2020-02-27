; **************************************************************************** ;
;                                                                              ;
;    Project: minishell                                   ::::::::             ;
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
	global FN_LABEL(ft_strlen)

FN_LABEL(ft_strlen):
	mov			rax,		-16
	mov			rcx,		rdi
	vpxor		ymm0,		ymm0

strlen_loop:
	add			rax,		16
	vpcmpistri	xmm0,		[rdi + rax],	SSE42_EQUAL_EACH
	jnz			strlen_loop

	add			rax,		rcx
	ret