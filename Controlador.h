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

class Controlador{
	private:
		Programa prog;
		fstream archivo_control;
		string ultima_version;
		string anterior_version;
		bool delta_creado;
	public:
		Controlador();
		void crear(string,string);
		vector<int> split(string);
		vector<string> obtener(string,string);
		void modificar(string,vector<string>);
		void nuevoDelta(string);
		void impresion();
		string diferencia(string,string,string);
		Programa infoPrograma();
		string getUltima();
		string getAnterior();
		vector<Version> totalVersiones();
		bool estadoDelta();

		~Controlador();
};


#endif /* CONTROLADOR_H_ */
