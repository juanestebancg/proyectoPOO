/*
 * Main.cpp
 *
 *  Created on: 20 may. 2018
 *      Author: juanes
 */

#include "Controlador.h"
#include <iostream>
#include <cstdlib>

using namespace std;

int main(){
	Controlador control;
	control.crear("prog1.txt","hhh.txt");
	control.obtener("jeje.txt","1.2");
	control.nuevoDelta("2");

	return 0;

}
