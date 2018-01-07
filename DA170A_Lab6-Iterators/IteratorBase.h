#pragma once
#include <iterator>

template <typename T>	//char .... const char
class IteratorBase : public std::iterator<std::forward_iterator_tag, T>
{
protected:
	T *ptr = nullptr;

public:
	IteratorBase() : ptr(nullptr)
	{}

	IteratorBase(T *ptr) : ptr(ptr)
	{}
	
	IteratorBase(const IteratorBase &it) :ptr(it.ptr)
	{}

	~IteratorBase() = default;

	T& operator*() const
	{
		return *ptr;
	}
	bool operator==(const IteratorBase& rhs) const
	{
		return ptr == rhs.ptr;
	}

	bool operator!=(const IteratorBase& rhs) const
	{
		return !(*this == rhs);
	}

	const T* Get() const
	{
		return ptr;
	}

	IteratorBase& operator=(const IteratorBase &rhs)
	{
		ptr = rhs.ptr;
		return *this;
	}

};