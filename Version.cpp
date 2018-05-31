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

string Version::getNombre(){
	return ID_version ;
}


Version::~Version(){

}
