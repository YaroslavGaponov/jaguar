
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;         manager of syscall functions         ; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		
_syscall:
	call dword [_systab+eax*4]
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                clearscreen                   ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_sys_cls:
	call _clrscr
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                  printchar                   ; 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_sys_printc:
	mov eax,ebx
	call _print
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;               printstring                    ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_sys_prints:
	push esi
	mov esi,ebx
	cld
_sys_printstring.3:
	lodsb
	cmp al,'\'
	jne _sys_printstring.1
	lodsb
	cmp al,'n'
	jne _sys_printstring.1
	mov al,CR
_sys_printstring.1:
	test al,al
	jz _sys_printstring.2
	call _print
	jmp _sys_printstring.3
_sys_printstring.2:
	pop esi
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                 _sys_getkey                  ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_sys_getkey:
	call _getkey
	ret 

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;          table of all syscall                ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_systab	dd _sys_cls
	dd _sys_printc
	dd _sys_prints
	dd _sys_getkey
					