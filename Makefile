libmonodraw.so: monodraw.c monodraw.h
	gcc monodraw.c -o libmonodraw.so -lm -fPIC -shared

install: libmonodraw.so monodraw.h
	cp ./libmonodraw.so /usr/lib/
	cp ./monodraw.h /usr/include

uninstall:
	rm /usr/lib/libmonodraw.so /usr/include/monodraw.h

test_breathing_ring: tests/breathing_ring.c
	gcc tests/breathing_ring.c -o test_breathing_ring -lm -lmonodraw

test_universe: tests/universe.c
	gcc tests/universe.c -o test_universe -lmonodraw

clear:
	rm libmonodraw.so test_breathing_ring test_universe
