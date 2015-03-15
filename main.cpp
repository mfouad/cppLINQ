#include "ImmediateEval.h"
#include "LazyEval.h"
#include <assert.h>

void TestImmediateEvaluation()
{
	vector<int> v{ 0, 1, 2, 3, 4 };

	From(v).Where([](int& e){ return (e == 1); }).Print();

	assert(From(v).Count() == 5);
	From(v).Where([](int& e){ return (e == 1); }).Count();

	//	From(v).Where([](int& e){ return (e == 1); }).any([](int& e){return (e == 1); });
	//*/
}


void TestLazyQuery()
{
	vector<int> v{ 0, 1, 2, 3, 4 };

	//v >>
	where([](int& e) -> bool { return (e == 1); });
}

int main()
{
	// TestImmediateEvaluation();
	TestLazyQuery();

	return 0;
}

