#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <exception>

#include "managError.h"
#include "vector.hpp"

int main()
{
    using namespace mylib;

    try
    {
        std::cout << "Tests constructors\n\n";

        Vector<double> v1;
        std::cout << "Default:\n";
        std::cout << v1 << "\n";

        std::cout << "With parameters: \n";
        Vector<double> v2(2, 3., 4.);
        Vector<double> v3(3, 3.0, 4.0, 0.0);
        std::cout << v2 << "\n" << v3 << "\n";

        std::cout << "From array: \n";
        double arr[5] = {5, 1, 7, 4, 0};
        Vector<double> v4(5, arr);
        std::cout << v4 << "\n";

        std::cout << "From existing vector:\n";
        Vector<double> v5(v3);
        std::cout << v5 << "\n";


        std::cout << "\nTest methods\n\n";

        std::cout << "Length of vector (3, 4, 0): " << v3.len() << "\n";
        std::cout << "Size of vector (3, 4, 0): " << v3.getSize() << "\n";
        std::cout << "Get second element {5, 1, 7, 4, 0}: "<< v4.getElementVector(1) <<"\n";

        std::cout << "Multiply by 10: " << (v4 *= 10) << "\n";
        std::cout << "Divide by 10: " << (v4 /= 10) << "\n";
        std::cout << "Subtract two vectors {5, 1, 7, 4, 0} minus {3, 4, 0}: " << (v4 -= v3) << "\n";
        std::cout << "Change to opposite direction (unary minus) {3, 4, 0}: " << (-v3) << "\n\n";

        Vector<double> v12{1., 2., 3., 4., 5.};
        std::cout << "Init vector {1., 2., 3., 4., 5.}: " << v12 << "\n";
        v12[2] = 10.;
        std::cout << "Change third element using []: " << v12 << "\n";
        v12.setElementVector(3, 11.);
        std::cout << "Change fourth element using set_elem_Vector method: " << v12 << "\n";
        v12 = v12.getSingleVector();
        std::cout << "Get vector with lenght of one: " << v12 << "\n\n";

        Vector<double> v6(3, 3.0, 4.0, 0.0);
        std::cout << "Vector multiplication {3,4,0} and {3,4,0}: " << (v3 &= v6) << "\n";
        Vector<int> v7(2, 10, 0);
        Vector<int> v8(2, 0, 10);
        std::cout << "Find angle between {10, 0} and {0, 10}: " << v7.angleBetweenVectors(v8) << "\n";
        Vector<double> v9(2, 5., 5.);
        Vector<double> v10(2, 10., 0.0);
        std::cout << "Fing angle between {5, 5} and {10, 0}: " << v9.angleBetweenVectors(v10) << "\n";
        Vector<double> v20(2, 20., 20.0);
        std::cout << "Check collinearity of {5, 5} and {20, 20}: " << v9.isCollinearity(v20) << "\n";
        std::cout << "Scalar multiplication {5, 5} and {10, 0}: " << v9 * v10 << "\n\n";

        Vector<int> v11(4, 1, 0, 0, 0);
        std::cout << "Is vector of length one {4, 1, 0, 0, 0}? " << v11.isSingle() << "\n";
        std::cout << "Are two vectors equal? {3, 4, 0} and {3, 4, 0}: " << (v3 == v6) << "\n";
        std::cout << "Are two vectors not equal? {3, 4, 0} and {3, 4, 0}: " << (v3 != v6) << "\n";
    }
    catch (baseError& err)
    {
        std::cout << err.what() << std::endl;
    }
    return 0;
}
