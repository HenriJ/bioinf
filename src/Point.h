/*
 * Point.h
 *
 *  Created on: 1 févr. 2011
 *      Author: Marie
 */


#ifndef POINT_H_
#define POINT_H_
#include <string>

class Point{
	public:

	Point();
	Point(double x, double y, double z);

	double getX(void);
	double getY(void);
	double getZ(void);

	void setX(double d);
	void setY(double d);
	void setZ(double d);

	double dist(Point p);
	Point moins(Point p);
	double norme();

	std::string toString();


	private:

	double x,y,z;
};

#endif /* POINT_H_ */

