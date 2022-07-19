#include <string>
#include <fstream>
#include <iostream>
#include "LinkedList.hpp"
#include "Test.h"

using namespace std;

int main()
{
	/*ifstream fin;
	fin.open("Test.txt");

	string str;
	while (::getline(fin, str))
	{
		cout << str << endl;
	}

	ofstream fout;
	fout.open("Test.txt");

	LinkedList<int> ll;
	ll.push_back(10);
	ll.push_back(20);
	ll.push_back(30);

	for (auto i = ll.begin(); i != ll.end(); i++)
	{
		fout << *i << " ";
	}
	fout << endl;

	ll.push_back(40);
	ll.push_back(50);

	for (auto& i : ll)
	{
		fout << i << " ";
	}
	fout << endl;

	ll.clear();
	fout.close();
	fin.close();*/

	//LinkedList<int> i;
	//i.push_back(1);

	ofstream fout;
	fout.open("Test.txt");

	LinkedList<Test*> t;
	//int i;
	//cin >> i;
	t.push_back(new Test(10));
	//t.push_back(new Test(10, "테스트1"));
	//t.push_back(new Test(20, "테스트2"));
	//t.push_back(new Test(30, "테스트3"));

	cin >> t.begin().ptr->data->num;
	fout << t.begin().ptr->data->num;
	//cout << t.begin().ptr->data->num;

	//cout >> t.test >> t.test << endl;

	fout.close();

	return 0;
}