#include "iteratorBase.h"
#include "iterator.h"

namespace mylib
{
    template<class SomeType>
    class Vector;

    template<typename SomeType>
    class ConstIterator : public IteratorBase
    {
    public:
        ConstIterator(const ConstIterator<SomeType>& iterator);
        ConstIterator(const Vector<SomeType>& vector);

        const SomeType& operator*() const;
        const SomeType* operator->() const;
        operator bool() const;

        ConstIterator<SomeType>& operator=(const Iterator<SomeType>& iterator);

        ConstIterator<SomeType>& operator+=(int n);
        ConstIterator<SomeType> operator+(int n) const;
        ConstIterator<SomeType>& operator++();
        ConstIterator<SomeType> operator++(int);

        ConstIterator<SomeType>& operator-=(int n);
        ConstIterator<SomeType> operator-(int n) const;
        ConstIterator<SomeType>& operator--();
        ConstIterator<SomeType> operator--(int);

        bool operator<=(const ConstIterator<SomeType>& b) const;
        bool operator<(const ConstIterator<SomeType>& b) const;
        bool operator>=(const ConstIterator<SomeType>& b) const;
        bool operator>(const ConstIterator<SomeType>& b) const;
        bool operator==(const ConstIterator<SomeType>& b) const;
        bool operator!=(const ConstIterator<SomeType>& b) const;

        bool check(int line) const;

    private:
        std::weak_ptr<SomeType> data;

    protected:
        SomeType* getCurrentPointer() const;
    };

    template<class SomeType>
    SomeType* ConstIterator<SomeType>::getCurrentPointer() const
    {
        std::shared_ptr<SomeType> copy_ptr = data.lock();

        return copy_ptr.get() + index;
    }

    template<class SomeType>
    ConstIterator<SomeType>::ConstIterator(const Vector<SomeType>& vector)
    {
        index = 0;
        numberElements = vector.numberElements;
        data = vector.data_list;
        index = 0;
    }

    template<class SomeType>
    ConstIterator<SomeType>::ConstIterator(const ConstIterator<SomeType>& iterator)
    {
        data = iterator.data;
        index = iterator.index;
        numberElements = iterator.numberElements;
    }

    template<class SomeType>
    const SomeType& ConstIterator<SomeType>::operator*() const
    {
        check(__LINE__);

        std::shared_ptr<SomeType> copy_ptr = data.lock();

        return *getCurrentPointer();
    }

    template<class SomeType>
    const SomeType* ConstIterator<SomeType>::operator->() const
    {
        check(__LINE__);

        return getCurrentPointer();
    }

    template<class SomeType>
    ConstIterator<SomeType>& ConstIterator<SomeType>::operator=(const Iterator<SomeType>& iterator)
    {
        check(__LINE__);

        data = iterator.data;

        return *this;
    }

    template<class SomeType>
    ConstIterator<SomeType>& ConstIterator<SomeType>::operator+=(int n)
    {
        check(__LINE__);

        data += n;

        return *this;
    }

    template<class SomeType>
    ConstIterator<SomeType> ConstIterator<SomeType>::operator+(int n) const
    {
        check(__LINE__);

        ConstIterator<SomeType> iterator(*this);
        iterator += n;

        return iterator;
    }

    template<class SomeType>
    ConstIterator<SomeType> ConstIterator<SomeType>::operator++(int)
    {
        check(__LINE__);

        ++(*this);

        return *this;
    }

    template<class SomeType>
    ConstIterator<SomeType>& ConstIterator<SomeType>::operator++()
    {
        check(__LINE__);

        ++index;

        return *this;
    }

    template<class SomeType>
    ConstIterator<SomeType>& ConstIterator<SomeType>::operator-=(int n)
    {
        check(__LINE__);

        index -= n;

        return *this;
    }

    template<class SomeType>
    ConstIterator<SomeType> ConstIterator<SomeType>::operator-(int n) const
    {
        check(__LINE__);

        ConstIterator<SomeType> iterator(*this);
        iterator -= n;

        return iterator;
    }

    template<class SomeType>
    ConstIterator<SomeType> ConstIterator<SomeType>::operator--(int)
    {
        check(__LINE__);

        --(*this);

        return *this;
    }

    template<class SomeType>
    ConstIterator<SomeType>& ConstIterator<SomeType>::operator--()
    {
        check(__LINE__);

        --index;

        return *this;
    }

    template<class SomeType>
    bool ConstIterator<SomeType>::operator<=(const ConstIterator<SomeType>& b) const
    {
        check(__LINE__);

        return data <= b.data;
    }

    template<class SomeType>
    bool ConstIterator<SomeType>::operator<(const ConstIterator<SomeType>& b) const
    {
        check(__LINE__);

        return data < b.data;
    }

    template<class SomeType>
    bool ConstIterator<SomeType>::operator>=(const ConstIterator<SomeType>& b) const
    {
        check(__LINE__);

        return data >= b.data;
    }

    template<class SomeType>
    bool ConstIterator<SomeType>::operator>(const ConstIterator<SomeType>& b) const
    {
        check(__LINE__);

        return data > b.data;
    }

    template<class SomeType>
    bool ConstIterator<SomeType>::operator==(const ConstIterator<SomeType>& b) const
    {
        check(__LINE__);

        return data == b.data;
    }

    template<class SomeType>
    bool ConstIterator<SomeType>::operator!=(const ConstIterator<SomeType>& b) const
    {
        check(__LINE__);

        return data != b.data;
    }

    template<class SomeType>
    ConstIterator<SomeType>::operator bool() const
    {
        check(__LINE__);

        if (index >= numberElements || index < 0 || (numberElements == 0))
            return false;
        else
            return true;
    }

    template<class SomeType>
    bool ConstIterator<SomeType>::check(int line) const
    {
        return !data.expired();
    }
}
