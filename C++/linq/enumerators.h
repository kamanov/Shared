#ifndef ENUMERATORS_H
#define ENUMERATORS_H

#include <exception>
#include <functional>
#include <memory>
#include <vector>
#include "ienumerator.h"


typedef std::shared_ptr<IEnumerator>  IEnumeratorPtr;


class CollectionEnumerator : public IEnumerator
{
	std::vector<int>::iterator current_;
	std::vector<int>::iterator end_;
	bool is_valid_;
public:
	CollectionEnumerator(std::vector<int>& vect);
	int current();
	bool next();
	~CollectionEnumerator() {}
	
};


class WhereClause : public IEnumerator
{
	IEnumeratorPtr enumerator_;
	std::function<bool(int)> functor_;

public:
	WhereClause(std::shared_ptr<IEnumerator> enumerator,std::function<bool(int)> functor);
	int current();
	bool next();
	~WhereClause() {}
};


class Selector : public IEnumerator 
{
	IEnumeratorPtr enumerator_;
	std::function<int(int)> functor_;
public:
	Selector(std::shared_ptr<IEnumerator> enumerator,std::function<int(int)> functor);
	int current();
	bool next();
	~Selector() {}
};






#endif //ENUMERATORS_H