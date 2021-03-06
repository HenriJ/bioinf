/*
 * Point.h
 *
 *  Created on: 1 févr. 2011
 *      Author: Marie
 */


#ifndef POINT_H_
#define POINT_H_
#include <string>
#include <list>

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
	Point plus(Point p);
	Point foisScalaire(double d);
	double scalaire(Point p);
	Point vectoriel(Point p);
	double norme();

	bool equals(Point p);

	std::list<Point> arrondi(void);

	std::string toString();


private:

	double x,y,z;
};

#endif /* POINT_H_ */

