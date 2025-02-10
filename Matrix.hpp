#ifndef MATRIX_HPP
#define MATRIX_HPP


#include <iostream>


template <typename Matrix> 
class mat_iterator
{   
public:
    using value_type     = typename Matrix::value_type; 
    using pointer_type   = value_type*;
    using reference_type = value_type&;
public:
    mat_iterator(pointer_type ptr) : _ptr(ptr) {}
private:
    pointer_type m_ptr;
}; 



template <typename T> 
class Matrix final
{ 
public: 
    using T = value_type;
    using iterator = mat_iterator<Matrix<T>>;
private:  
    T** m_data; 
    int m_row, m_column;

    struct Proxy_Matrix
    {
        T* row;
        int length;
        Proxy_Matrix(T* mat, int length): row(mat), length(length){}
        const T& operator[](int n) const {return row[n];}
        T& operator[](int n) {return row[n];}
    };
public:
    
    // Constructors & Destructor
    Matrix(int row, int column);
    Matrix(int elem);
    Matrix();

    Matrix(const Matrix& mat);
    Matrix(Matrix&& mat) noexcept;

    Matrix& operator=(const Matrix& mat);
    Matrix& operator=(Matrix&& mat) noexcept;
  
    ~Matrix();

    //Static methods
    static Matrix eye(int lines);
    
    // Overloading operators
    Matrix& operator++();
    Matrix operator++(int);
    Matrix& operator--();
    Matrix operator--(int);

    Matrix& operator+=(const Matrix& rmt);
    Matrix& operator-=(const Matrix& rmt);
    Matrix& operator*=(const Matrix& rmt);
    

    Proxy_Matrix operator[](int n);
    // Class methods //
    void fill(T t);
    int size(){return m_row*m_column;}

    iterator begin() {return m_data;}
     iterator end() {return ;}

    // Getters
    int get_row() const {return m_row;}
    int get_columns() const {return m_column;}
    Matrix<T> get_diag(int) const;
    Matrix<T> get_diag() const;

    // Setters 
    void set_diag(int num,Matrix<T> &vec);
    void set_column(int,Matrix<T> &vec);
    void set_row(int, Matrix<T> &vec);
    void set_column(int,T);
    void set_row(int,T);
    void set_submatrix(int,int,int,int,Matrix<T> &vec);

    
    // Others methods
    void filling_Matrix();
    Matrix& transpose() &;
    Matrix& negation() &;
    Matrix mat_vec_multipl(Matrix<T>&);
    Matrix right_multipl(Matrix<T>&);

    void dump(std::ostream& os) const;

    //Determenant
    value_type det();

    Matrix inverse();
    Matrix cofactor();
    Matrix adj();
};

#include "Matrix.inl"

#endif