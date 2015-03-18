#include <vector>
#include <list>
#include <queue>
#include <algorithm>
#include <iostream>
#include <string>
#include <functional>
using namespace std;

typedef vector<int> Container;
typedef function<bool(int&)> Predicate;

// A Command pattern, it is lazy evaluated at the end of the query, after you call Execute()
// it is also a Strategy pattern, used to specify how a command will execute
class Command
{
public:
	Predicate	m_predicate;
	string		m_name;
public:
	Command(string name, Predicate& predicate) : m_name(name), m_predicate(predicate)
	{
		cout << name << " command created" << endl;
	}

	virtual void Execute(list<int>& container) = 0;
};

class WhereCommand: public Command
{
public:

	WhereCommand(Predicate& predicate) : Command("Where", predicate)
	{}

	void Execute(list<int>& container)
	{
		container.remove_if(std::not1(m_predicate));
	};
};


// kinda implements the ChainOfResponsiblity Pattern
// This class maintains a chain of commands in a query, till the query is invoked, it executes them sequentially
class CommandChain
{
protected:
	list<Command*>	m_chain;
	
public:

	~CommandChain()
	{
		for (auto pCmd : m_chain)
		{
			delete pCmd;
			pCmd = nullptr;
		}
		m_chain.clear();
	}

	void Chain(Command* pNextCommand)
	{
		m_chain.push_back(pNextCommand);
	}

	

};

// Contains algorithms that can convert a list to a single item, e.g. (Count, First, Last, Max, TrueIfAny, TrueIfAll, ..)
// These functions are executed immediately and are not lazy-loaded
// currently implements just a subset of these functions..
class ListComprehension 
{
protected:
	list<int> m_result;				// a temp container of the same type, so that we don't alter the original container

	virtual void BeforeEvaluation() {}
public:
	bool Any(Predicate& predicate)
	{
		BeforeEvaluation();
		return std::any_of(m_result.begin(), m_result.end(), predicate);
	}

	// Evaluators (terminal operations that terminate the query and evaluates it)
	void Print(Predicate& predicate)
	{
		BeforeEvaluation();
		std::for_each(m_result.begin(), m_result.end(), [&predicate](int& e) { if (predicate(e)) cout << e << " "; });
		cout << endl;
	}

	void Print()
	{
		BeforeEvaluation();
		std::for_each(m_result.begin(), m_result.end(), [](int& e) { cout << e << " "; });
		cout << endl;
	}

	int Count(Predicate& predicate)
	{
		BeforeEvaluation();
		return std::count_if(m_result.begin(), m_result.end(), predicate);
	}

	int Count()
	{
		BeforeEvaluation();
		return m_result.size();
	}
};

// An abstract factory pattern, it creates concrete instances of Command class (Where, select, join ...)
class LazyQuery : public ListComprehension, public CommandChain
{
public:

	LazyQuery(const Container& collection)
	{
		// Copy to a list
		m_result.insert(m_result.begin(), collection.begin(), collection.end());
	}

	// override
	void BeforeEvaluation()
	{
		for (Command* pCmd : m_chain)
		{
			pCmd->Execute(m_result);
		}
	}

public:	// Factory methods 
	LazyQuery& Where(Predicate predicate)
	{
		Chain(new WhereCommand(predicate));
		return *this;
	}
	
};


LazyQuery LazyFrom(Container& collection)
{
	return LazyQuery(collection);
}
