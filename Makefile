ImageFilter: ImageFilter.o
	g++ -g ImageFilter.o -o ImageFilter
ImageFilter.o: ImageFilter.cpp
	g++ -c ImageFilter.cpp
clean:
	rm -f *.o
run: ImageFilter
	./ImageFilter
