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

%ifndef MACROS_S
	%define SSE42_EQUAL_EACH 1000b

	%ifidn __OUTPUT_FORMAT__, elf64
		%define SYS_READ 3
		%define SYS_WRITE 4
		%define LABEL_PREFIX(prefix)
	%elifidn __OUTPUT_FORMAT__, macho64
		%define SYS_READ 0x2000003
		%define SYS_WRITE 0x2000004
		%define LABEL_PREFIX(prefix) _
	%endif
    %define FN_LABEL(name) LABEL_PREFIX(0)name
%endif
