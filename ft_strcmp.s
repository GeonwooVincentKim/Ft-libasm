global ft_strcmp

section .text

; int ft_strcmp(const char *s1, const char *s2);
; rdi = s1, rsi = s2
; unsigned-byte compare; return s1[i] - s2[i] as 32-bit int
ft_strcmp:
.loop:
	movzx	eax, byte [rdi]
	movzx	ecx, byte [rsi]
	cmp	eax, ecx
	jne	.diff
	test	eax, eax
	je	.done
	inc	rdi
	inc	rsi
	jmp	.loop
.diff:
	sub	eax, ecx
.done:
	ret

section .note.GNU-stack noalloc noexec nowrite progbits
