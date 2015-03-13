#include <vector>
#include <list>
#include <queue>
#include <algorithm>
#include <iostream>
#include <string>
#include <functional>
using namespace std;

typedef vector<int> container_type;
class Command;

template <typename T>
class Command
{
	Command* m_pNextCommand;
	Command* m_pPrevCommand;
	list<T> m_result;

public:
	string m_name;
	Command(string name) : m_name(name)
	{
		cout << name << " Invoked" << endl;
	}


	Command(const vector<T>& collection)
	{
		// Copy to a list
		m_result.insert(m_result.begin(), collection.begin(), collection.end());
	}

	//template <typename param>
	Command& Where(std::function<bool(T&)> predicate)
	{
		// removes all the items that do not satisfy the predicate .. 
		m_result.remove_if(std::not1(predicate));
		return *this;
	}

	template <class Predicate>
	bool any(Predicate& predicate)
	{
		return std::any_of(m_result.begin(), m_result.end(), predicate);
	}

	template <class Predicate>
	void print(Predicate& predicate)
	{
		std::for_each(m_result.begin(), m_result.end(), [](int& e) { if (predicate(e)) cout << e << endl; });
	}

	void print()
	{
		std::for_each(m_result.begin(), m_result.end(), [](int& e) { cout << e << endl; });
	}

	list<int>& Execute(container_type::iterator beginIt, container_type::iterator endIt)
	{

	}

	void Chain(Command& nextCommand)
	{
		m_pNextCommand = &nextCommand;
	}

};

queue<Command>& operator>> (queue<Command>& chain, Command& nextCommand)
{
	chain.push(nextCommand);

	return chain;
}


Command& operator>> (Command& left, Command& right)
{
	cout << "chain " << left.m_name << " << " << right.m_name << endl;
	return left;
	// cmd.Execute(container.begin(), container.end());
}


Command& operator>> (container_type& container, Command& cmd)
{
	return cmd;
	// cmd.Execute(container.begin(), container.end());
}





int main()
{
	vector<int> v{ 0, 1, 2, 3, 4 };

	v >> Command("one") >> Command("two") >> Command("three");

	cout << Command<int>(v).Where([](int& e){ return (e == 1); }).any([](int& e){return (e == 1); });

	return 0;
}

