#ifndef POLY_H
#define POLY_H
#include <vector>
#include "vec2.h"
#include "color.h"
#include "shape.h"

/* simple data representation of a convex polygon - defined by a list of vertices */
class Polygon : public shape {
  public:
	Polygon(std::vector<vec2> inVerts, double d, color C) : shape{C, d},  
	theVerts(inVerts) {
		if (this->concave()) {
			std::cerr << "Not convex will not draw as expected" << std::endl;
		}
	}

	bool eval(double x, double y) override;
	void addVert(vec2 inV) { theVerts.push_back(inV); }
	void setVert(std::vector<vec2> inV) {theVerts = inV;}
	void setDepth(double inD) {depth = inD; }
	void validate() override {
		try
		{
			if(!check_verts())
			{
				std::cout << "polygon vert less zero" << std::endl;
			}
		}
		catch(const std::invalid_argument& e)
		{
			setColor(color(0,0,0));
			std::cerr << e.what() << std::endl;
		}
		try
		{
			if(concave())
			{
				std::cout << "polygon concave" << std::endl;
			}
		}
		catch(const std::invalid_argument& e)
		{
			std::vector<vec2> new_vec;
			new_vec.push_back(theVerts[0]);
			new_vec.push_back(theVerts[1]);
			new_vec.push_back(theVerts[theVerts.size()-1]);
			setVert(new_vec);
			setColor(color(255,0,0));
			std::cerr << e.what() << std::endl;
		}
		
	}
	bool concave();
	bool check_verts()
	{
		for(auto i : theVerts)
		{
			if(i.x()<0||i.y()<0) return false;
		}
		return true;
	}
	void translate(vec2 offSet)  { 
		for (int i=0; i < theVerts.size(); i++ ){
			theVerts[i] += offSet;
		}
	}
	void scale(double s){
		for (int i=0; i < theVerts.size(); i++)
			theVerts.at(i) *= s;
	}
	//vec2 getCenter() override { vec2 cOm = vec2(0); for (auto v : theVerts) cOm += v; return 1.0/(theVerts.size())*cOm;}

	std::vector<vec2> getTheVerts() const { return theVerts; }

	double getMinX();
	double getMinY();
	double getMaxX();
	double getMaxY();

  private:
	std::vector<vec2> theVerts; //keep the vertices local to polygon
};

#endif
