#pragma once
#include <iostream>
#include <vector>
#include "Histogram.h"
#include "Student.h"

template <class X>
void get_xseries(DynamicArray<Pair<X, X>>& xseries) {
	Pair<X, X> pair;
	std::cout << "Enter pair of partition:\n";
	std::cin >> pair.first >> pair.second;
	while (pair.first != X() && pair.second != X()) {
		xseries.Append(pair);
		std::cout << "Enter pair of partition:\n";
		std::cin >> pair.first >> pair.second;
	}
}

template <class T>
void menu_type() {
	int var = 1;
	Histogram<Student, int, T> hist;
	while (var) {
		std::cout << "Choose option:\n 1. Fill random\n 2. Add\n 3. Remove\n 4. Show\n 5. Show with elements\n 6. Describe\n 7. Back\n> ";
		std::cin >> var;
		switch (var) {
		case 1:
		{
			size_t count = 0;
			std::cout << "Enter quantity: ";
			std::cin >> count;
			DynamicArray<Pair<int, int>> xseries;
			xseries.Reserve(count);
			get_xseries<int>(xseries);
			hist.fill_rand(count, xseries); }
			break;
		case 2:
		{std::cout << "Enter name, age, group, course:\n";
		std::string _name;
		int _age;
		int _group;
		int _course;
		std::cin >> _name >> _age >> _group >> _course;
		Student st(_name, _age, _group, _course);
		hist.insert(st); }
		break; 
		case 3:
		{
			int a = 0;
			std::cout << "Enter value: ";
			std::cin >> a;
			hist.remove(a); }
			break;
		case 4:
			hist.show();
			break;
		case 5:
			std::cout << hist;
			break;
		case 6:
			hist.describe();
			break;
		case 7:
			var = 0;
			break;
		default:
			std::cout << "Wrong option... Try again\n";
			break;
		}
	}
}

void menu_hist() {
	int var = 1;
	while (var) {
		std::cout << "Chose category to work with:\n 1. Age\n 2. Group\n 3. Course\n 4. Quit\n> ";
		std::cin >> var;
		switch (var) {
		case 1:
			menu_type<Age>();
		break;
		case 2:
			menu_type<Group>();
		break;
		case 3:
			menu_type<Course>();
		break;
		case 4:
			var = 0;
			break;
		default:
			std::cout << "Wrong input... Try again\n";
		}
	}
}
template <bool Counter>
void menu_wp_type() {
	int var = 1;
	WordPointer<Counter>* wp = nullptr;
	while (var) {
		std::cout << "Choose option:\n 1. Input\n 2. Fill rand\n 3. Add\n 4. Remove\n 5. Print\n 6. Back\n> ";
		std::cin >> var;
		switch (var) {
		case 1:
		{
			if (wp) delete wp;
			int page_size = 0;
			std::cout << "Enter page size: ";
			std::cin >> page_size;
			std::string input;
			std::cin.ignore();
			std::cout << "Enter string:\n";
			std::getline(std::cin, input);
			wp = new WordPointer<Counter>(input, page_size);
			break; 
		}
		case 2:
		{
			std::cout << "Enter words quantity: ";
			size_t count = 0;
			std::cin >> count;
			std::cout << "Enter page size: ";
			size_t ps = 0;
			std::cin >> ps;
			if (wp) delete wp;
			srand(time(NULL));
			std::string str;
			str.reserve(count);
			for (int j = 0; j < count; ++j) {
				for (int i = 0; i < 12; i++) {
					str.push_back(static_cast<char>(33 + rand() % 95));
				}
				str.push_back(' ');
			}
			wp = new WordPointer<Counter>(str, ps);
			break;
		}
		case 3:
		{
			std::string word;
			std::cout << "Enter word or sentence:\n";
			std::cin.ignore();
			std::getline(std::cin, word);
			wp->add(word);
			break;
		}
		case 4:
		{
			std::string word;
			std::cout << "Enter word or sentence:\n";
			std::cin.ignore();
			std::getline(std::cin, word);
			wp->remove(word); 
			break;
		}
		case 5:
			if (wp) {
				wp->print();
			}
			break;
		case 6:
			if (wp) delete wp;
			var = 0;
			break;
		default:
			std::cout << "Wrong option... Try again\n";
		}
	}
}

void menu_wp() {
	int var = 1;
	while (var) {
		std::cout << "Choose page size measure:\n 1. Chars\n 2. Words\n 3. Back\n> ";
		std::cin >> var;
		switch (var) {
		case 1:
			menu_wp_type<false>();
			break;
		case 2:
			menu_wp_type<true>();
			break;
		case 3:
			var = 0;
			break;
		default:
			std::cout << "Wrong input... Try again\n";
		}
	}
}

void menu() {
	int var = 1;
	while (var) {
		std::cout << "Choose the class:\n1. Histogram\n2. Word pointer\n3. Quit\n> ";
		std::cin >> var;
		switch (var) {
		case 1:
			menu_hist();
			break;
		case 2:
			menu_wp();
			break;
		case 3:
			var = 0;
			break;
		default:
			std::cout << "Wrong option... Try again\n";
		}
	}
}