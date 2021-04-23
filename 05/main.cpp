#include <iostream>
#include <limits>
#include <sstream>
#include <cassert>
#include "serializer.hpp"

using namespace std;

struct Data
{
    bool a;
    bool b;
    uint64_t c;
    bool d;
    uint64_t e;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c, d, e);
    }
    
    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c, d, e);
    }
};

struct DataErr1
{
    bool a;
    uint64_t b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }
    
    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c);
    }
};

struct DataErr2
{
    bool a;
    std::string b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }
    
    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c);
    }
};


void CorrectTest()
{
    Data x {false, true, 123, true, 90};
    Data y {false, false, 0, false, 0};
    
    std::stringstream stream;
    Serializer serializer(stream);
    Deserializer deserializer(stream);
    
    assert(serializer.save(x)   == Error::NoError);
    assert(deserializer.load(y) == Error::NoError);
    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
    assert(x.d == y.d);
    assert(x.e == y.e);
}


void DifferentStructuresTest()
{
    Data x {false, true, 123, true, 90};
    DataErr1 y {false, 0, 0};
    
    std::stringstream stream;
    Serializer serializer(stream);
    Deserializer deserializer(stream);
    
    assert(serializer.save(x)   == Error::NoError);
    assert(deserializer.load(y) == Error::CorruptedArchive);
}


void DifferentTypesTest()
{
    DataErr2 x {false, "str", 0};
    
    std::stringstream stream;
    Serializer serializer(stream);
    
    assert(serializer.save(x) == Error::CorruptedArchive);
}


void DeserializerWithoutSerializerTest()
{
    Data x {false, true, 123, true, 90};
    
    std::stringstream stream;
    Deserializer deserializer(stream);
    
    assert(deserializer.load(x) == Error::CorruptedArchive);
}

void TwiceSerializerTest()
{
    Data x {false, true, 123, true, 90};
    Data y {true, true, 5673, false, 8};
    
    std::stringstream stream;
    Serializer serializer(stream);
    
    assert(serializer.save(x) == Error::NoError);
    assert(serializer.save(y) == Error::CorruptedArchive);
}

int main()
{
    CorrectTest();
    DifferentStructuresTest();
    DifferentTypesTest();
    DeserializerWithoutSerializerTest();
    TwiceSerializerTest();

    cout << "Success!\n";
    
    return 0;
}