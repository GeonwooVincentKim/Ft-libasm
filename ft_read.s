global ft_read
extern __errno_location

section .text

; ssize_t ft_read(int fd, void *buf, size_t count);
; rdi = fd, rsi = buf, rdx = count
; Linux SYS_read = 0
ft_read:
	xor	rax, rax
	syscall
	cmp	rax, 0
	jge	.done
	neg	rax
	push	rax
	call	__errno_location wrt ..plt
	pop	rdi
	mov	dword [rax], edi
	mov	rax, -1
.done:
	ret

section .note.GNU-stack noalloc noexec nowrite progbits
