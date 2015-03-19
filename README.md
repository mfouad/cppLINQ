# cppLINQ
LINQ for C++

This project offers two implementations to a LINQ support in C++

##Immediate Evaluation
using the header file `ImmediateEval.h`:

#
```javascript
From(v).Where([](int& e){ return (e == 1); }).Count();
```
