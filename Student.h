#pragma once
#include <string>
#include <iostream>

class Student {
private:
	std::string name;
	int age = 0;
	int group = 0;
	int course = 0;
public:
	Student() = default;
	~Student() = default;
	explicit Student(std::string name, int age = 0, int group = 0, int course = 0) {
		this->name = name;
		this->age = age;
		this->group = group;
		this->course = course;
	}
	Student(const Student& another) {
		name = another.name;
		age = another.age;
		group = another.group;
		course = another.course;
	}
	std::string GetFirstName() const {
		return name;
	}
	int GetAge() const {
		return age;
	}
	int GetGroup() const {
		return group;
	}
	int GetCourse() const {
		return course;
	}	
	void SetAge(int a) {
		age = a;
	}
	void SetGroup(int g) {
		group = g;
	}
	void SetCourse(int c) {
		course = c;
	}
	void SetName(std::string n) {
		name = n;
	}
	Student& operator=(const Student& st) {
		name = st.name;
		age = st.age;
		group = st.group;
		course = st.course;
		return *this;
	}
};

bool operator<(const Student& first, const Student& second) {
	return first.GetAge() < second.GetAge();
}
bool operator>(const Student& first, const Student& second) {
	return second < first;
}
bool operator==(const Student& first, const Student& second) {
	return !(first < second || second < first);
}
bool operator!=(const Student& first, const Student& second) {
	return !(first == second);
}
std::ostream& operator<<(std::ostream& out, const Student& student) {
	out << "{ " << student.GetFirstName() <<  " " << student.GetAge() << " " << student.GetGroup() << " " << student.GetCourse() << " }";
	return out;
}



struct Age {
	int operator()(const Student& st){
		return st.GetAge();
	}
};
struct Course {
	int operator() (const Student& st) {
		return st.GetCourse();
	}
};
struct Group {
	int operator() (const Student& st) {
		return st.GetGroup();
	}
};