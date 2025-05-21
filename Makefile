CC=gcc
STD=gnu11

PREFIX=/usr/local/bin

FILE=pwdw

all:
	${CC} -std=${STD} -O3 ${FILE}.c -o ${FILE}

install: all
	mv ${FILE} ${PREFIX}

clean:
	@rm -f ${FILE}