BUILD=./build

all: polyProduct polyGenerator

polyGenerator: gen_poly
	gcc -Wall -o polyGenerator -lm ${BUILD}/gen_poly.o 

gen_poly: gen_poly.c
	gcc -Wall -c gen_poly.c -o ${BUILD}/gen_poly.o

polyProduct: fft main
	gcc -o polyProduct -lm ${BUILD}/main.o ${BUILD}/fft.o

main: main.c fft.h
	gcc -Wall -c -g main.c -o ${BUILD}/main.o

fft: fft.c fft.h
	gcc -Wall -c -g fft.c -o ${BUILD}/fft.o

clean:
	rm -f ${BUILD}/*.o polyGenerator polyProduct
