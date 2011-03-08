

#include <sstream>
#include <math.h>
#include "Point.h"


using namespace std;

Point::Point() {
}

Point::Point(double x, double y, double z): x(x), y(y), z(z) {
}

double Point::getX() {
	return x;
}

double Point::getY() {
	return y;
}
double Point::getZ() {
	return z;
}

void Point::setX(double d) {
	x = d;
}

void Point::setY(double d) {
	y = d;
}

void Point::setZ(double d) {
	z = d;
}

double Point::dist(Point p) {
	return sqrt(pow(p.x - x, 2) + pow(p.y - y, 2) + pow(p.z - z, 2));
}

Point Point::moins(Point p){
	double X = x - p.getX();
	double Y = y - p.getY();
	double Z = z - p.getZ();
	return Point(X,Y,Z);
}

Point Point::plus(Point p){
	double X = x + p.getX();
	double Y = y + p.getY();
	double Z = z + p.getZ();
	return Point(X,Y,Z);
}

Point Point::foisScalaire(double d){
	double X = x * d;
	double Y = y * d;
	double Z = z * d;
	return Point(X,Y,Z);
}

double Point::scalaire(Point p){
	return ( this->getX() * p.getX() + this->getY() * p.getY() + this->getZ() * p.getZ() );
}

Point Point::vectoriel(Point p){
	double X = this->getY() * p.getZ() - this->getZ() * p.getY();
	double Y = this->getZ() * p.getX() - this->getX() * p.getZ();
	double Z = this->getX() * p.getY() - this->getY() * p.getX();
	return Point(X,Y,Z);
}

double Point::norme(){
	Point Zero = Point(0,0,0);
	return this->dist(Zero);
}

string Point::toString() {
	stringstream out;
	out << "[" << x << ", " << y << ", " << z << "]";
	return out.str();
}
