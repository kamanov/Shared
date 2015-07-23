#ifndef IENUMERATOR_H
#define IENUMERATOR_H


class IEnumerator
{
public:
	virtual int current() = 0;
	virtual bool next() = 0;
	virtual ~IEnumerator() {}
};


#endif //IENUMERATOR_H