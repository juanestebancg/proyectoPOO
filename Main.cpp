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

	string s = "1.2";
	int val = s[2]-'0';
	cout<<val+10;
	return 0;

}
