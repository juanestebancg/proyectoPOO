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
	prog.addVersion("1.1",v1);

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
	int puntos = 0,aux = 0,pot = 0;
	int RN = 0;
	string nombre_newVersion, nombre_newSubver;
	vector<Version> versiones_temp = prog.getVersiones();
	vector<Subversion> subver_temp;
	Version nuevaVersion,version_temp;
	Subversion nuevaSubver;
	for(int i = 0;i<s.size();i++){
		if(s[i] == '.'){
			puntos++;
		}
	}

	if(puntos == 1 && s == versiones_temp[versiones_temp.size()-1].getNombre()){
		for(int i = s.size()-1;i>=0;i--){
			if(s[i]=='.'){
				nombre_newVersion = s.substr(0,i+1);
				break;
			}
			RN += ((s[i]-'0')*pow(10,pot));
			pot++;
		}
		RN += 1;
		nombre_newVersion += to_string(RN);
		nuevaVersion.setNombre(nombre_newVersion);
		versiones_temp.push_back(nuevaVersion);

	}

	if(puntos == 1 && s!= versiones_temp[versiones_temp.size()-1].getNombre()){
		for(int i = 0;i<versiones_temp.size();i++){
			if(versiones_temp[i].getNombre() == s){
				version_temp = versiones_temp[i];
				nuevaSubver.setID(s+".1.1");
				version_temp.addSubversion(nuevaSubver);
				versiones_temp[i] = version_temp;
				break;
			}
		}
	}
	if(puntos == 3){
		for(int i = 0;i<s.size() ;i++){
			if(s[i] == '.'){
				aux++;
			}
			if(aux < 2){
				nombre_newVersion.push_back(s[i]);
			}
			if(aux>3){
				nombre_newSubver.push_back(s[i]);
			}

		}
		for(int i = 0;i<versiones_temp.size();i++){
			if(versiones_temp[i].getNombre() == nombre_newVersion){
				subver_temp = versiones_temp[i].getSubversiones();
				if(subver_temp[subver_temp.size()-1].getID() == s){
					for(int j = nombre_newSubver.size()-1; j>=0;j--){
						RN += (nombre_newSubver[j]-'0')*pow(10,pot);
						pot++;
					}
					RN+=1;
					nombre_newVersion += "." + to_string(RN);
					nuevaSubver.setID(nombre_newVersion);
					versiones_temp[i].addSubversion(nuevaSubver);
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



