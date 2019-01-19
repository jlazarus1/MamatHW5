//
// Created by Or David on 19/01/2019.
//

#ifndef MAMATHW5_SQ_MAT_IMPL_H
#define MAMATHW5_SQ_MAT_IMPL_H

#include "sq_mat.h"
#include "mat.h"
#include "vec.h"

template <class T>
T rec_det(SqMat<T> m){
    if ( m.width()==1) return m[0][0];
    if ( m.width()==2){
        T det = (m[0][0]*m[1][1])+(m[1][0]*m[0][1]);
        return det;
    }
    T det = rec_det(create_small_mat(m,0));
    for( int i=1 ; i<m.height() ; i++){
        det = det + rec_det(create_small_mat(m,i));
    }
}


template <class T>
SqMat create_small_mat(SqMat<T> m, int i){
    Vec() det_rowV;
    Vec() det_colV;
    if(i!=0){
        det_rowV.push_back(0);
    }
    for (int k=1 ; k<m.size() ; k++){
        det_colV.push_back(k);
        if (k==i) continue;
        det_rowV.push_back(k);
    }
    Mat(m.get_cols(det_colV)) Mtmp;
    SqMat(Mtmp.get_rows(det_rowV)) Msml;
    return Msml;
}


template <class T>
SqMat::SqMat(Mat<T> m){
    if(m.height() != m.width()){
        ExceptionWrongDimensions exp;
        throw exp;
    }
    Mat(m);
}


template <class T>
unsigned int SqMat::size() const{
    return this->width();
}


template <class T>
T SqMat::determinant() const{
    T det = rec_det(*this);
}

#endif //MAMATHW5_SQ_MAT_IMPL_H
