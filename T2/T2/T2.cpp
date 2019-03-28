/****************************************************************************************
* Project name  : TOPU                                                                  *
* Project type  : win32 console app                                                     *
* File name     : kurs                                                               *
* Programmers   : Pronin I. D.                                                      *
* Modified      : -                                                                     *
* Created       : 10.01.19 14:27                                                        *
* Last Revision : 11.01.19 15:33                                                        *
****************************************************************************************/
#include "stdafx.h"
#include <iostream>
#include <math.h>
using namespace std;
const unsigned int line = 4;    // ����� ����� �� ������� �������
const unsigned int column = 5;  //����� �������� �� ������� �������

								/**************************************************************************************/
								/*                       � � � � � � � � �    � � � � � � �                           */
								/**************************************************************************************/
double *Proizv1(double Te_2[line][column + 3]);
double *Proizv2(double a[line + 3][column + 3], int k);
/***************************************************************************************/
/*                       � � � � � � � �     � � � � � � � � �                         */
/***************************************************************************************/
int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	int N[line] = { 3, 4, 5 };
	int KeyColumn;                          // ������� �������
	int KeyLine;                            // ������� ������
	double Out_A[line + 3][column + 3];             // �������, ������� ��������� �� ������ ������ ���������
	double T_2[line][column + 3];
	double min, per;					    // ���������� ��� ������ ����������� ������
	double max, per2;                       // ���������� ��� ������ ������������ ������� 
	int Nbr, Nbr_1, Num, Num_1;
	int SimpLine = line - 1;
	// ������� ������
	double A[line][column + 1] =
	{
		{ 21, 3, 1, 1, 0, 0 },
		{ 6, -4, 2, 0, 1, 0 },
		{ 6, 0, 1, 0, 0, 1 },
		{ 0, 8, 3, 0, 0, 0 }
	};
	// ���������� �_2
	for (int i = 0; i < line; i++)
	{
		T_2[i][1] = A[i][0];
		for (int j = 2; j < column; j++)
			T_2[i][j] = A[i][N[j - 2]];
	}
	for (int i = 0; i < line - 1; i++)
		T_2[i][column] = 0;
	T_2[line - 1][column] = 1;
	for (int i = 0; i < line - 1; i++)
		T_2[i][0] = N[i];

	//���������� ���������
	for (int i = 0; i < line; i++)
	{
		for (int j = 0; j < column; j++)
		{
			Out_A[i][j] = A[i][j + 1];
		}//for
	}
	for (int i = 0; i < line; i++)
	{
		Out_A[i][column] = T_2[line - 1][i + 2];
	}
	for (int j = 0; j < column; j++)
	{
		Out_A[line][j] = Proizv2(Out_A, 0)[j];
	}

	//����������� ������� 
	Nbr = 0;
	max = 0;
	for (int j = 0; j < column; j++)
	{
		Nbr_1 = j;
		per2 = Out_A[line][j];
		if (per2 > max)
		{
			max = per2;
			Nbr = Nbr_1;
		}//if
	}//for
	KeyColumn = Nbr;
	//���������� ������������ �������	
	for (int i = 0; i < line; i++)
		T_2[i][column + 1] = Out_A[i][KeyColumn];

	for (int i = 0; i < line; i++)
		T_2[i][column + 2] = Proizv1(T_2)[i];

	//����������� ������
	Num = 0;
	min = T_2[0][1] / T_2[0][column + 2];
	if (T_2[0][column + 2] < 0)
		min = 1000000;
	for (int i = 1; i < line - 1; i++)
	{
		Num_1 = i;
		per = T_2[i][1] / T_2[i][column + 2];
		if (T_2[i][column + 2] < 0)
			continue;
		if (per < min)
		{
			min = per;
			Num = Num_1;
		}//if
	}//for
	KeyLine = Num;


	double razrElement;
	int k = 1;
	bool flag = false;
	while (true)
	{
		printf("\n--------------- K=%d: --------------\n", k);
		printf("\n\n--------------- ��������-�������: --------------\n");
		for (int i = 0; i < line; i++)
		{
			for (int j = 0; j < column + 3; j++)
			{
				if (fabs(T_2[i][j]) > 5000)
					T_2[i][j] = NULL;
				printf("%6.2f ", T_2[i][j]);
			}
			cout << endl;
		}
		printf("\n\n--------------- ���������: --------------\n");
		for (int i = 0; i < line + 3; i++)
		{
			for (int j = 0; j < column + 3; j++)
			{
				if (fabs(Out_A[i][j]) > 5000)
					Out_A[i][j] = NULL;
				printf("%6.2f ", Out_A[i][j]);
			}
			cout << endl;
		}
		if (flag == true)
			break;
		// ������ ����������� �����
		razrElement = T_2[KeyLine][column + 2];
		printf("����������� �������:    A[%d][%d] = %f\n\n�������:\n\n", KeyLine, KeyColumn, razrElement);
		T_2[KeyLine][0] = KeyColumn + 1;
		// ������������� ������ ������� � ����������� ���������
		for (int j = 1; j < column + 1; j++)
			T_2[KeyLine][j] = T_2[KeyLine][j] / razrElement;

		for (int i = 0; i < line; i++)
		{
			for (int j = 1; j < column + 1; j++)
			{                                               // ������������� �������
				if (i != KeyLine)
					T_2[i][j] = T_2[i][j] - T_2[KeyLine][j] * T_2[i][column + 2];
			}//for
		}
		//������� ������� d � ������ �
		for (int i = 0; i < line; i++)
		{
			Out_A[i][column + k] = T_2[line - 1][i + 2];
		}
		for (int j = 0; j < column; j++)
		{
			Out_A[line + k][j] = Proizv2(Out_A, k)[j];
		}

		//����������� ������� 
		Nbr = 0;
		max = 0;
		for (int j = 0; j < column; j++)
		{
			Nbr_1 = j;
			per2 = Out_A[line + k][j];
			if (per2 > max)
			{
				max = per2;
				Nbr = Nbr_1;
			}//if
		}//for
		KeyColumn = Nbr;
		if (max <= 0)
			flag = true;
		//���������� ������������ �������	
		for (int i = 0; i < line; i++)
			T_2[i][column + 1] = Out_A[i][KeyColumn];

		for (int i = 0; i < line; i++)
			T_2[i][column + 2] = Proizv1(T_2)[i];

		//����������� ������
		Num = 0;
		min = T_2[0][1] / T_2[0][column + 2];
		if (T_2[0][column + 2] < 0)
			min = 1000000;
		for (int i = 1; i < line - 1; i++)
		{
			Num_1 = i;
			per = T_2[i][1] / T_2[i][column + 2];
			if (T_2[i][column + 2] < 0)
				continue;
			if (per < min)
			{
				min = per;
				Num = Num_1;
			}//if
		}//for
		KeyLine = Num;
		k++;
	}
	double optimum[2];
	for (int i = 0; i < line - 1; i++)
		if (T_2[i][0] <= 2)
		{
			int k = T_2[i][0];
			optimum[k - 1] = T_2[i][1];
		}

	printf("\n����������� ������ (%f; %f)\n", optimum[0], optimum[1]);
	printf("\n���������� �������� Z=%f*%f+%f*%f=%f\n", A[line - 1][1], optimum[0], A[line - 1][2], optimum[1], -T_2[line - 1][1]);
	system("pause");
	return 0;
}//main

 /**************************************************************************************/
 /*                                 ���������� �������                                 */
 /**************************************************************************************/

double *Proizv1(double Te_2[line][column + 3])
{
	double a[line] = { 0 };
	for (int i = 0; i < line; i++)
		for (int j = 2; j < column + 1; j++)
			a[i] = a[i] + Te_2[j - 2][column + 1] * Te_2[i][j];
	return a;
}
double *Proizv2(double Aa[line + 3][column + 3], int k)
{
	double a[column] = { 0 };
	for (int j = 0; j < column; j++)
		for (int i = 0; i < line; i++)
			a[j] = a[j] + Aa[i][column + k] * Aa[i][j];
	return a;
}