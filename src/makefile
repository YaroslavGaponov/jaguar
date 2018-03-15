

kernel/kernel.i:
	(cd kernel;make kernel.i)

boot/boot.i: kernel/kernel.i
	(echo -n "secsystem = ";ls -l kernel/kernel.i | awk '{ print $$5,"/ secsize + 1" }';) > boot/size.s
	(cd boot;make boot.i)

vmware/floppy.i: boot/boot.i fs/fat1.i fs/fat2.i fs/root.i fs/data.i kernel/kernel.i 
	dd if=boot/boot.i of=vmware/floppy.i bs=512 seek=0 count=1
	dd if=fs/fat1.i of=vmware/floppy.i bs=512 seek=1 count=9
	dd if=fs/fat2.i of=vmware/floppy.i bs=512 seek=10 count=9
	dd if=fs/root.i of=vmware/floppy.i bs=512 seek=19 count=14
	dd if=fs/data.i of=vmware/floppy.i bs=512 seek=33
	sync
	mount vmware/floppy.i /mnt/floppy -t msdos -o loop=/dev/loop3
	cp kernel/kernel.i /mnt/floppy/jaguar.sys
	umount /mnt/floppy

start: vmware/floppy.i
	vmware -x vmware/jaguar.cfg &

clean:
	rm -f vmware/floppy.i
	rm -f vmware/jaguar.log
	(cd kernel;make clean)
	(cd boot;make clean)

