#include "VG.h"

//#include "UnsignedTest.h"
#include "String.h"

//#include <string>

#include <iostream>
using std::cout;
using std::cin;

#include <cassert>

//#include <utility>
#include"StringTest.h"

//#include <iostream>
//#include <vector>

void PrintReallocationScheme() {

    //typedef std::vector<int> Vector;
    //typedef std::string Vector;
    typedef String Vector;
    size_t sz;

    Vector foo;
    sz = foo.Capacity();
    std::cout << "mGrowing from default:\n";
    std::cout << "capacity is: " << sz << '\n';
    for (int i = 0; i < 100; ++i) {
        foo.Push_back(i);
        if (sz != foo.Capacity()) {
            sz = foo.Capacity();
            std::cout << "capacity changed: " << sz << '\n';
        }
    }

    Vector bar;
    bar.Reserve(100);   // this is the only difference with foo above
    sz = bar.Capacity();
    std::cout << "reserve(100) no reallocations\n";
    std::cout << "capacity is: " << sz << '\n';
    for (int i = 0; i < 100; ++i) {
        bar.Push_back(i);
        if (sz != bar.Capacity()) {
            sz = bar.Capacity();
            std::cout << "capacity changed: " << sz << '\n';
        }
    }
	//std::cin.get();
}

void TestPushBackReallocation() {
    String str("hej");
    assert(str.Size() <= str.Capacity());

#ifdef VG
    //If VG we try to take 20 empty places: (size+1 < capacity)
    //we push_back one more until it is more then 20 places left (or sting to big)
    while (str.Size() + 20 >= str.Capacity() && str.Size() < 1000)
        str.Push_back('A' + rand() % 32);
    assert(str.Size() < 1000);	//If this fail it prbably the case that capacity is increased with a constant.
#endif //VG

    auto internalBuf = str.Data();
    auto cap = str.Capacity();
    auto siz = str.Size();
    int i;
    for (i = siz + 1; i <= cap; ++i)
	{
        str.Push_back(char(i) + 'a');
        assert(internalBuf == str.Data());
        assert(cap == str.Capacity());
        assert(i == str.Size());
    }
    str.Push_back(char(i));
    assert(internalBuf != str.Data());
    assert(cap < str.Capacity());
    assert(i == str.Size());

    assert(str.Size() != str.Capacity());
    internalBuf = str.Data();
    cap = str.Capacity();
    siz = str.Size();
    str.Shrink_to_fit();
    assert(internalBuf != str.Data());
    assert(str.Size() == str.Capacity());
    assert(i == str.Size());

    str = "hej";
    str.Resize(10);
    assert(10 == str.Size() && str[7] == char());
    cap = str.Capacity() + 10;
    str.Resize(cap);
    assert(str.Size() == cap && str.Capacity() >= cap);
}

void TestFörGodkäntString() {
    //-	String()
    String str0;
    String str00("");
    assert(str0 == str00);
    str0 != str00;
    //-	String(Sträng sträng)
    String s1("foo"); assert(s1 == "foo");
    String str(s1); assert(str == "foo");
    String s3("bar");  assert(s3 == "bar");

    //-	~String() Kom ihåg destruktorn!
    delete new String("hej");

    //	-	operator =(Sträng sträng)
    assert((str = s3) == s3);
    assert((str = str) == s3);	//self assignment


    String str1("foo"), str2("bar"), str3("hej");
    str3 = str = str1;
    assert(str3 == str);
    assert(str1 == str);

    // operator bool

    assert(String("huj"));
    assert(!String(""));

    //-	operator== 
    //testas överallt!


	//-	operator[](int i) som indexerar utan range check.
	str = "bar";
    str[-1]; str[1000];	//No error
    assert(str[1] == 'a');
    str[1] = 'y';
    assert(str[1] == 'y');

    const String sc(str);
    assert(sc[1] == 'y');
    assert(std::is_const<std::remove_reference< decltype(sc[1])>::type>::value); //Kolla att det blir en const resultat av indexering

                                                                                 //-	push_back(char c) lägger till ett tecken sist.
    str = "bar";
    str.Push_back('a');
    assert(str == "bara");
    str.Push_back('\0');
    str.Push_back('x');
    assert(str.Size() == 6 && str[4] == '\0' && str[5] == 'x');

    //-	size(), capacity() and reloccation test;
    TestPushBackReallocation();
    PrintReallocationScheme();
    
    cout << String("hej\n");
    cout << "Om det står hej på föregående rad så är TestFörGodkänt klar\n";

}

#ifdef VG

void TestFörVälGodkäntString() {
    String str("bar");

    //-	at(int i) som indexerar med range check
    try {
        str.At(-1);
        assert(false);
    }
    catch (std::out_of_range&) {};
    try {
        str.At(3);
        assert(false);
    }
    catch (std::out_of_range&) {};

    //- at indexerar

    //-	at(int i) 
    str = "bar";
    assert(str.At(1) == 'a');
    str.At(1) = 'y';
    assert(str.At(1) == 'y');

    const String strC(str);
    assert(strC.At(1) == 'y');
    assert(std::is_const<std::remove_reference< decltype(strC.At(1))>::type>::value); //Kolla att det blir en const resultat av indexering

                                                                                      // ConvertToChars
    const char* temp = strC.Data();
    assert(strC.Size() == 3);
    assert(std::memcmp(temp, strC.Data(), strC.Size()) == 0);
    assert(temp[strC.Size()] == '\0');

    //	reserve()
    auto internalBuf = str.Data();
    auto cap = str.Capacity();
    auto siz = str.Size();

    str.Reserve(cap);
    assert(internalBuf == str.Data());
    assert(cap == str.Capacity());
    assert(siz == str.Size());

    str.Reserve(cap + 1);
    assert(internalBuf != str.Data());
    assert(cap + 1 == str.Capacity());
    assert(siz == str.Size());

    /////////////////
    //-	operator+=(Sträng sträng) som tolkas som konkatenering.
    //foo, bar, hej
    String str1("foo"), str2("bar"), str3("hej");
    ((str = "xyz") += str1) += (str3 += str1);
    assert(str3 == "hejfoo" && str == "xyzfoohejfoo" && str1 == "foo");

    //+= som får plats;
    str = "bar";
    str.Reserve(10);
    str += "foo";
    assert(str == "barfoo");

    //+= som inte får plats;
    str.Reserve(10);
    str = "";
    int i;
    for (i = 0; str.Size() < str.Capacity(); ++i)
        str.Push_back('0' + i);
    str1 = "bar";
    str += str1;
    for (int k = 0; k < i; ++k)
        assert(str[k] == '0' + k);
    assert(str[i] == 'b');
    //+= Själv assignment	//Borde testa med att capacity tar slut!
    str = "foo";
    str += str;
    assert(str == "foofoo");

    //-	operator+
    str = "bar";
    assert(str + String("foo") == "barfoo");

    //move
    const char* strdata = str.Data();
    String mStr(std::move(str));
    assert(strdata == mStr.Data());
    assert(nullptr == str.Data());

    str = std::move(mStr);
    assert(strdata == str.Data());
    assert(nullptr == mStr.Data());

    cout << "\nTestFörVälGodkänt klar\n";
}

#endif //VG