#include <cassert>

#include <functional>
#include <algorithm>
#include <concepts>
#include <iostream>
#include <limits>
#include <string>
#include <chrono>
#include <array>

template <typename T>
concept arithmetic = std::integral<T> || std::floating_point<T>;

template <arithmetic T>
constexpr T MIN_NUMBER = std::numeric_limits<T>::min();

template <arithmetic T>
constexpr T MAX_NUMBER = std::numeric_limits<T>::max();

void Timer(const std::function<void()>& f)
{
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	f();
	std::cout
		<< "time: " << std::fixed
		<< (std::chrono::steady_clock::now() - start).count() / 1000000.0
		<< "ms\n";
}

struct range
{
public:
	struct range_iterator
	{
	public:
		range_iterator(int value, int step) : value(value), step(step) {}
		int& operator * () { return value; }
		range_iterator& operator ++ () { value += step; return *this; }
		bool operator != (const range_iterator& other) { return value < other.value; }

	private:
		int value, step;
	};

public:
	range(int stop) : start(0), stop(stop), step(1) {}
	range(int start, int stop, int step = 1) : start(start), stop(stop), step(step) {}
	range_iterator begin() { return range_iterator(start, step); }
	range_iterator end() { return range_iterator(stop, step); }

private:
	int start, stop, step;
};

constexpr size_t WIN = 3;
constexpr size_t DRAW = 2;
constexpr size_t LOSE = 1;

enum class status_type
{
	O,
	X,
	empty
};

struct game_map
{
	std::array<status_type, 9> map;

	game_map() { map.fill(status_type::empty); }

	game_map(const game_map&) = default;
	game_map(game_map&&) = default;
	~game_map() = default;
	game_map& operator = (const game_map&) = default;
	game_map& operator = (game_map&&) = default;

	void update(size_t step, status_type type) { map.at(step) = type; }

	bool is_full() const
	{
		return std::ranges::all_of(map.begin(), map.end(), [](auto t) { return t != status_type::empty; });
	}

	bool is_win(status_type type) const
	{
		for(auto i : range(3))
		{
			if(map[i] == type && map[i + 3] == type && map[i + 6] == type) return true;
			if(map[i * 3] == type && map[i * 3 + 1] == type && map[i * 3 + 2] == type) return true;
		}
		if(map[0] == type && map[4] == type && map[8] == type) return true;
		if(map[2] == type && map[4] == type && map[6] == type) return true;
		return false;
	}
};

std::ostream& operator << (std::ostream& os, const game_map& m)
{
	static std::string str = "   |   |  \n-----------\n   |   |  \n-----------\n   |   |  \n";
	const std::array index_list = { 1, 5, 9, 24, 28, 32, 47, 51, 55 };
	for(auto i : range(9))
	{
		switch(m.map[i])
		{
            case status_type::O:	 str[index_list[i]] = 'O'; break;
            case status_type::X:	 str[index_list[i]] = 'X'; break;
            case status_type::empty: str[index_list[i]] = ' '; break;
		}
	}
	os << str;
	return os;
}

struct AI
{
	const status_type type;
	game_map& m;

	AI(status_type type, game_map& m) : type(type), m(m) {}
	AI() = delete;
	AI(const AI&) = default;
	AI(AI&&) = default;
	~AI() = default;
	AI& operator = (const AI&) = default;
	AI& operator = (AI&&) = default;

	size_t find_max_step()
	{
        return 0;
	}

	size_t find_min_step()
	{
        return 0;
	}

	size_t find_step()
	{
        return 0;
	}
};

size_t player_input(const game_map& m)
{
	size_t step;
	for(;;)
	{
		std::cout << "Please input you step: ";
		std::cin >> step;
		if(step >= 1 && step <= 9 && m.map[step - 1] == status_type::empty)
		{
			return step - 1;
		}
		std::cout << "Try again. Enter a correct number in 1-9.\n";
	}
}

int main()
{
	size_t time = 0;
	game_map m;
	AI ai{ status_type::X, m };

	size_t step;
	status_type status;

	bool flag = true;

	std::cout << "game start!\n" << m << '\n';
	while(time <= 8)
	{
		if(flag)
		{
			flag = false;
			step = player_input(m);
			status = status_type::O;
		}
		else
		{
			flag = true;
			// Timer([&]() { step = ai.find_step(); });
			step = ai.find_step();
			status = status_type::X;
		}

		m.update(step, status);
		std::cout << m << '\n';

		if(m.is_win(status)) break;

		status = status_type::empty;
		time++;
	}

	std::cout << m << '\n';
	switch(status)
	{
		case status_type::O:	 std::cout << "You win!\n";		break;
		case status_type::X:	 std::cout << "You failed.\n";  break;
		case status_type::empty: std::cout << "draw.\n";		break;
	}
}
