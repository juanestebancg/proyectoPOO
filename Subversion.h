/*
 * Subversion.h
 *
 *  Created on: 22 may. 2018
 *      Author: juanes
 */

#ifndef SUBVERSION_H_
#define SUBVERSION_H_

#include <iostream>
#include <string>

using namespace std;

class Subversion{
	private:
		string ID_Subversion;
	public:
		Subversion();
		string getID();
		void setID(string s);
		~Subversion();
};



#endif /* SUBVERSION_H_ */
