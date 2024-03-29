#ifndef IMAGE_H
#define IMAGE_H

#include <math.h>
#include "color.h"

using namespace std;


template <class T> class image  {

	public:
		image(int w, int h, T backGround) : width(w), height(h) {
			for(int i=0; i <width*height; i++)
				elements.push_back(backGround);
		}

		int w() const {return width; }
		int h() const {return height; } 
	    void writePixel(ostream& out, int x, int y, T cOut) const;
	    void writeHeader(ostream& out) const;
	    void writeNewLine(ostream& out) const;
	    void setPixel(int x, int y, T in) {
	    	elements.at(mapXY(x,y)) = in;
	    }
	    void fullWriteOut(ostream& out);

	private:
		int mapXY(int x, int y) {return y*(width-1) + x; }
		int width;
		int height;
		vector<T> elements;
};

template <class T>
void image<T>::fullWriteOut(ostream& out) {

	writeHeader(out);
	//for ach pixel, write out its color
	for (int y=0; y < height; y++) {
		for (int x =0; x < width; x++) {
			writePixel(out, x, y, elements.at(mapXY(x, y)));
		}
		writeNewLine(out);
	}
}


template <>
inline void image<int>::writePixel(ostream& out, int x, int y, int cOut) const {
 	out << cOut << endl; 		
}
template <>
inline void image<bool>::writePixel(ostream& out, int x, int y, bool cOut) const {
	int result = 0;
	if (cOut == true){
		result = 1;
	}else{
		result = 0;
	}
	out << result << endl;
}
template <>
inline void image<color>::writePixel(ostream& out, int x, int y, color cOut) const {

 	out << static_cast<int>(clamp(cOut.r(), 0.0, 255)) << " "
 					<< static_cast<int>(clamp(cOut.g(), 0.0, 255)) << " "
 					<< static_cast<int>(clamp(cOut.b(), 0.0, 255)) << endl; 	
}
template <>
inline void image<char>::writePixel(ostream& out, int x, int y, char cOut) const {
	
	out << cOut;
}




template <class T>
void image<T>::writeNewLine(ostream& out) const {
 	out << "\n"; 
}




//grey
template<>
inline void image<int>::writeHeader(ostream& out) const {
	//PPM format header
 	out << "P2\n" << width << " " << height << "\n255\n"; 
}
//black and white
template<>
inline void image<bool>::writeHeader(ostream& out) const {
	//PPM format header
 	out << "P1\n" << width << " " << height << endl; 
}
template<>
inline void image<color>::writeHeader(ostream& out) const {
	//PPM format header
 	out << "P3\n" << width << " " << height << "\n255\n"; 
}
template<>
inline void image<char>::writeHeader(ostream& out) const {
	//PPM format header
 	out << "Asci\n" << width << " " << height << endl; 
}
#endif


