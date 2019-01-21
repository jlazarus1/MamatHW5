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
    if (vec1.size() != vec2.size()){
        ExceptionWrongDimensions exp;
        throw exp;
    }

    T elem = (*vec1_it)*(*vec2_it);
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
: w_(vec_1d.size()) , Vec<Vec<T>>(vec_1d){
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
    Mat* newMat;
    newMat = new Mat<T>(w_);
    for (this_it=this->begin();this_it!=this->end();this_it++){
        newMat->push_back(rhs*(*this_it));
    }
    return *newMat;
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
    Mat<T>* newMat;
    newMat = new Mat<T>(w_);
    newMat->w_=this->w_;
    *newMat=rhs.transpose();
    Vec<T>* Vtmp;

    Mat* outMat;
    outMat = new Mat<T>(w_);
    for(this_it=this->begin() ; this_it!=this->end() ; this_it++){
        Vtmp = new Vec<T>;
        for (newMat_it=newMat->begin();newMat_it!=newMat->end();newMat_it++){
         Vtmp->push_back(VecMul(*this_it,*newMat_it));
        }
        outMat->push_back(*Vtmp);
        delete Vtmp;




    }
    delete newMat;

    return *outMat;
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

    Mat<T>* newM;
    newM = new Mat<T>(w_);
    for (this_it=this->begin();this_it!=this->end();this_it++)
    {
        newM->push_back(*this_it);
    }
    for (rhs_it=rhs.begin();rhs_it!=rhs.end();rhs_it++){
        newM->push_back(*rhs_it);
    }
    return *newM;
}

template <class T>
// create new matrix only from the specific rows from the inserted vector
Mat<T> Mat<T>::get_rows(const Vec<unsigned int>& ind) const{
    typename std::list<Vec<T>>::const_iterator this_it;
    int h = ind.size();
    if (h < 1){
        ExceptionWrongDimensions exp;
        throw exp;
    }
    Mat<T> newM();

    for (auto p:ind)
    {
        for (this_it=this->begin();this_it!=this->end();this_it++)
        {

            newM.push_back(*this_it[p]);

        }

    }

    return *newM;

}


template <class T>
// transpose the matrix and do the same as 'get_rows'
Mat<T> Mat<T>::get_cols(const Vec<unsigned int>& ind) const{
    typename std::list<Vec<T>>::const_iterator this_it;
    typename std::list<Vec<T>>::const_iterator ind_it;
    int h = ind.size();
    if (h < 1){
        ExceptionWrongDimensions exp;
        throw exp;
    }
    Mat<T>* newM;
    newM = new Mat<T>;
    for(ind_it=ind.begin();ind_it!=ind.end();ind_it++)
    {
        if (*ind_it < 0 || *ind_it > this->height()) {
            ExceptionWrongDimensions exp;
            throw exp;
        }

        for(this_it=this->begin();this_it!=*ind_it;this_it++){}

        newM->push_back(*this_it);

    }

    newM=newM->transpose();



    return *newM;
}

template <class T>
// the function creates vector from each coloumn and insert the vector as a row to new matrix
Mat<T> Mat<T>::transpose() const{
    typename std::list<Vec<T>>::const_iterator this_it;
    typename std::list<T>::const_iterator vec_it;
    Mat<T>* Mnew;
    Mnew = new Mat<T>(this->height());
    Vec<T>* tmp_vec;


    for (int i=0;i<width();i++)
    {
        tmp_vec = new Vec<T>;
        for (this_it=this->begin();this_it!=this->end();this_it++)
        {
            vec_it=(*this_it).begin();
            std::advance(vec_it,i);
            tmp_vec->push_back(*vec_it);
        }
        Mnew->push_back(*tmp_vec);
        delete tmp_vec;
    }

    return *Mnew;

}

template <class T>
Mat<T> operator*(const T& lhs, const Mat<T>& rhs){
    typename std::list<Vec<T>>::const_iterator rhs_it;

    Mat<T>* tmp;
    tmp = new Mat<T>(rhs.width());
    for (rhs_it=rhs.begin();rhs_it!=rhs.end();rhs_it++)
    {
        tmp->push_back(lhs*(*rhs_it));

    }

    return *tmp;


}



template <class T>
ostream& operator<<(ostream& ro, const Mat<T>& m){
    typename std::list<Vec<T>>::const_iterator this_it;

    for (this_it=m.begin();this_it!=m.end();this_it++)
    {
        ro << *this_it;
    }
    return ro;

}


#endif //MAT_IMPL_H
