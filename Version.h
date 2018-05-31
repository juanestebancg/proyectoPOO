/*
 * Version.h
 *
 *  Created on: 20 may. 2018
 *      Author: juanes
 */

#ifndef VERSION_H_
#define VERSION_H_

#include <iostream>
#include <string>
#include <vector>

#include "Subversion.h"

using namespace std;

class Version{
	private:
		string ID_version;
		vector<Subversion> subversiones;
	public:
		Version();
		void setNombre(string);
		void addSubversion(Subversion);
		vector<Subversion> getSubversiones();
		void nuevaSubver(vector<Subversion>);
		string getNombre();
		~Version();

};



#endif /* VERSION_H_ */
