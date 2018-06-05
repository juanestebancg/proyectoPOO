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

class verificar_version : public exception{
	public:
		const char* what() const throw(){
			return "Porfavor ingrese una version que se encuentre en el historial";
		}

};

class verificar_archivo : public exception{
	public:
		const char* what() const throw(){
			return "Porfavor ingrese un nombre valido para el archivo";
		}
};

class verificar_modificacion : public exception{
	public:
		const char* what() const throw(){
			return "Porfavor ingrese una version valida para modificar";
		}
};



void Vista::menuPrincipal(){
	cout<<"Bienvenido al controlador de versiones!"<<endl;
	string opcion;
	cout<<"Porfavor oprima un comando: (1) Obtener, (2) Modificar, (3) Crear, (4) Diferencia, (5) Historial, (6) Salir"<<endl;
	cin>>opcion;
	try{
		if( opcion != "1" && opcion != "2" && opcion!="3" && opcion != "4" && opcion != "5" && opcion != "6" ) throw verificar_entero();

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


bool Vista::validacion(string s){
	int puntos = 0,aux = 0;
	string temp;
	vector<Version> v1 = control.totalVersiones();
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
}



void Vista::option_Crear(){
	string param1,param2;
	cout<<"Ingrese nombre del archivo actual "<<endl;
	cin>>param1;
	fstream archivo;
	archivo.open(param1.c_str(),ios::in);
	try{
		if(archivo.fail()) throw verificar_archivo();
	}
	catch(exception &e){
		cout<<e.what()<<endl;
		archivo.close();
		option_Crear();
	}
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
	archivo.close();
	menuPrincipal();

}



void Vista::option_Obtener(){
	vector<string> copia;
	string param1 ;
	cout<<"Ingrese la version :"<<endl;
	cin>>param1;
	try{
		if(!validacion(param1) || param1.size()>7 || param1[1] != '.' || (param1.size()==7 && param1[3] != '.') || param1.size()==5 || param1.size() == 1) throw verificar_version();
	}
	catch(exception &e){
		cout<<e.what()<<endl;
		option_Obtener();
	}
	copia = control.obtener(nomb_control,param1);
	while(copia.empty()){
		copia = control.obtener(nomb_control,param1);
	}
	for(int i = 0;i <copia.size();i++)
			cout<<copia[i]<<endl;


	menuPrincipal();
}



void Vista::option_Modificar(){
	string tmp,param1;
	cout<<"ingrese la version a modificar"<<endl;
	cin>>param1;
	int cont = 0;
	vector<string> param2;
	bool flag = true;
	control.nuevoDelta(param1);
	try{
		if(!control.estadoDelta() || param1.size()>7) throw verificar_modificacion();

	}
	catch(exception &e){
		cout<<e.what()<<endl;
		option_Modificar();
	}
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


	control.modificar(nomb_control, param2);
	info_Modificacion();
}

void Vista::info_Modificacion(){
		vector<string> v1 = control.obtener(nomb_control,control.getUltima());
		while(v1.empty()){
			v1 = control.obtener(nomb_control,control.getUltima());
		}
		vector<string> v2 = control.obtener(nomb_control,control.getAnterior());
		while(v2.empty()){
			v2 = control.obtener(nomb_control,control.getAnterior());
		}

		int tam,iguales = 0,eliminadas = 0,insertadas = 0,i,j;
		for(i = 0;i<v1.size() && i<v2.size();i++){
			if(v1[i]==v2[i])
				iguales++;
			else{
				insertadas++;
				eliminadas++;
			}
		}
		if(i<v1.size()){
			for(j = i;j<v1.size();j++){
				insertadas++;
			}
		}

		if(i<v2.size()){
			for(j = i; j<v2.size();j++){
				eliminadas++;
			}
		}
		cout<<"la ultima version: "<<control.getUltima()<<endl;

		cout<<"insertadas "<<insertadas<<" eliminadas "<<eliminadas<<" iguales "<<iguales<<endl;
		menuPrincipal();
}


void Vista::option_Diferencia(){
	string v1,v2;
	cout<<"Porfavor ingrese la version 1"<<endl;
	cin>>v1;
	cout<<"Porfavor ingresa la version 2"<<endl;
	cin>>v2;

	try{
		if( v1.size()>7 ||
				 v2.size()>7 || (v1.size()==7 && v1[3] != '.') ||
				 (v2.size()==7 && v2[3] != '.')|| v1.size()==5 || v1.size() == 1 || v2.size() ==1 || v2.size()==5|| !validacion(v1) || !validacion(v2)) throw verificar_version();
	}
	catch(exception &e){
		cout<<e.what()<<endl;
		option_Diferencia();
	}
	vector<string> vec1 = control.obtener(nomb_control,v1);
	while(vec1.empty()){
		cout<<"while1"<<endl;
		vec1 = control.obtener(nomb_control,v1);
	}
	vector<string> vec2 = control.obtener(nomb_control,v2);
	while(vec2.empty()){
		cout<<"while2"<<endl;
		vec2 = control.obtener(nomb_control,v2);
	}
	cout<<"llego"<<endl;
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
					eliminadas.push_back(vec1[j]);
				}
			}
			if(i == vec2.size() || i == vec1.size()){
				cout<<intervaloe_nc1<<"-"<<intervaloe_nc2-1<<"e"<<endl;
				for(int j = 0;j<eliminadas.size();j++){
					cout<<"<"<<eliminadas[j]<<endl;
				}
			}
			else{
				cout<<intervaloe_nc1<<"-"<<intervaloe_nc2-1<<"e"<<i+1<<endl;
				for(int j = 0;j<eliminadas.size();j++){
					cout<<"<"<<eliminadas[j]<<endl;
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
