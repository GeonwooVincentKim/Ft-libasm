global ft_strlen

section .text

; size_t ft_strlen(const char *s);
; rdi = s
ft_strlen:
	xor	rax, rax
.loop:
	cmp	byte [rdi + rax], 0
	je	.done
	inc	rax
	jmp	.loop
.done:
	ret

section .note.GNU-stack noalloc noexec nowrite progbits
