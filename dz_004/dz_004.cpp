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

class Product;

class Builder {	//abstract builder
public:
	virtual ~Builder(){}
	virtual void setBottle() = 0;
	virtual void setWater() = 0;
	virtual void setCap() = 0;
	virtual void setLabel() = 0;
	virtual Product* getProduct() = 0;
};

class Product {
	Bottle* bottle;
	Water* water;
	Cap* cap;
	Label* label;
public:
	Product() : bottle{ nullptr }, water{ nullptr }, cap{ nullptr }, label{ nullptr } {}
	void setBottle(Bottle* b) { bottle = b; }
	void setWater(Water* w) { water = w; }
	void setCap(Cap* c) { cap = c; }
	void setLabel(Label* l) { label = l; }
	void showProduct() {
		if (bottle)
			cout << bottle->info() << endl;
		if (water)
			cout << water->info() << endl;
		if (cap)
			cout << cap->info() << endl;
		if (label)
			cout << label->info() << endl;
		cout << endl;
	}
};

class CCBuilder : public Builder {
	Product* p;
public:
	CCBuilder() { Reset(); }
	~CCBuilder() { delete p; }
	void Reset() { p = new Product; }
	void setBottle() override { p->setBottle(new CCBottle); }
	void setWater() override { p->setWater(new CCWater); }
	void setCap() override { p->setCap(new CCCap); }
	void setLabel() override { p->setLabel(new CCLabel); }
	Product* getProduct() {
		Product* result = p;
		Reset();
		return result;
	}
};

class PCBuilder : public Builder {
	Product* p;
public:
	PCBuilder() { Reset(); }
	~PCBuilder() { delete p; }
	void Reset() { p = new Product; }
	void setBottle() override { p->setBottle(new PCBottle); }
	void setWater() override { p->setWater(new PCWater); }
	void setCap() override { p->setCap(new PCCap); }
	void setLabel() override { p->setLabel(new PCLabel); }
	Product* getProduct() {
		Product* result = p;
		Reset();
		return result;
	}
};

class TBuilder : public Builder {
	Product* p;
public:
	TBuilder() { Reset(); }
	~TBuilder() { delete p; }
	void Reset() { p = new Product; }
	void setBottle() override { p->setBottle(new TBottle); }
	void setWater() override { p->setWater(new TWater); }
	void setCap() override { p->setCap(new TCap); }
	void setLabel() override { p->setLabel(new TLabel); }
	Product* getProduct() {
		Product* result = p;
		Reset();
		return result;
	}
};

class Director {
	Builder* builder;
public:
	Director(Builder* b) { builder = b; }
	void setBuilder(Builder* b) { builder = b; }
	void buildSmall() {
		builder->setBottle();
		builder->setWater();
	}
	void buildFull() {
		builder->setBottle();
		builder->setWater();
		builder->setCap();
		builder->setLabel();
	}
};

//int main()
//{
//	SetConsoleCP(1251);
//	SetConsoleOutputCP(1251);
//	srand(time(NULL));
//	Builder* build = nullptr;
//	CCBuilder cola;
//	PCBuilder pepsi;
//	TBuilder tarhun;
//	int time = rand() % 3;
//	switch (time) {
//	case 0: build = &cola; break;
//	case 1: build = &pepsi; break;
//	case 2: build = &tarhun;
//	}
//	Director dir(build);
//	dir.buildFull();
//
//	Product* product = nullptr;
//	switch (time) {
//	case 0: product = cola.getProduct(); break;
//	case 1: product = pepsi.getProduct(); break;
//	case 2: product = tarhun.getProduct();
//	}
//	product->showProduct();
//	dir.buildSmall();
//	switch (time) {
//	case 0: product = cola.getProduct(); break;
//	case 1: product = pepsi.getProduct(); break;
//	case 2: product = tarhun.getProduct();
//	}
//	product->showProduct();
//}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	Builder* build = nullptr;
	int time = rand() % 3;
	switch (time) {
	case 0: build = new CCBuilder; break;
	case 1: build = new PCBuilder; break;
	case 2: build = new TBuilder;
	}
	Director dir(build);
	dir.buildFull();
	Product* product = build->getProduct();
	product->showProduct();
	dir.buildSmall();
	product = build->getProduct();
	product->showProduct();
	delete build;
	delete product;
}