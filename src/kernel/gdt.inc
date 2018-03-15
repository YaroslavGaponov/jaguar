

_setup_gdt:
	lgdt fword [cs:_gdt_48]
	ret

_gdt	dw 0		; dummy
	dw 0
	dw 0
	dw 0

	dw 0x07ff	; 8Mb - limit=2047 (2048*4096=8Mb)	
	dw 0x0000	; base address=0
	dw 0x9a00	; code read/exec
	dw 0x00c0	; granularity=4096

	dw 0x07ff	; 8mb - limit=2047 (2048*4096=8Mb)
	dw 0x0000	; base address=0
	dw 0x9200	; data & stack read/write
	dw 0x00c0	; granularity=4096

repeat 85
	dw 0
	dw 0
	dw 0
	dw 0

	dw 0
	dw 0
	dw 0
	dw 0

	dw 0
	dw 0
	dw 0
	dw 0
end repeat

_gdt_48	dw 0x07ff	; gdt limit=2048, 256 GDT entries
	dd _gdt		; _gdt base

