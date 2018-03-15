

boot.i : empty.i
	dd if=empty.i of=boot.i bs=512 skip=0 count=1

fat1.i : empty.i
	dd if=empty.i of=fat1.i bs=512 skip=1 count=9

fat2.i : empty.i
	dd if=empty.i of=fat2.i bs=512 skip=10 count=9

root.i : empty.i
	dd if=empty.i of=root.i bs=512 skip=19 count=14

data.i : empty.i
	dd if=empty.i of=data.i bs=512 skip=33

break : boot.i fat1.i fat2.i root.i data.i

build : boot.i fat1.i fat2.i root.i data.i
	dd if=boot.i of=full.i bs=512 seek=0 count=1
	dd if=fat1.i of=full.i bs=512 seek=1 count=9
	dd if=fat2.i of=full.i bs=512 seek=10 count=9
	dd if=root.i of=full.i bs=512 seek=19 count=14
	dd if=data.i of=full.i bs=512 seek=33

install : full.i
	dd if=full.i of=/dev/fd0 bs=512

clean :
	rm -f full.i
	rm -f boot.i
	rm -f fat1.i
	rm -f fat2.i
	rm -f root.i
	rm -f data.i
