all: cuebin.sys

cuebin.sys: cuebin_drv.c
	bcc -ansi -o cuebin.sys cuebin_drv.c

clean:
	rm -f cuebin.sys
