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
#include "../ParcoursGraphe.h"
using namespace std;

namespace Constantes
{
	double voisinage = 6;
	double EPSILON_APPARTIENT = 0.07;
	double EPSILON_CERCLES = 0.005;
}

int main(int argc, char *argv[]) {
	std::string path = "mol.graphe";

	if (argc > 1) {
		path = argv[1];
	}

	/*
	 * Import du graphe partiel
	 */
	Mol mol = mol.importerGraphe(path);


	/*
	 * Reconstruction du (ou des) graphe(s) avec positionnement
	 * absolu des atomes.
	 */

	ParcoursGraphe parcours(mol);
	parcours.placer(1);

	return 0;
}
