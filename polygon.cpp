#include "polygon.h"
#include <cassert>
#include <algorithm>
using namespace std;


double Polygon::getMinX() {
	return min_element(theVerts.begin(), theVerts.end(), [](vec2 l, vec2 r){
				return l.x() < r.x();
      			}
      		)->x();
}

double Polygon::getMinY() {
	vec2 min 
      	= *min_element(theVerts.begin(), theVerts.end(), [](vec2 l, vec2 r){
				return l.y() < r.y();
      			}
      		);
     return min.y();
}

double Polygon::getMaxX() {
	vec2 max 
      	= *max_element(theVerts.begin(), theVerts.end(), [](vec2 l, vec2 r){
				return l.x() < r.x();
      			}
      		);
    return max.x();
}

double Polygon::getMaxY(){
	vec2 max 
      	= *max_element(theVerts.begin(), theVerts.end(), [](vec2 l, vec2 r){
				return l.y() < r.y();
      			}
      	);
    return max.y();
}

//definition of an implicit line
//f(x; y) = (y0 - y1) * x + (x1 - x0)*y + x0 * y1 - x1 *y0 = 0
double implicitLine(vec2 v0, vec2 v1, vec2 p) {
	return( (v0.y()-v1.y())*p.x() + (v1.x()-v0.x())*p.y()  + v0.x()*v1.y() - v1.x()*v0.y() );
}

/* polygon evaluation forms lines out of vertices around the shape and tests
   that the input point is on the same 'side' of all the lines = inside 
   vertices should be passed in counter clockwise CCW! */
bool Polygon::eval(double x, double y) {
	//init as inside
	bool inside = true;
	vec2 v1, v2;
	float d1;
	//must at least be a triangle (assuming closed polygon not line)
	assert(theVerts.size() >=3);

	std::vector<vec2>::iterator nxt = theVerts.begin();
	vec2 start = theVerts.at(0);

	v1 = start;
	//use iterator loop
	for (std::vector<vec2>::iterator it = theVerts.begin() ; 
		it != theVerts.end(); ++it) {

		//advance to the next vertex
		nxt++;
		//if it is valid process the line
		if (nxt != theVerts.end()){
			v2 = *nxt;
			//if point falls outside any line
			d1 = implicitLine(v1, v2, vec2(x, y));
			//cout << "dist: " << d1 << endl;
			if ( d1 < 0) {
				inside = false;
			}
		} 
		//if valid set up for the next line
		v1 = v2;
	}
	//do final line
	//cout << "final line: (v2, s): " << v2 << "  " << start << endl;
	d1 = implicitLine(v2, start, vec2(x, y));
	//cout << "dist: " << d1 << endl;
	if (d1 < 0) {
		inside = false;
	}
	
	return inside;
}


/* helper cross on 3 verts - create vector and cross */
double magCross(vec2 v1, vec2 v2, vec2 v3) {
	double v = ((v2.x()-v1.x())*(v3.y()-v2.y()) - (v3.x()-v2.x())*(v2.y()-v1.y()));
	//cout << "v1: " << v1 << " v2: " << v2 << " v3: " << v3 <<  " mag: " << v << endl;
	return v;
}

/*test is a polygon, specified by CCW vertices is concave or not */
bool Polygon::concave() {

	bool concave = false;
	vec2 v1, v2, v3;
	float d1;
	//must at least be a triangle (assuming closed polygon not line)
	assert(theVerts.size() >=3);
	//triangles cannot be concave
	if (theVerts.size() == 3)
		return false;

	//keep track of 3 vertices
	std::vector<vec2>::iterator cur;
	std::vector<vec2>::iterator before;
	std::vector<vec2>::iterator after;

	//for every vertex get before and after
	for (std::vector<vec2>::iterator it = theVerts.begin() ; 
		it != theVerts.end(); ++it) {

		//non-edge case set up
		cur = it;
		after = cur;
		before = cur;
		after++;
		//edge case at start, grab end
		if (cur == theVerts.begin()){
			before = theVerts.end();
		}
		before--;
		//edge case at end, grab beginning
		if (after == theVerts.end()){
			after = theVerts.begin();
		}
		v1 = *before;
		v2 = *cur;
		v3 = *after;
		//if any vertex is concave, break and return
		if ( magCross(v3, v2, v1) > 0) {
			concave = true;
			break;
		}		
	}
	
	return concave;
}

