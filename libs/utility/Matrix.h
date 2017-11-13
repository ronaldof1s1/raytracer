#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "Vector3.h"
namespace utility{

  class Matrix{
  public:
    double matrix[4][4];

    Matrix(){
      for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
          matrix[i][j] = 0;
        }
      }
    }

    Matrix(double m[4][4]){
      for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
          matrix[i][j] = m[i][j];
        }
      }
    }

    inline Matrix & operator=(const Matrix m){
      for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
          matrix[i][j] = m.matrix[i][j];
        }
      }
      return *this;
    }

    inline bool operator==(const Matrix m){
      for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {

          if(matrix[i][j] != m.matrix[i][j]){
            return false;
          }

        }
      }
      return true;
    }

    inline Matrix & operator-(void){
      for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
          matrix[i][j] *= -1;
        }
      }
      return *this;
    }



    inline Matrix& operator+=( const Matrix& );
    inline Matrix& operator-=( const Matrix& );
    inline Matrix& operator*=( const double );
    inline Matrix& operator/=( const double );


    double determinant();
    Point3 transform_point(Point3 p);
    Vector3 transform_vector(Vector3 v);
  };

}

#include "Matrix.inl"
#endif
