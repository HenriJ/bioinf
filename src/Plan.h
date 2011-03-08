/*
 * Plan.h
 *
 *  Created on: 15 févr. 2011
 *      Author: samuel
 */

#ifndef PLAN_H_
#define PLAN_H_

#include "Point.h"

class Plan {
public:
	Plan();
	Plan(Point n, Point p);
	virtual ~Plan();

	Point getPoint(void);
	Point getNormale(void);

private:
	Point normale;
	Point point;
};

#endif /* PLAN_H_ */
