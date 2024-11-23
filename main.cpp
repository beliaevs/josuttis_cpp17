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

template<typename T1, typename T2>
void show(T1 x1, T2 x2)
{
	std::cout << typeid(x1).name() << " " << typeid(x2).name() << "\n";
}

// print type
template<typename T>
void printType(T)
{
	std::cout << typeid(T).name() << " ";
}

// Alexandrescu's strange example
template<typename... Ts, typename... Us>
void strange(Ts... ts, Us... us)
{
	std::cout << "Ts: ";
	(..., printType(ts));
	std::cout << "\n";
	std::cout << "Us: ";
	(..., printType(us));
	std::cout << "\n";
}

int main()
{
	printSpaced(12, 3.456, "sasha");

	{
		// Alexandrescu, partial spec
		show(2, 3.0);
		show<double>(5, "a");
	}
	{
		// Alexandrescu strange sample
		strange(1, 2., 3.f);
		strange<int, char>(0, 0, "aa", 3.5);
	}
	return 0;
}