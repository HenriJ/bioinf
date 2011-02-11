/*
 * Point.h
 *
 *  Created on: 1 févr. 2011
 *      Author: Marie
 */

#ifndef POINT_H_
#define POINT_H_

class Point{
public:
	double getX(void);
	double getY(void);
	double getZ(void);
	void setX(double d);
	void setY(double d);
	void setZ(double d);


private:
	double x,y,z;

};

#endif /* POINT_H_ */
