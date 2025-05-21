CC=gcc
STD=gnu11

PREFIX=/usr/local/bin

FILE=pwdw

all:
	${CC} -std=${STD} ${FILE}.c -o ${FILE}

install: all
	mv ${FILE} ${PREFIX}

clean:
	@rm -f ${FILE}