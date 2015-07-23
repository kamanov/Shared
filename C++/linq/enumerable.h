#ifndef ENUMERABLE_H
#define ENUMERABLE_H

#include <functional>
#include <memory>
#include "enumerators.h"

class Enumerable;
typedef std::shared_ptr<Enumerable> EnumerablePtr;

class Enumerable
{
	
	IEnumeratorPtr  enumerator_;
public:
	Enumerable(IEnumeratorPtr enumerator);
	IEnumeratorPtr GetEnumerator() { return enumerator_;}
	EnumerablePtr Select(std::function<int(int)> functor);
	EnumerablePtr Where(std::function<bool(int)> functor);
	int Count(std::function<bool(int)> functor);
	std::shared_ptr<std::vector<int> > toVector();
	~Enumerable() {}


};

#endif //ENUMERABLE_H