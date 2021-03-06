//
// Created by Or David on 19/01/2019.
//

#ifndef MAMATHW5_SQ_MAT_IMPL_H
#define MAMATHW5_SQ_MAT_IMPL_H

#include <cmath>


//constructor of the sqmat.

template <class T>
SqMat<T>::SqMat(Mat<T> m) : Mat<T>(m){
    if(m.height() != m.width()){
        ExceptionWrongDimensions exp;
        throw exp;
    }
}
//Function name:size().
//returns size of sqmat.
template <class T>
unsigned int SqMat<T>::size() const{
    return this->width();
}


//Function name: determinant. 
//returns the determinant of the matrix by using recusive calculations. 
template <class T>
T SqMat<T>::determinant() const{
    unsigned int size = this->size();
    if ( size==0) {
        ExceptionEmptyOperand exp;
        throw exp;
    }
    if ( size==1) return (*this)[0][0];
    if ( size==2){
        return (((*this)[0][0] * (*this)[1][1]))-((*this)[1][0] * (*this)[0][1]);
    }
    T det(0);
    unsigned int sec_row=1;
    for( unsigned int i=0 ; i<size ; i++){
        T sign (pow((-1),(i%2)));
        T base = (*this)[0][i] * sign; // current element for minor calculate
        Vec <unsigned int> minorV = ((range<unsigned int>(0,i)) , (range<unsigned int>(i+1,size-i-1))); // create vector for excluding the right column
        Vec <unsigned int> decreas_row = range<unsigned int>(sec_row,this->size()-1);
        Mat <T> tmpM (this->get_rows(decreas_row)); // creating small matrix for the next minor
        Mat<T> t (tmpM.get_cols(minorV));
        SqMat<T> minorM(t);
        det = det + base*minorM.determinant(); // recursive calculate
    }
    return det;
}

#endif //MAMATHW5_SQ_MAT_IMPL_H
