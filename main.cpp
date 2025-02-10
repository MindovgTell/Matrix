#include "Matrix.hpp"
#include <complex>

using namespace std::complex_literals;


int main(){
    int S = 9;
    int s = std::sqrt(S);
    // std::complex<double> m_r(1.,3.);
    Matrix<std::complex<double> > M(S,S); // Matrix S*S elements
    Matrix<std::complex<double> > d(S,S);
    Matrix<std::complex<double> > p(S,1);
    Matrix<std::complex<double> > di(S,1);


    for(int i = 0; i < S-1; i += s){
        Matrix<std::complex<double> > D(s);
        Matrix<std::complex<double> > vec(s,1);
        Matrix<std::complex<double> > vec2(s-1,1);
        for(int j = i; j < i + s; ++j){
            vec[j-i][0] = d[j][0];
        }
        for(int j = i; j < i + s-1; ++j){
            vec2[j-i][0] = 4.+1i;
        }
        D.set_diag(-1,vec2);
        D.set_diag(1,vec2);
        D.set_diag(0,vec);
        M.set_submatrix(i, i, i+s-1, i+s-1,D);
    }
    for (int i = s; i < S; i+=s){ // last index= S-s
        Matrix<std::complex<double> > ND(s);
        Matrix<std::complex<double> > vec(s,1);
        vec.fill(2. + 1i);
        ND.set_diag(0,vec); // fill diagonal with r value
        M.set_submatrix(i-s, i, i-1, i+s-1, ND);
        M.set_submatrix(i, i-s, i+s-1, i-1, ND);
    } 
    // p.fill(3.+1i);
    // di.fill(1.);
    // d.fill(0.0);
    // d.set_diag(0,di);
    // d.set_diag(-2,di);
    // d.set_diag(1,p);
    // d.set_column(3,p);

    // //std::complex<double> r = d.det();
    Matrix<std::complex<double> > a = M.inverse();

    std::cout << M << '\n';
    std::cout << a << '\n';
    // std::cout << d.right_multipl(a) << '\n';

    
    return 0;
}