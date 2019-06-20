#include "vectorBase.h"

using namespace mylib;

VectorBase::VectorBase()
{
    numberElements = 0;
}

VectorBase::VectorBase(const VectorBase &base)
{
    numberElements = base.numberElements;
}
