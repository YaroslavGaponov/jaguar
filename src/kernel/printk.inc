
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                  printk                      ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

macro printk string {
	local printk.1,printk.2,printk.3,printk.4,printk.5
	jmp printk.2
printk.1:	
	db string,0
printk.2:
	cld	
	mov esi,printk.1
printk.3:
	lodsb
	test al,al
	jz printk.4
	cmp al,'\'
	jne printk.5
	lodsb
	cmp al,'n'
	jne printk.5
	mov al,CR
printk.5:
	call _print
	jmp printk.3
printk.4:
}

	