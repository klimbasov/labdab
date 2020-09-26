//вариант 10

#include <iomanip>
#include <string>
#include<conio.h>
using namespace std;

class Clothes {
protected:
	string clothesName;
	string clothesInfo;
	Clothes(string Name, string Info) :clothesName(Name), clothesInfo(Info) {}

public:
	Clothes() {}

	void SetClothesName(string clothesName){
		this->clothesName = clothesName;
	}
	string GetClothesName() {
		return clothesName;
	}
	void SetClothesInfo(string clothesInfo) {
		this->clothesInfo= clothesInfo;
	}
	string SetClothesInfo() {
		return clothesInfo;
	}
	virtual void Thanks() = 0;
	virtual void Intro() = 0;
	virtual int MathClothesSize(int high, int chest, int weight) = 0;
	virtual ~Clothes() {
		cout << "By, little clothes object" << endl;
	}
	
};
class Light:public Clothes {
	int temperatureLimitHihg;
public:

	Light(string Name, string Info,int Temperature) :temperatureLimitHihg(Temperature),Clothes(Name,Info) {}
	virtual void Thanks() {
		cout << "Thanks for the purchasing. Let the summer will be cool" << endl;
	}
	virtual void Intro() {
		cout << "there is Light clothes object here" << endl;
	}
	virtual int MathClothesSize(int high, int chest, int weight) {
		return high * chest * 0.3 + weight * 0.1;
	}
	~Light() {
		cout << "By, little Light object" << endl;
	}
};
class Warm :public Clothes{
	int temperatureLimitLow;
public:
	Warm(string Name, string Info, int Temperature) :temperatureLimitLow(Temperature), Clothes(Name, Info) {}
	virtual void Thanks() {
		cout << "Thanks for the purchasing. Let the Winter will be snowy" << endl;
	}
	virtual void Intro() {
		cout << "there is Warm clothes object here" << endl;
	}
	virtual int MathClothesSize(int high, int chest, int weight) {
		return high * chest * 0.4 + weight * 0.2;
	}
	~Warm() {
		cout << "By, little Warm object" << endl;
	}
};
class Shirt:public Light {
	bool slevee;
	int size;
public:
	Shirt(string Name, string Info, int Temperature,bool isThereSleeve):slevee(isThereSleeve),Light(Name, Info, Temperature) {}
	
	~Shirt() {
		cout << "By, little Shirt object" << endl;
	}
};

int main()
{

	Clothes** assoortment = new Clothes* [3];
	Light* i;
	assoortment[0] = new Light("Tshirt", "They are pretty light", 40);
	assoortment[1] = new Warm("Coat", "They are pretty warm", -30);
	assoortment[2] = new Shirt("Serotonin", "This idea was stolen", 30,true);
	for (int i = 0; i != 3; i++) {
		assoortment[i]->Thanks();
		assoortment[i]->Intro();
		cout<< "your size is: "<<assoortment[i]->MathClothesSize(145,92,30);
	}
}
