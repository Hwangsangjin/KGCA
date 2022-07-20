#include <string>
#include <fstream>
#include <iostream>
#include "LinkedList.h"
#include "StudentManager.h"

using namespace std;

int main()
{
	//ifstream fin;
	//fin.open("Student.txt");

	//string str;
	//while (::getline(fin, str))
	//{
	//	cout << str << endl;
	//}

	ofstream fout;
	fout.open("Student.txt");

	StudentManager sm;
	sm.run();

	fout.close();
	//fin.close();

	return 0;
}