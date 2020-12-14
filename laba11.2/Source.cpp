#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <Windows.h> 

using namespace std;

enum Spec { KN, INF, ME, FI, TN };
string SpecStr[] = { "����.�����", "�����������", "���������� �� ��������", "Գ���� �� �����������", "������� ��������" };

struct Student
{
	string prizv;
	int kurs;
	Spec spec;
	int physics;
	int math;
	int inform;
};

void CreateBIN(char* fname, Student* p)
{
	int spec;
	ofstream fout(fname, ios::binary);
	char ch;
	int i = 0;
	do
	{
		cin.get();
		cin.sync();
		cout << "������� � " << i + 1 << ":" << endl;
		cout << " �������: "; cin >> p[i].prizv;
		//fout.write((char*)&p[i].prizv, sizeof(p[i].prizv));
		cout << " ����: "; cin >> p[i].kurs;
		cout << " ������������: (0 - ����.�����, 1 -����������� , 2 - ���������� �� ��������, 3 - Գ���� �� �����������,4 - ������� ��������): ";
		cin >> spec;
		p[i].spec = (Spec)spec;
		cout << " ������ �� ������: "; cin >> p[i].physics;
		cout << " ������ �� ����������: "; cin >> p[i].math;
		cout << " ������ �� �����������: "; cin >> p[i].inform;
		if (!fout.write((char*)&p, sizeof(Student)))
		{
			cerr << "Error writing file." << endl;
		}
		cout << "continue? (y/n): "; cin >> ch;
		i++;
	} while (ch == 'y' || ch == 'Y');
	cout << endl;
}
void PrintBIN(char* fname, Student* p)
{
	ifstream fin(fname, ios::binary);
	int i = 0;
	cout << "========================================================================="
		<< endl;
	cout << "| � | ������� | ���� | ������������ | Գ���� | ���������� | �����������|"
		<< endl;
	cout << "-------------------------------------------------------------------------"
		<< endl;
	while (fin.read((char*)&p, sizeof(Student)))
	{

		cout << "|" << setw(3) << right << i + 1 << " ";
		cout << "|  " << setw(6) << left << p[i].prizv << "| " << setw(4) << right << p[i].kurs << "  "
			<< "| " << setw(6) << left << SpecStr[p[i].spec] << setw(4);
		cout << "   |" << setw(4) << right << p[i].physics << setw(4) << right << "| ";
		cout << setw(4) << right << p[i].math << setw(4) << right << "    | ";
		cout << setw(4) << right << p[i].inform << setw(1) << right << " |" << endl;
		cout << "========================================================================="
			<< endl;
		i++;
	}
	cout << "========================================================================="
		<< endl;
	cout << endl;
}
double LineSearch(Student* p, char* fname);
double LineSearch1(Student* p, char* fname);
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Student* p = new Student[10000];
	char fname[100];
	cout << "enter file name 1: "; cin >> fname;
	CreateBIN(fname, p);
	PrintBIN(fname, p);
	int cnt = LineSearch(p, fname);
	cout << "ʳ������ ��������,�� ���������� �� ������ �� �����:" << endl;
	cout << cnt << endl;
	int proc = LineSearch1(p, fname);
	cout << "������� ��������, � ���� ������� ��� ������ 4:" << endl;
	cout << proc << '%' << endl;
	return 0;


}
double LineSearch(Student* p, char* fname) {
	int n = 0;
	ifstream fin(fname, ios::binary);
	int i = 0;
	while (fin.read((char*)&p, sizeof(Student)))
	{
		if ((p[i].physics > 3) && (p[i].math > 3) && (p[i].inform > 3))
		{
			n++;
		}
		i++;
	}
	return n;
}
double LineSearch1(Student* p, char* fname) {
	int n = 0, k = 0;
	ifstream fin(fname, ios::binary);
	int i = 0;
	while (fin.read((char*)&p, sizeof(Student)))
	{
		n++;
		if (((p[i].physics + p[i].math + p[i].inform) / 3) < 4)
		{
			k++;
		}
		i++;
	}
	return 100 * k / n;
}