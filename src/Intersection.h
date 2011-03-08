/*
 * Intersection.h
 *
 *  Created on: 15 févr. 2011
 *      Author: samuel
 */

#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include <list>
#include "Point.h"

class Intersection {
public:
	Intersection();
	Intersection(int n, std::list<Point> points);
	virtual ~Intersection();

	int getNombre(void);
	std::list<Point> &getPoints(void);

private:
	int nombre;
	std::list<Point> points;
};

#endif /* INTERSECTION_H_ */
