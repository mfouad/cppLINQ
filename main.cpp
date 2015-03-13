#include <vector>
#include <list>
#include <queue>
#include <algorithm>
#include <iostream>
#include <string>
#include <functional>
using namespace std;

typedef vector<int> container_type;

template <typename T>
class Command
{
	list<T> m_result;
	
public:

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


	// Evaluators (terminal operations that terminate the query and evaluates it)
	template <class Predicate>
	void print(Predicate& predicate)
	{
		std::for_each(m_result.begin(), m_result.end(), [](int& e) { if (predicate(e)) cout << e << endl; });
	}

	void print()
	{
		std::for_each(m_result.begin(), m_result.end(), [](int& e) { cout << e << endl; });
	}

	template <class Predicate>
	int count(Predicate& predicate)
	{
		return std::count_if(m_result.begin(), m_result.end(), predicate);
	}

	int count()
	{
		return m_result.size();
	}

};


int main()
{
	vector<int> v{ 0, 1, 2, 3, 4 };

	Command<int>(v).Where([](int& e){ return (e == 1); }).print();

	cout << Command<int>(v).Where([](int& e){ return (e == 1); }).count();


	cout << Command<int>(v).Where([](int& e){ return (e == 1); }).any([](int& e){return (e == 1); });

	return 0;
}

