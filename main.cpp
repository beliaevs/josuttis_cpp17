#include<iostream>

template<auto sep = ' ', typename First, typename... Types>
void printSpaced(const First& arg, const Types&... args)
{
	std::cout << arg;
	auto outWithSep = [](const auto& arg) {
		std::cout << sep << arg; };

	(..., outWithSep(args));
	std::cout << "\n";
}

int main()
{
	printSpaced(12, 3.456, "sasha");
	return 0;
}