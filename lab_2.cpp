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
	motosicle(int id, string name) : id(id), name(name){
		cout << "this is call of deafult constructer" << endl;
	}
	void show_runlong() {
		cout << "the runlong is: " << runlong << endl;
	}
	~motosicle(){}
	friend class oner;
};
class oner {
public:
	void set_runlong(motosicle &obj, float run_long) {
		obj.runlong = run_long;
	}
};
int main()
{
	motosicle object(15950, "gosha", 112000);
	oner Object_1;
	object.show_runlong();
	Object_1.set_runlong(object, 12);
	object.show_runlong();

}
