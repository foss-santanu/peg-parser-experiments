test: test.cpp peglib.h
	g++ test.cpp -I. -std=c++17 -o test -O3 -Wall               

clean:
	rm -rf test