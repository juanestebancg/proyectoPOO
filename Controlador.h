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
		string ultima_version;
		string anterior_version;
	public:
		Controlador();
		void crear(string,string);
		vector<int> split(string);
		vector<string> obtener(string,string);
		void modificar(string,vector<string>);
		void nuevoDelta(string,string);
		void impresion();
		bool validacion(string);
		void infoModificacion(string);

		~Controlador();
};


#endif /* CONTROLADOR_H_ */
