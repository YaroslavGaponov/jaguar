
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;        procedure initialize keyboard          ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_setup_keyboard:
	call _keyboard_test
	call _enable_interrupt_keyboard
	ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;          enable keyboard interrupt            ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_enable_interrupt_keyboard:
	in al,0x21
	and al,0xfd
	jmp $+2
	jmp $+2
	out 0x21,al	
	ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;           reset and test keyboard            ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_keyboard_test:
	call _wait_8042_buffer_empty
	mov al,0xff
	out 0x60,al
_keyboard_test_wait_success:
	in al,0x60
	cmp al,0xaa
	jne _keyboard_test_wait_success
	ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;   wait when buffer of keyboard is empty     ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_wait_8042_buffer_empty:
	push cx
	mov cx,0xffff
_wait_8042_buffer_empty.1:
	in al,0x64
	test al,0x02
	loopnz 	_wait_8042_buffer_empty.1
	pop cx
	ret
	