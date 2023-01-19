#include "pch.h"
#include "CppUnitTest.h"
#include "..\lab2_sem2\Stack.h"
#include "..\lab2_sem2\Complex.h"
#include "..\lab2_sem2\Student.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab2UnitTest
{
	TEST_CLASS(Lab2UnitTest)
	{
	public:
		
		TEST_METHOD(DynamicArrayTest)
		{
			DynamicArray<int> arr_i{ 1, 2, 3, 4, 5 };
			DynamicArray<double> arr_d{ 1.1, 2.2, 3.3, 4.4, 5.5 };
			DynamicArray<Complex> arr_c{ Complex(1.1, 2.2), Complex(3.3, 4.4), Complex(5.5, 6.6) };
			DynamicArray<Student> arr_s = { Student("Popkov Ivan Sergeevich", 18, 514), Student("Danilin Yan Sergeevich", 18, 514) };
			DynamicArray<int> expected1 = arr_i;
			Assert::IsTrue(expected1 == arr_i, L"Copy constructor isn`t working");
			DynamicArray<double> expected2{ 1.1, 2.2, 3.3 };
			DynamicArray<double> expected3{ 4.4 };
			DynamicArray<double> expected4{ 1.1,2.2,3.3,4.4,5.5,1.1,2.2,3.3};
			DynamicArray<Complex> expected5{ Complex(1.1, 2.2), Complex(3.3, 4.4), Complex(5.5, 6.6),Complex(8.8, 9.9) };
			Complex number(1.1, 2.2);
			
			Assert::IsTrue(number == arr_c.Get(0), L"Getter method");
			Assert::IsTrue(arr_s.GetSize() == 2, L"GetSize method");
			Assert::IsTrue(*(arr_d.GetSublist(0, 2)) == expected2, L"GetSublist method");
			Assert::IsTrue(*arr_d.GetSublist(3, 3) == expected3, L"GetSublist method one element");
			arr_c.InsertAt(3, Complex(8.8, 9.9));
			Assert::IsTrue(arr_c == expected5, L"InsertAt method");
			Assert::IsTrue(*arr_d.Concat(&expected2) == expected4);
			arr_i.Resize(20);
			Assert::IsTrue(arr_i.GetSize() == 20, L"Resize check");
			expected4.Resize(3);
			Assert::IsTrue(expected4 == expected2, L"Resize check");
		}
		/*TEST_METHOD(LinkedListTest)
		{
			LinkedList<int> arr_i{ 1, 2, 3, 4, 5 };
			LinkedList<int> arr{ 1, 2, 3, 4, 5 };
			LinkedList<double> arr_d{1.1, 2.2, 3.3, 4.4, 5.5};
			LinkedList<Complex> arr_c{ Complex(1.1, 2.2), Complex(3.3, 4.4), Complex(5.5, 6.6) };
			LinkedList<Student> arr_s = { Student("Popkov Ivan Sergeevich", 18, 514), Student("Danilin Yan Sergeevich", 18, 514) };
			LinkedList<int> expected1 = arr_i;
			Assert::IsTrue(expected1 == arr_i, L"Copy constructor");
			LinkedList<double> expected2{ 1.1, 2.2, 3.3 };
			LinkedList<double> expected3{ 4.4 };
			LinkedList<double> expected4{ 1.1,2.2,3.3,4.4,5.5,1.1,2.2,3.3 };
			LinkedList<Complex> expected5{ Complex(1.1, 2.2), Complex(3.3, 4.4), Complex(5.5, 6.6), Complex(8.8, 9.9) };
			LinkedList<int> expected6{ 1, 2, 3, 4, 5, 9 };
			LinkedList<double> expected7{ 9.9,1.1,2.2,3.3 };
			LinkedList<Student> expected8 = { Student("Popkov Ivan Sergeevich", 18, 514) };
			Complex number(1.1, 2.2);

			Assert::IsTrue(number == arr_c.Get(0), L"Getter method");
			Assert::IsTrue(Complex(1.1, 2.2) == arr_c.GetFirst(), L"Getter method");
			Assert::IsTrue(Complex(5.5, 6.6) == arr_c.GetLast(), L"Getter method");
			Assert::IsTrue(arr_s.GetLength() == 2, L"GetSize method");
			Assert::IsTrue(*(arr_d.GetSublist(0, 2)) == expected2, L"GetSublist method");
			Assert::IsTrue(*arr_d.GetSublist(3, 3) == expected3, L"GetSublist method one element");
			arr_c.InsertAt(3, Complex(8.8, 9.9));
			Assert::IsTrue(arr_c == expected5, L"InsertAt method");
			Assert::IsTrue(*arr_d.Concat(&expected2) == expected4);
			arr_i.Append(9);
			Assert::IsTrue(arr_i == expected6, L"Resize check");
			expected2.Prepend(9.9);
			Assert::IsTrue(expected7 == expected2, L"Resize check");
			arr_s.DeleteLast();
			Assert::IsTrue(expected8 == arr_s, L"DeleteLast element");
		}
		/*TEST_METHOD(ArraySequenceTest) {
			ArraySequence<int> arr_i{ -3, 2, 5, 6 };
			ArraySequence<double> arr_d{ 1.2, 4.7, 5.3 };
			ArraySequence<Complex> arr_c{ Complex(2.4, 6.4),Complex(4.3, 9.7), Complex(1.9, 3.2) };
			ArraySequence<Student> arr_s{ Student("Ivanov Ivan Ivanovich", 20, 503), Student("Petrov Petr Petrovich", 22, 105) };
			ArraySequence<double> arr = arr_d;
			ArraySequence<int> expected1{ -3, 2, 5, 6, 7 };
			ArraySequence<double> expected2{ 1.2, 4.7 };
			ArraySequence<double> expected3{2.0, 1.2, 4.7};
			ArraySequence<Complex> expected5{ Complex(2.4,6.4), Complex(4.3, 9.7) };
			ArraySequence<int> expected6{ -3, 2, 5, 6, 7, -3, 2, 5, 6, 7 };
			ArraySequence<double> expected7{ 2.0, 1.111, 1.2, 4.7 };

			Assert::IsTrue(arr_d == arr, L"Copy constructor");
			Assert::IsTrue(arr_c.GetFirst() == Complex(2.4, 6.4), L"GetFirst method");
			Assert::IsTrue(arr_d.GetLast() == 5.3, L"GetLast method");
			Assert::IsTrue(arr_i.Get(1) == 2, L"Get method");
			Assert::IsTrue(arr_c.GetLength() == 3, L"GetLength method");
			arr_i.Append(7);
			Assert::IsTrue(arr_i == expected1, L"Append method");
			arr_d.DeleteLast();
			Assert::IsTrue(arr_d == expected2, L"DeleteLast method");
			arr_d.Prepend(2.0);
			Assert::IsTrue(arr_d == expected3, L"Prepend method");
			arr_d.InsertAt(1, 1.111);
			Assert::IsTrue(arr_d == expected7, L"InsertAt method");
			Assert::IsTrue(*arr_c.GetSubsequence(0, 1) == expected5, L"Subsequence method");
			Assert::IsTrue(*arr_i.Concat(&expected1) == expected6, L"Concat method");
		}
		TEST_METHOD(LinkedListSequenceTest) {
			LinkedListSequence<int> arr_i{ -3, 2, 5, 6 };
			LinkedListSequence<double> arr_d{ 1.2, 4.7, 5.3 };
			LinkedListSequence<Complex> arr_c{ Complex(2.4, 6.4),Complex(4.3, 9.7), Complex(1.9, 3.2) };
			LinkedListSequence<Student> arr_s{ Student("Ivanov Ivan Ivanovich", 20, 503), Student("Petrov Petr Petrovich", 22, 105) };
			LinkedListSequence<double> arr = arr_d;
			LinkedListSequence<int> expected1{ -3, 2, 5, 6, 7 };
			LinkedListSequence<double> expected2{ 1.2, 4.7 };
			LinkedListSequence<double> expected3{ 2.0, 1.2, 4.7 };
			LinkedListSequence<Complex> expected5{ Complex(2.4,6.4), Complex(4.3, 9.7) };
			LinkedListSequence<int> expected6{ -3, 2, 5, 6, 7, -3, 2, 5, 6, 7 };
			LinkedListSequence<double> expected7{ 2.0, 1.111, 1.2, 4.7 };

			Assert::IsTrue(arr_d == arr, L"Copy constructor");
			Assert::IsTrue(arr_c.GetFirst() == Complex(2.4, 6.4), L"GetFirst method");
			Assert::IsTrue(arr_d.GetLast() == 5.3, L"GetLast method");
			Assert::IsTrue(arr_i.Get(1) == 2, L"Get method");
			Assert::IsTrue(arr_c.GetLength() == 3, L"GetLength method");
			arr_i.Append(7);
			Assert::IsTrue(arr_i == expected1, L"Append method");
			arr_d.DeleteLast();
			Assert::IsTrue(arr_d == expected2, L"DeleteLast method");
			arr_d.Prepend(2.0);
			Assert::IsTrue(arr_d == expected3, L"Prepend method");
			arr_d.InsertAt(1, 1.111);
			Assert::IsTrue(arr_d == expected7, L"InsertAt method");
			Assert::IsTrue(*arr_c.GetSubsequence(0, 1) == expected5, L"Subsequence method");
			Assert::IsTrue(*arr_i.Concat(&expected1) == expected6, L"Concat method");
		}
		TEST_METHOD(StackTest) {
			Stack<int> st_i({ -4,2,5,6,1,9 }, 1);
			Stack<double> st_d({ -8.2, 7.5, 3.2}, 2);
			Stack<Complex> st_c({ Complex(1.2, 3.4), Complex(1.1, 2.2) }, 1);
			Assert::IsTrue(st_i.Top() == 9, L"Top method");
		}*/
	};
}
