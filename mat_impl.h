//
// Created by Or David on 18/01/2019.
//

#ifndef MAT_IMPL_H
#define MAT_IMPL_H

#include "mat.h"


// Side functions

// two vectors multiplication
template <class T>
// calculate vector's multiple
T VecMul (Vec<T> vec1 , Vec<T> vec2){
    if (vec1.size() != vec2.size()){
        ExceptionWrongDimensions exp;
        throw exp;
    }

    T elem = vec1[0]*vec2[0];
    for( int i=1 ; i<vec1.size() ; i++){
        elem = elem+(vec1[i]*vec2[i]);
    }
    return elem;
}

// Implementation for class Mat

template <class T>
// create empty matrix
Mat<T>::Mat(unsigned int w) : w_(w), Vec<T>() {
    if (w_<1){
        ExceptionEmptyOperand exp;
        throw exp;
    }
}

template <class T>
// create matrix with only one row
Mat<T>::Mat(Vec<T> vec_1d)
: w_(vec_1d.size()) , Vec<Vec<T>>(vec_1d){
    if (w_<1){
        ExceptionEmptyOperand exp;
        throw exp;
    }
}

template <class T>
// create new matrix from a matrix
Mat<T>::Mat(Vec<Vec<T>> vec_2d)
: w_(vec_2d[0].size())  {
    if (w_<1){
        ExceptionEmptyOperand exp;
        throw exp;
    }
    for (int i=1 ; i<vec_2d.size() ; i++){
        if (w_ != vec_2d[i]){
            ExceptionWrongDimensions exp;
            throw exp;
        }
        this[i].push_back(vec_2d[i]);
    }
}

template <class T>
// returns the matrix width
unsigned int Mat<T>::width() const {
    return w_;
}

template <class T>
// returns the matrix height
unsigned int Mat<T>::height() const {
    return(this->size());
}


template <class T>
// sum two matrices
Mat<T> Mat<T>::operator+(const Mat<T>& rhs) const {
    if(w_ != rhs.width() || this->height() != rhs.height()) { //checking the matrixes dimensions fits
        ExceptionWrongDimensions exp;
        throw exp;
    }

    Mat<T> newMat (w_);
    for( int i = 0 ; i < w_ ; i++){
        newMat[i].pushback(this[i]+rhs[i]);
    }
    return *this;
}


template <class T>
// multiple every element in the matrix
Mat<T> Mat<T>::operator*(const T& rhs) const{
    Mat newMat (w_);
    for (int i=0 ; i<w_ ; i++){
        newMat[i].pushback(this[i]*rhs);
    }
    return newMat;
}


template <class T>
// doing algebraic matrix multiplication
Mat<T> Mat<T>::operator*(const Mat<T> &rhs) const {
    if (w_ != rhs.height()){
        ExceptionWrongDimensions exp;
        throw exp;
    }

    Mat<T> newMat (w_);
    Mat<T> mul_Mat(rhs.transpose());
    for(int i=0 ; i<this->height() ; i++){
        Vec<T> Vtmp ();
        for (int j=0 ; j<mul_Mat.height() ; j++){
            Vtmp.push_back(VecMul(this[i],mul_Mat[j]));
        }
        newMat.push_back(Vtmp);
        delete[] Vtmp;
    }
    return newMat;
}


template <class T>
// connect two matrices into one
Mat<T> Mat<T>::operator,(const Mat<T> &rhs) const {
    if (w_ != rhs.width()){
        ExceptionWrongDimensions exp;
        throw exp;
    }

    Mat<T> newM(*this);
    for (int i=0 ; i<rhs.width() ; i++){
        newM.push_back(rhs[i]);
    }
    return newM;
}

template <class T>
// create new matrix only from the specific rows from the inserted vector
Mat<T> Mat<T>::get_rows(const Vec<unsigned int>& ind) const{
    int h = ind.size();
    if (h < 1){
        ExceptionWrongDimensions exp;
        throw exp;
    }
    Mat<T> newM(h);
    for (int i=0 ; i<h ; i++){
        if (ind[i] < 0 || ind[i] > this->height()){
            ExceptionWrongDimensions exp;
            throw exp;
        }
        newM.push_back(this[ind[i]]);
    }
}


template <class T>
// transpose the matrix and do the same as 'get_rows'
Mat<T> Mat<T>::get_cols(const Vec<unsigned int>& ind) const{
    int h = ind.size();
    if (h < 1){
        ExceptionWrongDimensions exp;
        throw exp;
    }
    Mat<T> newM(h);
    for (int i=0 ; i<h ; i++){
        if (ind[i] < 0 || ind[i] > this->height()){
            ExceptionWrongDimensions exp;
            throw exp;
        }
        newM.push_back(this->transpose()[ind[i]]);
    }
}

template <class T>
// the function creates vector from each coloumn and insert the vector as a row to new matrix
Mat<T> Mat<T>::transpose() const{
    int w_new = this->height();
    Mat<T> Mnew(w_new);

    for (int i=0 ; i<w_ ; i++){
        Vec<T> Vtmp();
        for (int j=0 ; j<this->height() ; j++){
            Vtmp.push_back((this[j])[i]);
        }
        Mnew.push_back(Vtmp);
        delete[] Vtmp;
    }

}

#endif //MAT_IMPL_H
