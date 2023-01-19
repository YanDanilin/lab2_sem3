#include "pch.h"
#include "CppUnitTest.h"
#include "../lab2_sem3/Histogram.h"
#include "../lab2_sem3/WordPointer.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(HistogramTests)
	{
	public:
		
		TEST_METHOD(Filling)
		{
			srand(time(NULL));
			struct KeyGetter {
				char operator()(const std::string& str) {
					if (str.empty()) return ' ';
					return str[0];
				}
			};
			DynamicArray<Pair<char, char>> xseries({ Pair<char,char>{'a', 'f'},Pair<char,char>{'g', 'k'},Pair<char,char>{'l', 'p'},Pair<char,char>{'q', 'v'},Pair<char,char>{'w', 'z'} });
			DynamicArray<std::string> str_arr;
			str_arr.Reserve(10000);
			for (int i = 0; i < 10000; ++i) {
				str_arr.Append(generate<std::string>());
			}
			Histogram<std::string, char, KeyGetter> hist(xseries, str_arr);
			for (int i = 0; i < 1000; ++i) {
				hist.insert(generate<std::string>());
			}
			char c = 'c';
			char i = 'i';
			char o = 'o';
			char x = 'x';
			char r = 'r';
			hist.remove(c);
			hist.remove(i);
			hist.remove(o);
			hist.remove(x);
			hist.remove(r);
		}
		TEST_METHOD(Functions) {
			DynamicArray<Pair<int, int>> xseries({ Pair<int, int>{1, 20}, Pair<int, int>{21, 40},
												Pair<int, int>{41, 60},Pair<int, int>{61, 80},
												Pair<int, int>{81, 100} });
			DynamicArray<Student> objs({ Student("Yan", 19), Student("Alexey", 19),
			Student("Andrey", 20), Student("Artem", 40), Student("Nikita", 28),
			Student("Artem", 42), Student("Michail", 55), Student("Ivan", 63),
			Student("Jimmy", 69), Student("Maxim", 24), Student("Rob", 82),
			Student("John", 31), Student("LordByron", 49) });
			Histogram<Student, int, Age> hist(xseries, objs);
			double mean1 = 19 + 19 + 20;
			double mean2 = 40 + 28 + 24 + 31;
			double mean3 = 42 + 55 + 49;
			double mean4 = 69 + 63;
			double mean5 = 82;
			Assert::IsTrue(hist.mean(Pair<int, int>{1, 20}) == mean1/3, L"First column, mean");
			Assert::IsTrue(hist.mean(Pair<int, int>{21, 40}) == mean2/4, L"Second column, mean");
			Assert::IsTrue(hist.mean(Pair<int, int>{41, 60}) == mean3/3, L"Third column, mean");
			Assert::IsTrue(hist.mean(Pair<int, int>{61, 80}) == mean4/2, L"First column, mean");
			Assert::IsTrue(hist.mean(Pair<int, int>{81, 100}) == mean5, L"First column, mean");

			Assert::IsTrue(hist.max(Pair<int, int>{1, 20}) == 20, L"First column, max");
			Assert::IsTrue(hist.max(Pair<int, int>{21, 40}) == 40, L"Second column, max");
			Assert::IsTrue(hist.max(Pair<int, int>{41, 60}) == 55, L"Third column, max");
			Assert::IsTrue(hist.max(Pair<int, int>{61, 80}) == 69, L"First column, max");
			Assert::IsTrue(hist.max(Pair<int, int>{81, 100}) == 82, L"First column, max");

			Assert::IsTrue(hist.min(Pair<int, int>{1, 20}) == 19, L"First column, min");
			Assert::IsTrue(hist.min(Pair<int, int>{21, 40}) == 24, L"Second column, min");
			Assert::IsTrue(hist.min(Pair<int, int>{41, 60}) == 42, L"Third column, min");
			Assert::IsTrue(hist.min(Pair<int, int>{61, 80}) == 63, L"First column, min");
			Assert::IsTrue(hist.min(Pair<int, int>{81, 100}) == 82, L"First column, min");

			Assert::IsTrue(hist.get_columns_count() == 5, L"Get columns count method");
			Assert::IsTrue(hist.get_count() == 13, L"Get count method");
		}
	};
	TEST_CLASS(WPointerTests) {
		TEST_METHOD(Filling) {
			srand(time(NULL));
			std::string str;
			str.reserve(10000);
			for (int j = 0; j < 500; ++j) {
				for (int i = 0; i < 20; i++) {
					str.push_back(static_cast<char>(33 + rand() % 95));
				}
				str.push_back(' ');
			}
			WordPointer<true> wp(str, 10);
		}
		TEST_METHOD(WordCountCorrectness) {
			std::string str("I live in Moscow although my friends live near London");
			WordPointer<true> wp(str, 3);
			Assert::IsTrue(wp.get_page("I")[0] == 1, L"I");
			Assert::IsTrue(wp.get_page("live")[0] == 2, L"live(first occurannce");
			Assert::IsTrue(wp.get_page("in")[0] == 2, L"in");
			Assert::IsTrue(wp.get_page("Moscow")[0] == 2, L"Moscow");
			Assert::IsTrue(wp.get_page("although")[0] == 3, L"although");
			Assert::IsTrue(wp.get_page("my")[0] == 3, L"my");
			Assert::IsTrue(wp.get_page("friends")[0] == 3, L"friends");
			Assert::IsTrue(wp.get_page("live")[1] == 4, L"live(second ocurrance");
			Assert::IsTrue(wp.get_page("near")[0] == 4, L"near");
			Assert::IsTrue(wp.get_page("London")[0] == 4, L"London");
			Assert::IsTrue(wp.get_page("We")[0] == 0, L"We");
			Assert::IsTrue(wp.get_page_count() == 4, L"Get page count method");
			Assert::IsTrue(wp.get_words_count() == 10, L"Get words count method");
			wp.add("It is cool");
			Assert::IsTrue(wp.get_page("It")[0] == 5, L"It");
			Assert::IsTrue(wp.get_page("is")[0] == 5, L"is");
			Assert::IsTrue(wp.get_page("cool")[0] == 5, L"cool");
		}
		TEST_METHOD(CharCountCorrectness) {
			std::string str("I live in Moscow although my friends live near London");
			WordPointer<false> wp(str, 9);
			Assert::IsTrue(wp.get_page("I")[0] == 1, L"I");
			Assert::IsTrue(wp.get_page("live")[0] == 2, L"live(first occurannce");
			Assert::IsTrue(wp.get_page("in")[0] == 2, L"in");
			Assert::IsTrue(wp.get_page("Moscow")[0] == 3, L"Moscow");
			Assert::IsTrue(wp.get_page("although")[0] == 4, L"although");
			Assert::IsTrue(wp.get_page("my")[0] == 5, L"my");
			Assert::IsTrue(wp.get_page("friends")[0] == 6, L"friends");
			Assert::IsTrue(wp.get_page("live")[1] == 7, L"live(second ocurrance");
			Assert::IsTrue(wp.get_page("near")[0] == 7, L"near");
			Assert::IsTrue(wp.get_page("London")[0] == 8, L"London");
			Assert::IsTrue(wp.get_page("We")[0] == 0, L"We");
			wp.add("It is cool");
			Assert::IsTrue(wp.get_page("It")[0] == 8, L"It");
			Assert::IsTrue(wp.get_page("is")[0] == 9, L"is");
			Assert::IsTrue(wp.get_page("cool")[0] == 9, L"cool");
		}
		TEST_METHOD(RemoveWithWordCount) {
			std::string str("I live in Moscow although my friends live near London");
			WordPointer<true> wp_w(str, 3);
			wp_w.remove("live");
			Assert::IsTrue(wp_w.get_page("I")[0] == 1, L"I");
			Assert::IsTrue(wp_w.get_page("live")[0] == 0, L"live(first occurannce");
			Assert::IsTrue(wp_w.get_page("in")[0] == 2, L"in");
			Assert::IsTrue(wp_w.get_page("Moscow")[0] == 2, L"Moscow");
			Assert::IsTrue(wp_w.get_page("although")[0] == 2, L"although");
			Assert::IsTrue(wp_w.get_page("my")[0] == 3, L"my");
			Assert::IsTrue(wp_w.get_page("friends")[0] == 3, L"friends");
			Assert::IsTrue(wp_w.get_page("live")[0] == 0, L"live(second ocurrance");
			Assert::IsTrue(wp_w.get_page("near")[0] == 3, L"near");
			Assert::IsTrue(wp_w.get_page("London")[0] == 4, L"London");
			Assert::IsTrue(wp_w.get_page_count() == 4, L"Get page count after removing");
		}
		TEST_METHOD(RemoveWithCharCount) {
			std::string str("I live in Moscow although my friends live near London");
			WordPointer<false> wp_c(str, 9);
			wp_c.remove("live");
			Assert::IsTrue(wp_c.get_page("I")[0] == 1, L"I");
			Assert::IsTrue(wp_c.get_page("live")[0] == 0, L"live(first occurannce");
			Assert::IsTrue(wp_c.get_page("in")[0] == 1, L"in");
			Assert::IsTrue(wp_c.get_page("Moscow")[0] == 2, L"Moscow");
			Assert::IsTrue(wp_c.get_page("although")[0] == 3, L"although");
			Assert::IsTrue(wp_c.get_page("my")[0] == 4, L"my");
			Assert::IsTrue(wp_c.get_page("friends")[0] == 5, L"friends");
			Assert::IsTrue(wp_c.get_page("live")[0] == 0, L"live(second ocurrance");
			Assert::IsTrue(wp_c.get_page("near")[0] == 6, L"near");
			Assert::IsTrue(wp_c.get_page("London")[0] == 7, L"London");
			Assert::IsTrue(wp_c.get_page_count() == 7, L"Get page count after removing");
		}
	};
}
