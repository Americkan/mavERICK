CFLAGS = -I ./include
##LIB    = ./libggfonts.so
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr

all: mavERICK

mavERICK: mavERICK.cpp ppm.c log.c 
	g++ $(CFLAGS) mavERICK.cpp erickT.cpp erickH.cpp andrewP.cpp \
	log.c libggfonts.a /usr/lib/x86_64-linux-gnu/libopenal.so \
	/usr/lib/x86_64-linux-gnu/libalut.so -Wall -Wextra $(LFLAGS) -o mavERICK
	

clean:
	rm -f mavERICK
	rm -f *.o
	rm -f *.out


