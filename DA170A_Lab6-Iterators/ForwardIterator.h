#pragma once
#include "IteratorBase.h"

template <typename T>
class ForwardIterator : public IteratorBase<T>
{
public:
	ForwardIterator()
	{
		IteratorBase::IteratorBase();
	}

	ForwardIterator(T *ptr) : IteratorBase(ptr)
	{
	}

	ForwardIterator(const ForwardIterator &it) : IteratorBase(it)
	{
	}

	~ForwardIterator() = default;

	ForwardIterator& operator--()
	{
		--ptr;
		return *this;
	}
	ForwardIterator& operator++()
	{
		++ptr;
		return *this;
	}
	ForwardIterator operator++(int) //postfix
	{
		ForwardIterator copy = *this;
		++ptr;
		return copy;
	}
	ForwardIterator operator+(const size_t rhs) const
	{
		return ForwardIterator(ptr + rhs);
	}

	size_t operator-(const ForwardIterator rhs) const
	{
		return ptr - rhs.ptr;
	}

	T& operator[](const size_t i) const
	{
		return *(ptr + i);
	}

	bool operator<(const ForwardIterator& rhs) const
	{
		return ptr < rhs.ptr;
	}
};

template <typename T>
bool operator<(const ForwardIterator<T>& lhs, int rhs)
{
	return lhs.Get() < rhs;
}