#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include <fstream>
#include <math.h>

using namespace std;
double k = 0;
int r = 0;
double s = 2.5, m = 4.0, n = 8.0, e = 2.6;
double** Coordinate = new double* [64];
double** Distance = new double* [64];
double** Energy = new double* [64];

void EnergySolution(int Element, int i)
{
	double Res1, Res2, Res3, Res4, Res5;

	Energy[i] = new double[Element + 1];

	for (int j = 1; j < Element + 1; j++)
	{
		Res1 = 4 * e;
		Res2 = s / Distance[i][j];
		Res3 = pow(Res2, n);
		Res4 = pow(Res2, m);
		Res5 = Res3 - Res4;
		Energy[i][j] = Res1 * Res5;
	}
	Energy[i][0] = Element;


}

void DistSolution()
{

	double Xin, Yin, Xout, Yout, fX, fY, tempmass[64], rex;

	for (int i = 0; i < 64; i++)
	{
		for (int i = 0; i < 64; i++)
		{
			tempmass[i] = -1;
		}
		int CountOfElem = 0;
		for (int j = 0; j < 64; j++)
		{
			Xin = Coordinate[i][0];
			Yin = Coordinate[i][1];
			Xout = Coordinate[j][0];
			Yout = Coordinate[j][1];
			fX = fabs(Xin - Xout);
			fY = fabs(Yin - Yout);

			rex = sqrt(pow(fX, 2) + pow(fY, 2));



			for (int o = 0; o < 64; o++)
			{
				if (rex == tempmass[o]) {

					break;
				}
				else
					if ((rex != 0) && (tempmass[o] == -1))
					{

						tempmass[o] = rex;
						CountOfElem += 1;
						break;
					}

			}


		}

		Distance[i] = new double[CountOfElem + 1];
		for (int j = 1; j < CountOfElem + 1; j++)
		{
			Distance[i][j] = tempmass[j];

		}
		Distance[i][0] = CountOfElem;
		EnergySolution(CountOfElem, i);

	}

}

void CoordinateSolution()
{

	for (int i = 0; i < 64; i++)
	{
		Coordinate[i] = new double[2];
	}

	int counter;
	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 2; j++)
		{

			if (i % 8 == 0)
			{
				counter = -1;
				k = i / 8;

			}
			if (j == 0)
			{

				Coordinate[i][j] = s * k;
			}
			else
			{
				counter += 1;
				Coordinate[i][j] = counter * s;
			}


		}

	}
}

void EnergyOutOut()
{

	for (int i = 0; i < 64; i++)
	{
		printf("\n");
		for (int j = 1; j < Energy[i][0]; j++)
		{
			printf("Энергия точки T %d под №  %d  =  %lf\n", i, j, Energy[i][j]);
		}
	}

}

void ShowDist()
{
	for (int i = 0; i < 64; i++)
	{
		printf("\n");
		for (int j = 1; j < Distance[i][0]; j++)
		{
			printf("Расстояние точки T %d под №  %d  =  %lf\n", i, j, Distance[i][j]);
		}
	}

}

void CoordinateOutOut()
{
	for (int i = 0; i < 64; i++)
	{
		printf("\n");
		printf("Координаты точки %d равны (%lf, %lf)\n", i, Coordinate[i][0], Coordinate[i][1]);
	}

}

void FileOutPut()
{
	ofstream fout("DATA.txt");
	fout << "~Координаты всех точек~" << endl;
	for (int i = 0; i < 64; i++)
	{
		fout << endl;

		fout << "Координаты точки " << i << " равны (  " << Coordinate[i][0] << " , " << Coordinate[i][1] << " )";

	}
	fout << "~Дистанция точек~" << endl;
	for (int i = 0; i < 64; i++)
	{
		fout << endl;
		for (int j = 0; j < Distance[i][0]; j++)
		{

			fout << "Расстояние точки T" << i << " под № " << j << " = " << Distance[i][j] << endl;
		}
	}
	fout << "~Энергия всех точек~" << endl;
	for (int i = 0; i < 64; i++)
	{
		fout << endl;
		for (int j = 0; j < Energy[i][0]; j++)
		{

			fout << "Энергии точки T" << i << " под номером №" << j << " равна = " << Energy[i][j] << endl;
		}
	}
	fout.close();

}

void Clear()
{

	for (int i = 0; i < 64; i++)
	{
		delete[] Coordinate[i];
	}
	delete[]Coordinate;

	for (int i = 0; i < 64; i++)
	{
		delete[] Distance[i];
	}
	delete[]Distance;

	for (int i = 0; i < 64; i++)
	{
		delete[] Energy[i];
	}
	delete[]Energy;
}

int main()
{
	setlocale(LC_ALL, "rus");

	CoordinateSolution();
	DistSolution();
	FileOutPut();
	int l_Key;
	do
	{
		printf("1 - Вывести координаты всех точек\n");
		printf("2 - Вывести все дистанции\n");
		printf("3 - Вывести все энергии\n");
		scanf_s("%d", &l_Key);
		switch (l_Key)
		{
		case 1:CoordinateOutOut();
			break;
		case 2:ShowDist();
			break;
		case 3:EnergyOutOut();
			break;
		}

	} while (l_Key != 0);

	Clear();
	_getch();
	return 0;
}