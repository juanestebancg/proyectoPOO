/*
 * Programa.h
 *
 *  Created on: 20 may. 2018
 *      Author: juanes
 */

#ifndef PROGRAMA_H_
#define PROGRAMA_H_

#include "Version.h"
#include <map>
#include <vector>
#include <fstream>
class Programa{
	private:
		vector<Version> Versiones;
		string archivo_original;


	public:
		Programa();
		vector<Version> getVersiones();
		string getOriginal();
		void addVersion(string,Version);
		void setOriginal(string);
		void actualizarVersiones(vector<Version>);
		~Programa();


};


#endif /* PROGRAMA_H_ */
