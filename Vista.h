/*
 * Vista.h
 *
 *  Created on: 22 may. 2018
 *      Author: juanes
 */

#ifndef VISTA_H_
#define VISTA_H_

#include <iostream>
#include <string>
#include "Controlador.h"

using namespace std;

class Vista{
protected:
	Controlador control;
	string nomb_control;
	bool bandera;
public:
	Vista();
	~Vista();
	void menuPrincipal();
	void option_Obtener();
	void option_Modificar();
	void option_Crear();
	void option_Diferencia();
	void validacion();
	void option_Historial();
	void info_Modificacion();

};



#endif /* VISTA_H_ */
