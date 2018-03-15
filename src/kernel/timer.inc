
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;        procedure initialize timer            ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_setup_timer:
	call _set_timer_speed
	call _enable_interrupt_timer
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;            setup timer's speed               ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_set_timer_speed:
	mov al,0x34
	out 0x43,al
	mov al,0x9b
	out 0x40,al
	mov al,0x2e
	out 0x40,al
	ret
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;          enable timer's interrupt            ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_enable_interrupt_timer:
	in al,0x21
	and al,0xfe
	jmp $+2
	jmp $+2
	out 0x21,al
	ret
	