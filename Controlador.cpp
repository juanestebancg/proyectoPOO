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


void Controlador::impresion(){
	vector<Version> v1;
	vector<Subversion> v2;
	v1 = prog.getVersiones();
	for(int i = 0;i<v1.size();i++){
		cout<<v1[i].getNombre()<<endl;
		if(!(v1[i].getSubversiones().empty())){
			v2 = v1[i].getSubversiones();
			cout<<"sub ";
			for(int j = 0; j<v2.size();j++){
				cout<<v2[j].getID()<<" -> ";

			}
			cout<<endl;
		}
	}
}
void Controlador::crear(string temp,string s){

    archivo_control.open(s.c_str(), ios::out);
    if(archivo_control.fail()){
    	archivo_control.close();
    	crear(temp,s);
    	cout<<"error crear"<<endl;
    }
    anterior_version = "1.1";
	Version v1;
	prog.setOriginal(temp);
	prog.addVersion("1.1",v1);
	archivo_control.close();
}
vector<int> Controlador::split(string s){
	vector<int> posiciones;
	string temp;
	for(int i = 0; i<s.size();i++){
		if(s[i] != ' '){
			while(s[i] != ' ' && i<s.size()){
				temp.push_back(s[i]);
				i++;
			}
		}
		posiciones.push_back(atoi(temp.c_str()));
		temp.clear();
	}
	return posiciones;


}

bool Controlador::validacion(string s){
	int puntos = 0,aux = 0;
	string temp;
	vector<Version> v1 = prog.getVersiones();
	vector<Subversion> v2;
	for(int i = 0;i<s.size();i++){
		if(s[i] == '.'){
			puntos++;
		}
	}
	if(puntos== 1 ){
		for(int i = 0;i<v1.size();i++){
			if(v1[i].getNombre()==s){
				return true;
			}
		}
	}
	else if(puntos == 3){
		for(int i = 0;i<s.size() && aux < 2;i++){
			if(s[i] == '.')
				aux++;
			if(aux<2)
				temp.push_back(s[i]);
		}
		for(int i = 0;i<v1.size();i++){
			if(v1[i].getNombre() == temp){
				v2 = v1[i].getSubversiones();
				for(int j = 0; j<v2.size();j++){
					if(v2[j].getID() == s)
						return true;
				}
			}
		}


	}
	else if (puntos !=3 && puntos != 1){
		return true;
	}
	return false;
}

void Controlador::nuevoDelta(string s,string control){
	anterior_version = s;
	int puntos = 0,aux = 0,pot = 0;
	int RN = 0;
	bool band = true;
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
		ultima_version = nombre_newVersion;
	}

	else if(puntos == 1 && s!= versiones_temp[versiones_temp.size()-1].getNombre()){
		for(int i = 0;i<versiones_temp.size();i++){
			if(versiones_temp[i].getNombre() == s){
				version_temp = versiones_temp[i];
				nuevaSubver.setID(s+".1.1");
				string hola = nuevaSubver.getID();
				version_temp.addSubversion(nuevaSubver);
				versiones_temp[i] = version_temp;
				ultima_version = hola;
				break;
			}
		}

	}
	else if(puntos == 3){
		for(int i = 0;i<s.size() ;i++){
			if(s[i] == '.'){
				aux++;
			}
			if(aux < 2){
				nombre_newVersion.push_back(s[i]);
			}
			if(aux>=2){
				nombre_newSubver.push_back(s[i]);
			}

		}
		aux = 0;
		for(int i = 0;i<versiones_temp.size();i++){
			if(versiones_temp[i].getNombre() == nombre_newVersion){
				subver_temp = versiones_temp[i].getSubversiones();
				if(subver_temp[subver_temp.size()-1].getID() == s){
					for(int j = nombre_newSubver.size()-1 ; j>=0 && nombre_newSubver[j] != '.';j--){
						RN += (nombre_newSubver[j]-'0')*pow(10,pot);
						pot++;

					}
					for(int j = 0 ; j<nombre_newSubver.size() && aux !=2 ;j++){
						if(nombre_newSubver[j] == '.')
							aux++;
						nombre_newVersion += nombre_newSubver[j];
					}
					RN+=1;
					nombre_newVersion +=  to_string(RN);
					nuevaSubver.setID(nombre_newVersion);
					versiones_temp[i].addSubversion(nuevaSubver);
					ultima_version =  nombre_newVersion;
					break;
				}

			}
		}

	}
	else if(puntos==0){
		string auxs = versiones_temp[versiones_temp.size()-1].getNombre();
		int R = stoi(auxs.substr(0,auxs.find(".")));
		int N = stoi(s);
		if(N>R){
			R += 1;
			nombre_newVersion = to_string(R)+".1";
			nuevaVersion.setNombre(nombre_newVersion);
			versiones_temp.push_back(nuevaVersion);
			ultima_version =  nombre_newVersion;

		}

	}
	else if(puntos == 2 ){
		string temp,otro;
		int num,num2;
		for(int i = 0;i<s.size() ;i++){
				if(s[i] == '.'){
					aux++;
				}
				if(aux < 2){
					nombre_newVersion.push_back(s[i]);
				}
				if(aux == 2 && s[i] != '.'){
					nombre_newSubver.push_back(s[i]);
				}

		}
		aux = 0;

		for(int i = 0; i<versiones_temp.size() && band;i++){
			if(versiones_temp[i].getNombre() == nombre_newVersion){
				subver_temp = versiones_temp[i].getSubversiones();
				temp = subver_temp[subver_temp.size()-1].getID();
				for(int j = 0; j<temp.size() && band;j++){
					if(temp[j] == '.'){
						aux++;
					}
					if(aux==2){
						otro = temp.substr(j+1,temp.size()-1);
						otro = otro.substr(0,otro.find("."));
						 num =atoi(otro.c_str());
						 num2 = atoi(nombre_newSubver.c_str());
						if(num<num2 ){
							s += ".1";
							nuevaSubver.setID(s);
							subver_temp.push_back(nuevaSubver);
							versiones_temp[i].nuevaSubver(subver_temp);
							band = false;
							ultima_version = s;
							break;

						}


					}
				}

			}
		}
	}
	prog.actualizarVersiones(versiones_temp);


}

vector<string> Controlador::obtener(string control,string version){
	archivo_control.open(control.c_str(),ios::in);
    string linea;
    fstream archivo;
    archivo.open(prog.getOriginal().c_str(),ios::in);
    bool band = true;
    vector<string> cambios;
    vector<int> eliminadas;
    vector<int> agregadas;
    vector<string> copia;
    int cont = 1;
    if(archivo_control.fail() || archivo.fail()){
    	cout<<"error1"<<endl;
    	archivo.close();
    	archivo_control.close();
    	obtener(control,version);
    }
    if(version == "1.1"){
    	while(!archivo.eof()){
    		getline(archivo,linea);
    		copia.push_back(linea);
    	}
    }
    else{
		while(!archivo_control.eof() && band){
				getline(archivo_control,linea);
				if(linea == version){
					while(!archivo_control.eof()){


						getline(archivo_control,linea);
						if(linea=="_#"){
							   band = false;
							   archivo_control.close();
							   break;
						  }
						if(linea!="_#" && cont!=1 && cont!=2){
							cambios.push_back(linea);
						}
						if(cont==1){
							eliminadas = split(linea);

						}
						if(cont==2){
							agregadas = split(linea);

						}

						cont++;
					}

				}

			}
    }
    	if(cont==1){
    		archivo.close();
    		return copia;
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
     //for(int i = 0;i<copia.size();i++){
    	// cout<<copia[i]<<endl;
     //}

     archivo.close();
     archivo_control.close();
     return copia;

}

void Controlador::modificar(string s,vector<string> mod){
	archivo_control.open(s.c_str(),ios::app);
	fstream archivo;
	archivo.open(prog.getOriginal().c_str(),ios::in);
	if(archivo_control.fail() || archivo.fail()){
		archivo.close();
		archivo_control.close();
		cout<<"error modificar"<<endl;
		modificar(s,mod);
	}
	int i = 0,j;
	vector<string> cambios;
	vector<string> insertadas;
	vector<string> eliminadas;
	string linea;
	string temp;
	//getline(archivo,linea);
	while(!archivo.eof()){
		getline(archivo,linea);
		if(mod[i] != linea){
			temp = to_string(i+1);
			eliminadas.push_back(temp);
			cambios.push_back(mod[i]);
			insertadas.push_back(temp);
		}

		i++;
	}
	archivo.close();
	if(i<mod.size()){
		for( j = i;j<mod.size();j++){
			temp = to_string(j+1);
			insertadas.push_back(temp);
			cambios.push_back(mod[j]);
		}
	}


		archivo_control<<"\n";
		archivo_control<<ultima_version;
		archivo_control<<"\n";

		for(int i = 0; i<eliminadas.size();i++){
			archivo_control<<eliminadas[i];
			archivo_control<<" ";
		}
		archivo_control<<"\n";
		for(int i = 0; i<insertadas.size();i++){
			archivo_control<<insertadas[i];
			archivo_control<<" ";
		}
		archivo_control<<"\n";
		for(int i = 0;i<cambios.size();i++){
			archivo_control<<cambios[i];
			archivo_control<<"\n";
		}
		archivo_control<<"_#";

	archivo_control.close();

}
void Controlador::infoModificacion(string control){
	//esto no funciona bien, inverti ultima version con anterior version y se jode
	vector<string> v1 = obtener(control,ultima_version);
	vector<string> v2 = obtener(control,anterior_version);
	//las dos lineas de arriba
	for(int h = 0;h<v1.size();h++)
		cout<<v1[h]<<endl;
	cout<<"la otra"<<endl;
	for(int h = 0;h<v2.size();h++)
		cout<<v2[h]<<endl;

	cout<<"ant "<<anterior_version<<"ult "<<ultima_version<<endl;
	int tam,iguales = 0,eliminadas = 0,insertadas = 0,i,j;
	if(v1.size()>=v2.size()){
		tam = v2.size();
		for(i = 0;i<tam;i++){
			if(v1[i] != v2[i]){
				eliminadas++;
				insertadas++;
			}
			else{
				iguales++;
			}

		}
		insertadas += (v1.size()-tam);
	}
	else{
		tam = v1.size();
		for(i = 0; i<tam;i++){
			if(v1[i] != v2[i]){
				eliminadas++;
				insertadas++;
			}
			else{
				iguales++;
			}
		}
		insertadas += (v2.size()-tam);
	}

	cout<<"i "<<insertadas<<" e "<<eliminadas<<" ig "<<iguales<<endl;

}
Controlador::~Controlador(){

}



