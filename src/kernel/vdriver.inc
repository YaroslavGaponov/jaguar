
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                 video driver                  ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; count lines & columns in text mode
LINES     = 25
COLUMNS	  = 80

; address begin video memory
VIDEOBASE = 0x000B8000

; default attribute
ATTRIB = 0x07

; controls symbol
CR  = 0x0d ; char symbol '\n'


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;              basic print function             ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_print:
	push eax
	push ebx
	push ecx
	push esi
	push edi
	push edx
	
	push eax
	
	mov dx,0x3d4
	mov al,0x0e
	out dx,al
	mov dx,0x3d5
	in al,dx
	xchg ah,al
	mov dx,0x3d4
	mov al,0x0f
	out dx,al
	mov dx,0x3d5
	in al,dx

	xor ebx,ebx
	mov ebx,eax
	pop eax
	
	cmp al,CR
	jne _print.1
	xor eax,eax
_print.3:
	add eax,COLUMNS
	cmp eax,ebx
	jle _print.3
	mov ebx,eax
	jmp _print.2
	
_print.1:
	mov ah,ATTRIB 	
	mov word [ds:ebx*2+VIDEOBASE],ax
	inc ebx

_print.2:
	cmp ebx,COLUMNS*LINES
	jl _print.4

	cld
	mov esi,VIDEOBASE+COLUMNS*2
	mov edi,VIDEOBASE
	mov ecx,COLUMNS*2*(LINES-1)
	rep 
	movsb
	
	cld
	mov edi,VIDEOBASE+COLUMNS*2*(LINES-1)
	mov ecx,COLUMNS
	mov ah,ATTRIB
	mov al,' '
	rep
	stosw
	
	mov ebx,COLUMNS*(LINES-1)

_print.4:
	mov dx,0x3d4
	mov al,0x0e
	mov ah,bh
	out dx,ax
	mov dx,0x3d4
	mov al,0x0f
	mov ah,bl
	out dx,ax

	pop edx
	pop edi
	pop esi
	pop ecx
	pop ebx
	pop eax
	
	ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;               clear all screen                ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_clrscr:

	push eax
	push ecx
	push edi
	push edx

	cld
	mov edi,VIDEOBASE
	mov ecx,COLUMNS*LINES
	mov ah,ATTRIB
	mov al,' '
	rep
	stosw
	
	mov dx,0x3d4
	mov al,0x0e
	xor ah,ah
	out dx,ax
	mov dx,0x3d4
	mov al,0x0f
	xor ah,ah
	out dx,ax
	
	pop edx
	pop edi
	pop ecx
	pop eax
	
	ret	