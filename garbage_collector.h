#ifndef GARBAGE_COLLECTOR_H_INCLUDED
#define GARBAGE_COLLECTOR_H_INCLUDED

#include <iterator>
#include <atomic>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <cstddef> // for offsetof
#include <vector>
#include <cassert>
#include <iostream>
#include <array>
#include <initializer_list>
#include <mutex> // for lock_guard
#include "range.h"

using namespace std;

class GCObject;

struct GCPtrDesc
{
    void * GCObject::*ptr;
    const size_t GCObject::*sizePtr;
    size_t count;
    template <typename T, typename PT>
    constexpr GCPtrDesc(PT * T::*member)
        : ptr(reinterpret_cast<void * GCObject::*>(static_cast<PT * GCObject::*>(member))), sizePtr(nullptr), count(1)
    {
        //static_assert(std::is_base_of<GCObject, T>::value, "T must derive from GCObject");
        //static_assert(std::is_base_of<GCObject, PT>::value, "PT must derive from GCObject");
    }
    template <typename T, typename PT>
    constexpr GCPtrDesc(PT ** T::*member, const size_t T::*sizeMember)
        : ptr(reinterpret_cast<void * GCObject::*>(static_cast<PT ** GCObject::*>(member))), sizePtr(static_cast<const size_t GCObject::*>(sizeMember)), count(0)
    {
        //static_assert(std::is_base_of<GCObject, T>::value, "T must derive from GCObject");
        //static_assert(std::is_base_of<GCObject, PT>::value, "PT must derive from GCObject");
    }
    template <typename T, typename PT>
    constexpr GCPtrDesc(PT * const * T::*member, const size_t T::*sizeMember)
        : ptr(reinterpret_cast<void * GCObject::*>(static_cast<PT * const * GCObject::*>(member))), sizePtr(static_cast<const size_t GCObject::*>(sizeMember)), count(0)
    {
        //static_assert(std::is_base_of<GCObject, T>::value, "T must derive from GCObject");
        //static_assert(std::is_base_of<GCObject, PT>::value, "PT must derive from GCObject");
    }
    template <typename T, typename PT, size_t N>
    constexpr GCPtrDesc(PT * (T::*member)[N])
        : ptr(reinterpret_cast<void * GCObject::*>(static_cast<PT * (GCObject::*)[N]>(member))), sizePtr(nullptr), count(N)
    {
        //static_assert(std::is_base_of<GCObject, T>::value, "T must derive from GCObject");
        //static_assert(std::is_base_of<GCObject, PT>::value, "PT must derive from GCObject");
    }
    constexpr GCPtrDesc(const GCPtrDesc & rt)
        : ptr(rt.ptr), sizePtr(rt.sizePtr), count(rt.count)
    {
    }
    constexpr GCPtrDesc(GCPtrDesc && rt)
        : ptr(rt.ptr), sizePtr(rt.sizePtr), count(rt.count)
    {
    }
    constexpr GCObject ** begin(GCObject * object) const
    {
        return count == 0 ? reinterpret_cast<GCObject **>(object->*ptr) : reinterpret_cast<GCObject **>(&(object->*ptr));
    }
    constexpr GCObject * const * begin(const GCObject * object) const
    {
        return count == 0 ? reinterpret_cast<GCObject * const *>(object->*ptr) : reinterpret_cast<GCObject * const *>(&(object->*ptr));
    }
    constexpr GCObject ** end(GCObject * obj) const
    {
        return count == 0 ? (begin(obj) == nullptr ? nullptr : begin(obj) + obj->*sizePtr) : begin(obj) + count;
    }
    constexpr GCObject * const * end(const GCObject * obj) const
    {
        return count == 0 ? (begin(obj) == nullptr ? nullptr : begin(obj) + obj->*sizePtr) : begin(obj) + count;
    }
    constexpr range<GCObject **> get(GCObject * obj) const
    {
        return make_range(begin(obj), end(obj));
    }
    constexpr range<GCObject * const *> get(const GCObject * obj) const
    {
        return make_range(begin(obj), end(obj));
    }
    void initObject(GCObject * obj) const
    {
        for(GCObject *& p : get(obj))
        {
            p = nullptr;
        }
    }
};

class GCObjectIterator : public iterator<random_access_iterator_tag, range<GCObject **>>
{
    friend class GCObjectConstIterator;
    GCObject * object;
    const GCPtrDesc * pointerDescriptor;
public:
    GCObjectIterator(GCObject * object, const GCPtrDesc * pointerDescriptor)
        : object(object), pointerDescriptor(pointerDescriptor)
    {
    }
    GCObjectIterator()
        : object(nullptr), pointerDescriptor(nullptr)
    {
    }
    const GCObjectIterator & operator ++()
    {
        pointerDescriptor++;
        return *this;
    }
    const GCObjectIterator operator ++(int)
    {
        return GCObjectIterator(object, pointerDescriptor++);
    }
    const GCObjectIterator & operator --()
    {
        pointerDescriptor--;
        return *this;
    }
    const GCObjectIterator operator --(int)
    {
        return GCObjectIterator(object, pointerDescriptor--);
    }
    friend bool operator ==(const GCObjectIterator & a, const GCObjectIterator & b)
    {
        return a.pointerDescriptor == b.pointerDescriptor;
    }
    friend bool operator !=(const GCObjectIterator & a, const GCObjectIterator & b)
    {
        return a.pointerDescriptor != b.pointerDescriptor;
    }
    value_type operator *() const
    {
        return pointerDescriptor->get(object);
    }
    friend GCObjectIterator operator +(ptrdiff_t count, const GCObjectIterator & iter)
    {
        return GCObjectIterator(iter.object, iter.pointerDescriptor + count);
    }
    friend GCObjectIterator operator +(const GCObjectIterator & iter, ptrdiff_t count)
    {
        return GCObjectIterator(iter.object, iter.pointerDescriptor + count);
    }
    friend GCObjectIterator operator -(const GCObjectIterator & iter, ptrdiff_t count)
    {
        return GCObjectIterator(iter.object, iter.pointerDescriptor - count);
    }
    friend ptrdiff_t operator -(const GCObjectIterator & a, const GCObjectIterator & b)
    {
        return a.pointerDescriptor - b.pointerDescriptor;
    }
    friend bool operator <(const GCObjectIterator & a, const GCObjectIterator & b)
    {
        return a.pointerDescriptor < b.pointerDescriptor;
    }
    friend bool operator >(const GCObjectIterator & a, const GCObjectIterator & b)
    {
        return a.pointerDescriptor > b.pointerDescriptor;
    }
    friend bool operator <=(const GCObjectIterator & a, const GCObjectIterator & b)
    {
        return a.pointerDescriptor <= b.pointerDescriptor;
    }
    friend bool operator >=(const GCObjectIterator & a, const GCObjectIterator & b)
    {
        return a.pointerDescriptor >= b.pointerDescriptor;
    }
    const GCObjectIterator & operator +=(ptrdiff_t count)
    {
        pointerDescriptor += count;
        return *this;
    }
    const GCObjectIterator & operator -=(ptrdiff_t count)
    {
        pointerDescriptor -= count;
        return *this;
    }
    value_type operator [](ptrdiff_t index) const
    {
        return GCObjectIterator(object, pointerDescriptor + index).operator *();
    }
};

class GCObjectConstIterator : public iterator<random_access_iterator_tag, range<GCObject * const *>>
{
    const GCObject * object;
    const GCPtrDesc * pointerDescriptor;
public:
    GCObjectConstIterator(const GCObject * object, const GCPtrDesc * pointerDescriptor)
        : object(object), pointerDescriptor(pointerDescriptor)
    {
    }
    GCObjectConstIterator()
        : object(nullptr), pointerDescriptor(nullptr)
    {
    }
    GCObjectConstIterator(const GCObjectIterator & rt)
        : object(rt.object), pointerDescriptor(rt.pointerDescriptor)
    {
    }
    const GCObjectConstIterator & operator ++()
    {
        pointerDescriptor++;
        return *this;
    }
    const GCObjectConstIterator operator ++(int)
    {
        return GCObjectConstIterator(object, pointerDescriptor++);
    }
    const GCObjectConstIterator & operator --()
    {
        pointerDescriptor--;
        return *this;
    }
    const GCObjectConstIterator operator --(int)
    {
        return GCObjectConstIterator(object, pointerDescriptor--);
    }
    friend bool operator ==(const GCObjectConstIterator & a, const GCObjectConstIterator & b)
    {
        return a.pointerDescriptor == b.pointerDescriptor;
    }
    friend bool operator !=(const GCObjectConstIterator & a, const GCObjectConstIterator & b)
    {
        return a.pointerDescriptor != b.pointerDescriptor;
    }
    value_type operator *() const
    {
        return pointerDescriptor->get(object);
    }
    friend GCObjectConstIterator operator +(ptrdiff_t count, const GCObjectConstIterator & iter)
    {
        return GCObjectConstIterator(iter.object, iter.pointerDescriptor + count);
    }
    friend GCObjectConstIterator operator +(const GCObjectConstIterator & iter, ptrdiff_t count)
    {
        return GCObjectConstIterator(iter.object, iter.pointerDescriptor + count);
    }
    friend GCObjectConstIterator operator -(const GCObjectConstIterator & iter, ptrdiff_t count)
    {
        return GCObjectConstIterator(iter.object, iter.pointerDescriptor - count);
    }
    friend ptrdiff_t operator -(const GCObjectConstIterator & a, const GCObjectConstIterator & b)
    {
        return a.pointerDescriptor - b.pointerDescriptor;
    }
    friend bool operator <(const GCObjectConstIterator & a, const GCObjectConstIterator & b)
    {
        return a.pointerDescriptor < b.pointerDescriptor;
    }
    friend bool operator >(const GCObjectConstIterator & a, const GCObjectConstIterator & b)
    {
        return a.pointerDescriptor > b.pointerDescriptor;
    }
    friend bool operator <=(const GCObjectConstIterator & a, const GCObjectConstIterator & b)
    {
        return a.pointerDescriptor <= b.pointerDescriptor;
    }
    friend bool operator >=(const GCObjectConstIterator & a, const GCObjectConstIterator & b)
    {
        return a.pointerDescriptor >= b.pointerDescriptor;
    }
    const GCObjectConstIterator & operator +=(ptrdiff_t count)
    {
        pointerDescriptor += count;
        return *this;
    }
    const GCObjectConstIterator & operator -=(ptrdiff_t count)
    {
        pointerDescriptor -= count;
        return *this;
    }
    value_type operator [](ptrdiff_t index) const
    {
        return GCObjectConstIterator(object, pointerDescriptor + index).operator *();
    }
};

template <typename ...Args>
constexpr size_t countArgs(Args...)
{
    return sizeof...(Args);
}

template<size_t N>
struct GCObjectMembersPointerDescriptorArray
{
    const GCPtrDesc pointerDescriptorArray[N];
    constexpr const GCPtrDesc * begin() const
    {
        return pointerDescriptorArray;
    }
    constexpr const GCPtrDesc * end() const
    {
        return pointerDescriptorArray + N;
    }
};

template <size_t N>
constexpr range<const GCPtrDesc *> make_range(const GCObjectMembersPointerDescriptorArray<N> & v)
{
    return range<const GCPtrDesc *>(v.begin(), v.end());
}

template <typename ...Args>
constexpr GCObjectMembersPointerDescriptorArray<sizeof...(Args)> makeGCObjectMembersPointerDescriptorArray(Args ...args)
{
    return GCObjectMembersPointerDescriptorArray<sizeof...(Args)>{GCPtrDesc(args)...};
}

#define GCOBJECT_POINTER_VARIABLES(...) \
friend class ::GarbageCollector;\
public:\
static const ::GCObjectMembersPointerDescriptorArray<countArgs(__VA_ARGS__)> & pointerDescriptorArray()\
{\
    static ::GCObjectMembersPointerDescriptorArray<countArgs(__VA_ARGS__)> retval = ::makeGCObjectMembersPointerDescriptorArray(__VA_ARGS__);\
    return retval;\
}
class GarbageCollector;

class GCObject
{
    friend class GarbageCollector;
    template <typename T>
    friend class GCObjectPointerArray;
    template <typename T>
    friend class StackedGCObject;
    template <typename...Args>
    static void * operator new[](size_t, Args...) = delete;
    static void * operator new(size_t) = delete;
    static constexpr void * operator new(size_t, void * memory)
    {
        return memory;
    }
private:
    template <typename...Args>
    static void operator delete[](void *, Args...) {}
protected:
    static void operator delete(void *) {}
private:
    enum State
    {
        Unused,
        Used,
        Finalized,
    };
    mutable State state;
    range<const GCPtrDesc *> pointerDescriptorArrayInternal;
    size_t size;
    GarbageCollector * gc;
    template <size_t N>
    void init(const GCObjectMembersPointerDescriptorArray<N> & membersPointerDescriptorArray, size_t size, GarbageCollector * gc)
    {
        state = Used;
        pointerDescriptorArrayInternal = make_range(membersPointerDescriptorArray);
        this->size = size;
        this->gc = gc;
        for(const GCPtrDesc & pointerDescriptor : pointerDescriptorArrayInternal)
        {
            pointerDescriptor.initObject(this);
        }
    }
protected:
    range<const GCPtrDesc *> getPointerDescriptorArray() const
    {
        return pointerDescriptorArrayInternal;
    }
    range<GCObjectIterator> pointerMembers()
    {
        range<const GCPtrDesc *> objectOffsetArray = getPointerDescriptorArray();
        return make_range(GCObjectIterator(this, objectOffsetArray.begin()), GCObjectIterator(this, objectOffsetArray.end()));
    }
    range<GCObjectConstIterator> pointerMembers() const
    {
        range<const GCPtrDesc *> objectOffsetArray = getPointerDescriptorArray();
        return make_range(GCObjectConstIterator(this, objectOffsetArray.begin()), GCObjectConstIterator(this, objectOffsetArray.end()));
    }
    GarbageCollector & getGarbageCollector() const
    {
        return *gc;
    }
public:
    virtual ~GCObject() noexcept
    {
    }
};

template <typename T = GCObject>
class GCObjectPointerArray : public GCObject
{
    static_assert(std::is_base_of<GCObject, T>::value, "T must derive from GCObject");
    T ** array;
    size_t sizeInternal;
    GCObjectPointerArray(const GCObjectPointerArray &) = delete;
    const GCObjectPointerArray & operator =(const GCObjectPointerArray &) = delete;
    GCOBJECT_POINTER_VARIABLES(GCPtrDesc(&GCObjectPointerArray::array, &GCObjectPointerArray::sizeInternal))
public:
    GCObjectPointerArray(size_t size)
        : array(new T *[size]), sizeInternal(size)
    {
        for(T *& p : array)
        {
            p = nullptr;
        }
    }
    virtual ~GCObjectPointerArray()
    {
        delete []array;
        array = nullptr;
        sizeInternal = 0;
    }
    const size_t size() const
    {
        return sizeInternal;
    }
    T *& operator [](size_t index)
    {
        return array[index];
    }
    T * const & operator [](size_t index) const
    {
        return array[index];
    }
    typedef T ** iterator;
    typedef T * const * const_iterator;
    iterator begin()
    {
        return array;
    }
    iterator end()
    {
        return array + sizeInternal;
    }
    const_iterator begin() const
    {
        return array;
    }
    const_iterator end() const
    {
        return array + sizeInternal;
    }
    const_iterator cbegin() const
    {
        return array;
    }
    const_iterator cend() const
    {
        return array + sizeInternal;
    }
};

class GarbageCollector;

template <typename T>
class StackedGCObject final
{
    static_assert(std::is_base_of<GCObject, T>::value, "T must derive from GCObject");
    template <typename...Args>
    static void * operator new(size_t, Args...) = delete;
    template <typename...Args>
    static void * operator new[](size_t, Args...) = delete;
private:
    template <typename...Args>
    static void operator delete(void *, Args...) {}
    template <typename...Args>
    static void operator delete[](void *, Args...) {}
private:
    T * obj;
    size_t slotIndex;
    void set();
    void free();
    void allocate();
    StackedGCObject(T * obj, size_t slotIndex)
        : obj(obj), slotIndex(slotIndex)
    {
    }
public:
    StackedGCObject(T * obj = nullptr)
        : obj(obj)
    {
        allocate();
    }
    StackedGCObject(std::nullptr_t)
        : obj(nullptr)
    {
        allocate();
    }
    StackedGCObject(const StackedGCObject & rt)
        : obj(rt.obj)
    {
        allocate();
    }
    StackedGCObject(StackedGCObject && rt)
        : obj(rt.obj), slotIndex(rt.slotIndex)
    {
        rt.obj = nullptr;
    }
    static StackedGCObject attach(T * obj, size_t slotIndex)
    {
        return StackedGCObject(obj, slotIndex);
    }
    const StackedGCObject & operator =(T * o)
    {
        if(o == obj)
            return *this;
        if(o == nullptr)
        {
            free();
            obj = nullptr;
        }
        else if(obj == nullptr)
        {
            obj = o;
            allocate();
        }
        else
        {
            obj = o;
            set();
        }
        return *this;
    }
    const StackedGCObject & operator =(const StackedGCObject & rt)
    {
        return operator =(rt.obj);
    }
    const StackedGCObject & operator =(StackedGCObject && rt)
    {
        std::swap(obj, rt.obj);
        std::swap(slotIndex, rt.slotIndex);
        return *this;
    }
    operator T *() const
    {
        return obj;
    }
    T * operator ->() const
    {
        return obj;
    }
    T & operator *() const
    {
        return *obj;
    }
    friend bool operator ==(const StackedGCObject & a, const StackedGCObject & b)
    {
        return a.obj == b.obj;
    }
    friend bool operator !=(const StackedGCObject & a, const StackedGCObject & b)
    {
        return a.obj != b.obj;
    }
    friend bool operator ==(const StackedGCObject & sobj, std::nullptr_t)
    {
        return sobj.obj == nullptr;
    }
    friend bool operator !=(const StackedGCObject & sobj, std::nullptr_t)
    {
        return sobj.obj != nullptr;
    }
    friend bool operator ==(std::nullptr_t, const StackedGCObject & sobj)
    {
        return sobj.obj == nullptr;
    }
    friend bool operator !=(std::nullptr_t, const StackedGCObject & sobj)
    {
        return sobj.obj != nullptr;
    }
    friend bool operator ==(const StackedGCObject & sobj, T * obj)
    {
        return sobj.obj == obj;
    }
    friend bool operator ==(T * obj, const StackedGCObject & sobj)
    {
        return sobj.obj == obj;
    }
    friend bool operator !=(const StackedGCObject & sobj, T * obj)
    {
        return sobj.obj != obj;
    }
    friend bool operator !=(T * obj, const StackedGCObject & sobj)
    {
        return sobj.obj != obj;
    }
    ~StackedGCObject()
    {
        free();
    }
};

inline ostream & operator <<(ostream & os, const unordered_set<GCObject *> & s)
{
    os << "{";
    const char * seperator = "";
    for(GCObject * obj : s)
    {
        os << seperator << (void *)obj;
        seperator = ", ";
    }
    return os << "}";
}

inline ostream & operator <<(ostream & os, const vector<GCObject *> & v)
{
    os << "[";
    const char * seperator = "";
    for(GCObject * obj : v)
    {
        os << seperator << (void *)obj;
        seperator = ", ";
    }
    return os << "]";
}

class GarbageCollector final
{
    GarbageCollector(const GarbageCollector &) = delete;
    const GarbageCollector & operator =(const GarbageCollector &) = delete;
private:
    vector<GCObject *> rootStack;
    unordered_set<size_t> freeRootStackSlots;
    unordered_set<GCObject *> rootSet;
    unordered_set<GCObject * const *> staticRootSet;
    unordered_set<GCObject *> objectsSet;
    unordered_set<GCObject *> finalizingSet;
    bool isFinalizing = false;
    size_t lockCount = 0;
    size_t maxSize;
    size_t startCollectSize;
    size_t currentSize = 0;
    void freeObjectNoDestruct(GCObject * object)
    {
        objectsSet.erase(object);
        currentSize -= object->size;
        delete [](char *)object;
    }
public:
    GarbageCollector(size_t maxSize, size_t startCollectSize)
        : maxSize(maxSize), startCollectSize(startCollectSize)
    {
    }
    GarbageCollector(size_t maxSize = (size_t)100 << 20) // 100MB
        : GarbageCollector(maxSize, 4 * maxSize / 5)
    {
    }
    ~GarbageCollector()
    {
        for(GCObject * obj : objectsSet)
        {
            delete [](char *)obj;
        }
    }
    size_t allocateRootStackSlot(GCObject * obj)
    {
        assert(obj != nullptr);
        if(freeRootStackSlots.empty())
        {
            rootStack.push_back(obj);
            return rootStack.size() - 1;
        }
        size_t index = *freeRootStackSlots.begin();
        freeRootStackSlots.erase(freeRootStackSlots.begin());
        rootStack[index] = nullptr;
        return index;
    }
    void freeRootStackSlot(size_t index)
    {
        assert(index < rootStack.size());
        if(index == rootStack.size() - 1)
        {
            rootStack.resize(rootStack.size() - 1);
            while(rootStack.size() > 0 && freeRootStackSlots.find(rootStack.size() - 1) != freeRootStackSlots.end())
            {
                freeRootStackSlots.erase(rootStack.size() - 1);
                rootStack.resize(rootStack.size() - 1);
            }
        }
        else
        {
            rootStack[index] = nullptr;
            freeRootStackSlots.insert(index);
        }
    }
    void setRootStackSlot(size_t index, GCObject * obj)
    {
        assert(index < rootStack.size());
        assert(obj != nullptr);
        assert(rootStack[index] != nullptr);
        rootStack[index] = obj;
    }
    GCObject * getRootStackSlot(size_t index)
    {
        assert(index < rootStack.size());
        GCObject * retval = rootStack[index];
        assert(retval != nullptr);
        return retval;
    }
    void addRoot(GCObject * obj)
    {
        assert(obj != nullptr);
        rootSet.insert(obj);
    }
    void addStaticRoot(GCObject * const * pobj)
    {
        assert(pobj != nullptr);
        staticRootSet.insert(pobj);
    }
    void removeRoot(GCObject * obj)
    {
        assert(obj != nullptr);
        rootSet.erase(obj);
    }
    void removeStaticRoot(GCObject * const * pobj)
    {
        assert(pobj != nullptr);
        staticRootSet.erase(pobj);
    }
    template <typename T, typename... ArgTypes>
    StackedGCObject<T> allocate(ArgTypes... args)
    {
        static_assert(std::is_base_of<GCObject, T>::value, "can't allocate type not derived from GCObject");
        const size_t size = sizeof(T);
        if(currentSize + size > startCollectSize)
            gc();
        if(currentSize + size > maxSize)
            return nullptr;
        void * memory = (void *)new char[size];
        if(memory == nullptr)
            return nullptr;
        currentSize += size;
        ((GCObject *)memory)->init(T::pointerDescriptorArray(), size, this);
        objectsSet.insert((GCObject *)memory);
        size_t index = allocateRootStackSlot((GCObject *)memory);
        return StackedGCObject<T>::attach(new(memory) T(std::forward<ArgTypes>(args)...), index);
    }
    void gc() // tricolor mark-sweep
    {
        if(lockCount > 0)
            return;
        unordered_set<GCObject *> graySet;
        // don't have variable for black set
        unordered_set<GCObject *> whiteSet = objectsSet;

        // mark roots
        for(GCObject * obj : rootStack)
        {
            if(obj == nullptr)
                continue;
            whiteSet.erase(obj);
            graySet.insert(obj);
        }
        for(GCObject * obj : rootSet)
        {
            whiteSet.erase(obj);
            graySet.insert(obj);
        }
        for(GCObject * obj : finalizingSet)
        {
            whiteSet.erase(obj);
            graySet.insert(obj);
        }
        for(GCObject * const * pobj : staticRootSet)
        {
            GCObject * obj = *pobj;
            if(obj == nullptr)
                continue;
            whiteSet.erase(obj);
            graySet.insert(obj);
        }

        //cout << "after mark roots : \nWhite Set : " << whiteSet << "\n Gray Set : " << graySet << endl;

        // mark everything else
        while(!graySet.empty())
        {
            unordered_set<GCObject *> newGraySet;
            while(!graySet.empty())
            {
                GCObject * currentObject = *graySet.begin();
                for(range<GCObject * const *> objects : currentObject->pointerMembers())
                {
                    for(GCObject * obj : objects)
                    {
                        if(obj == nullptr)
                            continue;
                        if(whiteSet.find(obj) != whiteSet.end())
                        {
                            whiteSet.erase(obj);
                            newGraySet.insert(obj);
                        }
                    }
                }
                graySet.erase(graySet.begin());
            }
            graySet = newGraySet;
        }

        //cout << "after mark all : \nWhite Set : " << whiteSet << "\n Gray Set : " << graySet << endl;

        // sweep
        for(GCObject * obj : whiteSet)
        {
            if(obj->state == GCObject::Finalized)
                freeObjectNoDestruct(obj);
            else if(!isFinalizing)
                finalizingSet.insert(obj);
        }
        if(isFinalizing || finalizingSet.empty())
            return;
        isFinalizing = true;
        for(GCObject * obj : finalizingSet)
        {
            obj->~GCObject();
        }
        isFinalizing = false;
        for(GCObject * obj : finalizingSet)
        {
            obj->state = GCObject::Finalized;
        }
        finalizingSet.clear();
        //don't free finalized objects yet because they might be reachable again
    }
    void dumpRoots() const
    {
        cout << "Stack :\n";
        for(GCObject * obj : rootStack)
        {
            cout << (void *)obj << endl;
        }
        cout << endl;
    }
    void lock()
    {
        lockCount++;
    }
    void unlock()
    {
        lockCount--;
    }
};

template <typename T>
inline void StackedGCObject<T>::allocate()
{
    if(obj != nullptr)
        slotIndex = obj->getGarbageCollector().allocateRootStackSlot(obj);
}

template <typename T>
inline void StackedGCObject<T>::set()
{
    if(obj != nullptr)
        obj->getGarbageCollector().setRootStackSlot(slotIndex, obj);
}

template <typename T>
inline void StackedGCObject<T>::free()
{
    if(obj != nullptr)
        obj->getGarbageCollector().freeRootStackSlot(slotIndex);
    obj = nullptr;
}

typedef std::lock_guard<GarbageCollector> GCLockGuard;

#endif // GARBAGE_COLLECTOR_H_INCLUDED
