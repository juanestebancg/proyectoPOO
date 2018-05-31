/*
 * Controlador.h
 *
 *  Created on: 22 may. 2018
 *      Author: juanes
 */

#ifndef CONTROLADOR_H_
#define CONTROLADOR_H_


#include <string>
#include "Programa.h"
#include "Vista.h"

class Controlador{
	private:
		Programa prog;
		fstream archivo_control;
	public:
		Controlador();
		void crear(string,string);
		vector<int> split(string);
		void obtener(string,string);
		void modificar(string);
		void nuevoDelta(string);

		~Controlador();
};


#endif /* CONTROLADOR_H_ */
