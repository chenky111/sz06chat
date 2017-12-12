
chat.bin: main.c userinput.c udpinput.c
	gcc $^ -lbox -o chat.bin

clean:
	rm chat.bin
