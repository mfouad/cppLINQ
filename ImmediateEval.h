#pragma once

#include <vector>
#include <list>
#include <queue>
#include <algorithm>
#include <iostream>
#include <string>
#include <functional>

using namespace std;


template <class container>
class ImmediateQuery
{
	// Types
	typedef typename container::value_type value_type;	// the type of the collection elements. e.g. "int" in "vector<int>"
	typedef std::function<bool(value_type&)> Predicate;	// The predicate function (or lambda) that will be used to filter elements

	list<value_type> m_result;									// a temp container of the same type, so that we don't alter the original container

public:

	ImmediateQuery(const container& collection)
	{
		// Copy to a list
		m_result.insert(m_result.begin(), collection.begin(), collection.end());
	}

	//template <typename param>
	
	ImmediateQuery& Where(Predicate predicate)
	{
		// removes all the items that do not satisfy the predicate .. 
		remove_if(m_result.begin(), m_result.end(), std::not1(predicate));
		return *this;
	}

	bool Any(Predicate& predicate)
	{
		return std::any_of(m_result.begin(), m_result.end(), predicate);
	}


	// Evaluators (terminal operations that terminate the query and evaluates it)
	void Print(Predicate& predicate)
	{
		std::for_each(m_result.begin(), m_result.end(), [](int& e) { if (predicate(e)) cout << e << " "; });
		cout << endl;
	}

	void Print()
	{
		std::for_each(m_result.begin(), m_result.end(), [](int& e) { cout << e << " "; });
		cout << endl;
	}

	int Count(Predicate& predicate)
	{
		return std::count_if(m_result.begin(), m_result.end(), predicate);
	}

	int Count()
	{
		return m_result.size();
	}

};


template <typename container>
ImmediateQuery<container> From(container& collection)
{
	return ImmediateQuery<container>(collection);
}

