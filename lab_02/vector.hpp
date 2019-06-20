#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <stdlib.h>
#include <cstddef>

#include "vector.h"
#include "managError.h"

#define EPS 1e-5

namespace mylib
{

    int max(int a, int b)
    {
        if (a >= b)
            return a;
        else
            return b;
    }
    template<typename SomeType>
    std::shared_ptr<IteratorBase> Vector<SomeType>::begin()
    {
        auto newPtr = std::make_shared<Iterator<SomeType> >(*this);

        return newPtr;
    }

    template<typename SomeType>
    std::shared_ptr<IteratorBase> Vector<SomeType>::end()
    {
        auto newPtr = std::make_shared<Iterator<SomeType> >(*this);

        for (; *newPtr; *newPtr++)
        ;

        return newPtr;
    }

    template<typename SomeType>
    Vector<SomeType>::Vector()
    {
        numberElements = 0;

        newVector(numberElements);
    }

    template<typename SomeType>
    Vector<SomeType>::Vector(int number)
    {
        time_t t_time = time(NULL);

        if (number < 0)
            throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

        numberElements = number;

        newVector(numberElements);

        if (!data_list)
            throw memError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

        Iterator<SomeType> iterator(*this);
        for (; iterator; iterator++)
            *iterator = 0;
    }

    template<typename SomeType>
    int Vector<SomeType>::getSize() const
    {
        return numberElements;
    }

    template<typename SomeType>
    bool Vector<SomeType>::isEmpty() const
    {
        return !numberElements;
    }

    template<typename SomeType>
    Vector<SomeType>::Vector(int number, SomeType vector, ...)
    {
        time_t t_time = time(NULL);
        if (number < 1)
            throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

        numberElements= number;
        newVector(numberElements);

        if (!data_list)
            throw memError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

        Iterator<SomeType> iterator(*this);
        va_list ap;
        va_start(ap, vector);
        for (; iterator; iterator++)
        {
            *iterator = vector;
            vector = va_arg(ap, SomeType);
        }
        va_end(ap);
    }

    template<typename SomeType>
    Vector<SomeType>::Vector(int number, SomeType* vector)
    {
        time_t t_time = time(NULL);
        if (number <= 0)
            throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

        numberElements = number;
        newVector(numberElements);

        Iterator<SomeType> iter(*this);
        for (int i = 0; iter; i++, iter++)
            *iter = vector[i];
    }

    template<typename SomeType>
    Vector<SomeType>::Vector(std::initializer_list<SomeType> args)
    {
        if (args.size() == 0)
            Vector();

        numberElements = int(args.size());
        newVector(numberElements);

        Iterator<SomeType> iter(*this);
        for (auto &element : args)
        {
            *iter = element;
            iter++;
        }
    }

    template<typename SomeType>
    Vector<SomeType>::Vector(const Vector<SomeType> &vector)
    {
        numberElements = vector.numberElements;
        newVector(numberElements);

        Iterator<SomeType> iter_new(*this);
        Iterator<SomeType> iter(vector);
        for (; iter_new; iter++, iter_new++)
            *iter_new = *iter;
    }

    template<typename SomeType>
    SomeType &Vector<SomeType>::getElementVector(int index)
    {
        time_t t_time = time(NULL);
        if (index < 0 || index >= numberElements)
            throw indexError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

        Iterator<SomeType> iter(*this);
        for (int i = 0; i < index; i++, iter++)
            ;

        return *iter;
    }

    template<typename SomeType>
    const SomeType &Vector<SomeType>::getElementVector(int index) const
    {
        time_t t_time = time(NULL);
        if (index < 0 || index >= numberElements)
            throw indexError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

        newVector(numberElements);
        Iterator<SomeType> iter(*this);
        for (int i = 0; i <= index; i++, iter++)
            ;

        return *iter;
    }

    template <typename SomeType>
    bool Vector<SomeType>::operator ==(const Vector<SomeType>& vector) const
    {
        int equal = 1;
        if (numberElements != vector.numberElements)
            return false;
        else
        {
            Iterator<SomeType> iter1(*this);
            Iterator<SomeType> iter2(vector);

            for (; iter1 && equal; iter1++, iter2++)
                if (fabs(*iter1 - *iter2) > EPS)
                    equal = 0;
        }

        return equal;
    }

    template <typename SomeType>
    bool Vector<SomeType>::operator !=(const Vector<SomeType>& vector) const
    {
        if (*this == vector)
            return false;
        else
            return true;
    }

    template<typename SomeType>
    SomeType Vector<SomeType>::len(void) const
    {
        time_t t_time = time(NULL);
        if (numberElements < 0)
            throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

        Iterator<SomeType> iter(*this);
        double sum = 0;
        for (; iter; iter++)
            sum += *iter * *iter;

        return sqrt(sum);
    }

    template <typename SomeType>
    SomeType Vector<SomeType>::operator *(const Vector<SomeType>& vector) const
    {
        time_t t_time = time(NULL);
        if (numberElements < 0 || vector.numberElements < 0)
            throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

        int max_len = max(numberElements, vector.numberElements);
        Vector<SomeType> new_vector;
        new_vector = multVectors(vector);

        return new_vector.sumAllElements();
    }

    template <typename SomeType>
    Vector<SomeType> Vector<SomeType>::operator +(const Vector<SomeType>& vector) const
    {
        time_t t_time = time(NULL);
        if (numberElements < 0 || vector.numberElements < 0)
            throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

        int max_len = max(numberElements, vector.numberElements);
        Vector<SomeType> new_vector(max_len);
        sum_vectors(new_vector, *this, vector);

        return new_vector;
    }

    template <typename SomeType>
    Vector<SomeType>& Vector<SomeType>::operator +=(const Vector<SomeType>& vector)
    {
        time_t t_time = time(NULL);
        if (numberElements < 0 || vector.numberElements < 0)
            throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

        sum_vectors(*this, *this, vector);

        return *this;
    }

    template <typename SomeType>
    Vector<SomeType> Vector<SomeType>::operator -(const Vector<SomeType>& vector) const
    {
        time_t t_time = time(NULL);
        if (numberElements < 0 || vector.numberElements < 0)
            throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

        int max_len = max(numberElements, vector.numberElements);
        Vector<SomeType> new_vector(max_len);
        difference_vectors(new_vector, *this, vector);

        return new_vector;
    }

    template <typename SomeType>
    Vector<SomeType> Vector<SomeType>::operator -()
    {
        Vector<SomeType> new_vector(*this);
        Iterator<SomeType> iter(new_vector);
        for (; iter; iter++)
            *iter = -*iter;

        return new_vector;
    }

    template <typename SomeType>
    Vector<SomeType>& Vector<SomeType>::operator -=(const Vector<SomeType>& vector)
    {
        time_t t_time = time(NULL);
        if (numberElements < 0 || vector.numberElements < 0)
            throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

        *this = differenceVectors(vector);

        return *this;
    }

    template<typename SomeType>
    Vector<SomeType>& Vector<SomeType>::operator *=(const SomeType& mult)
    {
        time_t t_time = time(NULL);
        if (numberElements < 0)
            throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

        Iterator<SomeType> iter(*this);
        for (; iter; iter++)
            *iter *= mult;

        return *this;
    }

    template<typename SomeType>
    Vector<SomeType>& Vector<SomeType>::operator /=(const SomeType& div)
    {
        time_t t_time = time(NULL);
        if (!div)
            throw zero_divError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

        SomeType div_new = 1 / div;
        *this *= div_new;

        return *this;
    }

    template<typename SomeType>
    Vector<SomeType>& Vector<SomeType>::operator &=(const Vector<SomeType>& vector)
    {
        if (numberElements != 3)
            return *(new Vector<SomeType>);

        double x = data_list.get()[1] * vector.data_list.get()[2] - data_list.get()[2] * vector.data_list.get()[1];
        double y = data_list.get()[2] * vector.data_list.get()[0] - data_list.get()[0] * vector.data_list.get()[2];
        double z = data_list.get()[0] * vector.data_list.get()[1] - data_list.get()[1] * vector.data_list.get()[0];

        *this = Vector<SomeType>(3, x, y, z);
        return *this;
    }

    template<typename SomeType>
    Vector<SomeType> Vector<SomeType>::operator &(const Vector<SomeType>& vector) const
    {
        if (numberElements != 3)
            return Vector<SomeType>();

        double x = data_list.get()[1] * vector.data_list.get()[2] - data_list.get()[2] * vector.data_list.get()[1];
        double y = data_list.get()[2] * vector.data_list.get()[0] - data_list.get()[0] * vector.data_list.get()[2];
        double z = data_list.get()[0] * vector.data_list.get()[1] - data_list.get()[1] * vector.data_list.get()[0];

        Vector<SomeType> new_vector(3, x, y, z);
        return new_vector;
    }

    template<typename SomeType>
    Vector<SomeType>& Vector<SomeType>::operator =(const Vector<SomeType>& vector)
    {
        numberElements = vector.numberElements;
        newVector(numberElements);

        Iterator<SomeType> iter_new(*this);
        Iterator<SomeType> iter(vector);
        for (; iter_new; iter_new++, iter++)
            *iter_new = *iter;

        return *this;
    }

    template<typename SomeType>
    Vector<SomeType>& Vector<SomeType>::operator =(std::initializer_list<SomeType> args)
    {
        numberElements = int(args.size());
        newVector(numberElements);

        Iterator<SomeType> iter(*this);
        for (auto &element : args)
        {
            *iter = element;
            iter++;
        }

        return *this;
    }

    template<typename SomeType>
    Vector<SomeType>& Vector<SomeType>::operator =(Vector<SomeType> &&vector)
    {
        numberElements = vector.numberElements;
        newVector(numberElements);
        data_list = vector.data_list;
        vector.data_list.reset();

        return *this;
    }

    template<typename SomeType>
    SomeType& Vector<SomeType>::operator [](int index)
    {
        return getElementVector(index);
    }

    template<typename SomeType>
    const SomeType& Vector<SomeType>::operator [](int index) const
    {
        return getElementVector(index);
    }

    template<typename SomeType>
    Vector<SomeType>::~Vector<SomeType>()
    {
        if (data_list)
            data_list.reset();
    }

    template<typename SomeType>
    void Vector<SomeType>::newVector(int number)
    {
        data_list.reset();
        std::shared_ptr<SomeType> sp_temp(new SomeType[number], std::default_delete<SomeType[]>());
        data_list = sp_temp;
    }

    template<typename SomeType>
    SomeType Vector<SomeType>::sumAllElements()
    {
        time_t t_time = time(NULL);
        if (numberElements <= 0)
            throw emptyError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

        Iterator<SomeType> iter(*this);
        SomeType sum = 0;
        for (; iter; iter++)
            sum += *iter;

        return sum;
    }

    template<typename SomeType>
    double Vector<SomeType>::angleBetweenVectors(const Vector<SomeType> &vector) const
    {
        time_t t_time = time(NULL);
        if (!this->len() || !vector.len())
            throw zero_divError(__FILE__, typeid(*this).name(), __LINE__, ctime(&t_time));

        double angle = (*this * vector)/(this->len() * vector.len());
        return acos(angle) * 180 / M_PI;
    }

    template<typename SomeType>
    bool Vector<SomeType>::isSingle() const
    {
        if (abs(this->len() - 1) < EPS)
            return true;
        else
            return false;
    }

    template<typename SomeType>
    bool Vector<SomeType>::isZero() const
    {
        if (this->len() == 0)
            return true;
        else
            return false;
    }

    template<typename SomeType>
    bool Vector<SomeType>::setElementVector(int index, const SomeType& number)
    {
        if (index < 0 || index >= numberElements)
            return false;

        getElementVector(index) = number;

        return true;
    }

    template<typename SomeType>
    Vector<SomeType> Vector<SomeType>::getSingleVector() const
    {
        Vector<SomeType> new_vector(*this);
        SomeType len = this->len();

        Iterator<SomeType> iter(new_vector);
        for (; iter; iter++)
            *iter /= len;

        return new_vector;
    }

    /*
    template<typename SomeType>
    int Vector<SomeType>::size() const
    {
        return numberElements;
    }
    */

    template<typename SomeType>
    bool Vector<SomeType>::isCollinearity(const Vector<SomeType>& vector) const
    {
        if (this->angleBetweenVectors(vector) < EPS)
            return true;
        else
            return false;
    }

    template<typename SomeType>
    bool Vector<SomeType>::isOrthogonality(const Vector<SomeType>& vector) const
    {
        if (abs(this->angleBetweenVectors(vector) - 90) < EPS)
            return true;
        else
            return false;
    }

    template <typename SomeType>
    Vector<SomeType> &Vector<SomeType>::sumVectors(const Vector<SomeType>& vec2) const
    {
        int max_len = max(numberElements, numberElements);
        Vector<SomeType> new_vector(max_len);
        Iterator<SomeType> iter_result(new_vector);
        Iterator<SomeType> iter_vec1(*this);
        Iterator<SomeType> iter_vec2(vec2);

        for (int i = 0; iter_result; i++, iter_result++, iter_vec1++, iter_vec2++)
        {
            if (i >= numberElements)
                *iter_result = *iter_vec2;
            else if (i >= vec2.numberElements)
                *iter_result = *iter_vec1;
            else
                *iter_result = *iter_vec1 + *iter_vec2;
        }

        return new_vector;
    }

    template <typename SomeType>
    Vector<SomeType> &Vector<SomeType>::differenceVectors(const Vector<SomeType>& vec2) const
    {
        int max_len = max(numberElements, numberElements);
        Vector<SomeType> new_vector(max_len);
        Iterator<SomeType> iter_result(new_vector);
        Iterator<SomeType> iter_vec1(*this);
        Iterator<SomeType> iter_vec2(vec2);
        for (int i = 0; iter_result; i++, iter_result++, iter_vec1++, iter_vec2++)
        {
            if (i >= numberElements)
                *iter_result = -*iter_vec2;
            else if (i >= vec2.numberElements)
                *iter_result = *iter_vec1;
            else
                *iter_result = *iter_vec1 - *iter_vec2;
        }

        return new_vector;
    }


    template <typename SomeType>
    Vector<SomeType> &Vector<SomeType>::multVectors(const Vector<SomeType>& vec2) const
    {
        int max_len = max(numberElements, numberElements);
        Vector<SomeType> new_vector(max_len);
        Iterator<SomeType> iter_result(new_vector);
        Iterator<SomeType> iter_vec1(*this);
        Iterator<SomeType> iter_vec2(vec2);

        for (int i = 0; iter_result; i++, iter_result++, iter_vec1++, iter_vec2++)
        {
            if (i >= numberElements || i >= vec2.numberElements)
                *iter_result = 0;
            else
                *iter_result = *iter_vec1 * *iter_vec2;
        }

        return new_vector;
    }
}

#endif //VECTOR_H
