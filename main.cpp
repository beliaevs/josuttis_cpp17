#include<iostream>
#include<list>
#include<map>
#include<ranges>
#include<string>
#include<variant>
#include<vector>

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

//concepts: c++20
void myprint(const std::ranges::input_range auto& cont)
{
	for (const auto& el : cont)
	{
		std::cout << el << " ";
	}
	std::cout << "\n";
}

void ranges_test()
{
	std::vector<int> vec{ 1, 3, 2, 4, 3, 5, 4, 6 };
	std::list<int> l{ 2, 4, 3, 6, 4, 7, 6, 9, 10 };
	myprint(vec);
	myprint(l);
	// views: c++20
	myprint(std::views::take(vec, 3));
	myprint(l | std::views::take(3));
	myprint(vec | std::views::take(4)
		| std::views::transform([](auto v) {
			return std::to_string(v) + 's';
			}));
	// zip_view: c++23
	for (auto [idx, el] : std::ranges::zip_view(std::views::iota(1), vec))
	{
		std::cout << idx << ": " << el << "\n";
	}
}

void more_advanced()
{
	std::map<std::string, int> composers{
		{"Bach", 1685},
		{"Mozart", 1756},
		{"Beethoven", 1770},
		{"Tchaikovsky", 1840},
		{"Chopin", 1810},
		{"Vivaldi", 1678}
	};
	namespace vws = std::views;
	for (const auto& elem : composers
		| vws::filter([](const auto& v) { return v.second > 1700; })
		| vws::take(3)
		| vws::keys)
	{
		std::cout << "-" << elem << "\n";
	}
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
	{
		// josuttis on ranges c++20
		ranges_test();
		more_advanced();
	}
	return 0;
}