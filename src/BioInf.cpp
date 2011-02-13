//============================================================================
// Name        : BioInf.cpp
// Author      : Introduction au C++
// Version     :
// Copyright   :
// Description :
//============================================================================

#include <iostream>
#include "Point.h"
#include "Noeud.h"
using namespace std;

ostream &operator<< ( ostream &out, Point &p )
{
    return out << p.toString();
}

ostream &operator<< ( ostream &out, Noeud &n )
{
    return out << n.toString();
}

int main() {

	Point a(1, 1, 1);
	Point b(1, 2, 13);

	cout << "Point a: " << a << endl;
	cout << "Point b: " << b << endl;
	cout << "Dist a-b: " << a.dist(b) << endl;

	map<int, Noeud> noeuds;

	Noeud n(1, Noeud::C);
	noeuds.insert(pair<int, Noeud>(n.getIndex(), n));

	for (map<int, Noeud>::iterator it = noeuds.begin() ; it != noeuds.end(); it++ ) {
		cout << "Noeud " << (*it).first << " => " << (*it).second << endl;
	}

	return 0;
}
