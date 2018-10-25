CFLAGS = -g -Werror
LDFLAGS = -lpthread
 
src = $(wildcard *.c)
target = $(patsubst %.c, %, ${src})
 
.PHONY: all clean
 
%:%.c
	$(CC) ${CFLAGS} ${LDFLAGS} $^ -o $@
 
all: ${target}
 
clean:
	rm -f ${target}
	rm -f *.o
