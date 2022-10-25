#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

class Bottle {  //abstract product
public:
	virtual string info() = 0;
};

class CCBottle : public Bottle {	//concrete product
public:
	string info() override { return "Coca-Cola bottle"; }
};

class PCBottle : public Bottle {	//concrete product
public:
	string info() override { return "Pepsi-Cola bottle"; }
};

class TBottle : public Bottle {	//concrete product
public:
	string info() override { return "Tarhun bottle"; }
};

class Water {   //abstract product
public:
	virtual string info() = 0;
};

class CCWater : public Water {	//concrete product
public:
	string info() { return "Coca-Cola water"; }
};

class PCWater : public Water {	//concrete product
public:
	string info() { return "Pepsi-Cola water"; }
};

class TWater : public Water {	//concrete product
public:
	string info() { return "Tarhun water"; }
};

class Cap {	//abstract product
public:
	virtual string info() = 0;
};

class CCCap : public Cap {	//concrete product
public:
	string info() override { return "Coca-Cola cap"; }
};

class PCCap : public Cap {	//concrete product
public:
	string info() override { return "Pepsi-Cola cap"; }
};

class TCap : public Cap {	//concrete product
public:
	string info() override { return "Tarhun cap"; }
};

class Label {	//abstract product
public:
	virtual string info() = 0;
};

class CCLabel : public Label {	//concrete product
public:
	string info() override { return "Coca-Cola label"; }
};

class PCLabel : public Label {	//concrete product
public:
	string info() override { return "Pepsi-Cola label"; }
};

class TLabel : public Label {	//concrete product
public:
	string info() override { return "Tarhun label"; }
};

class Brand {   //abstract factory
public:
	virtual Bottle* getBottle() = 0;
	virtual Water* getWater() = 0;
	virtual Cap* getCap() = 0;
	virtual Label* getLabel() = 0;
};

class CocaCola : public Brand {	//concrete factory
public:
	Bottle* getBottle() override { return new CCBottle(); }
	Water* getWater() override { return new CCWater(); }
	Cap* getCap() override { return new CCCap(); }
	Label* getLabel() override { return new CCLabel(); }
};

class Pepsi : public Brand {	//concrete factory
public:
	Bottle* getBottle() override { return new PCBottle(); }
	Water* getWater() override { return new PCWater(); }
	Cap* getCap() override { return new PCCap(); }
	Label* getLabel() override { return new PCLabel(); }
};

class Tarhun : public Brand {	//concrete factory
public:
	Bottle* getBottle() override { return new TBottle(); }
	Water* getWater() override { return new TWater(); }
	Cap* getCap() override { return new TCap(); }
	Label* getLabel() override { return new TLabel(); }
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	Brand* firma = nullptr;
	CocaCola* coke = new CocaCola;
	Pepsi* pepsi = new Pepsi;
	Tarhun* tarhun = new Tarhun;
	int time = rand() % 3;
	switch (time) {
	case 0: firma = coke; break;
	case 1: firma = pepsi; break;
	case 2: firma = tarhun;
	}
	cout << firma->getBottle()->info() << endl;
	cout << firma->getCap()->info() << endl;
	cout << firma->getLabel()->info() << endl;
	cout << firma->getWater()->info() << endl;
	
}