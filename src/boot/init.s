 
_init:
	cli

gdt_and_idt:
	lgdt fword [cs:gdt_48]
	lidt fword [cs:idt_48]

disable_nmi:
	mov al,0xff
	out 0x21,al
	jmp $+2
	jmp $+2
	out 0xa1,al
	jmp $+2
	jmp $+2

enable_a20:
	call emply_8042
	mov al,0xd1
	out 0x64,al
	call emply_8042
	mov al,0xdf
	out 0x60,al
	call emply_8042

switch_pm:
	mov eax,cr0
	or al,1
	mov cr0,eax

	mov ax,0x10
	mov ds,ax
	mov es,ax
	mov ss,ax
	mov esp,0x9ffff

	db 0x66
	db 0xea
	dd (SYSTSEG shl 4) + 4
	dw 8

emply_8042:
	push cx
	mov cx,0xffff
wait_8042:
	in al,0x64
	test al,2
	loopnz wait_8042 
	pop cx
	ret

gdt	dw 0		; dummy
	dw 0
	dw 0
	dw 0

	dw 0x07ff	; 8Mb - limit=2047 (2048*4096=8Mb)	
	dw 0x0000	; base address=0
	dw 0x9a00	; code read/exec
	dw 0x00c0	; granularity=4096

	dw 0x07ff	; 8mb - linit=2047 (2048*4096=8Mb)
	dw 0x0000	; base address=0
	dw 0x9200	; data & stack read/write
	dw 0x00c0	; granularity=4096

idt_48	dw 0		; idt limit=0
	dw 0,0		; idt base=0L

gdt_48	dw 0x0800	; gdt limit=2048, 256 GDT entries
	dd (INITSEG shl 4) + gdt	; gdt base=0x0009XXXX

