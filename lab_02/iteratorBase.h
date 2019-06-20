#ifndef ITERATORBASE_H
#define ITERATORBASE_H

namespace mylib
{
    class IteratorBase
    {
    public:
        IteratorBase();

        IteratorBase(const IteratorBase &);

        virtual IteratorBase &operator++() = 0;
        virtual IteratorBase &operator*() = 0;
        virtual I

        virtual ~IteratorBase() = default;

    protected:
        int index = 0;

        int numberElements = 0;
    };
}

# endif // ITERATORBASE_H
