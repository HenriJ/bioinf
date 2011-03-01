/*
 * Cercle.h
 *
 *  Created on: 15 févr. 2011
 *      Author: samuel
 */



#ifndef CERCLE_H_
#define CERCLE_H_

#include "Point.h"
#include "Plan.h"

class Cercle {
public:
	Cercle();
	virtual ~Cercle();
	Cercle(Point centre, double rayon, Plan p);

	Point getCentre(void);
	double getRayon(void);
	Plan getPlan(void);

private:
	Point centre;
	double rayon;
	Plan p;
};

#endif /* CERCLE_H_ */
