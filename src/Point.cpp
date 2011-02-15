#include "Point.h"
#include <string>
#include <sstream>
#include <math.h>

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
	double X = this.getX() - p.getX();
	double Y = this.getY() - p.getY();
	double Z = this.getZ() - p.getZ();
	return new Point(X,Y,Z);
}

double norme(){
	Point Zero = new Point(0,0,0);
	return this.dist(Zero);
}

string Point::toString() {
	stringstream out;
	out << "[" << x << ", " << y << ", " << z << "]";
	return out.str();
}
