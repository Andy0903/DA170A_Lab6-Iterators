#pragma once
#include "IteratorBase.h"

template <typename T>
class ReverseIterator : public IteratorBase<T>
{
public:
	ReverseIterator()
	{
		IteratorBase::IteratorBase();
	}

	ReverseIterator(T *ptr) : IteratorBase(ptr)
	{
	}

	ReverseIterator(const ReverseIterator &it) : IteratorBase(it)
	{
	}

	~ReverseIterator() = default;

	ReverseIterator& operator--()
	{
		++ptr;
		return *this;
	}

	ReverseIterator& operator++()
	{
		--ptr;
		return *this;
	}

	ReverseIterator operator++(int) //postfix
	{
		ReverseIterator copy = *this;
		--ptr;
		return copy;
	}

	ReverseIterator operator+(const size_t rhs) const
	{
		return ReverseIterator(ptr - rhs);
	}

	size_t operator-(const ReverseIterator rhs) const
	{
		return rhs.ptr - ptr;
	}

	T& operator[](const size_t i) const
	{
		return *(ptr - i);
	}

	bool operator<(const ReverseIterator& rhs) const
	{
		return ptr > rhs.ptr;
	}

};

template <typename T>
bool operator<(const ReverseIterator<T>& lhs, int rhs)
{
	return lhs.Get() > rhs;
}