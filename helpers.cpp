#ifndef HELPERS_CPP
#define HELPERS_CPP

#include <iostream>
#include <set>
#include <vector>
using namespace std;

#define all(c) (c).begin(), (c).end()


// Output for vector, space separated
template <typename T>
ostream& operator << (ostream& os, const vector<T> &v)
{
	for (size_t i=0; i<v.size(); i++)
	{
		os << v[i];
		if (i < v.size()-1) os << " ";
	}
	return os;
}

// Output for set, space separated
// Not sure how to not space on the last one
template <typename T>
ostream& operator << (ostream& os, const set<T> &s)
{
	for (auto it = s.begin(); it != s.end(); it++)
	{
		os << *it << " ";
	}
	return os;
}

// check whether a vector's elements aren't empty
// bool has_elements(const vector<string> &v)
// {
// 	for (size_t i=0; i<v.size(); i++)
// 	{
// 		if (!v[i].empty()) return true;
// 	}
// 	return false;
// }

#endif // HELPERS_CPP
