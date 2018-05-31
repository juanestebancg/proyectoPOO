/*
 * Version.cpp
 *
 *  Created on: 20 may. 2018
 *      Author: juanes
 */


#include "Version.h"

Version::Version(){

}

void Version::setNombre(string s){
	ID_version = s;
}

void Version::addSubversion(Subversion subv){
	subversiones.push_back(subv);
}

vector<Subversion> Version::getSubversiones(){
	return subversiones;
}
string Version::getNombre(){
	return ID_version ;
}

void Version::nuevaSubver(vector<Subversion> subv){
	subversiones = subv;
}


Version::~Version(){

}
