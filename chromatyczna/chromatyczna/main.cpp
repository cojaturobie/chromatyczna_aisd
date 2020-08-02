#include<iostream>
#pragma warning(disable : 4996)

using namespace std;

bool pelny(char **mac, int y) {
	for (int i = 0; i < y; i++) {
		for (int j = i + 1; j < y; j++) {
			if (i != j && mac[i][j] == '0')return false;
		}
	}
	return true;
}

bool cykl(char **mac, int y) {
	int licznik = 0;
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < y; j++) {
			if (mac[i][j] == '1')licznik++;
			if (licznik > 2)return false;
		}
		if (licznik < 2 || licznik >2)return false;
		licznik = 0;
	}
	return true;
}

bool pojedynczy(char **mac, int y) {
	int licznik = 0;
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < y; j++) {
			if (mac[i][j] == '1')licznik++;
			if (licznik > 1)return false;
		}
		if (licznik >1)return false;
		licznik = 0;
	}
	return true;
}

void DFS(int wierz, int *odwiedzony, char **mac, int y, int &licz) {

	licz++;
	odwiedzony[wierz] = 1;
	for (int j = 0; j < y; j++) {
		if (!odwiedzony[j] && mac[wierz][j] == '1')DFS(j, odwiedzony, mac, y, licz);
	}
}

bool niespojny_pelny(char **mac, int y) {
	int max = 0;
	int max_id = NULL;
	int licznik = 0;
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < y; j++) {
			if (mac[i][j] == '1')licznik++;
			if (licznik > max) {
				max = licznik;
				max_id = i;
			}
		}
		licznik = 0;
	}
	int *odwiedzony = new int[y];
	for (int i = 0; i < y; i++) {
		odwiedzony[i] = 0;
	}
	int x = 0;
	DFS(max_id, odwiedzony, mac, y, x);
	if (max == 1 && x == 2) {
		delete[] odwiedzony;
		return true;
	}
	licznik = 0;
	for (int i = 0; i < y; i++) {
		if (odwiedzony[i] == 1) {
			for (int j = 0; j < y; j++) {
				if (mac[i][j] == '1')licznik++;
			}
			if (licznik < max) {
				delete[] odwiedzony;
				return false;
			}
		}
		licznik = 0;
	}
	delete[] odwiedzony;
	return true;
}


bool niespojny_cykl(char **mac, int y) {
	int *stopnie = NULL;
	stopnie = new int[y];
	for (int j = 0; j < y; j++) {
		stopnie[j] = 0;
	}
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < y; j++) {
			if (mac[i][j] == '1')stopnie[i]++;
		}
	}
	int max = 0;
	int max_id;
	for (int j = 0; j < y; j++) {
		if (stopnie[j] > max) {
			max = stopnie[j];
			max_id = j;
		}
	}
	int *odwiedzony = new int[y];
	for (int i = 0; i < y; i++) {
		odwiedzony[i] = 0;
	}
	int x = 0;
	DFS(max_id, odwiedzony, mac, y, x);
	if (max == 2 && x % 2 == 1 && y%2==0)return true;
	else return false;
}

int main() {
	int x, y;
	char **mac = NULL;
	char *pom = NULL;
	scanf("%d", &x);
	while (x--) {
		//wpisanie i ustawienie rozmiaru macie¿y
		scanf("%d ", &y);
		pom = new char[y*y];
		mac = new char *[y];
		for (int i = 0; i < y; i++) {
			mac[i] = new char[y];
		}
		//wpisanie elementów do macierzy
		scanf("%s", &pom[0]);
		for (int i = 0; i < y; i++) {
			for (int j = 0; j < y; j++) {
				mac[i][j] = pom[i*y + j];
			}
		}
		delete[] pom;
		//sprawdzanie czy jest spójny
		int *odwiedzony = new int[y];
		for (int i = 0; i < y; i++) {
			odwiedzony[i] = 0;
		}
		int wierz = 0;
		int licz = 0;
		DFS(wierz, odwiedzony, mac, y, licz);
		//drukowanie wyniku
		if (licz == y && y % 2 == 1 && cykl(mac, y) == true)printf("True\n");
		else if (licz == y && y % 2 == 0 && cykl(mac, y) == true)printf("False\n");
		else if (pelny(mac, y) == true)printf("True\n");
		else if (pojedynczy(mac, y) == true)printf("True\n");
		else if (licz != y && niespojny_pelny(mac, y) == true)printf("True\n");
		else if (licz != y && niespojny_cykl(mac, y) == true)printf("True\n");
		else printf("False\n");
		//czyszczenie macierzy
		delete[] odwiedzony;
		for (int i = 0; i < y; i++) delete[] mac[i];
		delete[] mac;
	}
	return 0;
}