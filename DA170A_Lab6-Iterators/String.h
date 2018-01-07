#pragma once
#include <iostream>
#include "ForwardIterator.h"
#include "ReverseIterator.h"

class String
{
public:
	typedef ForwardIterator<char> iterator;
	typedef ForwardIterator<const char> const_iterator;
	typedef ReverseIterator<char> reverse_iterator;
	typedef ReverseIterator<const char> const_reverse_iterator;

	inline iterator begin()
	{
		return iterator(letters);
	}

	inline iterator end()
	{
		return iterator(letters + size);
	}

	inline const_iterator cbegin() const
	{
		return const_iterator(letters);
	}

	inline const_iterator cend() const
	{
		return const_iterator(letters + size);
	}

	inline reverse_iterator rbegin()
	{
		return reverse_iterator(letters + size - 1);
	}

	inline reverse_iterator rend()
	{
		return reverse_iterator(letters - 1);
	}

	inline const_reverse_iterator crbegin() const
	{
		return const_reverse_iterator(letters + size - 1);
	}

	inline const_reverse_iterator crend() const
	{
		return const_reverse_iterator(letters - 1);
	}


	String();
	String(const String &rhs);
	String(String &&rhs);
	String(const char *cstr);
	String& operator=(const String &rhs);
	String& operator=(String &&rhs);
	~String();

	void Reserve(size_t);
	void Shrink_to_fit();
	void Push_back(char c);
	void Resize(size_t n);
	String& operator +=(const String& rhs);
	String String::operator+(const String &rhs) const;

	friend bool operator==(const String &lhs, const String &rhs);
	friend bool operator !=(const String &lhs, const String &rhs);
	friend std::ostream& operator<<(std::ostream& cout, String& rhs);

	inline char& String::At(const size_t i)
	{
		if (i < 0 || capacity <= i)
		{
			throw std::out_of_range("Index out of bounds.");
		}
		else
		{
			return letters[i];
		}
	}

	inline const char& String::At(const size_t i) const
	{
		if (i < 0 || capacity <= i)
		{
			throw std::out_of_range("Index out of bounds.");
		}
		else
		{
			return letters[i];
		}
	}

	inline operator bool()
	{
		return capacity != 0;
	}

	inline char& String::operator[](const size_t i)
	{
		return letters[i];
	}

	inline const char& String::operator[](const size_t i) const
	{
		return letters[i];
	}

	inline char* String::Data()
	{
		return letters;
	}

	inline const char* String::Data() const
	{
		return letters;
	}

	inline int Capacity()
	{
		return capacity;
	}

	inline int Capacity() const
	{
		return capacity;
	}

	inline int String::Size()
	{
		return size;
	}

	inline const int String::Size() const
	{
		return size;
	}

private:
	char *letters;
	int size;
	int capacity;

	inline bool Invariant() const
	{
		return capacity >= size && (letters == nullptr || letters[size] == '\0');
	}
};