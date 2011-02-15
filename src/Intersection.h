/*
 * Intersection.h
 *
 *  Created on: 15 févr. 2011
 *      Author: samuel
 */

#ifndef INTERSECTION_H_
#define INTERSECTION_H_

class Intersection {
public:
	Intersection();
	virtual ~Intersection();

private:
	int nombre;
	Set<Point> points;
};

#endif /* INTERSECTION_H_ */
