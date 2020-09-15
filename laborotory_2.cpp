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
}
