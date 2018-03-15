

tmp.s : start.s kernel.s
	cat start.s *.inc kernel.s > tmp.s

kernel.i : tmp.s
	fasm tmp.s kernel.i

clean :
	rm -f tmp.s
	rm -f kernel.i

