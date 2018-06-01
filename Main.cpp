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
	//control.obtener("jeje.txt","1.2");
	control.nuevoDelta("1.2","jeje.txt");


	control.nuevoDelta("1.3","jeje.txt");
	control.obtener("jeje.txt","1.3");

	control.nuevoDelta("1.1","jeje.txt");
	control.obtener("jeje.txt","1.1");

	control.nuevoDelta("1.1.1.1","jeje.txt");
	control.obtener("jeje.txt","1.1.1.1");

	control.nuevoDelta("1.2","jeje.txt");
	control.obtener("jeje.txt","1.2");

	control.nuevoDelta("1.3","jeje.txt");
	control.obtener("jeje.txt","1.3");

	control.impresion();

	/*
	control.nuevoDelta("1.4");
	control.nuevoDelta("1.5");
	control.nuevoDelta("1.1");
	control.nuevoDelta("1.1.1.1");
	control.nuevoDelta("1.4.1.1");
	control.nuevoDelta("1.4.1.2");
	control.nuevoDelta("1.4.1.3");
	control.nuevoDelta("2");
	control.nuevoDelta("3");
	control.nuevoDelta("3.1");
	control.nuevoDelta("1.1.2");
	control.nuevoDelta("1.4.2");


	*/

	return 0;

}
