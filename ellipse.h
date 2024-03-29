#ifndef ELLIPSE_H
#define ELLIPSE_H
#include <iostream>
#include "color.h"
#include "vec2.h"
#include "shape.h"

/* simple data representation of an implicit ellipse */
class ellipse : public shape {
  public:
	ellipse(double cX, double cY, double r1, double r2, color C) : shape{C, 0}, 
		center(cX, cY), radii(r1, r2) {}
	ellipse(vec2 inC, double r1, double r2, double d, color C) : shape{C, d},
		 center(inC), radii(r1, r2) {}
	ellipse(vec2 inC, vec2 inR, double d, color C) : shape{C, d},
		 center(inC), radii(inR) {}
	ellipse(double cX, double cY, double r1, double r2, double d, color C) : shape{C, d},
		center(cX, cY), radii(r1, r2) {}

	bool eval(double x, double y) override {
		if( ((center.x()-x)*(center.x()-x))/(radii.x()*radii.x()) + 
				((center.y()-y)*(center.y()-y))/(radii.y()*radii.y()) - 1.0f < 0) {
			return true;
		}
		return false;
	}
	//note lifted getters

	double getMaxR() {return fmax(radii.x(), radii.y());}
	vec2 getCenter() const { return center; }

	void setCenter(vec2 inCenter) { center = inCenter; }
	void setRadii(vec2 rad) { radii = rad; }
	void validate() override
	{
		try
		{
			if(getCenter().x()< 0 || getCenter().y()< 0)
			{
				std::cout << "ellipse center less zero" << std::endl;
			}
		}
		catch(const std::invalid_argument& e)
		{
			setColor(color(0,0,0));
			std::cerr << e.what() << std::endl;
		}

		try
		{
			if(radii.x()== 0 || radii.y()== 0)
			{
				std::cout << "ellipse divide zero"<< std::endl;
			}
		}
		catch(const std::invalid_argument& e)
		{
			setRadii(2);
			setColor(color(255,0,0));
			std::cerr << e.what() << std::endl;
		}

	}

	friend std::ostream& operator<<(std::ostream &out, const shape &theEllipse);

  private:
	vec2 center; //center point of ellipse
	vec2 radii; //radii of the ellipse
	//note lifted data
};


#endif
