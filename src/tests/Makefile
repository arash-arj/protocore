CC = gcc # C compiler
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I ../../include/ -I ../../libs/apr-1.5.2/include/ -I ../../libs/apr-util-1.5.4/include/ -I ../../libs/apr-util-1.5.4/test/ -L ../../libs/apr-1.5.2/.libs/ -L ../../libs/apr-util-1.5.4/.libs/ -lapr-1 -laprutil-1
LDFLAGS = -shared -L ../../bin/ -lprcore # linking flags
# RM = rm -f  # rm command
TESTS = test # target lib

all:
	gcc -fPIC -L ../../bin/ -lprcore -o ../../bin/test01 ./test01.c -I  ../../include/ -I  ../../libs/apr-1.5.2/include/ -I  ../../libs/apr-util-1.5.4/include/ -I  ../../libs/apr-util-1.5.4/test/ -L  ../../libs/apr-1.5.2/.libs/ -L  ../../libs/apr-util-1.5.4/.libs/ -lapr-1 -laprutil-1

	gcc -fPIC -L ../../bin/ -lprcore -o ../../bin/test02 ./test02.c -I  ../../include/ -I  ../../libs/apr-1.5.2/include/ -I  ../../libs/apr-util-1.5.4/include/ -I  ../../libs/apr-util-1.5.4/test/ -L  ../../libs/apr-1.5.2/.libs/ -L  ../../libs/apr-util-1.5.4/.libs/ -lapr-1 -laprutil-1

