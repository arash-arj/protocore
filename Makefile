CC = gcc # C compiler
CFLAGS = -fPIC -I include/ -I libs/apr-1.5.2/include/ -I libs/apr-util-1.5.4/include/ -I libs/apr-util-1.5.4/test/ -L libs/apr-1.5.2/.libs/ -L libs/apr-util-1.5.4/.libs/ -lapr-1 -laprutil-1
LDFLAGS = -shared
# RM = rm -f  # rm command
TARGET_LIB = libprcore.so # target lib

SRCS = src/core.c src/core_event.c
OBJS = $(SRCS:.c=.o)


.PHONY: all
all: ${TARGET_LIB}
	cd src/tests/ && $(MAKE)
	cd src/modules/radius/ && $(MAKE)

$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} -o ./bin/$@ $^

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@


# libprotocore.so:
# 	gcc -g -Wall -o bin/libprcore.so -fPIC  -I include/ -I libs/apr-1.5.2/include/ -I libs/apr-util-1.5.4/include/ -I libs/apr-util-1.5.4/test/ -L libs/apr-1.5.2/.libs/ -L libs/apr-util-1.5.4/.libs/ -lapr-1 -laprutil-1

# 	# gcc -g -Wall -shared -lprcore -o bin/mod_cli.so -fPIC src/modules/cli/cli.c -I include/ -I src/modules/cli/ -I libs/apr-1.5.2/include/ -I libs/apr-util-1.5.4/include/ -I libs/apr-util-1.5.4/test/ -L libs/apr-1.5.2/.libs/ -L libs/apr-util-1.5.4/.libs/ -lapr-1 -laprutil-1

# 	# gcc -g -Wall -shared -lprcore -o bin/mod_radius.so -fPIC src/modules/radius/radius.c -I include/ -I src/modules/radius/ -I libs/apr-1.5.2/include/ -I libs/apr-util-1.5.4/include/ -I libs/apr-util-1.5.4/test/ -L libs/apr-1.5.2/.libs/ -L libs/apr-util-1.5.4/.libs/ -lapr-1 -laprutil-1

# 	# gcc -g -Wall -shared -lprcore -o bin/protocore src/main.c -I include/ -I libs/apr-1.5.2/include/ -I libs/apr-util-1.5.4/include/ -I libs/apr-util-1.5.4/test/ -L libs/apr-1.5.2/.libs/ -L libs/apr-util-1.5.4/.libs/ -lapr-1 -laprutil-1

