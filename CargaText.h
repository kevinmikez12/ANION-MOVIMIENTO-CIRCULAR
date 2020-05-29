#include "Face.h"
#include "Vertice.h"
#ifndef CARGARTEXT__H //definimos nuestra biblioteca 
#define CARGARTEXT_H

using namespace std;//hacemos mencion del espacio que estemos creando

struct Load{//creamos estructura de tipo load para poder utilizar la el metodo loadObject
	public:
	    void loadObject(const char* filename);//hacemos referencia en el metodo contenido en la estructura
		std::vector<Vertice> v;	//lista donde se guardaran todos los vertices del archivo
        vector<Vertice> test;
		std::vector<Face> f; 
		std::vector<Vertice>vn;
		//void set_faces_verts(vector<Vertice> x);
		//vector <Vertice> get_faces_verts();
};

#endif //cerramos nuestra biblioteca