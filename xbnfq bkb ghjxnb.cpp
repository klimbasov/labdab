// xbnfq bkb ghjxnb.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
введите строку символов, заменить каждый чётный символ '+'

*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
//---lab_1
class motosicle {
	
	int id;
	string name;
	float runlong;
	
public:

	motosicle(){
		cout << "this is call of deafult constructer" << endl;
	}
	
	motosicle(int id, string name, float runlong) :id(id), name(name), runlong(runlong) {
		cout << "object id : " << id << endl;
		cout << "object name : " << name << endl;
		cout << "object runlong : " << runlong << endl;
	}
	void show_runlong() {
		cout << "the runlong is: " << runlong << endl;
	}
	~motosicle(){}
	friend class oner;
	friend void show_all(const motosicle&);
};
class oner {
public:
	void set_runlong(motosicle &obj, float run_long) {
		if(run_long>=0)
		obj.runlong = run_long;
	}
};
void show_all(const motosicle& object) {
	cout << "id:" << object.id<<endl;
	cout << "name:" << object.name << endl;
	cout << "runlong:" << object.runlong << endl;
}
//---lab_2
/*class SOL {
	char* str=nullptr;


public:
	/*
	algoritm
	map  с ассоциативными ключами stl
	
	SOL(const char* str_in){
		str = new char[strlen(str_in)+1];
		strcpy(str, str_in);
	}
	SOL(const SOL& object) {

	}
	friend SOL& operator --(обёртка_чар_звёздочки& object);
	SOL& operator =( const SOL& str) {
		char* result_str = new char[strlen(str)+strlen(str_in)+1];
		strcpy(result_str, str);
		strcpy(result_str+strlen(str), str_in);
		delete str;
		str = result_str;
		return *this;
	}
	bool operator > (const обёртка_чар_звёздочки& object) {//(object.operator(object_1))<=> (object > obgect_1)
		if (strcmp(this->str, object.str) == -1)
			return true;
		else
			return false;
	}
	bool operator < (const обёртка_чар_звёздочки& object) {
		if (strcmp(this->str, object.str) == 1)
			return true;
		else
			return false;
	}
	int get_length(const обёртка_чар_звёздочки*& mass_object) {

	}
	SOL* sort_by_bubble(обёртка_чар_звёздочки*& mass_object) {

	}
	void show() {
		if (!this->str) {
			cout << "NULL";
			return;
		}
		cout << str << endl;
	}
	~SOL() {
		delete str;
	}
};*/




// obj+=str; obj = obj + str; obj+="скалка";
/*void BD(string str) {
	if (str.empty()) return;
	float length = str.length();
	
		cout << setfill('*') << setw(length * 1.5) << str;
	
}*/

int main()
{
	int counter = 0;
	motosicle object(15950, "gosha", 112000);
	oner Object_1;
	object.show_runlong();
	Object_1.set_runlong(object, 12);
	object.show_runlong();
	motosicle massive[] = { motosicle(2,"abc",1000),motosicle(5,"pos",1000) };
	while (counter!=2)
	{
		Object_1.set_runlong(massive[counter],1);
		++counter;
	}
	counter = 0;
	while (counter != 2)
	{
		show_all(massive[counter]);
		++counter;
	}
	/*motosicle mass[3] = { motosicle(5,"it"),motosicle(5,"he",102.3),motosicle(7,"us") };
	motosicle f;
	f.~motosicle();
	обёртка_чар_звёздочки object("pos");
	
	object.show();
	object += "oop";
	object.show();

	обёртка_чар_звёздочки object_1("xaosit");
	if (object < object_1) {
		cout << "true"<<endl;
	}
	else {
		cout << "false" << endl;
	}
	--object;
	object.show();*/
}