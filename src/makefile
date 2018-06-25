OBJ=smart3.o buzzer.o led.o key.o
CC=arm-none-linux-gnueabi-gcc
CFLAGS=-c


smart3:$(OBJ)
		$(CC) $^ -o $@
smart3.o:smart3.c buzzer.h led.h key.h
		$(CC) $(CFLAGS) $< -o $@
buzzer.o:buzzer.c buzzer.h
		$(CC) $(CFLAGS) $< -o $@
led.o:led.c led.h
		$(CC) $(CFLAGS) $< -o $@
key.o:key.c key.h
		$(CC) $(CFLAGS) $< -o $@
clean:
		rm -f smart2 *.o