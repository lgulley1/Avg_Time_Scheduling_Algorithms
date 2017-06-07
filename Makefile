start: scheduling_algorithms_time.o
	clang++ -std=c++11 -stdlib=libc++ scheduling_algorithms_time.o -o start

scheduling_algorithms_time.o: scheduling_algorithms_time.cpp
	clang++ -std=c++11 -stdlib=libc++ -c scheduling_algorithms_time.cpp
    
clean:
	rm *.o start