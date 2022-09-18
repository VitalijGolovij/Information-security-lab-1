// алгоритмы поддержки информационной безопасности (лаб. 1).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<string>
#include<list>
#include<iterator>
#include<math.h>
#include<set>
#include <deque>
#include <algorithm>
#include <iterator>
#include<vector>
#include<fstream>
#include<time.h>
using namespace std;

string MySwap(string s, int idx)
{
	if (s[idx] == 't') s[idx] = 'f';
	else s[idx] = 't';
	return s;
}

bool NextSet(int* a, int n, int m)
{
	int k = m;
	for (int i = k - 1; i >= 0; --i)
		if (a[i] < n - k + i + 1)
		{
			++a[i];
			for (int j = i + 1; j < k; ++j)
				a[j] = a[j - 1] + 1;
			return true;
		}
	return false;
}

string swapByIndexs(string s, int* a, int m)
{
	for (int i = 0; i < s.length(); i++)
	{
		for (int j = 0; j < m; j++)
			if (a[j] - 1 == i)
			{
				s = MySwap(s, i);
			}
	}
	return s;
}

set<string> gen2(string s, int m)
{
	set<string> setStr;
	int n = 10;
	int* a;
	a = new int[n];
	for (int i = 0; i < n; i++)
		a[i] = i + 1;
	if (n >= m)
	{
		setStr.insert(swapByIndexs(s, a, 10 - m));
		while (NextSet(a, n, 10 - m))
		{
			setStr.insert(swapByIndexs(s, a, 10 - m));
		}
	}
	return setStr;
}

vector<string> myUnion(set<string> a)
{
	set<string> b = { "" };
	vector<string> v(1000);
	vector<string>::iterator it;

	it = set_union(a.begin(), a.end(), b.begin(), b.end(), v.begin());

	v.resize(it - v.begin());

	return v;
}

vector<string> myIntersection(vector<string> a, set<string> b)
{
	vector<string> v(1000);
	vector<string>::iterator it;

	it = set_intersection(a.begin(), a.end(), b.begin(), b.end(), v.begin());


	v.resize(it - v.begin());

	return v;
}
int main()
{
	//читается из файла
	string line;
	fstream in("input.txt");
	int n = 0;
	string* a = nullptr;
	if (in.is_open())
	{
		getline(in, line);
		n = stoi(line);
		a = new string[n];
		for (int i = 0; i < n; i++)
		{
			getline(in, line);
			a[i] = line;
		}
	}
	//список из множеств возможных поролей
	list<set<string>> listSets;

	for (int i = 0; i < n; i++)
	{
		string temp_str = a[i];
		int countRight = temp_str[10] - '0';
		a[i].erase(10);
		listSets.push_back(gen2(a[i], countRight));
	}

	list<set<string>>::iterator it = listSets.begin();

	vector<string> v = myUnion(*it);

	for (; it != listSets.end(); it++)
	{
		v = myIntersection(v, (*it));
	}

	vector<string>::iterator v_it = v.begin();

	ofstream out;
	out.open("output.txt");
	if (v.size() == 1)
	{
		out << "ONE SOLUTION" << endl << *v_it;
	}
	else
	{
		out << "POSSIBLE SOLUTION" << endl;
		out << *v_it << endl;
	}
}
