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
	control.crear("prog1.txt","s_prog1.txt");
	vector<string> mod = {"from sys import *","import net","from string import *","","def main():","	# Imprime los numeros de 0 a 10 #",
			"	i = 0","	for i in range(10):","		print i","	return 0"};
	control.nuevoDelta("1.1","s_prog1.txt");
	control.modificar("s_prog1.txt",mod);
	control.infoModificacion("s_prog1.txt");

	//control.obtener("jeje.txt","1.2");


	/*
	control.nuevoDelta("1.2","jeje.txt");



	control.nuevoDelta("1.3","jeje.txt");
	control.obtener("jeje.txt","1.3");


	control.nuevoDelta("1.1","jeje.txt");
	control.obtener("jeje.txt","1.1");


	control.nuevoDelta("1.1.1.1","jeje.txt");
	control.obtener("jeje.txt","1.1.1.1");



	control.nuevoDelta("1.2","jeje.txt");
	control.obtener("jeje.txt","1.2");


	control.nuevoDelta("2","jeje.txt");
	control.obtener("jeje.txt","2");




	control.nuevoDelta("1.1.2","jeje.txt");
	control.obtener("jeje.txt","1.1.2");

	*/
	control.impresion();
	/*
	control.nuevoDelta("1.3","jeje.txt");
	control.obtener("jeje.txt","1.3");


	*/
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
