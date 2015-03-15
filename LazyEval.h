#include <vector>
#include <list>
#include <queue>
#include <algorithm>
#include <iostream>
#include <string>
#include <functional>
using namespace std;

typedef vector<int> Container;

// A Command pattern, it is lazy evaluated at the end of the query, after you call Execute()
// it is also a Strategy pattern, used to specify how a command will execute
class Command
{
	// types
	//typedef function<void(value_type&)> Filter;

	Filter		m_Filter;
	string		m_name;
public:
	Command(string name, Filter& filter) : m_name(name), m_Filter(filter)
	{
		cout << name << " Invoked" << endl;
	}

	template<typename Container>
	void Execute(Container& container)
	{
		m_Filter(container);
	}

	template <typename Predicate>
	Command& operator() (Predicate& predicate)
	{

		return *this;
	}

};

template <typename Predicate>
auto where(Predicate& predicate)  -> decltype(Command<_where>)
{
	auto _where = [&predicate](Container container)
	{
		container.remove_if(std::not1(predicate));
	};
	
	return Command("Where", _where);
}



// Follows the Chain of Responsibility pattern
class LazyQuery
{
	// Types
//	typedef typename container::value_type value_type;	// the type of the collection elements. e.g. "int" in "vector<int>"
//	typedef std::function<bool(value_type&)> Predicate;	// The predicate function (or lambda) that will be used to filter elements

	list<int> m_result;									// a temp container of the same type, so that we don't alter the original container
	list<Command&>	m_chain;

public:

	LazyQuery(const Container& collection)
	{
		// Copy to a list
		m_result.insert(m_result.begin(), collection.begin(), collection.end());
	}

	void Chain(Command& nextCommand)
	{
		m_chain.push_back(nextCommand);
	}

	LazyQuery& operator>> (Command& nextCommand)
	{
		Chain(nextCommand);

		return *this;
	}

	void ExecuteChain()
	{
		for (auto itr = m_chain.begin(); itr != m_chain.end(); itr++)
		{
			Command& cmd = *itr;
			cmd.Execute(m_result);
		}
	}
	
};

LazyQuery operator>> (const Container& container, Command& command)
{
	LazyQuery query(container);
	query.Chain(command);
}


