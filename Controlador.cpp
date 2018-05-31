/*
 * Controlador.cpp
 *
 *  Created on: 22 may. 2018
 *      Author: juanes
 */

#include "Controlador.h"
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
Controlador::Controlador(){

}


void Controlador::crear(string temp,string s){
	prog.setOriginal(temp);
    archivo_control.open(s.c_str(), ios::trunc);
	Version v1;
	//prog.addVersion("1.1",v1);

}
vector<int> Controlador::split(string s){
	vector<int> posiciones;
	string temp;
	for(int i = 0; i<s.size();i++){
		if(s[i] != ' '){
			while(s[i] != ' '){
				temp.push_back(s[i]);
				i++;
			}
		}
		posiciones.push_back(atoi(temp.c_str()));
		temp.clear();
	}
	return posiciones;


}

void Controlador::nuevoDelta(string s){
	int puntos = 0,aux=0;
	double RN = 0.0;
	vector<Version> versiones_temp = prog.getVersiones();
	for(int i = 0;i<s.size();i++){
		if(s[i] == '.'){
			puntos++;
		}
	}

	if(puntos == 1 && s == versiones_temp[versiones_temp.size()-1]){
		for(int i = 0; i<s.size();i++){
			if(s[i]=='.'){
				while(i<s.size()){
					RN += ((s[i]-'0')*pow(10,aux));
					aux++;
					i++;
				}
			}
		}

	}
}

void Controlador::obtener(string control,string version){
    string linea;
    archivo_control.open(control.c_str(),ios::in);
    fstream archivo;
    archivo.open(prog.getOriginal().c_str(),ios::in);
    bool band = true;
    vector<string> cambios;
    vector<int> eliminadas;
    vector<int> agregadas;
    vector<string> copia;
    int cont = 1;
    while(!archivo_control.eof() && band){
            getline(archivo_control,linea);
            if(linea == version){
                while(!archivo_control.eof()){

                    getline(archivo_control,linea);
                    if(linea!="_#" && cont!=1 && cont!=2){
                        cambios.push_back(linea);
                    }
                    if(cont==1){
                        eliminadas = split(linea);

                    }
                    if(cont==2){
                        agregadas = split(linea);

                    }
                    if(linea=="_#"){
                        band = false;
                        break;
                    }
                    cont++;
                }

            }

        }

        int j = 1, cont_e = 0;
        while(!archivo.eof()){
        	getline(archivo,linea);
        	if(j==eliminadas[cont_e]){
        		cont_e++;
        	}
        	else{
        		copia.push_back(linea);
        	}
        	j++;
    	}


    for(int i = 0; i<agregadas.size();i++){
    	copia.insert(copia.begin()+(agregadas[i]-1),cambios[i]);

    }

//Vista
     for(int i = 0;i<copia.size();i++){
    	 cout<<copia[i]<<endl;
     }
}

Controlador::~Controlador(){

}



