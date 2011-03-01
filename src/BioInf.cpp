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

	map<int, Noeud> noeuds;

	Noeud n1(1, Noeud::C, a);
	noeuds.insert(pair<int, Noeud>(n1.getIndex(), n1));
	Noeud n2(2, Noeud::Ca, b);
	n2.addVoisin(n1);
	n2.addVoisin(n2);
	noeuds.insert(pair<int, Noeud>(n2.getIndex(), n2));

	Noeud *n;
	for (map<int, Noeud>::iterator it = noeuds.begin() ; it != noeuds.end(); it++ ) {
		cout << it->first << " ";
		n = &(it->second);
		cout << n->getStringType() << " ";
		cout << n->getStringVoisins() << " ";
		cout << endl;
	}


	return 0;
}
