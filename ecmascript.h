#ifndef ECMASCRIPT_H_INCLUDED
#define ECMASCRIPT_H_INCLUDED

#include "garbage_collector.h"
#include <utility>
#include <cwchar>
#include <string>
#include <iterator>
#include <sstream>
#include <cmath>

using namespace std;

class ECMAValue : public GCObject
{
public:
    virtual wstring toString() const = 0;
    static wstring toString(ECMAValue * value)
    {
        if(value == nullptr)
            return L"undefined";
        return value->toString();
    }
};

class ECMAException : public exception
{
public:
    StackedGCObject<ECMAValue> value;
    ECMAException(StackedGCObject<ECMAValue> value)
        : value(std::move(value))
    {
    }
};

class ECMAValueNull : public ECMAValue
{
    GCOBJECT_POINTER_VARIABLES()
public:
    virtual wstring toString() const override
    {
        return L"null";
    }
};

class ECMAValueString : public ECMAValue
{
    GCOBJECT_POINTER_VARIABLES()
private:
    wstring value;
public:
    ECMAValueString(wstring value = L"")
        : value(value)
    {
    }
    wstring getValue() const
    {
        return value;
    }
    virtual wstring toString() const override
    {
        return value;
    }
};

class ECMAValueNumber : public ECMAValue
{
    GCOBJECT_POINTER_VARIABLES()
private:
    double value;
    double roundToDouble(long double v)
    {
        if(std::isnan(v) || std::isinf(v) || v == 0)
            return (double)v;
        if(abs(v) < std::pow((long double)2, -1074))
            return (v < 0) ? -0 : 0;
        if(abs(v) > (1 + (1 - std::pow((long double)2, -52))) * std::pow((long double)2, 1023))
            return (v < 0) ? -INFINITY : INFINITY;
        double retval = (double)v;
        long double delta = v - retval;
        double altRetval;
        if(delta < 0)
            altRetval = std::nextafter(retval, (double)-INFINITY);
        else
            altRetval = std::nextafter(retval, (double)INFINITY);
        if(abs(altRetval - v) < abs(delta))
            return altRetval;
        return retval;
    }
public:
    ECMAValueNumber(double value = 0)
        : value(value)
    {
    }
    ECMAValueNumber(wstring str)
    {
        long double value;
        size_t i = 0;
        while(!str.empty() && isStrWhiteSpace(str[str.size() - 1]))
            str.resize(str.size() - 1);
        while(i < str.size() && isStrWhiteSpace(str[i]))
            i++;
        if(i >= str.size())
        {
            this->value = 0;
            return;
        }
        if(str.substr(i, 2) == L"0x" || str.substr(i, 2) == L"0X")
        {
            if(str.size() - i == 2)
            {
                this->value = NAN;
                return;
            }
            value = 0;
            for(i += 2; i < str.size(); i++)
            {
                if(!isHexDigit(str[i]))
                {
                    this->value = NAN;
                    return;
                }
                value *= 0x10;
                value += getDigitValue(str[i]);
            }
            this->value = value;
            return;
        }
        value = 0;
        if(i >= str.size())
        {
            this->value = 0;
            return;
        }
        bool isNegative = false;
        bool gotSign = false;
        if(str[i] == '+' || str[i] == '-')
        {
            gotSign = true;
            isNegative = str[i++] == '-';
        }
        if(i >= str.size())
        {
            this->value = gotSign ? NAN : 0;
            return;
        }
        if(str.substr(i) == L"Infinity")
        {
            this->value = INFINITY;
            if(isNegative)
                this->value = -INFINITY;
            return;
        }
        if(!isDecimalDigit(str[i]) && str[i] != '.')
        {
            this->value = NAN;
            return;
        }
        bool gotAnyDigits = false;
        while(i < str.size() && isDecimalDigit(str[i]))
        {
            gotAnyDigits = true;
            value *= 10;
            value += getDigitValue(str[i++]);
        }
        if(i < str.size() && str[i] == '.')
        {
            i++;
            if(i >= str.size())
            {
                if(!gotAnyDigits)
                    this->value = NAN;
                else if(isNegative)
                    this->value = -roundToDouble(value);
                else
                    this->value = roundToDouble(value);
                return;
            }
            if(!gotAnyDigits && !isDecimalDigit(str[i]))
            {
                this->value = NAN;
                return;
            }
            long double decimalValue = 0;
            int digitCount = 0;
            while(i < str.size() && isDecimalDigit(str[i]))
            {
                decimalValue *= 10;
                digitCount++;
                decimalValue += getDigitValue(str[i++]);
            }
            value += decimalValue * std::pow((long double)10, (long double)-digitCount);
        }
        if(i < str.size() && (str[i] == 'e' || str[i] == 'E'))
        {
            i++;
            if(i >= str.size())
            {
                this->value = NAN;
                return;
            }
            bool isExponentNegative = false;
            if(str[i] == '+' || str[i] == '-')
            {
                isExponentNegative = str[i++] == '-';
            }
            if(i >= str.size() || !isDecimalDigit(str[i]))
            {
                this->value = NAN;
                return;
            }
            long double exponentValue = 0;
            while(i < str.size())
            {
                if(!isDecimalDigit(str[i]))
                {
                    value = NAN;
                    return;
                }
                exponentValue *= 10;
                exponentValue += getDigitValue(str[i++]);
            }
            if(isExponentNegative)
                exponentValue = -exponentValue;
            value *= std::pow((long double)10, exponentValue);
        }
        if(i < str.size())
        {
            this->value = NAN;
            return;
        }
        if(isNegative)
            this->value = -roundToDouble(value);
        else
            this->value = roundToDouble(value);
    }
    double getValue() const
    {
        return value;
    }
private:
    static wstring getUnsignedString(long double v)
    {
        assert(floor(v) == v && v >= 0);
        wstring retval;
        do
        {
            long double v_10 = std::floor((v + (long double)1 / 2) / 10);
            int digit = ((int)(v - 10 * v_10) % 10 + 10) % 10;
            retval.append(1, getDigitCharacter(digit));
            v = v_10;
        }
        while(v > 0);
        for(size_t i = 0, j = retval.size() - 1; i < j; i++, j--)
        {
            std::swap(retval[i], retval[j]);
        }
        return retval;
    }
    static wstring getUnsignedString(int v)
    {
        assert(v >= 0);
        wstring retval;
        do
        {
            retval.append(1, getDigitCharacter(v % 10));
            v = v / 10;
        }
        while(v > 0);
        for(size_t i = 0, j = retval.size() - 1; i < j; i++, j--)
        {
            std::swap(retval[i], retval[j]);
        }
        return retval;
    }
public:
    virtual wstring toString() const override
    {
        long double value = this->value;
        if(std::isnan(value))
            return L"NaN";
        wstring retval = L"";
        if(value == 0)
            return L"0";
        if(value < 0)
            retval += L'-';
        value = std::abs(value);
        if(std::isinf(value))
            return retval + L"Infinity";
        int log10Value = (int)std::floor(std::log10(value));
        constexpr int maxDigitCount = 16;
        log10Value -= maxDigitCount - 1;
        value *= std::pow((long double)10, -log10Value);
        value = std::floor(value + (long double)1 / 2);
        for(int i = 0; i < maxDigitCount && std::floor((value + (long double)1 / 2) / 10) * 10 == value; i++)
        {
            log10Value++;
            value = std::floor((value + (long double)1 / 2) / 10);
        }
        assert(value > 0);
        int k = (int)std::floor(std::log10(value)) + 1;
        assert(k > 0);
        int n = log10Value + k;
        long double s = value;
        if(k <= n && n <= 21)
        {
            retval += getUnsignedString(s);
            retval.append(n - k, L'0');
            return retval;
        }
        if(0 < n && n <= 21)
        {
            wstring str = getUnsignedString(s);
            str.insert(n, 1, L'.');
            return retval + str;
        }
        if(-6 < n && n <= 0)
        {
            retval += L"0.";
            retval.append(-n, L'0');
            retval += getUnsignedString(s);
            return retval;
        }
        if(k == 1)
        {
            retval += getDigitCharacter((int)std::floor((long double)1 / 2 + s));
            n--;
            retval += (n >= 0 ? L"e+" : L"e-");
            retval += getUnsignedString(std::abs(n));
            return retval;
        }
        n--;
        wstring str = getUnsignedString(s);
        str.insert(1, 1, L'.');
        retval += str;
        retval += (n >= 0 ? L"e+" : L"e-");
        retval += getUnsignedString(std::abs(n));
        return retval;
    }
};

class ECMAValueObject : public ECMAValue
{
private:
    class Node : public GCObject
    {
    public:
        const wstring key;
        ECMAValue * value = nullptr;
        Node * hashNext = nullptr;
        Node * listNext = nullptr;
        Node * listPrev = nullptr;
        GCOBJECT_POINTER_VARIABLES(&Node::value, &Node::hashNext, &Node::listNext, &Node::listPrev)
    public:
        Node(wstring key)
            : key(key)
        {
        }
    };
    Node ** array;
    size_t hashPrime, nodeCount = 0;
    Node * listHead = nullptr;
    static bool isPrime(size_t v)
    {
        if(v == 2 || v == 3 || v == 5)
            return true;
        if(v % 2 == 0)
            return false;
        if(v % 3 == 0)
            return false;
        if(v % 5 == 0)
            return false;
        if(v % 7 == 0)
            return false;
        if(v % 11 == 0)
            return false;
        if(v % 13 == 0)
            return false;
        if(v % 17 == 0)
            return false;
        if(v % 19 == 0)
            return false;
        if(v % 23 == 0)
            return false;
        if(v % 29 == 0)
            return false;
        if(v % 31 == 0)
            return false;
        if(v % 37 == 0)
            return false;
        if(v % 41 == 0)
            return false;
        if(v % 43 == 0)
            return false;
        if(v % 47 == 0)
            return false;
        if(v % 53 == 0)
            return false;
        if(v % 59 == 0)
            return false;
        if(v % 61 == 0)
            return false;
        if(v % 67 == 0)
            return false;
        if(v % 71 == 0)
            return false;
        if(v % 73 == 0)
            return false;
        if(v % 79 == 0)
            return false;
        if(v % 83 == 0)
            return false;
        if(v % 89 == 0)
            return false;
        if(v % 97 == 0)
            return false;
        if(v % 101 == 0)
            return false;
        if(v % 103 == 0)
            return false;
        if(v % 107 == 0)
            return false;
        if(v % 109 == 0)
            return false;
        if(v % 113 == 0)
            return false;
        if(v % 127 == 0)
            return false;
        if(v % 131 == 0)
            return false;
        if(v % 137 == 0)
            return false;
        if(v % 139 == 0)
            return false;
        if(v % 149 == 0)
            return false;
        if(v % 151 == 0)
            return false;
        if(v % 157 == 0)
            return false;
        if(v % 163 == 0)
            return false;
        if(v % 167 == 0)
            return false;
        if(v % 173 == 0)
            return false;
        if(v % 179 == 0)
            return false;
        if(v % 181 == 0)
            return false;
        if(v % 191 == 0)
            return false;
        if(v % 193 == 0)
            return false;
        if(v % 197 == 0)
            return false;
        if(v % 199 == 0)
            return false;
        if(v % 211 == 0)
            return false;
        if(v % 223 == 0)
            return false;
        if(v % 227 == 0)
            return false;
        if(v % 229 == 0)
            return false;
        if(v % 233 == 0)
            return false;
        if(v % 239 == 0)
            return false;
        if(v % 241 == 0)
            return false;
        if(v % 251 == 0)
            return false;
        if(v <= 0x10000)
            return true;
        for(size_t divisor = 257; divisor * divisor <= v; divisor += 2)
        {
            if(v % divisor == 0)
                return false;
        }
        return true;
    }
    static size_t nextPrime(size_t v)
    {
        if(v < 2)
            return 2;
        if(v < 3)
            return 3;
        v++;
        v |= 1; // if even change to next odd
        while(!isPrime(v))
            v += 2;
        return v;
    }
    size_t getHash(wstring v) const
    {
        return std::hash<wstring>()(v) % hashPrime;
    }
    size_t getHash(StackedGCObject<Node> v) const
    {
        return std::hash<wstring>()(v->key) % hashPrime;
    }
    void rehash()
    {
        {
            GCLockGuard guard(getGarbageCollector());
            hashPrime = nextPrime(nodeCount / 2);
            delete []array;
            array = new Node *[hashPrime];
            for(size_t i = 0; i < hashPrime; i++)
                array[i] = nullptr;
        }
        for(StackedGCObject<Node> i = listHead; i != nullptr; i = i->listNext)
        {
            size_t hash = getHash(i);
            i->hashNext = array[hash];
            array[hash] = i;
        }
    }
    StackedGCObject<Node> get(wstring key) const
    {
        size_t hash = getHash(key);
        Node ** pnode;
        for(pnode = &array[hash]; *pnode != nullptr; pnode = &(*pnode)->hashNext)
        {
            if((*pnode)->key == key)
            {
                StackedGCObject<Node> node = *pnode;
                *pnode = node->hashNext;
                node->hashNext = array[hash];
                array[hash] = node;
                return node;
            }
        }
        return nullptr;
    }
    StackedGCObject<Node> create(wstring key)
    {
        size_t hash = getHash(key);
        StackedGCObject<Node> node = getGarbageCollector().allocate<Node>(key);
        nodeCount++;
        node->listNext = listHead;
        if(listHead != nullptr)
            listHead->listPrev = node;
        node->listPrev = nullptr;
        listHead = node;
        node->hashNext = array[hash];
        array[hash] = node;
        return node;
    }
    GCOBJECT_POINTER_VARIABLES(GCPtrDesc(&ECMAValueObject::array, &ECMAValueObject::hashPrime), &ECMAValueObject::listHead)
public:
    ECMAValueObject(size_t startTableSize = 8191)
    {
        GCLockGuard guard(getGarbageCollector());
        hashPrime = nextPrime(max(startTableSize, (size_t)10) - 1);
        array = new Node *[hashPrime];
        for(size_t i = 0; i < hashPrime; i++)
            array[i] = nullptr;
    }
    void clear()
    {
        nodeCount = 0;
        for(size_t i = 0; i < hashPrime; i++)
            array[i] = nullptr;
        listHead = nullptr;
    }
    bool erase(wstring key)
    {
        size_t hash = getHash(key);
        Node ** pnode;
        for(pnode = &array[hash]; *pnode != nullptr; pnode = &(*pnode)->hashNext)
        {
            if((*pnode)->key == key)
            {
                StackedGCObject<Node> node = *pnode;
                *pnode = node->hashNext;
                if(node->listPrev != nullptr)
                    node->listPrev->listNext = node->listNext;
                else
                    listHead = node->listNext;
                if(node->listNext != nullptr)
                    node->listNext->listPrev = node->listPrev;
                return true;
            }
        }
        return false;
    }
    class iterator : public std::iterator<std::bidirectional_iterator_tag, ECMAValue *>
    {
        friend class ECMAValueObject;
        friend class const_iterator;
        StackedGCObject<Node> node;
        iterator(StackedGCObject<Node> node)
            : node(std::move(node))
        {
        }
    public:
        iterator()
            : node(nullptr)
        {
        }
        ECMAValue *& operator *() const
        {
            return node->value;
        }
        const iterator & operator ++()
        {
            node = node->listNext;
            return *this;
        }
        ECMAValue ** operator ++(int)
        {
            ECMAValue ** retval = &node->value;
            node = node->listNext;
            return retval;
        }
        const iterator & operator --()
        {
            node = node->listPrev;
            return *this;
        }
        ECMAValue ** operator --(int)
        {
            ECMAValue ** retval = &node->value;
            node = node->listPrev;
            return retval;
        }
        friend bool operator ==(const iterator & a, const iterator & b)
        {
            return a.node == b.node;
        }
        friend bool operator !=(const iterator & a, const iterator & b)
        {
            return a.node != b.node;
        }
        wstring key() const
        {
            return node->key;
        }
    };
    class const_iterator : public std::iterator<std::bidirectional_iterator_tag, ECMAValue * const>
    {
        friend class ECMAValueObject;
        StackedGCObject<Node> node;
        const_iterator(StackedGCObject<Node> node)
            : node(std::move(node))
        {
        }
    public:
        const_iterator()
            : node(nullptr)
        {
        }
        const_iterator(const ECMAValueObject::iterator & i)
            : node(i.node)
        {
        }
        const_iterator(ECMAValueObject::iterator && i)
            : node(std::move(i.node))
        {
        }
        ECMAValue * const & operator *() const
        {
            return node->value;
        }
        const const_iterator & operator ++()
        {
            node = node->listNext;
            return *this;
        }
        ECMAValue * const * operator ++(int)
        {
            ECMAValue * const * retval = &node->value;
            node = node->listNext;
            return retval;
        }
        const const_iterator & operator --()
        {
            node = node->listPrev;
            return *this;
        }
        ECMAValue * const * operator --(int)
        {
            ECMAValue * const * retval = &node->value;
            node = node->listPrev;
            return retval;
        }
        bool operator ==(const ECMAValueObject::iterator & b) const
        {
            return node == b.node;
        }
        bool operator !=(const ECMAValueObject::iterator & b) const
        {
            return node != b.node;
        }
        friend bool operator ==(const const_iterator & a, const const_iterator & b)
        {
            return a.node == b.node;
        }
        friend bool operator !=(const const_iterator & a, const const_iterator & b)
        {
            return a.node != b.node;
        }
        friend bool operator ==(const ECMAValueObject::iterator & a, const const_iterator & b)
        {
            return b.operator ==(a);
        }
        friend bool operator !=(const ECMAValueObject::iterator & a, const const_iterator & b)
        {
            return b.operator !=(a);
        }
        wstring key() const
        {
            return node->key;
        }
    };
    iterator begin()
    {
        return iterator(listHead);
    }
    const_iterator begin() const
    {
        return const_iterator(listHead);
    }
    const_iterator cbegin() const
    {
        return const_iterator(listHead);
    }
    iterator end()
    {
        return iterator(nullptr);
    }
    const_iterator end() const
    {
        return const_iterator(nullptr);
    }
    const_iterator cend() const
    {
        return const_iterator(nullptr);
    }
    bool empty() const
    {
        return nodeCount == 0;
    }
    size_t size() const
    {
        return nodeCount;
    }
    bool erase(const_iterator iter)
    {
        if(iter.node == nullptr)
            return false;
        return erase(iter.key());
    }
    pair<iterator, bool> insert(wstring key, StackedGCObject<ECMAValue> value)
    {
        StackedGCObject<Node> node = get(key);
        if(node != nullptr)
        {
            node->value = value;
            return make_pair(iterator(node), false);
        }
        node = create(key);
        node->value = value;
        return make_pair(iterator(node), true);
    }
    iterator find(wstring key)
    {
        return iterator(get(key));
    }
    const_iterator find(wstring key) const
    {
        return const_iterator(get(key));
    }
};

#endif // ECMASCRIPT_H_INCLUDED
