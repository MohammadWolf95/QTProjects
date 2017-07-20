// testConteiner.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
using namespace std;

int main()
{
	int current = 0;
	srand(time(NULL));
	list<int> list(20);
	cout << "Test for list"<<endl;
	cout << "Initialisation list"<<endl;
	for (auto&i : list) {
		i = rand() % 10;
	}
	list.sort();
	for (auto&i : list) {
		cout << "i = " << i << endl;
	}

	std::list<int>::iterator it;
	it = list.begin();
	while(it!=list.end()) {
		std::list<int>::iterator findIter = std::find(list.begin(), list.end(), 1);
		if (findIter != list.end()) {
			list.erase(findIter);
			++it;
			continue;
		}
		++it;
	}
	cout << "list after operation"<<endl<<
			"list.size() = "<<list.size()<<endl;
	for (auto&i : list) {
		cout << "i = " << i << endl;
	}

	cout << "Current = "<<current<<endl;
	system("pause");
    return 0;
}

