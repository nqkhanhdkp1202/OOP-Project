// 30_08_Cau24_2021.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <math.h>
#pragma warning(disable:4996)

using namespace std;

//khai bao kieu cau truc phan so
typedef struct phanso
{
	int tu;
	int mau;
};

//doc du lieu tu file va luu tru vao bang
void ReadfromFile(FILE*file, int **&arr, int &n)
{
	fscanf(file, "%d", &n);
	arr = new int *[n];//cap phat dong
	for (int i = 0; i < n; i++)
		arr[i] = new int[2];
	for (int j = 0; j < n; j++)
	{
		fscanf(file, "%d %d", &arr[j][0], &arr[j][1]);
	}
}

//Sap xep phan so theo thu tu tang dan
void Sapxep(phanso ps[], int n)
{
	phanso t;
	for (int i = 0; i<n - 1; i++)
	{
		for (int j = i + 1; j<n; j++)
		{
			if (ps[i].tu*ps[j].mau>ps[j].tu *ps[i].mau) //neu a/b > c/d => a*d>b*c
			{
				t = ps[i];
				ps[i] = ps[j];//doi cho hai phan so
				ps[j] = t;
			}
		}
	}
}

//Cong hai phan so
phanso congps(phanso ps1, phanso ps2)
{
	phanso kq;
	kq.tu = ps1.tu*ps2.mau + ps2.tu*ps1.mau;
	kq.mau = ps1.mau*ps2.mau;
	return kq;
}

phanso congtongps(phanso ps[], int n)
{
	phanso tong = congps(ps[0], ps[1]);
	if (n == 1) return ps[0];
	if (n == 2) return tong;
	for (int i = 2; i < n; i++)
	{
		tong = congps(tong, ps[i]);
	}
	return tong;
}

//Tim uoc so chung lon nhat cua 2 so
int USCLN(int a, int b)
{
	int r = a%b;
	while (r != 0)
	{
		a = b;
		b = r;
		r = a%b;
	}
	return b;
}

//Toi gian phan so
void toigianps(phanso &ps)
{
	int uocchung = USCLN(ps.tu, ps.mau);
	ps.tu = ps.tu / uocchung;
	ps.mau = ps.mau / uocchung;
}

//In phan so
void inps(FILE*file,phanso ps)
{
		fprintf(file, "%d/%d  ", ps.tu, ps.mau);
}

int main()
{
	FILE*fi = fopen("E:\\input_3.txt", "rt");
	if (fi == NULL)
	{
		cout << "File khong ton tai" << endl;
		return 0;
	}
	int **A;
	int n;
	ReadfromFile(fi, A, n);
	phanso *ps=new phanso[n];
	phanso tongps;
	//nhap day phan so tu du lieu bang A
	for (int i = 0; i<n; i++)
	{
		ps[i].tu = A[i][0];
		ps[i].mau = A[i][1];
	}
	FILE*fo = fopen("E:\\output3.txt", "w+t");
	//in ra ket qua cau 24
	fprintf(fo, "Bai 24: ");
	Sapxep(ps, n);
	for (int j = 0; j < n; j++)
	{
		inps(fo, ps[j]);
	}
	fprintf(fo, "\n");
	tongps = congtongps(ps, n);
	toigianps(tongps);
	//in ra ket qua cau 25
	fprintf(fo, "Bai 25: ");
	inps(fo, tongps);
	fclose(fi);
	fclose(fo);
	delete[]ps;
	delete[]A;
	return 0;
}