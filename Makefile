all: src/main.c
	gcc -g -Wall -o bin/protocore src/main.c src/core.c -I include/ -I src/modules/cli/ -I src/modules/radius/ -I libs/apr-1.5.2/include/ -I libs/apr-util-1.5.4/include/ -I libs/apr-util-1.5.4/test/ -L libs/apr-1.5.2/.libs/ -L libs/apr-util-1.5.4/.libs/ -lapr-1 -laprutil-1

	gcc -g -Wall -shared -o bin/mod_cli.so -fPIC src/modules/cli/cli.c -I include/ -I src/modules/cli/ -I libs/apr-1.5.2/include/ -I libs/apr-util-1.5.4/include/ -I libs/apr-util-1.5.4/test/ -L libs/apr-1.5.2/.libs/ -L libs/apr-util-1.5.4/.libs/ -lapr-1 -laprutil-1

	gcc -g -Wall -shared -o bin/mod_radius.so -fPIC src/modules/radius/radius.c -I include/ -I src/modules/radius/ -I libs/apr-1.5.2/include/ -I libs/apr-util-1.5.4/include/ -I libs/apr-util-1.5.4/test/ -L libs/apr-1.5.2/.libs/ -L libs/apr-util-1.5.4/.libs/ -lapr-1 -laprutil-1

