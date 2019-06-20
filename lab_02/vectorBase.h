#ifndef VECTORBASE_H
#define VECTORBASE_H

#include "iterator.h"

#include <time.h>

namespace mylib
{
    template<typename SomeType>
    class Iterator;

    class VectorBase
    {
    public:
        VectorBase();
        VectorBase(const VectorBase &);
        virtual ~VectorBase() = default;

        virtual std::shared_ptr<IteratorBase> begin() = 0;
        virtual std::shared_ptr<IteratorBase> end() = 0;

        virtual bool isEmpty() const = 0;
        virtual int getSize() const = 0;

    protected:
        int numberElements = 0;
    };

}

#endif //VECTORBASE_H
