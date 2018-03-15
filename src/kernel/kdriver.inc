
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;              keyboard driver            ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; return if buffer is empty
EMPTY_KEYBOARD_BUFFER = -1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;        main code keyboard driver        ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_keyboard:
	    push eax
	    push ebx
	    push ecx

	    in al,0x60

	    cmp al,0x2a
	    jne _keyboard.1
	    mov [shift],1
	    jmp _keyboard.exit
_keyboard.1:
	    cmp al,0xaa
	    jne _keyboard.2
	    mov [shift],0
	    jmp _keyboard.exit
_keyboard.2:
	    cmp al,0x36
	    jne _keyboard.3
	    mov [shift],1
	    jmp _keyboard.exit
_keyboard.3:
	    cmp al,0xb6
	    jne _keyboard.4
	    mov [shift],0
	    jmp _keyboard.exit
_keyboard.4:
	    cmp al,0x1d
	    jne _keyboard.5
	    mov [ctrl],1
	    jmp _keyboard.exit
_keyboard.5:
	    cmp al,0x9d
	    jne _keyboard.6
	    mov [ctrl],0
	    jmp _keyboard.exit
_keyboard.6:
	    cmp al,0x38
	    jne _keyboard.7
	    mov [alt],1
	    jmp _keyboard.exit
_keyboard.7:
	    cmp al,0xb8
	    jne _keyboard.8
	    mov [alt],0
	    jmp _keyboard.exit
_keyboard.8:
	    cmp al,0x80
	    ja _keyboard.exit

	    xor ecx,ecx
	    mov cl,al
	    cmp [shift],byte 1
	    jne _keyboard_drive.9
	    add ecx,keymap_shift
	    jmp _keyboard_drive.11
_keyboard_drive.9:
	    cmp [alt],byte 1
	    jne _keyboard_drive.10
	    add ecx,keymap_alt
	    jmp _keyboard_drive.11
_keyboard_drive.10:
	    add ecx,keymap

_keyboard_drive.11:
	    mov ah,[ecx]
	    cmp [ctrl],byte 1
	    jne _keyboard_drive.12
	    sub ah,96
_keyboard_drive.12:
	    mov bx,[_keyboard_position]
	    inc bl
	    cmp bh,bl
	    jne _keyboard_drive.13
	    inc bh
_keyboard_drive.13:
	    mov [_keyboard_position],bx
	    and ebx,0x0000000f
	    push ebx
	    add ebx,_keyboard_buffer_symbol
	    mov [ebx],ah
	    pop ebx
	    add ebx,_keyboard_buffer_code
	    mov [ebx],al
_keyboard.exit:
	    pop ecx
	    pop ebx
	    pop eax
	    ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                _getkey                 ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_getkey:
	    push ebx
	    xor eax,eax
	    mov bx,[_keyboard_position]
	    cmp bh,bl
	    je _getkey.1
	    push ecx
	    xor ecx,ecx
	    mov cl,bl
	    push ecx
	    add ecx,_keyboard_buffer_code
	    mov ah,[ecx]
	    pop ecx
	    add ecx,_keyboard_buffer_symbol
	    mov al,[ecx]
	    dec bl
	    mov [_keyboard_position],bx
	    pop ecx
	    pop ebx
	    ret
_getkey.1:
	    mov eax,EMPTY_KEYBOARD_BUFFER 
	    pop ebx
	    ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;            mode keyboard               ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

shift       db 0
ctrl        db 0
alt         db 0

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;              buffers                   ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_keyboard_buffer_code:
	    db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
_keyboard_buffer_symbol:
	    db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
_keyboard_position:
	    dw 0

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;              keymap's                  ; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

keymap:   
	    db   '6',27
	    db   '1234567890-=',8,9
	    db   'qwertyuiop[]',13
	    db   '~asdfghjkl;',39,96,0,'\zxcvbnm,./',0,'45 '
	    db   '@234567890123',180,178,184,'6',176,'7'
	    db   179,'8',181,177,183,185,182
	    db   'AB<D',255,'FGHIJKLMNOPQRSTUVWXYZ'
	    db   'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
	    db   'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
	    db   'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
   
keymap_shift:
	    db   '6',27
	    db   '!@#$%^&*()_+',8,9
	    db   'QWERTYUIOP{}',13
	    db   '~ASDFGHJKL:"~',0,'|ZXCVBNM<>?',0,'45 '
	    db   '@234567890123',180,178,184,'6',176,'7'
	    db   179,'8',181,177,183,185,182
	    db   'AB>D',255,'FGHIJKLMNOPQRSTUVWXYZ'
	    db   'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
	    db   'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
	    db   'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
   
keymap_alt:
	    db   ' ',27
	    db   ' @ $  {[]}\ ',8,9
	    db   '            ',13
	    db   '             ',0,'           ',0,'4',0,' '
	    db   '             ',180,178,184,'6',176,'7'
	    db   179,'8',181,177,183,185,182
	    db   'ABCD',255,'FGHIJKLMNOPQRSTUVWXYZ'
	    db   'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
	    db   'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
	    db   'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
