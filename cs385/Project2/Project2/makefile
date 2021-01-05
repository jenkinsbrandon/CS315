P2.out : Project2.o Svg2Bmp.o
	g++ -o P2.out Project2.o Svg2Bmp.o

P2D.out : Project2.o Svg2BmpD.o
	g++ -o P2D.out Project2.o Svg2BmpD.o

Project2.o : Project2.cpp Svg2Bmp.h
	g++ -std=c++11 -g -c Project2.cpp

Svg2Bmp.o : Svg2Bmp.cpp Svg2Bmp.h Svg2Bmp.hh Svg2Bmp.hpp Bitmap_Image.hpp
	g++ -std=c++11 -g -c Svg2Bmp.cpp -DDEBUG=false

Svg2BmpD.o : Svg2Bmp.cpp Svg2Bmp.h Svg2Bmp.hh Svg2Bmp.hpp Bitmap_Image.hpp
	g++ -std=c++11 -g -c Svg2Bmp.cpp -DDEBUG=true -o Svg2BmpD.o

clean :
	rm -rf P2*.out *.o *.gch *.bmp

submit : Project2.cpp Svg2Bmp.h Svg2Bmp.cpp Svg2Bmp.hh Svg2Bmp.hpp Bitmap_Image.hpp makefile README.txt
	rm -rf jenkinsP2
	mkdir jenkinsP2
	cp Project2.cpp jenkinsP2
	cp Svg2Bmp.h jenkinsP2
	cp Svg2Bmp.cpp jenkinsP2
	cp Svg2Bmp.hh jenkinsP2
	cp Svg2Bmp.hpp jenkinsP2
	cp Bitmap_Image.hpp jenkinsP2
	cp makefile jenkinsP2
	cp README.txt jenkinsP2
	cp *.svg jenkinsP2
	tar cfvz jenkinsP2.tgz jenkinsP2
	cp jenkinsP2.tgz ~tiawatts/cs375drop
