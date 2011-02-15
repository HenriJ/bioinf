/*
 * Sphere.h
 *
 *  Created on: 15 févr. 2011
 *      Author: samuel
 */

#ifndef SPHERE_H_
#define SPHERE_H_

class Sphere {
	public:


	Sphere();
	Sphere(Point centre, double rayon);
	virtual ~Sphere();

	Point getCentre(void);
	double getRayon(void);

	void setCentre(Point centre);
	void setRayon(double d);


	Cercle intersectionSpheres(Sphere p);

	Point intersectionCercle(Cercle c);


	std::string toString();


	private:

	Point centre;
	double rayon;





};

#endif /* SPHERE_H_ */
