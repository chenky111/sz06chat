
chat.bin: main.c userinput.c
	gcc $^ -lbox -o chat.bin

clean:
	rm chat.bin
