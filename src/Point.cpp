/**
 * Plan.cpp
 *
 *  Created on: 15 févr. 2011
 *      Author: samuel
 **/

#include <sstream>
#include <math.h>
#include <list>
#include "Point.h"


using namespace std;

/**
 * Méthode constructeur par défaut
 **/
Point::Point() {
}

/**
 * Méthode constructeur prenant en arguments
 * les coordonnées du Point
 **/
Point::Point(double x, double y, double z): x(x), y(y), z(z) {
}

/**
 * Renvoie la première coordonnée du Point
 **/
double Point::getX() {
	return x;
}

/**
 * Renvoie la deuxième coordonnée du Point
 **/
double Point::getY() {
	return y;
}

/**
 * Renvoie la troisième coordonnée du Point
 **/
double Point::getZ() {
	return z;
}

/**
 * Permet de modifier la première coordonnée du Point
 **/
void Point::setX(double d) {
	x = d;
}

/**
 * Permet de modifier la deuxième coordonnée du Point
 **/
void Point::setY(double d) {
	y = d;
}

/**
 * Permet de modifier la troisième coordonnée du Point
 **/
void Point::setZ(double d) {
	z = d;
}

/**
 * Renvoie la distance en norme euclidienne séparant deux Points
 **/
double Point::dist(Point p) {
	return sqrt(pow(p.x - x, 2) + pow(p.y - y, 2) + pow(p.z - z, 2));
}

/**
 * Renvoie le vecteur différence entre deux Points
 * Ce vecteur est sous la forme d'un Point
 **/
Point Point::moins(Point p){
	double X = x - p.getX();
	double Y = y - p.getY();
	double Z = z - p.getZ();
	return Point(X,Y,Z);
}

/**
 * Renvoie le vecteur somme de deux Points
 * Ce vecteur est sous la forme d'un Point
 **/
Point Point::plus(Point p){
	double X = x + p.getX();
	double Y = y + p.getY();
	double Z = z + p.getZ();
	return Point(X,Y,Z);
}

/**
 * Renvoie le vecteur multiplié par un scalaire d
 **/
Point Point::foisScalaire(double d){
	double X = x * d;
	double Y = y * d;
	double Z = z * d;
	return Point(X,Y,Z);
}

/**
 * Renvoie le produit scalaire de deux vecteurs
 **/
double Point::scalaire(Point p){
	return ( this->getX() * p.getX() + this->getY() * p.getY() + this->getZ() * p.getZ() );
}

/**
 * Renvoie le produit vectoriel de deux vecteurs
 **/
Point Point::vectoriel(Point p){
	double X = this->getY() * p.getZ() - this->getZ() * p.getY();
	double Y = this->getZ() * p.getX() - this->getX() * p.getZ();
	double Z = this->getX() * p.getY() - this->getY() * p.getX();
	return Point(X,Y,Z);
}

/**
 * Renvoie la norme euclidienne d'un vecteur
 **/
double Point::norme(){
	Point Zero = Point(0,0,0);
	return this->dist(Zero);
}

/**
 * Renvoie une liste de points correspondant aux diff�rents
 * arrondis possibles d'un Point
 * Chaque coordonnée est arrondie au millième près à sa valeur
 * supérieure ou inférieure
 * Puisque nous travaillons en dimension 3, la liste contient
 * huit éléments
 **/
list<Point> Point::arrondi(void){
	// Pour x
	double X1 = ( floor ((double) (1000 * x))) / 1000;
	double X2 = X1 + 0.001;
	// Pour y
	double Y1 = ( floor ((double) (1000 * y))) / 1000;
	double Y2 = Y1 + 0.001;
	// Pour z
	double Z1 = ( floor ((double) (1000 * z))) / 1000;
	double Z2 = Z1 + 0.001;

	list<Point> rep = list<Point>();
	rep.push_front(Point (X1,Y1,Z1));
	rep.push_front(Point (X1,Y1,Z2));
	rep.push_front(Point (X1,Y2,Z1));
	rep.push_front(Point (X2,Y1,Z1));
	rep.push_front(Point (X1,Y2,Z2));
	rep.push_front(Point (X2,Y1,Z2));
	rep.push_front(Point (X2,Y2,Z1));
	rep.push_front(Point (X2,Y2,Z2));
	return rep;
}

/**
 * Renvoie un Point comme une chaîne de caractères
 * pour qu'il soit lisible clairement sur la console
 * en sortie
 **/
string Point::toString() {
	stringstream out;
	out << "[" << x << ", " << y << ", " << z << "]";
	return out.str();
}
/**
 * Teste l'égalité de deux Points
 **/
bool Point::equals(Point p){
	return (p.x==x && p.y==y && p.z==z);
}
