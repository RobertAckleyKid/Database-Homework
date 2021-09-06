#include <iostream>
#include "p0_starter.h"

using namespace scudb;

int main()
{
	//01 fill from vector
	std::cout <<"TEST01 : fill from vector" << std::endl;
	RowMatrix<int> matrix_1(4,3);
    std::vector<int> vector1 = {1,2,3,4,5,6,7,8,9,10,11,12};
    matrix_1.FillFrom(vector1);
    std::cout << "    Matrix_1" << std::endl;
    RowMatrixOperations<int>::show(&matrix_1);
    
	RowMatrix<int> matrix_2(4,3);
    std::vector<int> vector2 = {12,11,10,9,8,7,6,5,4,3,2,1};
    matrix_2.FillFrom(vector2);
    std::cout << "    Matrix_2" << std::endl;
    RowMatrixOperations<int>::show(&matrix_2);
    
    RowMatrix<int> matrix_3(3,3);
    std::vector<int> vector3 = {1,0,0,0,1,0,0,0,1};
    matrix_3.FillFrom(vector3);
    std::cout << "    Matrix_3" << std::endl;
    RowMatrixOperations<int>::show(&matrix_3);
    
	//02 add
	std::cout <<"TEST02 : add" << std::endl;
	std::unique_ptr<RowMatrix<int>> matrix_sum12 = RowMatrixOperations<int>::Add(&matrix_1,&matrix_2);
	std::cout << "	Matrix_1 + Matrix_2 =" << std::endl;
    RowMatrixOperations<int>::show(matrix_sum12.get());
    
	//03 product
	std::cout <<"TEST03 : Multiply" << std::endl;
    std::unique_ptr<RowMatrix<int>> matrix_product13 = RowMatrixOperations<int>::Multiply(&matrix_1,&matrix_3);
	std::cout << "	Matrix_1 * Matrix_3 =" << std::endl;
    RowMatrixOperations<int>::show(matrix_product13.get());
    
    //04 sum 2.0
	std::cout <<"TEST04 : sum 2.0" << std::endl;
    std::unique_ptr<RowMatrix<int>> matrix_sumPlus = RowMatrixOperations<int>::GEMM(&matrix_1,&matrix_3,&matrix_2);
	std::cout << "	Matrix_1 * Matrix_3 + Matrix_2=" << std::endl;
    RowMatrixOperations<int>::show(matrix_sumPlus.get());
    
    return 0;
	
} 
