/*
 * Vista.cpp
 *
 *  Created on: 2 jun. 2018
 *      Author: juanes
 */



#include "Vista.h"
Vista::Vista(){
	bandera = false;

}

Vista::~Vista(){

}

class verificar_entero : public exception{
	public:
		const char* what() const throw(){
			return "Porfavor ingrese un entero del 1 al 5";
		}

};



void Vista::menuPrincipal(){
	cout<<"Bienvenido al controlador de versiones!"<<endl;
	string opcion;
	cout<<"Porfavor oprima un comando: (1) Obtener, (2) Modificar, (3) Crear, (4) Diferencia, (5) Historial, (6) Salir"<<endl;
	cin>>opcion;
	try{
		if( opcion != "1" && opcion != "2" && opcion!="3" && opcion != "4" && opcion != "5"  ) throw verificar_entero();

		}
		catch(exception& e){
			cout<<e.what()<<endl;
			menuPrincipal();
		}

	if(opcion=="3")
			option_Crear();

	if(!bandera){
		cout<<"porfavor cree un programa primero"<<endl;
		menuPrincipal();

	}
	if(opcion=="1" && bandera)
		option_Obtener();
	if(opcion=="2" && bandera)
		option_Modificar();

	if(opcion=="4" && bandera)
		option_Diferencia();
	if(opcion == "5" && bandera)
		option_Historial();


}



void Vista::option_Crear(){
	string param1,param2;
	cout<<"Ingrese nombre del archivo actual "<<endl;
	cin>>param1;
	param2 = "s_" + param1;
	nomb_control = param2;
	control.crear(param1,param2);
	Programa temp;
	temp = control.infoPrograma();
	if(!temp.getVersiones().empty()){
		cout<<"creacion exitosa"<<endl;
		bandera = true;
	}
	else{
		cout<<"error por favor vuelva a intentarlo"<<endl;
	}
	menuPrincipal();

}



void Vista::option_Obtener(){
	vector<string> copia;
	string param1 ;
	cout<<"Ingrese la version :"<<endl;
	cin>>param1;
	if((param1.size()==3 && param1[1] == '.')
			|| (param1.size()==7 && param1[1] == '.' && param1[3] == '.' && param1[5] == '.')){
		copia = control.obtener(nomb_control,param1);
		while(copia.empty()){
			copia = control.obtener(nomb_control,param1);
		}
		for(int i = 0;i <copia.size();i++)
				cout<<copia[i]<<endl;
	}
	else{
		cout<<"ingrese una version existente"<<endl;
		option_Obtener();
	}
	menuPrincipal();
}

void Vista::option_Modificar(){
	vector<string> mod = {"from sys import *","import net","from string import *","","def main():","	# Imprime los numeros de 0 a 10 #",
				"	i = 0","	for i in range(10):","		print i","	return 0"};
	string tmp,param1;
	cout<<"ingrese la version a modificar"<<endl;
	cin>>param1;
	int cont = 0;
	vector<string> param2;
	bool flag = true;
	cout<<"Ingrese la lista: [Parar (x)]"<<endl;
	while(flag){
		getline(cin,tmp);
		if(tmp!="x"){
			if(cont!=0){
				param2.push_back(tmp);
			}
			cont++;

		}else{
			flag = false;
		}
	}

	control.nuevoDelta(param1);
	control.modificar(nomb_control, param2);
	info_Modificacion();
}

void Vista::info_Modificacion(){
	//esto no funciona bien, inverti ultima version con anterior version y se jode
		vector<string> v1 = control.obtener(nomb_control,control.getUltima());
		while(v1.empty()){
			v1 = control.obtener(nomb_control,control.getUltima());
		}
		vector<string> v2 = control.obtener(nomb_control,control.getAnterior());
		while(v2.empty()){
			v2 = control.obtener(nomb_control,control.getAnterior());
		}
		//las dos lineas de arriba


		cout<<"ant "<<control.getAnterior()<<" ult "<<control.getUltima()<<endl;
		int tam,iguales = 0,eliminadas = 0,insertadas = 0,i,j;
		if(v1.size()>=v2.size()){
			for(i = 0;i<v2.size();i++){
				if(v2[i] != v1[i]){
					insertadas++;
					eliminadas++;
				}
				else{
					iguales++;
				}
			}
			for(j = i;j<v1.size();j++){
				insertadas++;
			}
		}
		else{
			for(i = 0;i<v1.size();i++){
				if(v1[i] != v2[i]){
					insertadas++;
					eliminadas++;
				}
				else{
					iguales++;
				}
			}
			for(j = i; j<v2.size();j++){
				insertadas++;
			}
		}
		cout<<"la ultima version: "<<control.getUltima()<<endl;

		cout<<"insertadas "<<insertadas<<" eliminadas "<<eliminadas<<" iguales "<<iguales<<endl;
		menuPrincipal();
}


void Vista::option_Diferencia(){
	cout<<"entro1"<<endl;
	vector<string> vec1 = control.obtener(nomb_control,"1.1");
	while(vec1.empty()){
		vec1 = control.obtener(nomb_control,"1.1");
	}
	vector<string> vec2 = control.obtener(nomb_control,"1.2");
	while(vec2.empty()){
		vec2 = control.obtener(nomb_control,"1.2");
	}
	cout<<"1.1"<<endl;
	for(int i = 0; i < vec1.size(); i++){
		cout<<vec1[i]<<endl;
	}
	cout<<"1.2"<<endl;
	for (int i = 0; i < vec2.size(); ++i) {
		cout<<vec2[i]<<endl;
	}
	cout<<"entro2"<<endl;
	string temp,rel;
	vector<string> eliminadas;
	vector<string> insertadas;
	int intervaloe_nc1 = 0, intervaloe_nc2 = 1,intervaloe_nf1 = 1,intervalo_nf2 = 1;
	int intervaloi_nc1 = 1,intervaloi_nc2 = 1,intervaloi_nf1 = 1,intervaloi_nf2 = 1;
	for(int i = 0; i < vec2.size();i++ ){
		if(vec2[i] != vec1[i]){
			intervaloi_nc1 = i;
			intervaloi_nf1 = i+1;
			intervaloi_nf2 = intervaloi_nf1;
			intervaloe_nc1 = i+1;
			intervaloe_nc2 = intervaloe_nc1;

			while(vec2[i] != vec1[i] && i<vec2.size() && i <vec1.size()){
				intervaloe_nc2++;
				intervaloi_nf2++;
				eliminadas.push_back(vec1[i]);

				insertadas.push_back(vec2[i]);

				i++;

			}
			if(i<vec1.size() && vec2.size()<vec1.size()){
				for(int j = i;j<vec1.size();j++){
					intervaloe_nc2++;
					eliminadas.push_back(vec1[i]);
				}
			}
			if(i == vec2.size() || i == vec1.size()){
				cout<<intervaloe_nc1<<"-"<<intervaloe_nc2-1<<"e"<<endl;
				for(int j = 0;j<eliminadas.size();j++){
					cout<<"<"<<eliminadas[j]<<endl;
					rel+=eliminadas[j]+"\n";
				}
			}
			else{
				cout<<intervaloe_nc1<<"-"<<intervaloe_nc2-1<<"e"<<i+1<<endl;
				for(int j = 0;j<eliminadas.size();j++){
					cout<<"<"<<eliminadas[j]<<endl;
					rel+=eliminadas[j]+"\n";
				}
			}
			if(i >= vec1.size()){
				for(int j = i;j<vec2.size();j++){
					intervaloi_nf2++;
					insertadas.push_back(vec2[j]);
					i++;
				}
			}

				cout<<intervaloi_nc1<<"i"<<intervaloi_nf1<<"-"<<intervaloi_nf2-1<<endl;
				for(int j = 0;j<insertadas.size();j++){
					cout<<">"<<insertadas[j]<<endl;
					rel+=insertadas[j]+"\n";
				}


		}
		insertadas.clear();
		eliminadas.clear();

	}
	menuPrincipal();

}

void Vista::option_Historial(){
	/* este metodo imprime tod el historial de versiones
	 *
	 */
	vector<Version> v1;
	vector<Subversion> v2;
	v1 = control.totalVersiones();
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
	menuPrincipal();

}
