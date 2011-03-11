#ifndef GRAPHE_H_
#define GRAPHE_H_

#include "Noeud.h"

class Mol {
	public:
		Mol();
		virtual ~Mol();

		static Mol importerPDB(std::string path);
		static Mol importerGraphe(std::string path);

		Noeud* operator[](int i);
		std::string exporterGraphe();
		std::string exporterXYZ();
		void exporterXYZ(std::string path);

		int size();
		void insert(Noeud* p);

		Noeud* reset();
		Noeud* next();

	private:
		std::map<int, Noeud*> noeuds;
		std::map<int, Noeud*>::iterator internalIterator;
};

#endif /* GRAPHE_H_ */
