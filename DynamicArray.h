#pragma once

#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <time.h>
#include <stdlib.h>


template <class T> class DynamicArray {
private:
	size_t size = 0;
	T* array = nullptr;
	size_t capacity = 0;
public:
	DynamicArray();
	DynamicArray(size_t size, T* arr);
	DynamicArray(const DynamicArray<T>& d_arr);
	DynamicArray(std::initializer_list<T> lst);
	~DynamicArray();

	void MySwap(DynamicArray<T>& d_arr);
	DynamicArray<T>& operator=(DynamicArray<T> d_arr);

	void Print();
	void Print(int num);

	void Reserve(size_t new_cap);
	T& Get(int index);
	int GetSize();
	void Set(int index, T value);
	void Resize(size_t new_size);
	void InsertAt(int index, T value);
	void Append(T value);
	void Delete(size_t index);

	DynamicArray<T>* GetSublist(int start_index, int end_index);
	DynamicArray<T>* Concat(DynamicArray<T>* another);

	bool operator==(const DynamicArray<T>& a);
	bool operator!=(const DynamicArray<T>& a);
	T& operator[](int index);
	//friend std::ostream& operator<<(std::ostream&, const DynamicArray<T>&);
private:

};
template <class T> DynamicArray<T>::DynamicArray() {
	array = new T[5];
}
template <class T> DynamicArray<T>::DynamicArray(size_t size, T* arr) : capacity(2 * size), size(size) {
	array = new T[capacity];
	memcpy(array, arr, size * sizeof(T));
	/*for (int i = size; i < capacity; ++i) {
		array[i] = T();
	}*/
}
template <class T> DynamicArray<T>::DynamicArray(const DynamicArray<T>& d_arr) : DynamicArray(d_arr.size, d_arr.array) {
	//memcpy(array, d_arr.array, size * sizeof(T));
}
template <class T> DynamicArray<T>::DynamicArray(std::initializer_list<T> lst) {
	size = lst.size();
	capacity = 2 * size;
	this->array = new T[capacity];
	std::copy(lst.begin(), lst.end(), this->array);
	for (int i = size; i < capacity; ++i) {
		array[i] = T();
	}
}
template <class T> DynamicArray<T>::~DynamicArray() {
	if (array != nullptr) delete[] array;
}
template <class T> void DynamicArray<T>::MySwap(DynamicArray<T>& d_arr) {
	std::swap(size, d_arr.size);
	std::swap(capacity, d_arr.capacity);
	swap(array, d_arr.array);
}
template <class T> DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray<T> d_arr) {
	MySwap(d_arr);
	return *this;
	//DynamicArray& operator=(DynamicArray& d_arr) {
	//if (array) {
	//		delete[] array;
	//	}
	//size = d_arr.size;
	//array = new T[];
	//memcpy(array, d_arr, size*sizeof(T));
	//}
}
template <class T> T& DynamicArray<T>::Get(int index) {
	if (index < 0 || index >= size) {
			throw std::exception("Index is out of range");
		}
	return array[index];
}
template <class T> int DynamicArray<T>::GetSize() {
	return size;
}
template <class T> void DynamicArray<T>::Set(int index, T value) {
	if (index < 0 || index > size) {
		throw std::exception("Index is out of range");
	}
	array[index] = value;
}
template <class T> void DynamicArray<T>::Reserve(size_t new_cap) {
	if (new_cap <= capacity) return;
	T* buf = new T[new_cap];
	for (int i = 0; i < size; ++i) {
		buf[i] = array[i];
	}
	capacity = new_cap;
	delete[] array;
	array = buf;
}
template <class T> void DynamicArray<T>::Resize(size_t new_size) {
	if (new_size < 0) {
		throw std::exception("Index is out of range");
	}
	if (new_size <= size) {
		size = new_size;
	}
	else if (new_size <= capacity) {
		for (size_t i = size; i < new_size; ++i) {
			array[i] = T();
		}
		size = new_size;
	}
	else {
		capacity = new_size * 2;
		T* new_arr = new T[capacity];
		for (int i = 0; i < size; ++i) {
			new_arr[i] = array[i];
		}
		for (int i = size; i < capacity; ++i) {
			new_arr[i] = T();
		}
		size = new_size;
		delete[] array;
		array = new_arr;
	}
}
template <class T> void DynamicArray<T>::InsertAt(int index, T value) {
	if (index < 0 || index > size) {
		throw std::exception("Index is out of range");
	}
	else {
		if (size + 1 < capacity) {
			std::memmove(array + index + 1, array + index, (size - index) * sizeof(T));
			size++;
			Set(index, value);
		}
		else {
			Resize(size + 1);
			std::memmove(array + index + 1, array + index, (size - index) * sizeof(T));
			Set(index, value);
		}
	}
}
template <class T> void DynamicArray<T>::Append(T value) {
	if (size + 1 > capacity) {
		Reserve(2 * (size + 1));
	}
	array[size] = value;
	size++;
}
template <class T> DynamicArray<T>* DynamicArray<T>::GetSublist(int start_index, int end_index) {
	if (start_index < 0 || start_index >= size || end_index < 0 || end_index >= size) {
		throw std::exception("Index is out of range");
	}
	else {
		DynamicArray<T>* res = new DynamicArray<T>(end_index - start_index + 1, array + start_index);
		return res;
	}
}
template <class T> DynamicArray<T>* DynamicArray<T>::Concat(DynamicArray<T>* another) {
	DynamicArray<T>* res = new DynamicArray<T>(*this);
	res->Resize(another->GetSize() + this->GetSize());
	std::memcpy(res->array + size, another->array, another->GetSize() * sizeof(T));
	return res;
}
template <class T> void DynamicArray<T>::Print() {
	for (int i = 0; i < size; ++i) {
		std::cout << array[i] << '\n';
	}
}
template <class T> void DynamicArray<T>::Print(int num) {
	std::cout << " |";
	for (int i = 0; i < size; ++i) {
		std::cout << " -> " << array[i];
	}
	std::cout << '\n';
}
template <class T> bool DynamicArray<T>::operator==(const DynamicArray<T>& a) {
	if (size != a.size) {
		return false;
	}
	else {
		for (int i = 0; i < size; ++i) {
			if (array[i] != a.array[i]) {
				return false;
			}
		}
	}
	return true;
}
template <class T> bool DynamicArray<T>::operator!=(const DynamicArray<T>& a) {
	return !(*this == a);
}
template <class T> T& DynamicArray<T>::operator[](int index) {
	if (index < 0 || index >= size) {
		throw std::exception("Index is out of range");
	}
	return array[index];
}
template <class T>
std::ostream& operator<<(std::ostream& out, DynamicArray<T>& arr) {
	for (int i = 0; i < arr.GetSize(); ++i) {
		out << arr[i] << " ";
	}
	return out;
}
template <class T>
void DynamicArray<T>::Delete(size_t index) {
	if (index < 0 || index == size) {
		throw std::exception("Index out of range");
	}
	for (int i = index; i < size - 1; ++i) {
		array[i] = array[i + 1];
	}
	size--;
}
