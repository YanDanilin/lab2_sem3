#pragma once
#include "HashTable.h"
#include "LinkedList.h"
#include "DynamicArray.h"
#include <string>



template <bool WordCount>
class WordPointer {
private:
	HashTable<std::string, LinkedList<size_t>>* wp = nullptr;;
	size_t page_size = 0;
	size_t page_count = 0;
	const std::string punct_marks = ".,!?:;(){}[]/|~`@#$%^&*_-+=<>'\"\\";
	std::vector<std::string> words;

	void split(const std::string& str);
	void fill_wp();
public:
	WordPointer() = default;
	WordPointer(const std::string& str, size_t _page_size);
	~WordPointer() = default;
	void print();

	void add(const std::string& const);
	void remove(const std::string& const);
	LinkedList<size_t> get_page(const std::string& str);

	size_t get_page_count() const;
	size_t get_words_count() const;
};

template <bool WordCount>
WordPointer<WordCount>::WordPointer(const std::string& str, size_t _page_size) {
	page_size = _page_size;
	split(str);
	fill_wp();
}
template <bool WordCount>
void WordPointer<WordCount>::split(const std::string& str) {
	words.reserve(words.size() + str.size() / 2);
	std::string word = "";
	for (int i = 0; i < str.size(); ++i) {
		if (str[i] != ' ' && str[i] != '\n' && str[i] != '\t') {
			if (punct_marks.find(str[i]) == std::string::npos) {
				word.push_back(str[i]);
			}
		}
		else if (word != "") {
			words.push_back(word);
			word.clear();
		}
	}
	if (word != "")
	words.push_back(word);
}
template <bool WordCount>
void WordPointer<WordCount>::fill_wp() {
	if (wp) delete wp;
	wp = new HashTable<std::string, LinkedList<size_t>>;
	wp->Reserve(words.size());
	page_count = 1;
	if (WordCount) {
		int cur_counter = 0;
		for (int i = 0; i < words.size(); ++i) {
			cur_counter++;
			if (page_count == 1 && cur_counter > 0.5 * page_size || page_count % 10 == 0 && cur_counter > 0.75 * page_size) {
				page_count++;
				cur_counter = 1;
			}
			else if (cur_counter > page_size) {
				page_count++;
				cur_counter = 1;
			}
			wp->At(words[i]).Append(page_count);
		}
	}
	else {
		size_t char_count = 0;
		int cur_counter = 0;
		for (int i = 0; i < words.size(); ++i) {
			cur_counter += words[i].size();
			if (page_count == 1 && cur_counter > 0.5 * page_size || page_count % 10 == 0 && cur_counter > 0.75 * page_count) {
				page_count++;
				cur_counter = words[i].size();
			}
			else if (cur_counter > page_size) {
				page_count++;
				cur_counter = words[i].size();
			}
			wp->At(words[i]).Append(page_count);
			if (i != words.size() - 1)
			cur_counter++;
		}
	}
}
template <bool WordCount>
void WordPointer<WordCount>::print() {
	std::cout << "page count : " << page_count << '\n';
	std::cout << "word count : " << words.size() << '\n';
	std::cout << "page size  : " << page_size << '\n';
	for (int i = 0; i < words.size(); ++i) {
		int counter = 0;
		for (int j = i - 1; j > 0; j--) {
			if (words[i] == words[j]) {
				counter++;
			}
		}
		if (counter == 0) {
			std::cout << "\"" << words[i] << "\" : ";
			LinkedList<size_t>* ll = &(wp->At(words[i]));
			std::cout << "{ ";
			for (int k = 0; k < ll->GetLength(); ++k) {
				std::cout << ll->Get(k) << " ";
			}
			std::cout << "}\n";
		}
	}
}
template <bool WordCount>
size_t WordPointer<WordCount>::get_page_count() const {
	return page_count;
}
template <bool WordCount>
size_t WordPointer<WordCount>::get_words_count() const {
	return words.size();
}

template <bool WordCount>
void WordPointer<WordCount>::add(const std::string& str) {
	if (str.empty()) return;
	split(str);
	fill_wp();
}

template <bool WordCount>
void WordPointer<WordCount>::remove(const std::string& str) {
	if (!wp) return;
	if (str.empty() || !wp->Find(str)) return;
	std::string word = "";
	for (int i = 0; i < str.size(); ++i) {
		if (str[i] != ' ' && str[i] != '\n' && str[i] != '\t') {
			if (punct_marks.find(str[i]) == std::string::npos) {
				word.push_back(str[i]);
			}
		}
		else if (word != "") {
			for (std::vector<std::string>::iterator it = words.begin(); it != words.end(); it++) {
				if (*it == word) {
					words.erase(it);
				}
			}
			word.clear();
		}
	}
	if (word != "") {
		for (std::vector<std::string>::iterator it = words.begin(); it != words.end();) {
			if (*it == word) {
				it = words.erase(it);
			}
			else {
				++it;
			}
		}
	}
	fill_wp();
}

template <bool WordCount>
LinkedList<size_t> WordPointer<WordCount>::get_page(const std::string& str) {
	if (wp->Find(str)) {
		return wp->At(str);
	}
	return LinkedList<size_t>({ 0 });
}