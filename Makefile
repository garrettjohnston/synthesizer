all:
	g++ -std=c++11 -Ioperations -Iprograms -I. *.h *.hpp
clean:
	rm *~ *.gch
