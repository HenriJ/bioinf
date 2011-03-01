/*
 * Intersection.h
 *
 *  Created on: 15 févr. 2011
 *      Author: samuel
 */

#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include <set>
#include "Point.h"

class Intersection {
public:
	Intersection();
	Intersection(int n, set<Point> points);
	virtual ~Intersection();

	int getNombre(void);
	std::set<Point> getPoints(void);

private:
	int nombre;
	std::set<Point> points;
};

#endif /* INTERSECTION_H_ */
