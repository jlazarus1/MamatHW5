//
// Created by Or David on 19/01/2019.
//

#ifndef MAMATHW5_SQ_MAT_IMPL_H
#define MAMATHW5_SQ_MAT_IMPL_H

#include "sq_mat.h"
#include "mat.h"
#include "vec.h"
#include <cmath>



template <class T>
SqMat::SqMat(Mat<T> m) {}{
    if(m.height() != m.width()){
        ExceptionWrongDimensions exp;
        throw exp;
    }
    Mat<T>(Vec< Vec<T> > m);
}


template <class T>
unsigned int SqMat::size() const{
    return this->width();
}


template <class T>
T SqMat::determinant() const{
    if ( size()==0) {
        ExceptionEmptyOperand exp;
        throw exp;
    }
    if ( size()==1) return m[0][0];
    if ( size()==2){
        return (m[0][0]*m[1][1])-(m[1][0]*m[0][1]);
    }
    T det(0)
    T sign;
    for( unsigned int i=0 ; i<size() ; i++){
        sign = pow((-1),(i%2));
        T base = this[0][i]*sign; // current element for minor calculate
        Vec <unsigned int> minorV = (range(0,i),range(i+1,size()-i-1)); // create vector for excluding the right column
        Mat <T> tmpM = this->get_cols(minorV);
        SqMat<T> minorM = tmpM.get_rows(range(1,tmpM.height())); // creating small matrix for the next minor
        det = det + base*minorM.determinant(); // recursive calculate
    }
}

#endif //MAMATHW5_SQ_MAT_IMPL_H
