#include "ImmediateEval.h"

void TestImmediateEvaluation()
{
	vector<int> v{ 0, 1, 2, 3, 4 };

	From(v).Where([](int& e){ return (e == 1); }).print();
	
	assert(From(v).count() == 5);
	From(v).Where([](int& e){ return (e == 1); }).count();

//	From(v).Where([](int& e){ return (e == 1); }).any([](int& e){return (e == 1); });
	//*/
}



int main()
{
	TestImmediateEvaluation();

	return 0;
}

