#define BOOST_TEST_MODULE ip_pool_test_module

#include "matrix.h"

#include <boost/test/unit_test.hpp>

#include <iostream>
#include <string>

using namespace std::string_literals;

BOOST_AUTO_TEST_SUITE( matrix_test_suite )

BOOST_AUTO_TEST_CASE( matrix_test )
{
    Matrix<int, -1> matrix;
    BOOST_CHECK(  matrix.size() == 0);

    auto a = matrix[0][0];
    BOOST_CHECK(a == -1);
    BOOST_CHECK(matrix.size() == 0);

    matrix[100][100] = 314;
    BOOST_CHECK(matrix[100][100]== 314);
    BOOST_CHECK(matrix.size() == 1);

    matrix[100][100]= -1;
    BOOST_CHECK(matrix[100][100] == -1);
    BOOST_CHECK(matrix.size() == 0);

    matrix[200][200] = 3;

    std::stringstream sstream;
    auto backupCoutBuffer = std::cout.rdbuf();

    std::cout.rdbuf( sstream.rdbuf() );
    std::cout << matrix[200][200];
    std::cout.rdbuf( backupCoutBuffer );

    BOOST_CHECK(  sstream.str() == "3"s);
}

BOOST_AUTO_TEST_CASE( matrix3d_test )
{
    Matrix<int, -1, 3> matrix;
    BOOST_CHECK(  matrix.size() == 0);

    auto a = matrix[0][0][0];
    BOOST_CHECK(a == -1);
    BOOST_CHECK(matrix.size() == 0);

    matrix[100][100][100] = 314;
    BOOST_CHECK(matrix[100][100][100]== 314);
    BOOST_CHECK(matrix.size() == 1);

    matrix[100][100][100]= -1;
    BOOST_CHECK(matrix[100][100][100] == -1);
    BOOST_CHECK(matrix.size() == 0);

    matrix[200][200][200] = 3;

    std::stringstream sstream;
    auto backupCoutBuffer = std::cout.rdbuf();

    std::cout.rdbuf( sstream.rdbuf() );
    std::cout << matrix[200][200][200];
    std::cout.rdbuf( backupCoutBuffer );

    BOOST_CHECK(  sstream.str() == "3"s);
}

BOOST_AUTO_TEST_SUITE_END()
