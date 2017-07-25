// testConteiner.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
using namespace std;

int main()
{
	/*srand(time(NULL));
	vector<int> vec1(10);
	vector<int> vec2(3);
	vector<int> diff;

	cout << "Initaialization vec1"<<endl;
	for (auto&i:vec1) {
		i = rand()%10;
		cout << i<<endl;
	}

	cout << "Initaialization vec2" << endl;
	for (auto&i : vec2) {
		i = rand() % 10;
		cout << i << endl;
	}

	set_difference(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(),
					inserter(diff, diff.begin()));

	cout << "vector diff = " << endl;
	for (auto&i : diff) {
		cout << i << endl;
	}*/

	std::vector<int> v1;
	std::vector<int> v2;
	std::vector<int> diff;

	for (int i = 0; i < 6; i++) {
		int num = rand() % 10;
		v1.push_back(num);
		cout << v1[i] << endl;
	}

	for (int i = 0; i < 3; i++) {
		int num = rand() % 10;
		v2.push_back(num);
		cout << v2[i] << endl;
	}

	std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(),
		std::inserter(diff, diff.begin()));

	for (auto i : v1) std::cout << i << ' ';
	std::cout << "minus ";
	for (auto i : v2) std::cout << i << ' ';
	std::cout << "is: ";

	for (auto i : diff) std::cout << i << ' ';
	std::cout << '\n';

	system("pause");
    return 0;
}

