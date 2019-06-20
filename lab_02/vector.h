#ifndef VECTOR_H
#define VECTOR_H

#include <stdarg.h>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <memory>
#include <stdexcept>

#include "vectorBase.h"
#include "iterator.h"

#define EPS 1e-5

namespace mylib
{
    template<typename SomeType>
    class Vector : public VectorBase
    {
    public:
        friend class Iterator<SomeType>;

        Vector();
        Vector(int number);
        Vector(int number, SomeType *vector);
        Vector(int number, SomeType vector, ...);
        Vector(std::initializer_list<SomeType> args);
        explicit Vector(const Vector<SomeType> &vector);
        Vector(Vector<SomeType>&& vector);
        ~Vector() override;

        std::shared_ptr<IteratorBase> begin() override;
        std::shared_ptr<IteratorBase> end() override;

//        Iterator<SomeType> begin() override;
//        Iterator<SomeType> end() override;

        Vector<SomeType> &operator =(const Vector<SomeType> &vector);
        Vector<SomeType> &operator =(Vector<SomeType> &&vector);
        Vector<SomeType> &operator =(std::initializer_list<SomeType> args);

        //int size() const;
        SomeType len() const;

        bool isZero() const;
        bool isSingle() const;

        int getSize() const override;
        bool isEmpty() const override;

        SomeType &operator[](int index);
        const SomeType &operator[](int index) const;
        SomeType &getElementVector(int index);
        const SomeType &getElementVector(int index) const;

        bool setElementVector(int index, const SomeType &element);

        Vector<SomeType> &getUnitVector() const;

        Vector<SomeType> &operator *=(const SomeType &mult);
        Vector<SomeType> &operator /=(const SomeType &div);

        Vector<SomeType> operator -();

        SomeType operator *(const Vector<SomeType> &vector) const;

        Vector<SomeType> &operator &=(const Vector<SomeType> &vector);
        Vector<SomeType> operator &(const Vector<SomeType> &vector) const;

        Vector<SomeType> operator+(const Vector<SomeType> &vector) const;
        Vector<SomeType> &operator+=(const Vector<SomeType> &vector);

        Vector<SomeType> operator-(const Vector<SomeType> &vector) const;
        Vector<SomeType> &operator-=(const Vector<SomeType> &vector);

        bool operator==(const Vector<SomeType> &vector) const;
        bool operator!=(const Vector<SomeType> &vector) const;

        bool isCollinearity(const Vector<SomeType> &vector) const;
        bool isOrthogonality(const Vector<SomeType> &vector) const;

        Vector<SomeType> getSingleVector() const;

        double angleBetweenVectors(const Vector<SomeType> &vector) const;

    private:
         std::shared_ptr<SomeType> data_list;

         Vector<SomeType> &sumVectors(const Vector<SomeType>& vec2) const;
         Vector<SomeType> &differenceVectors(const Vector<SomeType>& vec2) const;
         Vector<SomeType> &multVectors(const Vector<SomeType>& vec2) const;

     protected:
         SomeType sumAllElements();
         void newVector(int number);

    };

    template<typename SomeType>
    std::ostream &operator <<(std::ostream& os, const Vector<SomeType> &vector)
    {
        Iterator<SomeType> iterator(vector);

        if (!iterator)
        {
            os << "Vector is empty.";
            return os;
        }

        os << '(' << *iterator;
        for (iterator++; iterator; iterator++)
            os << ", " << *iterator ;
        os << ')';

        return os;
    }
}

#endif
