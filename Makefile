
chat.bin: main.c
	gcc main.c -lbox -o chat.bin

clean:
	rm chat.bin
