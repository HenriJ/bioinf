/*
 * Sphere.h
 *
 *  Created on: 15 févr. 2011
 *      Author: samuel
 */


#ifndef SPHERE_H_
#define SPHERE_H_

#include "Point.h"
#include "Cercle.h"
#include "Plan.h"
#include "Intersection.h"

class Sphere {
public:

	Sphere();
	Sphere(Point centre, double rayon);
	virtual ~Sphere();

	Point getCentre(void);
	double getRayon(void);

	void setCentre(Point centre);
	void setRayon(double d);


	Cercle intersectionSphere(Sphere s);

	Intersection intersectionCercle(Cercle c);

	Intersection intersectionTroisSpheres(Sphere t, Sphere u);

	Intersection intersectionQuatreSpheres(Sphere t, Sphere u, Sphere v);

	std::string toString();


private:

	Point centre;
	double rayon;





};

#endif /* SPHERE_H_ */
