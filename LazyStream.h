#include <vector>
#include <list>
#include <queue>
#include <algorithm>
#include <iostream>
#include <string>
#include <functional>
using namespace std;

// A Command pattern, it is lazy evaluated at the end of the query, after you call Execute()
// it is also a Strategy pattern, used to specify how a command will execute
template <typename Filter>
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


/*
template <typename value_type>
Command<value_type> where(function<bool(value_type&)>& predicate)
{
return Command("Where", [&predicate] (Container container)
{
container.remove_if(std::not1(predicate));
});
}
*/
/*
template <typename Predicate>
Command<Predicate> count()
{
return ValueCommand();
}
*/

// Follows the Chain of Responsibility pattern
template <class container>
class LazyQuery
{
	// Types
	typedef typename container::value_type value_type;	// the type of the collection elements. e.g. "int" in "vector<int>"
	typedef std::function<bool(value_type&)> Predicate;	// The predicate function (or lambda) that will be used to filter elements

	list<value_type> m_result;									// a temp container of the same type, so that we don't alter the original container
	list<Command<value_type>&>	m_chain;

public:

	LazyQuery(const container& collection)
	{
		// Copy to a list
		m_result.insert(m_result.begin(), collection.begin(), collection.end());
	}

	void Chain(const Command<value_type>& nextCommand)
	{
		m_chain.push(nextCommand);
	}

	LazyQuery& operator>> (const Command<value_type>& nextCommand)
	{
		chain(nextCommand);

		return *this;
	}
	/*
	// if we find a terminal command like Count() or Select()
	int operator>> (const ValueCommand& valueCommand)
	{
	ExecuteChain();
	return valueCommand.Execute(m_result);
	}*/

	void ExecuteChain()
	{
		for (auto itr = m_chain.begin(); itr != m_chain.end(); itr++)
		{
			Command& cmd = *itr;
			cmd.Execute(m_result);
		}
	}

};

template <typename Container>
LazyQuery<Container> operator>> (const Container& container, Command<typename Container::value_type>& command)
{
	LazyQuery<Container> query(container);
	query.Chain(command);
}

