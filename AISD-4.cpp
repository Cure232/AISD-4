﻿// AISD-4.cpp: определяет точку входа для приложения.
//

#include "AISD-4.h"

using namespace std;

int main()
{
	vector<stats> sv = test_sort(shaker_sort<int>, 100, 3, 2, 3);
	cout << sv;
	vector<stats> sv2 = test_sort(insert_sort<int>, 100, 3, 2, 3);
	cout << sv2;
	vector<stats> sv3 = test_sort(comb_sort<int>, 100, 3, 2, 3);
	cout << sv3;
}