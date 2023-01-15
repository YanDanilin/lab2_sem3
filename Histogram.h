#pragma once
#include "HashTable.h"
#include "Generator.h"
#include <iostream>
#include <vector>

template <class X>
bool between(const X& x, const Pair<X, X>& pair) {
	if (x >= pair.first && x <= pair.second) return true;
	return false;
}

template <class X>
struct pair_hash {
	size_t operator()(const Pair<X, X>& pair) {
		std::hash<X> func;
		size_t res = func(pair.first) + func(pair.second);
		return res;
	}
};

template <class Obj, class X, class Pull>
class Histogram {
private:
	HashTable<Pair<X, X>, DynamicArray<Obj>*, pair_hash<X>>* columns;
	DynamicArray<Pair<X, X>> *xseries;
	size_t count;
	size_t columns_count;
	Pull take_parametr;

public:
	Histogram();
	Histogram(const Histogram<Obj, X, Pull>& another);
	Histogram(DynamicArray<Pair<X, X>>& _xseries, DynamicArray<Obj>& objects);
	~Histogram();
	void show(char symb = 42);
	void insert(Obj& object);
	void remove(X& value);

	void describe();

	size_t get_columns_count();
	size_t get_count();

	template <class Obj, class X, class Pull>
	friend std::ostream& operator<<(std::ostream& out, Histogram<Obj, X, Pull>& hist);
	double mean(const Pair<X, X>& pair);
	double median(const Pair<X, X>& pair);
	double max(const Pair<X, X>& pair);
	double min(const Pair<X, X>& pair);

	void fill_rand(size_t count, DynamicArray<Pair<X, X>>& _xaeries);
};
template <class Obj, class X, class Pull>
Histogram<Obj, X, Pull>::Histogram() {
	columns = new HashTable<Pair<X, X>, DynamicArray<Obj>*, pair_hash<X>>;
	xseries = new DynamicArray<Pair<X, X>>;
	count = 0;
	columns_count = 0;
}
template <class Obj, class X, class Pull>
Histogram<Obj, X, Pull>::~Histogram() {
	if (columns) delete columns;
	if (xseries) delete xseries;
}
template <class Obj, class X, class Pull>
Histogram<Obj, X, Pull>::Histogram(const Histogram<Obj, X, Pull>& another) {
	count = another.count;
	columns_count = another.columns_count;
	take_parametr = another.take_parametr;
	columns = new HashTable<Pair<X, X>, DynamicArray<Obj>*, pair_hash<X>>(*(another.columns));
	xseries = new DynamicArray<Pair<X, X>>(*(another.xseries));
}
template <class Obj, class X, class Pull>
Histogram<Obj, X, Pull>::Histogram(DynamicArray<Pair<X, X>>& _xseries, DynamicArray<Obj>& objects) {
	columns_count = _xseries.GetSize();
	count = objects.GetSize();
	columns = new HashTable<Pair<X, X>, DynamicArray<Obj>*, pair_hash<X>>;
	xseries = new DynamicArray<Pair<X, X>>(_xseries);
	columns->Reserve(_xseries.GetSize());
	size_t xsz = _xseries.GetSize();
	for (int j = 0; j < xsz; ++j) {
		columns->Insert(_xseries[j], new DynamicArray<Obj>);
	}
	int sz = objects.GetSize();
	for (int i = 0; i < sz; ++i) {
		for (int j = 0; j < xsz; ++j) {
			if (between(take_parametr(objects[i]), _xseries[j])) {
				columns->At(_xseries[j])->Append(objects[i]);
			}
		}
	}
}

template <class Obj, class X, class Pull>
size_t Histogram<Obj, X, Pull>::get_columns_count() {
	return columns_count;
}
template <class Obj, class X, class Pull>
size_t Histogram<Obj, X, Pull>::get_count() {
	return count;
}

template <class Obj, class X, class Pull>
void Histogram<Obj, X, Pull>::show(char symb) {
	if (!columns) return;
	for (int i = 0; i < columns_count; ++i) {
		size_t sz = columns->At(xseries->Get(i))->GetSize();
		std::cout << xseries->Get(i) << ":";
		for (int j = 0; j < sz; ++j) {
			std::cout << symb;
		}
		std::cout << "\n";
	}
}

template <class Obj, class X, class Pull>
void Histogram<Obj, X, Pull>::describe() {
	if (!columns) return;
	for (int i = 0; i < columns_count; ++i) {
		const Pair<X, X>& pair = xseries->Get(i);
		std::cout << pair << ":\n";
		std::cout << "\tCount: " << columns->At(pair)->GetSize() << '\n';
		std::cout << "\tMean: " << mean(pair) << '\n';
		std::cout << "\tMedian: " << median(pair) << '\n';
		std::cout << "\tMinimum: " << min(pair) << '\n';
		std::cout << "\tMaximum: " << max(pair) << '\n';
	}
}

template <class Obj, class X, class Pull>
std::ostream& operator<<(std::ostream& out, Histogram<Obj, X, Pull>& hist) {
	if (!hist.columns) return out;
	for (int i = 0; i < hist.columns_count; ++i) {
		out << hist.xseries->Get(i) << ": ";
		DynamicArray<Obj>* column = hist.columns->At(hist.xseries->Get(i));
		for (int j = 0; j < column->GetSize(); ++j) {
			std::cout << column->Get(j) << " ";//hist.take_parametr(column->Get(j)) << " ";
		}
		std::cout << '\n';
	}
	return out;
}

template <class Obj, class X, class Pull>
double Histogram<Obj, X, Pull>::mean(const Pair<X, X>& pair) {
	std::string type = typeid(pair.first).name();
	if (type == "int" || type == "double") {
		DynamicArray<Obj>* column = columns->At(pair);
		size_t sz = column->GetSize();
		double res = 0.0;
		if (sz == 0) return res;
		for (int i = 0; i < sz; ++i) {
			res += take_parametr(column->Get(i));
		}
		return res / sz;
	}
}
template <class Obj, class X, class Pull>
double Histogram<Obj, X, Pull>::median(const Pair<X, X>& pair) {
	std::vector<X> copy;
	DynamicArray<Obj>* column = columns->At(pair);
	size_t sz = column->GetSize();
	if (sz == 0) return X();
	copy.reserve(sz);
	for (int i = 0; i < sz; ++i) {
		copy.push_back(take_parametr(column->Get(i)));
	}
	std::sort(copy.begin(), copy.end());
	if (sz % 2 == 1) {
		return copy[sz / 2];
	}
	else {
		return 0.5 * (copy[sz / 2 - 1] + copy[sz / 2]);
	}
	return X();
}
template <class Obj, class X, class Pull>
double Histogram<Obj, X, Pull>::max(const Pair<X, X>& pair) {
	std::string type = typeid(pair.first).name();
	if (type == "int" || type == "double") {
		std::vector<X> copy;
		DynamicArray<Obj>* column = columns->At(pair);
		size_t sz = column->GetSize();
		if (sz == 0) return 0.0;
		copy.reserve(sz);
		for (int i = 0; i < sz; ++i) {
			copy.push_back(take_parametr(column->Get(i)));
		}
		std::sort(copy.begin(), copy.end());
		return copy[sz - 1];
	}
	return 0.0;
}
template <class Obj, class X, class Pull>
double Histogram<Obj, X, Pull>::min(const Pair<X, X>& pair) {
	std::string type = typeid(pair.first).name();
	if (type == "int" || type == "double") {
		std::vector<X> copy;
		DynamicArray<Obj>* column = columns->At(pair);
		size_t sz = column->GetSize();
		if (sz == 0) return 0.0;
		copy.reserve(sz);
		for (int i = 0; i < sz; ++i) {
			copy.push_back(take_parametr(column->Get(i)));
		}
		std::sort(copy.begin(), copy.end());
		return copy[0];
	}
	return 0.0;
}

template <class Obj, class X, class Pull>
void Histogram<Obj, X, Pull>::fill_rand(size_t _count, DynamicArray<Pair<X, X>>& _xseries) {
	srand(time(NULL));
	if (columns) delete columns;
	if (xseries) delete xseries;
	columns_count = _xseries.GetSize();
	count = _count;
	columns = new HashTable<Pair<X, X>, DynamicArray<Obj>*, pair_hash<X>>;
	columns->Reserve(_count);
	DynamicArray<Obj> objects;
	for (int i = 0; i < _count; ++i) {
		objects.Append(generate<Obj>());
	}
	xseries = new DynamicArray<Pair<X, X>>(_xseries);
	int i = 0;
	for (int j = 0; j < columns_count; ++j) {
		columns->Insert(_xseries[j], new DynamicArray<Obj>);
	}
	for (int i = 0; i < _count; ++i) {
		for (int j = 0; j < columns_count; ++j) {
			if (between(take_parametr(objects[i]), _xseries[j])) {
				columns->At(_xseries[j])->Append(objects[i]);
			}
		}
	}
}

template <class Obj, class X, class Pull>
void Histogram<Obj, X, Pull>::insert(Obj& object) {
	if (!xseries) return;
	for (int i = 0; i < columns_count; ++i) {
		if (between(take_parametr(object), xseries->Get(i))) {
			columns->At(xseries->Get(i))->Append(object);
		}
	}
}

template <class Obj, class X, class Pull>
void Histogram<Obj, X, Pull>::remove(X& value) {
	if (!columns) return;
	for (int i = 0; i < columns_count; ++i) {
		if (between(value, xseries->Get(i))) {
			for (int j = 0; j < columns->At(xseries->Get(i))->GetSize(); ++j) {
				if (take_parametr(columns->At(xseries->Get(i))->Get(j)) == value) {
					columns->At(xseries->Get(i))->Delete(j);
				}
			}
		}
	}
}