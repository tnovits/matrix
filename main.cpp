#include "matrix.h"

#include <iostream>

int
main()
{
    auto matrix = Matrix<int, 0>();

    for(auto i = 0, N = 10; i < N; i++)
    {
        matrix[i][i] = matrix[N - 1 - i][i] = i;
    }

    for( auto i = 0; i < 10; ++i)
    {
        for( auto j = i%2; j < 10; j+=2)
        {
            matrix[i][j] = 0;
        }
    }

    for (auto i = 1; i < 9; ++i)
    {
        for(auto j = 1; j < 9; ++j)
        {
            std::cout << matrix[i][j] << " ";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Size = " << matrix.size() << std::endl;
    std::cout << std::endl;

    for( const auto& element : matrix )
    {
        std::cout << element << std::endl;
    }
}