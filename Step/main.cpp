
template <typename Type>
class basic_loop {
public:

	basic_loop(Type _max) : count(0), maximum(_max) {}
	basic_loop(Type _min, Type _max) : count(_min), maximum(_max) {}

	inline basic_loop& begin() { return *this; }
	inline basic_loop& end() { return *this; }

	inline basic_loop& operator++() { count++; return *this; }
	inline bool operator!=(basic_loop&) const { return count < maximum; }
	inline Type& operator*() { return count; }

private:

	Type maximum;
	Type count;

};

using step = basic_loop<long long int>;

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <functional>

void func(std::function<void()> f) {

	const auto start = std::chrono::system_clock::now();

	f();

	const auto end = std::chrono::system_clock::now();

	const auto diff = end - start;
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() << "ms" << std::endl;
}

#define N 10000000000

int main() {

	func([]() {
		int a = 0;
		for (long long int i = 0; i < N; i++)
		{
			for (long long int j = 0; j < N; j++)
				a++;
		}
		std::cout << a << std::endl;
	});

	func([]() {
		int a = 0;
		for (const auto& i : step(N))
		{
			for (const auto& j : step(N))
				a++;
		}
		std::cout << a << std::endl;
	});

	return 0;
}
