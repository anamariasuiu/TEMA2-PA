all: build

build: curatare.cpp fortificatii.cpp beamdrone.cpp curse.cpp
	g++ -Wall curatare.cpp -o curatare -lm
	g++ -Wall fortificatii.cpp -o fortificatii -lm
	g++ -Wall beamdrone.cpp -o beamdrone -lm
	g++ -Wall curse.cpp -o curse -lm

run-p1:
	./curatare

run-p2:
	./fortificatii
	
run-p3:
	./beamdrone

run-p4:
	./curse



.PHONY: clean

clean:
	rm -f run-p1 run-p2 run-p3 run-p4
	rm -f *.out