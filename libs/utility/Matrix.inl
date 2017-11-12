#include "Matrix.h"

namespace utility{
  inline std::istream& operator>>( std::istream& is, Matrix & m )
  {
    for (size_t i = 0; i < 4; i++) {
      for (size_t j = 0; j < 4; j++) {
        is >> m.matrix[i][j];
      }
    }
      return is;
  }
  inline std::ostream& operator<<( std::ostream& os, const Matrix & m )
  {
      os << std::fixed << std::setprecision( 2 )
          << "{ ";
          for (size_t i = 0; i < 4; i++) {
            os << "[";
            for (size_t j = 0; j < 4; j++) {
              os << m.matrix[i][j] << " ";
            }
            os << "]\n";
          }
          os << " }";
      return os;
  }

  inline Matrix operator+(const Matrix m1, const Matrix m2){
    Matrix m;
    for (size_t i = 0; i < 4; i++) {
      for (size_t j = 0; j < 4; j++) {
        m.matrix[i][j] = m1.matrix[i][j] + m2.matrix[i][j];
      }
    }
    return m;
  }

  inline Matrix operator-(const Matrix m1, const Matrix m2){
    Matrix m;
    for (size_t i = 0; i < 4; i++) {
      for (size_t j = 0; j < 4; j++) {
        m.matrix[i][j] = m1.matrix[i][j] - m2.matrix[i][j];
      }
    }
    return m;
  }

  inline Matrix operator*(const Matrix m1, const Matrix m2){
    Matrix m = Matrix();
    for (size_t i = 0; i < 4; i++) {
      for (size_t j = 0; j < 4; j++) {
        for (size_t k = 0; k < 4; k++) {
          m.matrix[i][j] += m1.matrix[i][k] * m2.matrix[k][j];
        }
      }
    }
    return m;
  }

  inline Matrix operator*(const double d, const Matrix m1){
    Matrix m;
    for (size_t i = 0; i < 4; i++) {
      for (size_t j = 0; j < 4; j++) {
        m.matrix[i][j] = d * m1.matrix[i][j];
      }
    }
    return m;
  }

  inline Matrix operator*(const Matrix m1, const double d){
    Matrix m;
    for (size_t i = 0; i < 4; i++) {
      for (size_t j = 0; j < 4; j++) {
        m.matrix[i][j] = d * m1.matrix[i][j];
      }
    }
    return m;
  }

  inline Matrix operator/(const Matrix m1, const double d){
    Matrix m;
    for (size_t i = 0; i < 4; i++) {
      for (size_t j = 0; j < 4; j++) {
        m.matrix[i][j] = m1.matrix[i][j] / d;
      }
    }
    return m;
  }

  inline Matrix& Matrix::operator+=(const Matrix& m){
    for (size_t i = 0; i < 4; i++) {
      for (size_t j = 0; j < 4; j++) {
        matrix[i][j] += m.matrix[i][j];
      }
    }
    return *this;
  }

  inline Matrix& Matrix::operator-=(const Matrix& m){
    for (size_t i = 0; i < 4; i++) {
      for (size_t j = 0; j < 4; j++) {
        matrix[i][j] -= m.matrix[i][j];
      }
    }
    return *this;
  }

  inline Matrix& Matrix::operator*=(const double d){
    for (size_t i = 0; i < 4; i++) {
      for (size_t j = 0; j < 4; j++) {
        matrix[i][j] *= d;
      }
    }
    return *this;
  }

  inline Matrix& Matrix::operator/=(const double d){
    for (size_t i = 0; i < 4; i++) {
      for (size_t j = 0; j < 4; j++) {
        matrix[i][j] *= d;
      }
    }
    return *this;
  }


  static Matrix identity_matrix(){
    Matrix m = Matrix();
    m.matrix[0][0] = 1;
    m.matrix[1][1] = 1;
    m.matrix[2][2] = 1;
    m.matrix[3][3] = 1;
    return m;
  }

  static Matrix zero_matrix(){
    Matrix m = Matrix();
    return m;
  }

  static Matrix ones_matrix(){
    Matrix m;
    for (size_t i = 0; i < 4; i++) {
      for (size_t j = 0; j < 4; j++) {
        m.matrix[i][j] = 1;
      }
    }
    return m;
  }

  static Matrix transpose_matrix(Matrix m1){
    Matrix m;
    for (size_t i = 0; i < 4; i++) {
      for (size_t j = 0; j < 4; j++) {
        m.matrix[i][j] = m1.matrix[j][i];
      }
    }
    return m;
  }
  
  static Matrix inverse_matrix(Matrix m1);

}
