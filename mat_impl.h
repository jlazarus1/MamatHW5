//
// Created by Or David on 18/01/2019.
//

#ifndef MAT_IMPL_H
#define MAT_IMPL_H

#include "mat.h"


// Side functions

// two vectors multiplication
template <class T>
T VecMul (Vec<T> vec1 , Vec<T> vec2){
    if (vec1.size() != vec2.size()){
        ExceptionWrongDimensions exp;
        throw exp;
    }

    T newV;
    for( int i=0 ; i<vec1.size() ; i++){

    }
}

// Implementation for class Mat

Mat::Mat(unsigned int w) : w_(w), Vec() {}

template <class T>
Mat::Mat(Vec<T> vec_1d)
: w_(vec_1d.size()) , Vec<Vec<T>>(vec_1d){}

template <class T>
Mat::Mat(Vec<Vec<T>> vec_2d)
: w_(vec_2d[0].size()) , {
    Vec<Vec<T>>(vec_2d[0]);
    for (int i=1 ; i<vec_2d.size() ; i++){
        this[i].push_back(vec_2d[i]);
    }
}

unsigned int Mat::width() const {
    return w_;
}

unsigned int Mat::height() const {
    return(this->size();
}

Mat Mat::operator+(const Mat& rhs) const {
    if(w_ != rhs.width() || this->height() != rhs.height()) { //checking the matrixes dimensions fits
        ExceptionWrongDimensions exp;
        throw exp;
    }

    Mat(w_) newMat;
    for( int i = 0 ; i < w_ ; i++){
        newMat[i].pushback(this[i]+rhs[i]);
    }
    return *this
}


template <class T>
Mat Mat::operator*(const T& rhs) const{
    if (w_<1){
        ExceptionEmptyOperand exp;
        throw exp;
    }

    Mat(w_) newMat;
    for (int i=0 ; i<w_ ; i++){
        newMat[i].pushback(this[i]*rhs);
    }
    return newMat;
}


template <class T>
Mat Mat::operator*(const Mat<T> &rhs) const {
    if (w_ != rhs.height()){
        ExceptionWrongDimensions exp;
        throw exp;
    }

    Mat(w_) newMat; // TODO need to finish
    for(int i=0 ; )
}


template <class T>
Mat Mat::operator,(const Mat<T> &rhs) const {
    if (w_ != rhs.width()){
        ExceptionWrongDimensions exp;
        throw exp;
    }

    Mat(this) newM;
    for (int i=0 ; i<rhs.width() ; i++){
        newM.push_back(rhs[i]);
    }
    return newM;
}


Mat Mat::get_rows(const Vec<unsigned int>& ind) const{
    int h = ind.size();
    if (h < 1){
        ExceptionWrongDimensions exp;
        throw exp;
    }
    Mat(h) newM;
    for (int i=0 ; i<h ; i++){
        if (ind[i] < 0 || ind[i] > this->height()){
            ExceptionWrongDimensions exp;
            throw exp;
        }
        newM.push_back(this[ind[i]]);
    }
}


Mat Mat::get_cols(const Vec<unsigned int>& ind) const{
    int h = ind.size();
    if (h < 1){
        ExceptionWrongDimensions exp;
        throw exp;
    }
    Mat(h) newM;
    for (int i=0 ; i<h ; i++){
        if (ind[i] < 0 || ind[i] > this->height()){
            ExceptionWrongDimensions exp;
            throw exp;
        }
        newM.push_back(this->transpose()[ind[i]]);
    }
}


#endif //MAT_IMPL_H
