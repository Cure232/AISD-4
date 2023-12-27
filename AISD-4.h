#include<vector>
#include<iostream>
#include<random>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;

bool operator>(const std::string& str1, const std::string& str2) {
	return str1.compare(str2) > 0;
}

bool operator<(const std::string& str1, const std::string& str2) {
	return str1.compare(str2) < 0;
}


int generate_random_number(int min, int max, int seed) {
	mt19937 mt(seed);
	uniform_int_distribution<int> distribution(min, max);
	return distribution(mt);
}

struct stats {
	size_t comparison_count = 0;
	size_t copy_count = 0;
};

ostream& operator<<(ostream& stream, stats val) {
	stream << val.comparison_count << " " << val.copy_count << endl;
	return stream;
}

template<typename T>
fstream& operator<<(fstream& stream, vector<T> val) {
	for (int i = 0; i < val.size(); i++) {
		stream << val[i];
	}
	return stream;
}

template<typename T>
ostream& operator<<(ostream& stream, vector<T> val) {
	for (int i = 0; i < val.size(); i++) {
		stream << setw(3) << val[i] << " ";
	}
	return stream;
}

template<typename T>
stats sort(vector<T>& arr, stats func(vector<T>&)) {
	return func(arr);
}

stats get_average(vector<stats> arr) {
	stats stat;
	for (int i = 0; i < arr.size(); i++) {
		stat.comparison_count += arr[i].comparison_count;
		stat.copy_count += arr[i].copy_count;
	}
	stat.comparison_count /= arr.size();
	stat.copy_count /= arr.size();
	return stat;
}

template<typename T>
void write_stats(stats func(vector<T>&), string path, int count, int sort_type, int seed) {
	fstream file;
	file.open(path, std::ios::app);
	vector<int> vals = { 1,2,3,4,5,6,7,8,9,10,25,50,100 };
	if (file) {
		for (int i = 0; i < vals.size(); i++) {
			/*cout << vals[i] * 1000 << endl;*/
			vector<stats> res = test_sort(func, vals[i] * 1000, count, sort_type, seed);
			file << vals[i] * 1000 << " ";
			file << get_average(res);
		}
	}
	else {
		cout << "ERROR";
	}
	file.close();
}

template<typename T>
vector<stats> test_sort(stats func(vector<T>&), int limit, int count, int arr_type, int seed) {
	/// test_sort(sort_function: *func(type of sort funtion), limit: int(arr_len), count: int(arr_count),
	//  arr_type(0 - sorted; 1 - unsorted; 2 - random_shuffle): int) -> vector<stats>
	vector<stats> results;
	int seed_helper = 0;
	for (int i = 0; i <= count - 1; i++) {
		vector<int> arr;
		switch (arr_type)
		{
		case 0:
			for (int j = 0; j < limit; j++) {
				arr.push_back(j);
			}
			break;
		case 1:
			for (int j = 0; j < limit; j++) {
				arr.push_back(limit - j);
			}
			break;
		case 2:
			for (int j = 0; j < limit; j++) {
				arr.push_back(generate_random_number(1, 100, seed + seed_helper));
				seed_helper++;
			}
			break;
		}
		cout << arr << endl;
		results.push_back(func(arr));
	}
	return results;
}

template<typename T>
stats insert_sort(vector<T>& arr) {
	stats cur_stat;
	for (int i = 1; i < arr.size(); i++) {
		for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--) {
			cur_stat.comparison_count++;
			cur_stat.copy_count++;
			std::swap(arr[j - 1], arr[j]);
		}
		cur_stat.comparison_count++;
	}
	return cur_stat;
}

template<typename T>
stats shaker_sort(vector<T>& arr) {
	stats cur_stat;
	int control = static_cast<int>(arr.size() - 1);
	int left = 0, right = control;
	do {
		for (int i = left; i < right; i++) {
			cur_stat.comparison_count++;
			if (arr[i] > arr[i + 1]) {
				cur_stat.copy_count++;
				std::swap(arr[i], arr[i + 1]);
				control = i;
			}
		}
		right = control;
		for (int i = right; i > left; i--) {
			cur_stat.comparison_count++;
			if (arr[i] < arr[i - 1]) {
				cur_stat.copy_count++;
				std::swap(arr[i], arr[i - 1]);
				control = i;
			}
		}
		left = control;
	} while (left < right);
	return cur_stat;
}

template<typename T>
stats comb_sort(vector<T>& arr) {
	stats cur_stat;
	double factor = 1.2473309;
	int step = arr.size() - 1;
	while (step >= 1)
	{
		for (int i = 0; i + step < arr.size(); i++)
		{
			cur_stat.comparison_count++;
			if (arr[i] > arr[i + step])
			{
				cur_stat.copy_count++;
				std::swap(arr[i], arr[i + step]);
			}
		}
		step /= factor;
	}
	return cur_stat;
}