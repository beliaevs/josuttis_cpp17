#include<iostream>
#include<string>
#include<variant>

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

// odd2 is ill-formed: Us is always empty
//template<typename... Ts, typename... Us, typename... Vs>
//void odd3(Ts... ts, Us... us, Vs... vs)
//{}

template<typename...Ts>
void expansion(Ts... xs)
{
	int a[] = {xs...};
	for (auto t : a)
	{
		std::cout << t << " ";
	}
	std::cout << "\n";
}

// T cannot be deduced in any case
//template<typename...Ts, typename T>
//void f() {}

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
	{
		expansion(2, 3, 4, 5);
	}
	{
		std::tuple<> emptyTuple;
		std::cout << "empty tuple size: " << sizeof(emptyTuple) << "\n";
		std::tuple<int> oneElement{ 42 };
		std::cout << "one element tuple size: " << sizeof(oneElement) << ", val: " << std::get<0>(oneElement) << "\n";
		std::tuple<int, std::string> m;
		std::get<0>(m) = 24;
		std::get<1>(m) = "sasha";
		std::cout << "m = {" << std::get<0>(m) << ", " << std::get<1>(m) << "}\n";
	}
	{
		struct S1 
		{ 
			~S1()
			{
				std::cout << "~S1\n";
			}
		};
		struct S2
		{
			~S2()
			{
				std::cout << "~S2\n";
			}
		};
		std::variant<std::monostate, S1, S2> s;
		s.emplace<2>();
		s = S1();
	}
	return 0;
}