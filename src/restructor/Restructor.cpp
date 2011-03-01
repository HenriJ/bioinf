//============================================================================
// Name        : PDB Restructor
// Author      : Introduction au C++
// Version     :
// Copyright   :
// Description : Ce programme prend en entrée une représentation de graphe
//				 partiel et reconstruit un fichier .XYZ exploitable par JMol
//============================================================================

#include <iostream>
#include <string>
#include <sstream>
#include "../Noeud.h"
#include "../Mol.h"
using namespace std;

int main(int argc, char *argv[]) {
	Graphe mol;

	/*
	 * Import du graphe partiel
	 */
	Noeud n1(1, Noeud::C, Point(1, 1, 1));
	graphe.insert(n1);
	Noeud n2(2, Noeud::Ca, Point(1, 2, 13));
	graphe.insert(n2);
	Noeud n3(3, Noeud::N, Point(2, 0, 1));
	graphe.insert(n3);

	/*
	 * TODO: Reconstruction du (ou des) graphe(s) avec positionnement
	 * absolu des atomes.
	 */


	/*
	 * Exporte la molécule au format XYZ
	 */
	cout << mol.exporterGraphe();

	return 0;
}
