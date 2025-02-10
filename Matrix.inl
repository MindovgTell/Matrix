#ifndef MATRIX_INL
#define MATRIX_INL

#include "Matrix.hpp" 

//Constructors

template <typename T> Matrix<T>::Matrix(int row, int column)
{
    m_row = row;
    m_column = column;
    // Create Matrix
    m_data = new T*[m_row];
    for (int i = 0; i != m_row; ++i)
    {
        m_data[i] = new T[m_column]; 
    }
    // Fulling Matrix with 0
    for(int i = 0; i != m_row; ++i)
    {
        for(int j = 0; j != m_column; ++j)
        {
            m_data[i][j] = 0;
        }
    }
}

template <typename T> Matrix<T>::Matrix(int elem)
{
    m_row = elem;
    m_column = elem;
    // Create Matrix
    m_data = new T*[m_row];
    for (int i = 0; i != m_row; ++i)
    {
        m_data[i] = new T[m_column]; 
    }
    // Fulling Matrix with 0
    for(int i = 0; i != m_row; ++i)
    {
        for(int j = 0; j != m_column; ++j)
        {
            m_data[i][j] = static_cast<T>(0);
        }
    }
}

template <typename T> Matrix<T>::Matrix(): m_row(1),m_column(1){
    m_data = new T*[1];
    m_data[0] = new T[1];
}

// Copy coonstructor
template <typename T> Matrix<T>::Matrix(const Matrix<T>& mat)
{
    m_row = mat.m_row;
    m_column = mat.m_column;
    m_data = new T* [m_row];
    for(int i = 0; i != m_row; ++i)
    {
        m_data[i] = new T [m_column];
    }
    for(int i = 0; i != m_row; ++i)
    {
        for(int j = 0; j != m_column; ++j)
        {
            m_data[i][j] = mat.m_data[i][j];
        }
    }
}

template <typename T> Matrix<T>::Matrix(Matrix&& mat) noexcept
{
    m_data = mat.m_data;
    m_column = mat.m_column;
    m_row = mat.m_row;
    mat.m_data = nullptr;
}

template <typename T> Matrix<T> &Matrix<T>::operator=(Matrix &&mat) noexcept
{
    if(this == &mat) return *this;
    std::swap(m_data,mat.m_data);
    std::swap(m_column, mat.m_column);
    std::swap(m_row, mat.m_row);
    return *this;
}

template <typename T> Matrix<T>& Matrix<T>::operator=(const Matrix<T>& mat)
{
    if(this == &mat) return *this; 

    for (int i = 0; i != m_row; ++i)
    {
        delete [] m_data[i];
    }
    delete [] m_data;

    m_data = new T*[mat.m_row];
    m_column = mat.m_column;
    m_row = mat.m_row;

    for (int i = 0; i != m_column; ++i)
    {
        m_data[i] = new T[m_column]; 
    }

    for(int i = 0; i != m_row; ++i)
    {
        for(int j = 0; j != m_column; ++j)
        {
            m_data[i][j] = mat.m_data[i][j]; // Posible exception
        }
    }
    return *this;
}

//Destructor
template <typename T> Matrix<T>::~Matrix()
{
    // Deleting Matrix
    for (int i = 0; i != m_row; ++i)
    {
        delete [] m_data[i];
    }

    delete [] m_data;
}

////////////////
////Getters/////
template <typename T> Matrix<T> Matrix<T>::get_diag(int param) const {
    ///ADD CHECK FOR OUT OF RANGE VALUE!!!!!!!!!!
    int size = m_row;
    Matrix<T> diagonal(size - std::abs(param),1);

    if(param > 0){
        for(int i = 0; i != m_row-param; i++){
            diagonal[i][0] = this->m_data[i][i+param];
        }
    }
    else if(param < 0){
        for(int i = 0; i != m_row+param; i++){
            diagonal[i][0] = this->m_data[i-param][i];
        }
    }
    else{
        for(int i = 0; i != m_row; i++)
            diagonal[i][0] = this->m_data[i][i];
    }
    return diagonal;
}

template <typename T> Matrix<T> Matrix<T>::get_diag() const {
    int size = m_row;
    Matrix<T> diagonal(size,1);
    for(int i = 0; i != m_row; i++)
        diagonal[i][0] =  m_data[i][i];
    return diagonal;
}


/////Setters/////
///It's need the exceptions security
template <typename T> void Matrix<T>::set_diag(int num, Matrix<T> &vec){
    //Check the correc size as exception
    // if(vec.shape() != this->shape())
    //     throw ...
    int size = m_row;

    if(num > 0){
        for(int i = 0; i != m_row-num; i++){
            this->m_data[i][i+num] = vec[i][0];
        }
    }
    else if(num < 0){
        for(int i = 0; i != m_row+num; i++){
            this->m_data[i-num][i] = vec[i][0];
        }
    }
    else{
        for(int i = 0; i != m_row; i++)
            this->m_data[i][i] =  vec[i][0];
    }
}

template <typename T> void Matrix<T>::set_column(int index,Matrix<T> &vec){
    for(int i = 0; i < m_row; i++){
        this->m_data[i][index] = vec[i][0];
    }
}

template <typename T> void Matrix<T>::set_row(int index, Matrix<T> &vec){
    for(int i = 0; i < m_column; i++){
        this->m_data[index][i] = vec[i][0];
    } 
}

template <typename T> void Matrix<T>::set_column(int index,T num){
    for(int i = 0; i < m_row; i++){
        this->m_data[i][index] = num;
    }
}

template <typename T> void Matrix<T>::set_row(int index, T num){
    for(int i = 0; i < m_column; i++){
        this->m_data[index][i] = num;
    } 
}

template <typename T> void Matrix<T>::set_submatrix(int first_row, int first_col, int last_row, int last_col, Matrix<T> &submat){
    for(int i = first_row; i <= last_row; ++i){
        for(int j = first_col; j <= last_col; ++j){
            this->m_data[i][j] = submat[i-first_row][j-first_col];
        }
    }
}

//////////////// 


template <typename T> void Matrix<T>::fill(T t)
{
    for (int i = 0; i != m_row; ++i)
    {
        for(int j = 0; j != m_column; ++j)
        {
            m_data[i][j] = t;
        }
    } 
}

template<typename T> Matrix<T> Matrix<T>::eye(int lines)
{
    Matrix mat(lines, lines);

    for (int i = 0; i != lines; ++i)
    {
        mat[i][i] = 1;
    }
    
    return mat;
}


// Method for fulling matrix with elements from keyboard
template <typename T> void Matrix<T>::filling_Matrix()
{
    std::cout << "Give the matrix elements: " << '\n';
    for (int i = 0; i != m_row; ++i)
    {
        for(int j = 0; j != m_column; ++j)
        {
            std::cin >> m_data[i][j];
        }
    }
}

//Method for transpose matrix
template <typename T> Matrix<T>& Matrix<T>::transpose() &
{
    Matrix temp_mat(*this);

    if(m_column == m_row)
        for(int i = 0; i != m_row; ++i)
            for(int j = 0; j != m_column; ++j)
                m_data[i][j] = temp_mat[j][i];
    else 
    {
        for (int i = 0; i != m_row; ++i)
            delete [] m_data[i];
        delete [] m_data;

        int swp = m_column;
        m_column = m_row;
        m_row = swp;

        m_data = new T*[m_row];

        for (int i = 0; i != m_row; ++i)
        {
            m_data[i] = new T[m_column]; 
        }

        for(int i = 0; i != m_row; ++i)
        {
            for(int j = 0; j != m_column; ++j)
            {
                m_data[i][j] = temp_mat[j][i];
            }
        }
    }

    return *this;
}

//Method for negotiate matrix

template<typename T> Matrix<T>& Matrix<T>::negation() &
{
    for (int i = 0; i != m_row; ++i)
        for (int j = 0; j != m_column; ++j)
            m_data[i][j] *= -1;
    return *this; 
}

template <typename T> Matrix<T> Matrix<T>::mat_vec_multipl(Matrix<T>& vec)
{
    ///ADD THE EXCEPTIONS SUPPORT
    if(vec.get_row() != this->m_column){
        std::cout << "Vector and matrix have different spatial" << '\n';
        return 0;
    }
    int row = vec.get_row();
    int column = this->m_column;

    Matrix<T> result(row,1);
    for(int i = 0; i != row; ++i){
        T sum_row = 0;
        for(int j = 0; j != column; ++j){
            sum_row += m_data[i][j] * vec[j][0];
        }
        result[i][0] = sum_row;
    }
    return result;
}
//Multiplication of *this matrix on the matrix which stand on the right hand side
template <typename T> Matrix<T> Matrix<T>::right_multipl(Matrix<T> &mat){
    if(this->m_column != mat.get_row()){
        std::cout << "ERROR: UNCORRECT SIZE OF MATRIX" << '\n';
        return 0;
    }
    Matrix<T> solution(this->m_row,this->m_column);
    for(int i = 0; i != this->m_row; ++i){
        for(int j = 0; j != this->m_column; ++j){
            for(int k = 0; k != this->m_column; ++k){
                solution[i][j] += mat[i][k] * this->m_data[k][j];
            }
        }
    }
    return solution;
}

// Chain operators +=, -=, *=, /=

template<typename T> Matrix<T>& Matrix<T>::operator+=(const Matrix & rmt)
{   
    for(int i = 0; i != m_row; ++i)
    {
        for (int j = 0; j != m_column; ++j)
        {
            m_data[i][j] += rmt.m_data[i][j];
        }
    }
    return *this;
}

template<typename T> Matrix<T>& Matrix<T>::operator-=(const Matrix & rmt)
{   
    for(int i = 0; i != m_row; ++i)
    {
        for (int j = 0; j != m_column; ++j)
        {
            m_data[i][j] -= rmt.m_data[i][j];
        }
    }
    return *this;
}

template <typename T> Matrix<T>& Matrix<T>::operator*=(const Matrix & rmt)
{

    //chek size£!!

    Matrix<T> temp(m_row);

    return *this;
}

// Overloading operators ++ & --

template <typename T> Matrix<T>& Matrix<T>::operator++()
{
    for (int i = 0; i != m_row; ++i)
    {
        for (int j = 0; j != m_column; ++j)
        {
            m_data[i][j] += 1;
        }
    }
    return *this;
}

template <typename T> Matrix<T> Matrix<T>::operator++(int)
{
    Matrix mat(*this);
    ++(*this);
    return mat;
}

template <typename T> Matrix<T> &Matrix<T>::operator--()
{
    for (int i = 0; i != m_row; ++i)
    {
        for (int j = 0; j != m_column; ++j)
        {
            m_data[i][j] -= 1;
        }
    }
    return *this;
}

template <typename T> Matrix<T> Matrix<T>::operator--(int)
{
    Matrix mat(*this);
    --(*this);
    return mat;
}

//Overloading binary operators +, -, *, /, ...


// Overloading stream op

template <typename T> void Matrix<T>::dump(std::ostream& os) const
{
    for(int i = 0; i != m_row; ++i)
    {
        os << "[ ";
        for(int j = 0; j != m_column; ++j)
        {
            os << m_data[i][j] << ' ';
        }
        os << ']' << '\n';
    }
    os <<'\n';
}

template <typename T> std::ostream& operator<<(std::ostream& out, const Matrix<T>& mat)
{
    mat.dump(out);
    return out;
}

// Overloading operator[]

template <typename T> typename Matrix<T>::Proxy_Matrix Matrix<T>::operator[](int n)
{
    return Proxy_Matrix(m_data[n],m_column);
}

//YOU HAVE TO WRITE OVERLOADING OF <=> OPERATOR FOR USING +,-,... WITH ANY MATRIX


//Function for calculate matrix determinant
template <typename T> T Matrix<T>::det()
{
    //ADD THE ECXCEPTION SUPPORT
    T det = 0;
    T sign = 1;
    if(this->m_row != this->m_column){
        std::cout << "ERROR: NON QUADRATIC MATRIX" << '\n';
        return 0;
    }
    else if(this->m_row == 0)
        return 0;
    else if(this->m_row == 1)
        return this->m_data[0][0];
    else if(this->m_row == 2)
        return ((this->m_data[0][0] * this->m_data[1][1]) - (this->m_data[0][1] * this->m_data[1][0]));
    else{
        for(int i = 0; i != this->m_row; ++i){
            if(this->m_data[0][i] == static_cast<T>(0)){
                det += 0;
            }
            else{
                Matrix<T> cofactor(this->m_row-1,this->m_column-1);
                int sub_i = 0, sub_j = 0;
                for (int j = 1; j < this->m_row; j++) {
                    for (int k = 0; k < this->m_row; k++) {
                        if (k == i) {
                            continue;
                        }
                        cofactor[sub_i][sub_j] = this->m_data[j][k];
                        sub_j++;
                    }
                    sub_i++;
                    sub_j = 0;
                }
                det += sign * this->m_data[0][i] * cofactor.det();
            }
            sign = -sign;
        }
    }
    return det;
}

template <typename T> Matrix<T> Matrix<T>::cofactor(){
    Matrix<T> solution(this->m_row, this->m_column);

    Matrix<T> subMat(this->m_row-1,this->m_column-1);

    for(int i = 0; i != this->m_row; ++i) {
        for(int j = 0; j != this->m_column; ++j) {

            int p = 0;
            for(int x = 0; x != this->m_row; ++x) {
                if(x == i) {
                    continue;
                }
                int q = 0;

                for(int y = 0; y < this->m_row; ++y) {
                    if(y == j) {
                        continue;
                    }

                    subMat[p][q] = this->m_data[x][y];
                    q++;
                }
                p++;
            }
            solution[i][j] = std::pow(-1, i + j) * subMat.det();
        }
    }
    return solution;
}

template <typename T> Matrix<T> Matrix<T>::adj(){
    Matrix<T> solution(this->m_row, this->m_column);
    solution = solution.cofactor();
    return solution.transpose();
}

template <typename T> Matrix<T> Matrix<T>::inverse(){
    T determinant = this->det();
    //ADD EXCEPTION SUPPORT
    if(determinant == static_cast<T>(0)){
        std::cout << "ERROR: DET EQUAL ZERO" << '\n';
        return 0;
    }
    T d = 1./determinant;
    Matrix<T> solution(this->m_row,this->m_column);

    for(int i = 0; i != this->m_row; ++i) {
        for(int j = 0; j != this->m_column; ++j) {
            solution[i][j] = this->m_data[i][j]; 
        }
    }
    solution = solution.cofactor();
    solution = solution.transpose();

    for(int i = 0; i != this->m_row; ++i) {
        for(int j = 0; j != this->m_column; ++j) {
            solution[i][j] = solution[i][j]*d;
        }
    }
    return solution;
}



#endif