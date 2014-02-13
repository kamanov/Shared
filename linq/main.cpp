#include <iostream>
#include <memory>
#include <vector>
#include "enumerable.h"

EnumerablePtr Do(std::vector<int>& vect) {
	return EnumerablePtr(new Enumerable(IEnumeratorPtr(new CollectionEnumerator(vect))));
}

int main() {

	std::vector<int> vect;
	vect.push_back(1);
	vect.push_back(2);
	vect.push_back(3);
	vect.push_back(-7);
	vect.push_back(100);

	std::shared_ptr<std::vector<int> > vectPtr = Do(vect)->Select([](int obj)->int { return obj*3; })->Where([](int obj)->bool { return obj>0; })->toVector();
	auto it = vectPtr->begin();
	while(it != vectPtr->end()) {
		std::cout << *it << std::endl;
		++it;
	}

	return 0;

}