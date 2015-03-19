#LINQ for C++

This project offers two implementations to a LINQ support in C++, *Immediate Evaluation* and *Lazy Evaluation*.

###Immediate Evaluation
Each query function is immediatly evaluated, so `where` will return a filtered `list` not a `Query` object.

To use, include: `ImmediateEval.h`

```c++
ImmediateFrom(students).where( [](Student& s){return s.grades > 50} ).count();
```

###Lazy Evaluation
A more elaborate implementation. Each query function returns a refrence to the same `LazyQuery` object, so it can be chained or passed to functions or variables (similar to `iostream`)

To use, include `LazyEval.h`

```c++
ImmediateFrom(numbers).where( [](int& i){return i > 50} ).count();
```

**Note:** Lazy Evaluation currently supports `int` containers only

###Usage
```c++
From(_container_).query(_lambda_).aggregate(_lambda_);
```
 
* **From**  returns a `Query` object that will be evaluated later
* **query**	a query statement like `where, order by, join, map ...`. 
returns `Query` object, so it can be chained.
* **aggregate** an aggregate function that returns a single value `int, bool, object, a different container`, examples are: `count, all, any, select, reduce`

```cpp
From(v).Where( [](int& e){return (e == 1);} ).Count();
```

###Limitations
`ImmediateQuery` uses `templates<>` and works on any container of any type. While `LazyQuery` only works with integer containers

###Class Diagram
![class diagram](./Class Diagram.png?raw=true)
