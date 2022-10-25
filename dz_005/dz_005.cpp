// Max Likarenko Homework 005
/*
Додати клас MyTank - з методами/функціями, такі як :
● ChargeTheCannon - Зарядити Гармату
● Aim - Прицілитись,
● Shot - Постріл з Гармати
● при потребі додати інші…
Створити адаптер - Tank наслідуваного від інтерфейсу/класу
Weapon, реалізувати всі потрібні методи для класу Tank та метод
Атаки - Atack() що виконує послідовно 3 методи класу MyTank:
● ChargeTheCannon()
● Aim - Прицілитись()
● Shot()
Додати танк гравцю та зробити кілька пострілів з танку по
орках. Пересвідчитись, що орки знищені!
*/

#include <iostream>
#include <Windows.h>
using namespace std;
enum wtype { cold, fire, unknown };

class Weapon
{
protected:
	string m_name;
	string m_model;
	wtype m_type;
public:
	Weapon(string model = "", string name = "Unknown Weapon", wtype type = unknown) :
		m_name{ name }, m_model{ model }, m_type{ type } {}

	virtual ~Weapon() {} //= 0;

	virtual void Atack() = 0;

	virtual void ShowInfo() final {
		cout << "Info about Weapon !" << endl;

		Print();
	}

	virtual void Print() {
		cout << getName() << (m_model.empty() ? "" : " " + m_model);
	}

	virtual string& getName() final { return m_name; };
	virtual bool isAvailableWeapon() = 0;
	wtype getType() { return m_type; }
	virtual int getBullets() { return 0; }
};

class ColdWeapon : public Weapon {
public:
	ColdWeapon(string model = "", string name = "Unknown Weapon", wtype type = cold) :
		Weapon(model, name, type) {}
	bool isAvailableWeapon() override final { return true; }
	void Print() {
		Weapon::Print();
		cout << endl;
	}
};

class FireWeapon : public Weapon {
	int constBullet;
protected:
	int countBullets;
public:
	FireWeapon(string model = "", string name = "Unknown Weapon", int countBullet = 0) :
		Weapon(model, name, fire), countBullets{ countBullet }, constBullet{ countBullet } {}
	bool isAvailableWeapon() override final { return countBullets > 0; }
	void addBullet() { countBullets += constBullet; }
	int getBullets() override { return countBullets; }
	void Print() {
		Weapon::Print();
		cout << " " << getBullets() << endl;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////
class MyTank {
public:
	void ChargeTheCannon() { cout << "\nГармата заряджена\n"; }
	void Aim() { cout << "Ціль взята\n"; }
	void Shot() { cout << "BOOM!\n"; }
	void Check() { cout << "Ціль знищена\n\n"; }
};

class Tank : public MyTank, public FireWeapon {
public:
	Tank(string model = "", int countBullet = 5) : FireWeapon(model, "Tank", countBullet) {}
	void Atack() override {
		ChargeTheCannon();
		Aim();
		Shot();
		Check();
		countBullets--;
	}
};
/////////////////////////////////////////////////////////////////////////////////////////////

class Knife : public ColdWeapon {
public:
	Knife(string model = "") : ColdWeapon(model, "Knife") {}
	void Atack() override {
		cout << "Atack with a Knife !" << endl;
	}
};

class Machete : public ColdWeapon {
public:
	Machete(string model = "") : ColdWeapon(model, "Machete") {}
	void Atack() override {
		cout << "Atack with a Machete !" << endl;
	}
};

class Gun : public FireWeapon {
public:
	Gun(string model = "", int countBullet = 10) : FireWeapon(model, "Gun", countBullet) {}
	void Atack() override {
		cout << "Atack with a Gun !" << endl;
		countBullets--;
	}
};

class P90 : public FireWeapon {
public:
	P90(string model = "", int countBullet = 50) : FireWeapon(model, "P90", countBullet) {}
	void Atack() override {
		cout << "Atack with a P90 !" << endl;
		countBullets -= 5;
	}
};

class AK47 : public FireWeapon {
public:
	AK47(string model = "", int countBullet = 30) : FireWeapon(model, "AK47", countBullet) {}
	void Atack() override {
		cout << "Atack with a AK47 !" << endl;
		countBullets -= 5;
	}
};

class Granata : public FireWeapon {
public:
	Granata(string model = "", int countBullet = 1) : FireWeapon(model, "Granata", countBullet) {}
	void Atack() override {
		cout << "Atack with a Granata !" << endl;
		countBullets--;
	}
};

typedef Weapon* TpWeapon;
class Player {
	int m_maxWeaponCount = 4;
	TpWeapon* m_pWeaponSt = nullptr;
	int m_activeWeapon = 0;
public:
	Player() {
		m_pWeaponSt = new TpWeapon[m_maxWeaponCount]{ NULL };
	}

	~Player() {
		delete[] m_pWeaponSt;
	}

	void IncreaseWaponsSize(int addCount = 1) {
		int maxWeaponCountTmp = m_maxWeaponCount + addCount;
		TpWeapon* pWeaponStTmp = new TpWeapon[maxWeaponCountTmp]{ NULL };
		for (int i = 0; i < m_maxWeaponCount; i++)
			pWeaponStTmp[i] = m_pWeaponSt[i];
		if (m_pWeaponSt != nullptr)
			delete[] m_pWeaponSt;
		m_maxWeaponCount = maxWeaponCountTmp;
		m_pWeaponSt = pWeaponStTmp;
		cout << "Weapons increased to " << m_maxWeaponCount << endl;
	}

	bool Add(Weapon* pWeapon, int pos = 0) //1-4
	{
		if (pWeapon == NULL)
			return false;
		pos--;
		if (pos < 0) {
			if (pos == -1 && pWeapon->getType() == fire) {
				FireWeapon** tmp = (FireWeapon**)m_pWeaponSt;
				for (int i = 0; i < m_maxWeaponCount; i++)
					if (tmp[i]->getName() == pWeapon->getName()) {
						tmp[i]->addBullet();
						break;
					}
				return true;
			}
			for (int i = 0; i < m_maxWeaponCount; i++) {
				if (m_pWeaponSt[i] == NULL) {
					pos = i;
					break;
				}
			}
		}
		if (pos >= 0 && pos < m_maxWeaponCount) {
			Weapon* pWeaponTmp = m_pWeaponSt[pos];
			if (pWeaponTmp != NULL)
				delete pWeaponTmp;
			m_pWeaponSt[pos] = pWeapon;
			return true;
		}
		return false;
	}

	void Attack(int pos = 0) //1-4
	{
		pos--;
		Weapon* pWeapon = NULL;
		if (pos >= 0 && pos < m_maxWeaponCount)
			pWeapon = m_pWeaponSt[pos];
		if (pWeapon == NULL) {
			FireWeapon* fpWeapon = nullptr;
			for (int i = 0; i < m_maxWeaponCount; i++) {
				fpWeapon = dynamic_cast <FireWeapon*> (m_pWeaponSt[i]);
				if (fpWeapon) {
					pos = i;
					pWeapon = fpWeapon;
					break;
				}
			}
			if (fpWeapon && !pWeapon->isAvailableWeapon())
				for (int i = 0; i < m_maxWeaponCount; i++) {
					ColdWeapon* cpWeapon = dynamic_cast <ColdWeapon*> (m_pWeaponSt[i]);
					if (cpWeapon)
						pWeapon = cpWeapon;
					break;
				}
		}
		if (pWeapon != NULL && pWeapon->isAvailableWeapon()) {
			pWeapon->Atack();
			if (pWeapon->getBullets() == 0 && pWeapon->getType() == fire)
				cout << (pWeapon->getName() == "Granata" ? "No " : "No bullets in ") << pWeapon->getName() << endl;
		}
		else {
			cout << "Attack with hands :((( !" << endl;
		}
	}

	void ShowAllWeapons()
	{
		bool showTitle = false;
		for (int i = 0; i < m_maxWeaponCount; i++) {
			Weapon* pWeapon = m_pWeaponSt[i];
			if (pWeapon != NULL) {
				if (!showTitle) {
					cout << "\n========== Weapons ==========" << endl;
					showTitle = true;
				}
				pWeapon->Print();
			}
		}
		if (showTitle)
			cout << "=============================" << endl << endl;
	}

	void Remove(int pos) //1-4
	{
		pos--;
		if (pos >= 0 && pos < m_maxWeaponCount)
		{
			Weapon* pWeaponTmp = m_pWeaponSt[pos];
			if (pWeaponTmp != NULL) {
				delete pWeaponTmp;
				m_pWeaponSt[pos] = NULL;
			}
		}
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Player pl1;
	pl1.Add(new Machete(), 1);
	pl1.Add(new Knife(), 2);
	pl1.Add(new Gun("", 5), 3);
	pl1.Add(new Granata("", 2), 4);
	pl1.Add(new Tank("T-28"), 1);
	pl1.ShowAllWeapons();
	pl1.Attack();
	pl1.Attack();
	pl1.Attack();
	pl1.Attack();
	pl1.ShowAllWeapons();
}