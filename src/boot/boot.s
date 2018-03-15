
include "size.s"

; 1.44 Mb disks
heads	= 2
tracks	= 80
sectors = 18
secsize = 0x200

; systems variables
BOOTSEG = 0x07c0
INITSEG = 0x9000
SYSTSEG = 0x1000

org 0

_start:
	dw 0x3ceb,0x0090,0x0000,0x0000,0x0000,0x0000,0x0102,0x0001
	dw 0xe002,0x4000,0xf00b,0x0009,0x0012,0x0002,0x0000,0x0000
	dw 0x0000,0x0000,0x0000,0xd629,0x4511,0x4e3d,0x204f,0x414e
	dw 0x454d,0x2020,0x2020,0x4146,0x3154,0x2032,0x2020

	cli

	cld
	mov ax,BOOTSEG
	mov ds,ax
	mov ax,INITSEG
	mov es,ax
	xor si,si
	xor di,di
	mov cx,0x100
	rep movsw
	jmp dword INITSEG:go
go:	
	mov ax,INITSEG
	mov ds,ax
	mov es,ax
	mov ss,ax
	mov sp,0x700

print:
	mov ah,0x03
	xor bh,bh
	int 0x10

	mov ax,0x1301
	mov bx,0x0007
	mov bp,message
	mov cx,0x10
	int 0x10

read1:
	mov ax,SYSTSEG
	mov es,ax
	xor bx,bx

	xor dh,dh
	xor ch,ch
	mov cl,1

	mov si,secsystem

read2:
	push bx 
	push dx 
	push cx
	push si

	mov ax,0x0201
	xor dl,dl
	int 0x13

	test ah,ah
	jnz reset

	pop si
	pop cx
	pop dx
	pop bx

	cmp dword [es:0],0x21061977
	jne seek

	call progress

	dec si
	jz kill

	add bx,secsize

seek:
	inc cl
	cmp cl,sectors+1
	jne read2
	mov cl,1
	inc dh
	cmp dh,heads
	jne read2
	xor dh,dh
	inc ch
	cmp ch,tracks
	jne read2

kill:
	mov dx,0x03f2
	xor al,al
	out dx,al

	mov ax,0x0003
	int 0x10

 	include "init.s"

reset:
	xor ah,ah
	xor dl,dl
	int 0x13
	jmp read2

progress:
	push ax
	push bx
	mov ax,0x0e2e
	xor bh,bh
	int 0x10
	pop bx
	pop ax
	ret
	
message	db 0x0a,0x0d,'Loading system'


repeat 510-$
	db 0
end repeat

_end	dw 0xaa55

