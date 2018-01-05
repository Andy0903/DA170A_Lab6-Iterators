#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "String.h"
#include <assert.h>

String::String() : size(0), capacity(0)
{
	try
	{
		letters = new char[capacity + 1]{ '\0' };
	}
	catch (const std::bad_alloc &ba)
	{
	}
	assert(Invariant());
}

String::String(const String &rhs) : size(rhs.size), capacity(rhs.capacity)
{
	try
	{
		letters = new char[rhs.capacity + 1];
		memcpy(letters, rhs.letters, rhs.size + 1);
	}
	catch (const std::bad_alloc &ba)
	{
	}
	assert(Invariant());
}

String::String(const char *cstr) : size(0), capacity(0)
{
	try
	{
		int length = strlen(cstr);
		letters = new char[length + 1];
		size = length;
		capacity = length;
		memcpy(letters, cstr, length + 1);
	}
	catch (const std::bad_alloc &ba)
	{
	}
	assert(Invariant());
}

String::String(String &&rhs) : size(std::move(rhs.size)), capacity(std::move(rhs.capacity)), letters(std::move(rhs.letters))
{
	rhs.size = 0;
	rhs.capacity = 0;
	rhs.letters = nullptr;
	assert(Invariant());
}

String& String::operator=(const String & rhs)
{
	assert(Invariant());

	try
	{
		char* temp = new char[rhs.capacity + 1];
		memcpy(temp, rhs.letters, rhs.size + 1);
		delete[] letters;
		letters = temp;
		capacity = rhs.capacity;
		size = rhs.size;
	}
	catch (const std::bad_alloc &ba)
	{
	}

	assert(Invariant());
	return *this;
}

String& String::operator=(String &&rhs)
{
	assert(Invariant());
	if (this != &rhs)
	{
		delete[] letters;
		
		size = std::move(rhs.size);
		capacity = std::move(rhs.capacity);
		letters = std::move(rhs.letters);

		rhs.size = 0;
		rhs.capacity = 0;
		rhs.letters = nullptr;
	}

	assert(Invariant());
	return *this;
}

String::~String()
{
	delete[] letters;
}

void String::Reserve(size_t newCapacity)
{
	assert(Invariant());
	if (newCapacity > capacity)
	{
		int oldSize = size;
		Resize(newCapacity);
		size = oldSize;
	}
	assert(Invariant());
}

void String::Shrink_to_fit()
{
	assert(Invariant());
	Resize(size);
	assert(Invariant());
}

void String::Push_back(const char c)
{
	assert(Invariant());
	if (size >= capacity)
	{
		Reserve(capacity == 0 ? 10 : size * 2);
	}

	letters[size] = c;
	++size;
	assert(Invariant());
}

void String::Resize(size_t n)
{
	assert(Invariant());
	try
	{
		char *temp = new char[n + 1];
		capacity = n;
		memcpy(temp, letters, size);
		for (size_t i = size; i < n + 1; ++i)
		{
			temp[i] = '\0';
		}
		size = n;
		delete[] letters;
		letters = temp;
	}
	catch (const std::bad_alloc &ba)
	{
	}
	assert(Invariant());
}

String& String::operator+=(const String& rhs)
{
	assert(Invariant());
	Reserve(size + rhs.size);
	memcpy((letters + size), rhs.letters, rhs.size + 1);
	size += rhs.size;
	assert(Invariant());
	return *this;
}

String String::operator+(const String &rhs) const
{
	assert(Invariant());
	String temp = String(*this);
	temp += rhs;

	assert(Invariant());
	return temp;
}

bool operator==(const String &lhs, const String &rhs)
{
	if (lhs.size != rhs.size)
	{
		return false;
	}

	return 0 == memcmp(lhs.letters, rhs.letters, lhs.size);
}

bool operator!=(const String &lhs, const String &rhs)
{
	return !(lhs == rhs);
}


std::ostream& operator<<(std::ostream& cout, String& rhs)
{
	for (size_t i = 0; i < rhs.size; ++i)
	{
		cout << rhs[i];
	}
	return cout;
}
