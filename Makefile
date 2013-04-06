CFLAGS = -Wall -Os -DWIN32 -Iinclude

ixplay.dll : src/ixplay.o src/iTunesCOMInterface_i.o
	dllwrap --def src/ixplay.def --dllname ixplay.dll src/ixplay.o src/iTunesCOMInterface_i.o -lole32

%.o : %.c
	gcc $(CFLAGS) -c $< -o $@

.PHONY : clean

clean :
	rm -rf ixplay.dll src/ixplay.o src/iTunesCOMInterface_i.o