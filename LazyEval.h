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
	Predicate	m_predicate;
	string		m_name;
public:
	Command(string name, Predicate& predicate) : m_name(name), m_predicate(predicate)
	{
		cout << name << " Invoked" << endl;
	}

	template<typename Container>
	void Execute(Container& container)
	{

	}
};

class WhereCommand: public Command
{
public:

	WhereCommand(Predicate& predicate) : Command("Where", predicate)
	{}

	template<typename Container>
	void Execute(Container container)
	{
		container.remove_if(std::not1(m_predicate));
	};
};


// An Factory that will create Concrete Commands based on the command type
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
	list<int> m_result;									// a temp container of the same type, so that we don't alter the original container

public:
	bool Any(Predicate& predicate)
	{
		return std::any_of(m_result.begin(), m_result.end(), predicate);
	}

	// Evaluators (terminal operations that terminate the query and evaluates it)
	void Print(Predicate& predicate)
	{
		std::for_each(m_result.begin(), m_result.end(), [&predicate](int& e) { if (predicate(e)) cout << e << " "; });
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

// Follows the Chain of Responsibility pattern
class LazyQuery : public CommandChain, public ListComprehension
{
	// Types
//	typedef typename container::value_type value_type;	// the type of the collection elements. e.g. "int" in "vector<int>"
//	typedef std::function<bool(value_type&)> Predicate;	// The predicate function (or lambda) that will be used to filter elements

	

public:

	LazyQuery(const Container& collection)
	{
		// Copy to a list
		m_result.insert(m_result.begin(), collection.begin(), collection.end());
	}

	void ExecuteChain()
	{
		for (auto pCmd : m_chain)
		{
			pCmd->Execute(m_result);
		}
	}

public:	// Factory methods 
	LazyQuery Where(Predicate predicate)
	{
		new WhereCommand(predicate);
		return *this;
	}
	
};


LazyQuery LazyFrom(Container& collection)
{
	return LazyQuery(collection);
}

namespace CommandFactory
{
	
}
