#include "iostream"
#include "string"
#include<cmath> 
#include <stdlib.h> 
#include <time.h>   
#define BAS 1
#define YOL 0
#define DUVAR -1
#define ULASILAMAZ -2
//1 baþlangýç
//0 yol
//-1 duvar
//-2 ulaþýlamayan yol

using namespace std;
int boyut;
int **matris;
struct node
{
	int i;
	int j;
	node *next;
};

int labirentAtamasi();//labirente rastgele 0 ve X deðerlerini atar
void labirentDuzenleme();//labirent yolarýnýn kýsýtlý kalmamasý için ekstra eklemeler
void labirentGoster();//labirenti ekrana yazdýrýr
void cozum(int i, int j);//labirentin çözüm iþlemleri
void alternatifler(int i, int j);//labirentte bulunduðumuz noktadan gidilebilecek alternatifleri yýðýna atar
int toInteger(string _id);//girilen string deðerini inte çevirir
string toString(int id);//girilen int deðerini stringe çevirir

node *root = NULL;
node *pop(node *r);//yýðýndan son giren elemaný siler
node *push(node *r, int i, int j);//yýðýna eleman ekler
int main()
{
	srand(time(NULL));
	cout << "Matris boyutu: ";
	cin >> boyut;
	matris = new int*[boyut];
	while (true)
	{		
		for (int i = 0; i < boyut; i++)
		{
			matris[i] = new int[boyut];
		}

		//labirenti oluþturma
		for (int i = 0; i < boyut; i++)
		{
			for (int j = 0; j < boyut; j++)
			{
				matris[i][j] = labirentAtamasi();
			}
		}

		labirentDuzenleme();
		int i, j;
		do
		{
			i = rand() % boyut / 2 + boyut / 3;
			j = rand() % boyut / 2 + boyut / 3;
		} while (matris[i][j] != 0);
		matris[i][j] = 1;

		labirentGoster();

		cout << "Baslangic Noktas: (" << i << "," << j << ")" << endl;
		cozum(i, j);
		cout << endl << endl;
		labirentGoster();

		cout << endl;
		cout << "Labirenti Tekrar Olusturup Cozmek Icin: ";
		system("pause");
		system("cls");
	}
}
string labirentDeger(int i, int j) {
	if (matris[i][j] == BAS)
	{//baslangic
		return "*";
	}
	else if (matris[i][j] == DUVAR)
	{//duvar
		return "X";
	}
	else if (matris[i][j] == ULASILAMAZ)
	{//ulaþýlamaz
		return "U";
	}
	else if (matris[i][j] > BAS)
	{//gidilmiþ bir yol 
		return toString(matris[i][j] - 1);
	}
	else
	{//0 olma durumu (yanlýzca labirent çözülmediði zaman çalýþýr)
		return toString(matris[i][j]);
	}
}
void labirentGoster()
{
	for (int i = 0; i < boyut; i++)
	{
		for (int j = 0; j < boyut; j++)
		{
			string tmp = labirentDeger(i, j);
			//ekrana düzgün yazdýrýlmasý için tek basamaklý olanlarýn baþýna boþluk eklliyorum
			if (matris[i][j] - 1<10)
			{
				cout << " ";
			}
			cout << tmp << " ";
		}
		cout << endl;
	}
}
void labirentDuzenleme() {

	int ii = rand() % (boyut - 1) + 1;
	ii = ii / 2;
	for (int j = ii; j < boyut / 4; j++)
	{
		matris[ii][j] = 0;
		matris[j][ii] = 0;
	}

	for (int i = 1; i < boyut; i++)
	{
		for (int j = 1; j < boyut; j++)
		{//labirent optimize ediliyor
		 //4 tane 0 kare þeklinde yan yana gelirse o kýsýmlara tekrar atama yapýlýr
		 /*örnek
		 00  --> 01
		 00		 00
		 */
			if (matris[i][j] == 0 && matris[i - 1][j] == 0 && matris[i][j - 1] == 0 && matris[i - 1][j - 1] == 0)
			{
				matris[i][j] = -1;
				j++;
			}
		}
	}
}
int labirentAtamasi() {
	// 1/3 ihtimalle DUVAR eklenir
	// 2/3 ihtimalle YOL eklenir
	int a = rand() % 3;
	if (a == 1)
	{
		return DUVAR;
	}
	else
	{
		return YOL;
	}
}

void cozum(int i, int j)
{
	alternatifler(i, j);

	for (int i1 = 0; i1 < boyut; i1++)
	{
		for (int j1 = 0; j1 < boyut; j1++)
		{
			if (matris[i1][j1] == 0)
			{
				matris[i1][j1] = ULASILAMAZ;
			}
		}
	}
}

void alternatifler(int i, int j)
{
	//bulunan noktadaki alternatif yollarý bulup stacke atar ve ilerler
	if (i>0 && matris[i - 1][j] == 0)
	{//yukarý kontrol
		root = push(root, i, j);
		i = i - 1;
		matris[i][j] = matris[i + 1][j] + 1;
	}
	else if (j<boyut - 1 && matris[i][j + 1] == 0)
	{//sað kontrol
		root = push(root, i, j);
		j = j + 1;
		matris[i][j] = matris[i][j - 1] + 1;
	}
	else if (i<boyut - 1 && matris[i + 1][j] == 0)
	{//aþaðý kontrol
		root = push(root, i, j);
		i = i + 1;
		matris[i][j] = matris[i - 1][j] + 1;
	}
	else if (j>0 && matris[i][j - 1] == 0)
	{//sol kontrol
		root = push(root, i, j);
		j = j - 1;
		matris[i][j] = matris[i][j + 1] + 1;
	}
	else
	{
		if (root != NULL)
		{//gidilecek yol kalmadý stacteki son alternatife geri dön
			i = root->i;
			j = root->j;
			root = pop(root);
		}
		else
		{//stack boþ gidilebilecek tüm yollara gidildi
			return;
		}
	}
	alternatifler(i, j);
	
}
string toString(int id) {
	string _id = "";
	int r;
	if (id<0) {
		return "-1";
	}
	else if (id == 0) {
		return "0";
	}
	for (int i = 1; i <= id; i += 0) {
		i *= 10;
		r = (id / (i / 10)) % 10;
		_id = (char)(r + 48) + _id;
	}
	return _id;
}
int toInteger(string _id) {
	if (_id[0]=='-')
	{
		return -1;
	}
	int tmp = 0;
	for (int i = 0; i<_id.length(); i++) {
		if (_id[i] >= 48 || _id[i] <= 57) {
			tmp = tmp + (((int)_id[i]) - 48)*pow(10, _id.length() - 1 - i);
		}
		else {
			return -1;
		}
	}
	return tmp;
}
node *pop(node *r) {
	node *yrd = r;
	if (r == NULL)
	{
		return NULL;
	}
	else
	{
		r = yrd->next;
		yrd->next = NULL;
		delete yrd;
	}
	return r;
}
node *push(node *r, int i, int j) {
	node *yrd = new node;
	yrd->i = i;
	yrd->j = j;
	yrd->next = r;
	r = yrd;
	return r;
}