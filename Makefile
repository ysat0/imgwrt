imgwrt.x: imgwrt.o
	gcc -o imgwrt.x imgwrt.o -ldos

imgwrt.o: imgwrt.c
	gcc -O2 -c -o imgwrt.o imgwrt.c
