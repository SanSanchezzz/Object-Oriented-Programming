#include "iteratorBase.h"

using namespace mylib;

IteratorBase::IteratorBase()
{
    index = 0;

    numberElements = 0;
}

IteratorBase::IteratorBase(const IteratorBase &iterator)
{
    index = iterator.index;

    numberElements = iterator.numberElements;
}


