global ft_strdup
extern ft_strlen
extern malloc

section .text

; char *ft_strdup(const char *s);
; rdi = s
; allocate len+1 via malloc, copy including NUL, return new pointer
ft_strdup:
	push	rdi
	call	ft_strlen
	inc	rax
	mov	rdi, rax
	call	malloc wrt ..plt
	pop	rsi
	test	rax, rax
	jz	.done
	mov	rdi, rax
.loop:
	mov	dl, byte [rsi]
	mov	byte [rdi], dl
	inc	rsi
	inc	rdi
	test	dl, dl
	jnz	.loop
.done:
	ret

section .note.GNU-stack noalloc noexec nowrite progbits
