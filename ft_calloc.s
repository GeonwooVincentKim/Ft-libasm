global ft_calloc
extern malloc
extern __errno_location

section .text

; void *ft_calloc(size_t nmemb, size_t size);
; rdi = nmemb, rsi = size
; unsigned-safe nmemb * size; malloc; zero-fill; NULL on overflow/failure
; Linux ENOMEM = 12
ft_calloc:
	mov	rax, rdi
	mul	rsi
	test	rdx, rdx
	jnz	.overflow
	push	rax
	mov	rdi, rax
	call	malloc wrt ..plt
	pop	rcx
	test	rax, rax
	jz	.done
	mov	rdi, rax
	test	rcx, rcx
	jz	.done
.zero:
	mov	byte [rdi], 0
	inc	rdi
	dec	rcx
	jnz	.zero
.done:
	ret

.overflow:
	push	rax
	call	__errno_location wrt ..plt
	pop	rcx
	mov	dword [rax], 12
	xor	rax, rax
	ret

section .note.GNU-stack noalloc noexec nowrite progbits
