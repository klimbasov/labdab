//вариант 10


#include <iostream>
#include<conio.h>
using namespace std;


class clothes
{
protected:
	char* clothes_init_code;
public:
	clothes(){}
	clothes(char* CIC) :clothes_init_code(CIC) {}
	~clothes(){
		delete clothes_init_code;
	}
	void show() {
		cout << "CIC:" << clothes_init_code << endl;
	}
};
class overclothes : virtual protected clothes {
protected:
	char* oveclothes_init_code;
public:
	overclothes(){}
	overclothes(char* OIC): oveclothes_init_code(OIC) {}
	overclothes(char * OIC, char* CIC):oveclothes_init_code(OIC),clothes(CIC){	}
	~overclothes() {
		delete oveclothes_init_code;
	}
	void show() {
		cout << "OIC:" << oveclothes_init_code << endl;
		cout << "CIC:" << clothes_init_code << endl;
	}
};
class underwear : virtual protected clothes {
protected:
	char* underwear_init_code;
public:
	underwear(){}
	underwear(char* UIC) :underwear_init_code(UIC){}
	underwear(char* UIC, char* CIC):underwear_init_code(UIC),clothes(CIC) {}
	~underwear() {
		delete underwear_init_code;
	}
	void show() {
		cout << "UIC:" << underwear_init_code << endl;
		cout << "CIC:" << clothes_init_code << endl;
	}
};
class briefs :protected overclothes {
protected:
	char* briefs_init_code;
public:
	briefs() {}
	briefs(char* BIC, char* OIC) :briefs_init_code(BIC), overclothes(OIC) {}
	briefs(char* BIC, char* OIC, char* CIC) :briefs_init_code(BIC),overclothes(OIC,CIC){}
	~briefs() {
		delete briefs_init_code;
	}
	void show() {
		cout << "BIC:" << briefs_init_code << endl;
		cout << "OIC:" << oveclothes_init_code << endl;
		cout << "CIC:" << clothes_init_code << endl;
	}
};
class pants :protected underwear {
protected:
	char* pants_init_code;
public:
	pants(){}
	pants(char* PIC, char* UIC) :pants_init_code(PIC), underwear(UIC) {}
	pants(char* PIC, char* UIC, char* CIC) :pants_init_code(PIC),underwear(UIC,CIC){}
	~pants() {
		delete pants_init_code;
	}
	void show() {
		cout << "PIC:" << pants_init_code << endl;
		cout << "UIC:" << underwear_init_code << endl;
		cout << "CIC:" << clothes_init_code << endl;
	}
};
class boxing_truncs :protected pants, protected briefs {
protected:
	char* boxing_truncs_init_code;
public:
	boxing_truncs() {}
	boxing_truncs(char* BTIC, char* PIC, char* BIC, char* UIC, char* OIC, char* CIC) :boxing_truncs_init_code(BTIC), pants(PIC, UIC),briefs(BIC, OIC),clothes(CIC){
		//briefs_init_code = BIC;
	}
	~boxing_truncs() {
		delete boxing_truncs_init_code;
	}
	void show(){
		cout << "\nBTIC:" << boxing_truncs_init_code << endl;
		cout << "\nBIC:" << briefs_init_code<< endl;			// Да, как-то странно использовать управляющие символы вместе с манипуляторами,
		cout << "\nPIC:" << pants_init_code<< endl;			// и можно сделать всё чисто на одном или на втором.
		cout << "\nOIC:" << oveclothes_init_code<< endl;		// Но почему бы и нет, если так быстрее набирается? 
		cout << "\nUIC:" << underwear_init_code<< endl;			// С другой стороны встаёт вопрос: ведь этот коментарий набирается ещё дольше, тогда в чём смысл?
		cout << "\nCIC:" << clothes_init_code << endl;			// Но суть в том, что этот вопрос возник только после написания оного коментария.
																// вот такие вот пироги. 
	}
};

char* init_code_getCheck(const char*);
int main()
{

	boxing_truncs hottest_model_of_the_year(init_code_getCheck("\nset BTIC: "), init_code_getCheck("\nset PIC: "), init_code_getCheck("\nset BIC: "), init_code_getCheck("\nset UIC: "), init_code_getCheck("\nset OIC: "), init_code_getCheck("\nset CIC: "));
	hottest_model_of_the_year.show();
}

char* init_code_getCheck(const char* text_to_show) {
	char symbol, * code_str = nullptr;
	int length = 0;
	std::cout << text_to_show;
	while (symbol = _getch(), symbol != 13 || code_str)
	{
		if ((symbol >= '0' && symbol <= '9') || (symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z')) {
			std::cout << symbol;
			char* temp = new char[length + 2];
			temp[length + 1] = '\0';
			if (code_str)
				strcpy(temp, code_str);
			temp[length] = symbol;
			if (code_str)
				delete code_str;
			code_str = temp;
			temp = nullptr;
			++length;
		}
	}
	return code_str;
}
