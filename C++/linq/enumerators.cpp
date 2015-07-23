#include "enumerators.h"

CollectionEnumerator::CollectionEnumerator(std::vector<int>& vect)
		: current_(vect.begin())
		, end_(vect.end())
		, is_valid_(false)
{}

int CollectionEnumerator::current() 
{
		if (!is_valid_)
			throw std::exception();
		else
		return *current_;
}
	
bool CollectionEnumerator::next() 
{
		if(!is_valid_) {
			is_valid_ = true;
			return true;
		}	
		++current_;
		return current_ != end_;
}




WhereClause::WhereClause(std::shared_ptr<IEnumerator> enumerator,std::function<bool(int)> functor) 
		: functor_(functor)
		, enumerator_(enumerator)
{}

int WhereClause::current() 
{
		return enumerator_->current();
}

bool WhereClause::next() 
{
		while(enumerator_->next()) {
			if(functor_(enumerator_->current()))
				return true;
		}
		return false;
}



Selector::Selector(std::shared_ptr<IEnumerator> enumerator,std::function<int(int)> functor) 
		: functor_(functor)
		, enumerator_(enumerator)
{}

int Selector::current() 
{
		return functor_(enumerator_->current());
}

bool Selector::next() 
{
		return enumerator_->next();
}


