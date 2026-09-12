global ft_write
extern __errno_location

section .text

; ssize_t ft_write(int fd, const void *buf, size_t count);
; rdi = fd, rsi = buf, rdx = count
; Linux SYS_write = 1
ft_write:
	mov	rax, 1
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
