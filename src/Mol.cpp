#include <iostream>
#include <string>
#include <sstream>
#include "Mol.h"
#include "Point.h"
#include "Noeud.h"
#include <fstream>
using namespace std;

Mol::Mol() {

}

Mol::~Mol() {

}

Noeud& Mol::operator[](int i)
{
	return noeuds[i];
}

string Mol::exporterGraphe() {
	stringstream out_noeuds;
	stringstream out_liens;

	for (map<int, Noeud>::iterator it = noeuds.begin() ; it != noeuds.end(); ++it) {
		Noeud& n(it->second);
		out_noeuds << "N " << n.getIndex() << " " << n.getStringType() << endl;

		for (map<double, Noeud>::iterator sub = n.getVoisins().begin() ; sub != n.getVoisins().end(); ++sub) {
			out_liens << "L " << n.getIndex() << " " << sub->first << " " << sub->second.getIndex() << endl;
		}
	}

	out_noeuds << out_liens.str();
	return out_noeuds.str();
}

Mol Mol::importerPDB(std::string path) {
	Mol mol;

	Noeud n1(1, Noeud::C, Point(1, 1, 1));
	mol.insert(n1);
	Noeud n2(2, Noeud::Ca, Point(1, 2, 13));
	mol.insert(n2);
	Noeud n3(3, Noeud::N, Point(2, 0, 1));
	mol.insert(n3);

	return mol;
}

string Mol::exporterXYZ(){
    ofstream myFile;
    myFile.open("exemple.xyz");
	int a=noeuds.size();
	myFile << a << "\n";
    for (int i=1;i<=a;i++){
    	myFile << noeuds[i].getStringType() << " " << noeuds[i].getCoord().getX() << " "<< noeuds[i].getCoord().getY() << " "<< noeuds[i].getCoord().getZ() << "\n" ;

    }


return "";
}

void Mol::insert(Noeud& n) {
	noeuds.insert(pair<int, Noeud>(n.getIndex(), n));
}

Noeud* Mol::reset() {
	internalIterator = noeuds.begin();
	return &((internalIterator)->second);
}

Noeud* Mol::next() {
	if (internalIterator != noeuds.end()) {
		return &((internalIterator++)->second);
	}
	return NULL;
}
