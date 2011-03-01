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
	Mol mol;

	/*
	 * Import du graphe partiel
	 */
 mol=mol.importerGraphe("mol.graphe");


	/*
	 * TODO: Reconstruction du (ou des) graphe(s) avec positionnement
	 * absolu des atomes.
	 */


	/*
	 * Exporte la molécule au format XYZ
	 */
	cout << mol.exporterXYZ();

	return 0;
}