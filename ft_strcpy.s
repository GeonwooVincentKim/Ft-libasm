global ft_strcpy

section .text

; char *ft_strcpy(char *dst, const char *src);
; rdi = dst, rsi = src
; return original dst
ft_strcpy:
	mov	rax, rdi
.loop:
	mov	dl, byte [rsi]
	mov	byte [rdi], dl
	inc	rsi
	inc	rdi
	test	dl, dl
	jnz	.loop
	ret

section .note.GNU-stack noalloc noexec nowrite progbits
