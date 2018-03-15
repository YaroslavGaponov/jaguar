
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;              main procedure                 ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		
_start:
	printk "Jaguar OS Ver.0.01 Copyright (c) by Yaroslav Gaponov (gaponov@softline.kiev.ua)"
	printk "\nInitialize kernel..."
	
	printk "\nkernel: sets up a new gdt and loads it"
	call _setup_gdt
	
	printk "\nkernel: sets up a new idt and loads it"
	call _setup_idt
	
	printk "\nkernel: reload all segment registers"
	mov ax,0x10
	mov ds,ax
	mov es,ax
	mov ss,ax
	mov esp,0x1ffff

	printk "\nkernel: initialize timer"
	call _setup_timer
	
	printk "\nkernel: initialize keyboard"
	call _setup_keyboard
	
	printk "\nkernel: enable all interrupts"
	sti

        printk "\nkernel: starting first task"
	call _start_first_task

	printk "\nkernel: starting idle task as first task"
	call _idle_task
