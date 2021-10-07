#include <iostream>

#include <chrono>
#include <string_view>

namespace smp
{
	template<class F>
	static void time(F f, std::string_view message) {
		auto start = std::chrono::system_clock::now();
		std::chrono::duration<double> d = std::chrono::duration<double>::zero();

		size_t iteration = 0;
		for (; iteration < 100000; iteration++) {
			f();

			auto time = std::chrono::system_clock::now();
			d += time - start;

			start = time;

			if (d.count() > 5.0) {
				break;
			}
		}

		using namespace std::chrono;
		double seconds = d.count() / iteration;
		auto s = seconds;
		auto ms = s * 1000.0;
		auto us = ms * 1000.0;
		auto ns = us * 1000.0;

		double val;
		std::string_view suffix;
		if (ns < 1000.0) {
			val = ns;
			suffix = "ns";
		}
		else if (us < 1000.0) {
			val = us;
			suffix = "us";
		}
		else if (ms < 1000.0) {
			val = ms;
			suffix = "ms";
		}
		else {
			val = s;
			suffix = "s";
		}

		std::cout << "-------\n";
		std::cout << message << "\n" << "iterations: " << iteration << " average: " << val << suffix<<"\n";
		std::cout << "-------\n";
	}
}
