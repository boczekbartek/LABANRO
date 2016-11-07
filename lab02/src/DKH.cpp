// #include <ros/ros.h>
// #include <lab02/DKH.h>
#include <boost/numeric/ublas/matrix.hpp>
#include <vector>

using namespace boost::numeric::ublas;
matrix<double> matrix_multiply(std::vector< matrix<double> > skladowe){ //skladowe to macierze które wchodzą do mnożenia
	 matrix<double> result;

		result = prod(skladowe[0],skladowe[1]);			
	
	return result;
}

int main(){
	 std::vector< matrix<double> > v;
	 matrix<double> A(2,2);
        A(0,0) = 0; A(0,1) = 1;
        A(1,0) = 2; A(1,1) = 3;

     matrix<double> B(2,2);
     	A(0,0) = 5; A(0,1) = 2;
        A(1,0) = 2; A(1,1) = 1;
     
     v.push_back(A);
     v.push_back(B);

     matrix<double> y = matrix_multiply(v);
}