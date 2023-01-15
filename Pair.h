#pragma once

template <typename First, typename Second>
struct Pair {
public:
	First first;
	Second second;
public:
	Pair() = default;
	explicit Pair(First _first, Second _second) {
		first = _first;
		second = _second;
	}
	Pair(const Pair<First, Second>& another){
		first = another.first;
		second = another.second;
	}
	Pair(const std::pair<First, Second>& another) {
		first = another.first;
		second = another.second;
	}
	~Pair() = default;
	Pair& operator=(Pair pair) {
		std::swap(first, pair.first);
		std::swap(second, pair.second);
		return *this;
	}
};
template <typename First, typename Second>
bool operator==(const Pair<First, Second>& one, const Pair<First, Second>& two) {
	if (one.first == two.first && one.second == two.second) {
		return true;
	}
	return false;
}
template <typename First, typename Second>
bool operator!=(const Pair<First, Second>& one, const Pair<First, Second>& two) {
	return !(one == two);
}
template <typename First, typename Second>
std::ostream& operator<<(std::ostream& out, const Pair<First, Second>& pair) {
	out << "[" << pair.first << ", " << pair.second << "]";
	return out;
}