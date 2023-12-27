// AISD-4.cpp: определяет точку входа для приложения.
//

#include "AISD-4.h"

using namespace std;

int main()
{
	string path = "sorted_insert.txt";
	write_stats(shaker_sort<int>, path, 1, 0, 3);
}
