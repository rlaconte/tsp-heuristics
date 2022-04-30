#ifndef TP_ALGO_III_TEMPLATES_H
#define TP_ALGO_III_TEMPLATES_H
#include <vector>

// es importante que slice no me modifique mi vector original, supuestamente se usa el constructor de vector para crear vec entonces esto se cumple
template <typename T>
vector<T> slice(vector<T> const& v, int m, int n)
{
	auto first = v.begin() + m;
	auto last = v.begin() + n + 1; // incluye al n en el slice
	vector<T> vec(first, last);
	return vec;
}

// Dado un vector devuelve una copia invertida
template <typename T>
vector<T> darVuelta(vector<T> v)
{
	vector<int> res;
	int n = v.size();
	for (int i = 0; i < n; ++i)
	{
		res.push_back(v[n - i - 1]);
	}
	return res;
}

template <typename T>
bool pertenece(vector<T> v, T elem)
{

	bool res = false;
	for (int i = 0; i < v.size(); ++i)
        {
		if (v[i] == elem)
		{
			res = true;
		}
	}

	return res;
}


#endif //TP_ALGO_III_TEMPLATES_H