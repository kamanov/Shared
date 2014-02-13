#include "enumerable.h"

Enumerable::Enumerable(IEnumeratorPtr enumerator) 
		: enumerator_(enumerator) 
{}
EnumerablePtr Enumerable::Select(std::function<int(int)> functor) 
{
		return EnumerablePtr(new Enumerable(IEnumeratorPtr(new Selector(enumerator_,functor))));
}

EnumerablePtr Enumerable::Where(std::function<bool(int)> functor) 
{
		return EnumerablePtr(new Enumerable(IEnumeratorPtr(new WhereClause(enumerator_,functor))));
}

int Enumerable::Count(std::function<bool(int)> functor) 
{
		int cnt = 0;
		while (enumerator_->next()) {
			if(functor(enumerator_->current()))
				cnt++;
		}
		return cnt;
	
}

std::shared_ptr<std::vector<int> > Enumerable::toVector() 
{
		std::shared_ptr<std::vector<int> > tmp(new std::vector<int>);
		while (enumerator_->next()) {
			tmp->push_back(enumerator_->current());
		}
		return tmp;
}