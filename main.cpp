#include <iostream>

int main() {
	int mrówka = 100;
	cout << "Mrowisko sim 3000" << endl;
	for (int i = 0; i < 100; i++)
	{
		spawn_mrówencja();
	}
}

struct mruwa {
	char type;		//Typ mruwy
	int hp;			//Aktualne HP danej mruwy
	int maxhp;		//Maksymalne HP tej mruwy, za³ó¿my ¿e mrówka ka¿dego typu ma inne HP. Wojownik koks, robotnica a hita itd
	int strenght;	//Si³a gryz¹cej mruwencji
	int speed;		//Prêdkoœæ poruszania siê

};