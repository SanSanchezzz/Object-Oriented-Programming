#ifndef ITERATOR_H
#define ITERATOR_H

#include "iteratorBase.h"
#include <iostream>
#include <stdio.h>
#include <functional>
#include <memory>
#include <managError.h>

namespace mylib
{
    template<class SomeType>
    class Vector;

    template<typename SomeType>
    class Iterator : public IteratorBase
    {
    public:
        Iterator(const Iterator<SomeType> &iterator);
        Iterator(const Vector<SomeType> &vector);

        SomeType &operator*();
        const SomeType &operator*() const;
        SomeType *operator->();
        const SomeType *operator->() const;
        operator bool() const;

        Iterator<SomeType> &operator=(const Iterator<SomeType> &iterator);

        Iterator<SomeType> &operator+=(int n);
        Iterator<SomeType> operator+(int n) const;
        Iterator<SomeType> &operator++();
        Iterator<SomeType> operator++(int);

        Iterator<SomeType> &operator-=(int n);
        Iterator<SomeType> operator-(int n) const;
        Iterator<SomeType> &operator--();
        Iterator<SomeType> operator--(int);

        bool operator<=(const Iterator<SomeType>& b) const;
        bool operator<(const Iterator<SomeType>& b) const;
        bool operator>=(const Iterator<SomeType>& b) const;
        bool operator>(const Iterator<SomeType>& b) const;
        bool operator==(const Iterator<SomeType>& b) const;
        bool operator!=(const Iterator<SomeType>& b) const;

        bool check(int line) const;

    private:
        std::weak_ptr<SomeType> data;

    protected:
        SomeType *getCurrentPointer() const;
    };

    template<class SomeType>
    SomeType *Iterator<SomeType>::getCurrentPointer() const
    {
        std::shared_ptr<SomeType> copyPtr = data.lock();

        return copyPtr.get() + index;
    }

    template<class SomeType>
    Iterator<SomeType>::Iterator(const Vector<SomeType> &vector)
    {
        index = 0;
        numberElements = vector.numberElements;
        data = vector.data_list;
        index = 0;
    }

    template<class SomeType>
    Iterator<SomeType>::Iterator(const Iterator<SomeType> &iterator)
    {
        data = iterator.data;
        numberElements = iterator.numberElements;
        index = iterator.index;
    }

    template<class SomeType>
    SomeType &Iterator<SomeType>::operator*()
    {
        check(__LINE__);

        return *getCurrentPointer();
    }

    template<class SomeType>
    SomeType* Iterator<SomeType>::operator->()
    {
        check(__LINE__);

        return getCurrentPointer();
    }

    template<class SomeType>
    const SomeType* Iterator<SomeType>::operator->() const
    {
        check(__LINE__);

        return getCurrentPointer();
    }

    template<class SomeType>
    Iterator<SomeType>& Iterator<SomeType>::operator=(const Iterator<SomeType>& iterator)
    {
        check(__LINE__);

        data = iterator.data;
        return *this;
    }

    template<class SomeType>
    Iterator<SomeType>& Iterator<SomeType>::operator+=(int n)
    {
        check(__LINE__);
        data += n;

        return *this;
    }

    template<class SomeType>
    Iterator<SomeType> Iterator<SomeType>::operator+(int n) const
    {
        check(__LINE__);
        Iterator<SomeType> iterator(*this);
        iterator += n;

        return iterator;
    }

    template<class SomeType>
    Iterator<SomeType> Iterator<SomeType>::operator++(int)
    {
        check(__LINE__);
        ++(*this);

        return *this;
    }

    template<class SomeType>
    Iterator<SomeType>& Iterator<SomeType>::operator++()
    {
        check(__LINE__);
        ++index;

        return *this;
    }

    template<class SomeType>
    Iterator<SomeType>& Iterator<SomeType>::operator-=(int n)
    {
        check(__LINE__);
        index -= n;

        return *this;
    }

    template<class SomeType>
    Iterator<SomeType> Iterator<SomeType>::operator-(int n) const
    {
        check(__LINE__);

        Iterator<SomeType> iterator(*this);
        iterator -= n;

        return iterator;
    }

    template<class SomeType>
    Iterator<SomeType> Iterator<SomeType>::operator--(int)
    {
        check(__LINE__);
        --(*this);

        return *this;
    }

    template<class SomeType>
    Iterator<SomeType>& Iterator<SomeType>::operator--()
    {
        check(__LINE__);
        --index;

        return *this;
    }

    template<class SomeType>
    bool Iterator<SomeType>::operator<=(const Iterator<SomeType>& b) const
    {
        check(__LINE__);

        return data <= b.data;
    }

    template<class SomeType>
    bool Iterator<SomeType>::operator<(const Iterator<SomeType>& b) const
    {
        check(__LINE__);

        return data < b.data;
    }

    template<class SomeType>
    bool Iterator<SomeType>::operator>=(const Iterator<SomeType>& b) const
    {
        check(__LINE__);

        return data >= b.data;
    }

    template<class SomeType>
    bool Iterator<SomeType>::operator>(const Iterator<SomeType>& b) const
    {
        check(__LINE__);

        return data > b.data;
    }

    template<class SomeType>
    bool Iterator<SomeType>::operator==(const Iterator<SomeType>& b) const
    {
        check(__LINE__);

        return data == b.data;
    }

    template<class SomeType>
    bool Iterator<SomeType>::operator!=(const Iterator<SomeType>& b) const
    {
        check(__LINE__);

        return data != b.data;
    }

    template<class SomeType>
    Iterator<SomeType>::operator bool() const
    {
        check(__LINE__);

        if (index >= numberElements || index < 0 || (numberElements == 0))
            return false;
        else
            return true;
    }

    template<class SomeType>
    bool Iterator<SomeType>::check(int line) const
    {
        if (!data.expired())
            return true;

        time_t t_time = time(NULL);
        throw deletedObj(__FILE__, typeid(*this).name(), line, ctime(&t_time));

        return false;
    }
}

#endif // ITERATOR_H
