#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;
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
	motosicle(motosicle&& object) {
		object.id = 0;
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

class SOL {
	char* str=nullptr;

	friend SOL* sort_by_bubble(SOL* mass_object, int length);
public:
	
	
	
	SOL(const char* str_in){
		str = new char[strlen(str_in)+1];
		strcpy(str, str_in);
//		cout << this->str << endl;
	}
	SOL(const SOL& object) {
		this->str = new char [strlen(object.str) + 1];
		strcpy(this->str, object.str);
//		cout << this->str << endl;
	}
	friend bool operator < (SOL& left,const SOL& right);
	friend bool operator > (SOL& left, const SOL& right);
	friend bool operator < (SOL& left, const char* right);
	friend bool operator > (SOL& left, const char* right);
	SOL& operator = (const SOL& object) {
		delete [] str;
		this->str = new char[strlen(object.str)+1];
		strcpy(this->str, object.str);
		return *this;
	}
	int SOL_cmp(const SOL& object_1, const SOL& object_2) {
		if (strcmp(object_1.str, object_2.str) > 0) return 1;
		if (strcmp(object_1.str, object_2.str) == 0) return 0;
		else
			return -1;
	}
	int get_length(const SOL& object) {
		return strlen(object.str);
	}
	char* get_str() {
		return this->str;
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
};
SOL* sort_by_bubble(SOL* mass_object, int length) {
	int counter = 0;
	while (length>=1)
	{
		counter = 0;
		while (counter+1 != length)
		{
			if (mass_object[counter] > mass_object[counter + 1]) {
				SOL temp = mass_object[counter];
				mass_object[counter] = mass_object[counter + 1];
				mass_object[counter + 1] = temp;
			}
			++counter;
		}
		--length;
	}
	return mass_object;
}

bool operator < (SOL& left, const SOL& right) {
	if (strcmp(left.str,right.str) == 1)
		return true;
	else
		return false;
}
bool operator > (SOL& left, const SOL& right) {
	if (strcmp(left.str, right.str) == -1)
		return true;
	else
		return false;
}
bool operator < (SOL& left, const char* right) {
	if (strcmp(left.str, right) == 1)
		return true;
	else
		return false;
}
bool operator > (SOL& left, const char* right) {
	if (strcmp(left.str, right) == -1)
		return true;
	else
		return false;
}


int main()
{

	
	
	SOL massive_object[] = { {"abc"},{"bcd"},{"rota"} };
	for (int i = 0; i != 3; i++) {
		cout << massive_object[i].get_str() << endl;
	}
	cout << "sotrProsess:" << endl;
	sort_by_bubble(massive_object, 3);
	cout << "exitValues:" << endl;
	for (int i = 0; i != 3; i++) {
		cout << massive_object[i].get_str() << endl;
	}
	
}
