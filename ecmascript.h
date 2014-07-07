#ifndef ECMASCRIPT_H_INCLUDED
#define ECMASCRIPT_H_INCLUDED

#include "garbage_collector.h"
#include <utility>
#include <cwchar>
#include <string>
#include <iterator>

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
    wstring getValue() const
    {
        return value;
    }
    virtual wstring toString() const override
    {
        return value;
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
