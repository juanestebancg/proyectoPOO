/*
 * Programa.cpp
 *
 *  Created on: 20 may. 2018
 *      Author: juanes
 */


#include "Programa.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cstdio>
using namespace std;

Programa::Programa(){

}


vector<Version> Programa::getVersiones(){
	return Versiones;
}

string Programa::getOriginal(){
	return archivo_original;
}


void Programa::setOriginal(string s){
	archivo_original = s;
}

void Programa::addVersion(string s,Version v){
	v.setNombre(s);
	Versiones.push_back(v);
}
void Programa::actualizarVersiones(vector<Version> v){
	Versiones = v;
}

Programa::~Programa(){

}
