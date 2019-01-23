//
// Created by Or David on 18/01/2019.
//

#ifndef MAT_IMPL_H
#define MAT_IMPL_H




// Side functions

// two vectors multiplication
template <class T>
// calculate vector's multiple
T VecMul (Vec<T> vec1 , Vec<T> vec2){
    typename std::list<T>::const_iterator vec1_it=vec1.begin();
    typename std::list<T>::const_iterator vec2_it=vec2.begin();
    if (vec1.size() != vec2.size()) {
        ExceptionWrongDimensions exp;
        throw exp;
    }


    T elem((*vec1_it)*(*vec2_it));
    vec2_it++;
    vec1_it++;
    while(vec1_it!=vec1.end() ){
        elem = elem+(*vec1_it*(*vec2_it));
        vec2_it++;
        vec1_it++;
    }
    return elem;
}

// Implementation for class Mat

template <class T>
// create empty matrix
Mat<T>::Mat(unsigned int w) : w_(w) {
    if (w_<1){
        ExceptionEmptyOperand exp;
        throw exp;
    }
}

template <class T>
// create matrix with only one row
Mat<T>::Mat(Vec<T> vec_1d)
:  Vec<Vec<T>>(vec_1d),w_(vec_1d.size()) {
    if (w_<1){
        ExceptionEmptyOperand exp;
        throw exp;
    }
}

template <class T>
// create new matrix from a matrix
Mat<T>::Mat(Vec<Vec<T>> vec_2d) {
    typename std::list<T>::const_iterator i = vec_2d.begin();
    w_(i->size());
    if (w_<1){
        ExceptionEmptyOperand exp;
        throw exp;
    }
    while (i != vec_2d.end()) {
        if (w_ != vec_2d[i]){
            ExceptionWrongDimensions exp;
            throw exp;
        }
        this[i].push_back(*i);
        i++;
    }
}

template<class T>
// returns the matrix width
unsigned int Mat<T>::width() const {
    return w_;
}
template<class T>
// returns the matrix height
unsigned int Mat<T>::height() const {
    if (w_==0) return 0;
    return(this->size());
}


template <class T>
// sum two matrices
Mat<T> Mat<T>::operator+(const Mat& rhs) const {
    if(w_ != rhs.width() || this->height() != rhs.height()) { //checking the matrixes dimensions fits
        ExceptionWrongDimensions exp;
        throw exp;
    }
    Mat* newMat;
    newMat = new Mat;
    newMat->w_=this->w_;
    for( int i = 0 ; i < w_ ; i++){
        newMat[i].pushback(this[i]+rhs[i]);
    }
    return *newMat;
}


template <class T>
// multiple every element in the matrix
Mat<T> Mat<T>::operator*(const T& rhs) const{
    typename std::list<Vec<T>>::const_iterator this_it;
    Mat<T> newMat(w_);
    for (this_it=this->begin();this_it!=this->end();this_it++){
        newMat.push_back(rhs*(*this_it));
    }
    return newMat;
}


template <class T>
// doing algebraic matrix multiplication
Mat<T> Mat<T>::operator*(const Mat<T> &rhs) const {
    typename std::list<Vec<T>>::const_iterator this_it;
    typename std::list<Vec<T>>::const_iterator newMat_it;
    if (w_ != rhs.height()){
        ExceptionWrongDimensions exp;
        throw exp;
    }
    Mat<T> newMat(rhs.transpose());

    Mat<T> outMat(rhs.width());
    for(this_it=this->begin() ; this_it!=this->end() ; this_it++){
        Vec<T> Vtmp;
        for (newMat_it=newMat.begin();newMat_it!=newMat.end();newMat_it++){
            Vtmp.push_back(VecMul(*this_it,*newMat_it));
        }
        outMat.push_back(Vtmp);
    }
    return outMat;
}


template <class T>
// connect two matrices into one
Mat<T> Mat<T>::operator,(const Mat<T> &rhs) const {
    typename std::list<Vec<T>>::const_iterator this_it;
    typename std::list<Vec<T>>::const_iterator rhs_it;
    if (w_ != rhs.width()){
        ExceptionWrongDimensions exp;
        throw exp;
    }

    Mat<T> newM(w_);
    for (this_it=this->begin();this_it!=this->end();this_it++)
    {
        newM.push_back(*this_it);
    }
    for (rhs_it=rhs.begin();rhs_it!=rhs.end();rhs_it++){
        newM.push_back(*rhs_it);
    }
    return newM;
}

template <class T>
// create new matrix only from the specific rows from the inserted vector
Mat<T> Mat<T>::get_rows(const Vec<unsigned int>& ind) const{
    unsigned int h = ind.size();
    if (h < 1){
        ExceptionWrongDimensions exp;
        throw exp;
    }
    Mat<T> newM(this->width());
    for (unsigned int i=0 ; i<h ; i++){
        if (ind[i] < 0 || ind[i] > this->height()){
            ExceptionWrongDimensions exp;
            throw exp;
        }
        newM.push_back((*this)[ind[i]]);
    }
    return newM;
}


template <class T>
// transpose the matrix and do the same as 'get_rows'
Mat<T> Mat<T>::get_cols(const Vec<unsigned int>& ind) const{
    unsigned int h = ind.size();
    if (h < 1){
        ExceptionWrongDimensions exp;
        throw exp;
    }
    Mat<T> newM(h);
    Mat<T> trns_M(this->transpose());
    for (unsigned int i=0 ; i<h ; i++){
        if (ind[i] < 0 || ind[i] > h){
            ExceptionWrongDimensions exp;
            throw exp;
        }
        newM.push_back(trns_M[ind[i]]);
    }
    return newM;
}

template <class T>
// the function creates vector from each coloumn and insert the vector as a row to new matrix
Mat<T> Mat<T>::transpose() const{
    typename std::list<Vec<T>>::const_iterator this_it;
    unsigned int new_w = this->height();
    Mat<T> Mnew(new_w);

    for (unsigned int i=0 ; i<this->width() ; i++)
    {
        Vec<T> tmpV ;
        for (this_it = this->begin() ; this_it!=this->end() ; this_it++)
        {
            tmpV.push_back((*this_it)[i]);
        }
        Mnew.push_back(tmpV);
    }

    return Mnew;

}

template <class T>
Mat<T> operator*(const T& lhs, const Mat<T>& rhs){
    typename std::list<Vec<T>>::const_iterator rhs_it;


    Mat<T> tmp(rhs.width());
    for (rhs_it=rhs.begin();rhs_it!=rhs.end();rhs_it++)
    {
        tmp.push_back(lhs*(*rhs_it));

    }

    return tmp;


}



template <class T>
ostream& operator<<(ostream& ro, const Mat<T>& m){
    typename std::list<Vec<T>>::const_iterator this_it;
    ro << "(" <<endl;
    unsigned int i=0;
    for (this_it=m.begin();this_it!=m.end();this_it++)
    {
        ro << *this_it;
        if (i<(m.height()-1)) {
            ro << ",";
        }
        ro<<endl;
        i++;
    }
    ro<< ")";
    return ro;

}


#endif //MAT_IMPL_H
