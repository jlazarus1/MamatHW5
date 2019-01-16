//
// Created by josh on 1/13/19.
//

#ifndef HW5_VEC_IMPL_H
#define HW5_VEC_IMPL_H

#endif //HW5_VEC_IMPL_H

using namespace std;

// Implementing the Exception classes as asked.

const char* ExceptionIndexExceed::what()  const throw(){

    return "index exeeds operand dimensions\n";

}

const char* ExceptionWrongDimensions::what() const throw(){

    return "operand dimensions must agree\n";

}


const char* ExceptionEmptyOperand::what() const throw(){

    return "empty operand\n";

}


//Implementing class vec methods.

template <class T>
Vec<T>::Vec(const T &el) {

T* tmp;
tmp= new T;
*tmp=el;
push_back(tmp);

}


template <class T>

void Vec<T>::push_back(T el) {

    vals_.push_back(el);
    return;
}

template <class T>
unsigned int Vec<T>::size() const {
    return vals_.size;
}

template <class T>
Vec<T> Vec<T>::operator+(const Vec &rhs) const {
    int i;

    if(this==0 || rhs==0)
    {
        ExceptionEmptyOperand exp;
        throw exp;
    }

    else if (this->size()!= rhs.size())
    {
        ExceptionWrongDimensions exp;
        throw  exp;
    }

    else
        {
        for (i = 0; i < this->size(); i++) {
            this[i] = this[i] + rhs[i];
        }
    }
    return;
}

template <class T>
Vec<T> Vec<T>::operator*(const T &rhs) const {

    int i;

    if(this==0 || rhs==0)
    {
        ExceptionEmptyOperand exp;
        throw exp;
    }

    else if (this->size()!= rhs.size())
    {
        ExceptionWrongDimensions exp;
        throw  exp;
    }


    else
    {
        for (i = 0; i < this->size(); i++) {


            this[i] = this[i] * rhs[i];

        }
    }
    return;
}


template <class T>
T& Vec<T>::operator[](unsigned int ind) {
    int i;
    typename std::list<T>::iterator tmp;    //created an iterator called tmp

    if (ind>=this->size  || ind<0) {         // if the index is out of range we throw an exception.
        ExceptionIndexExceed exp;
        return exp;
    }
    else
        tmp=begin();                //we initiate the iterator to be begin()
        for (i=0;i<ind;i++)
        {
            tmp++;
        }
            return tmp;         //TODO: not sure this is correct. might need to return *tmp

}

template <class T>
const T& Vec<T>::operator[](unsigned int ind) const {

    int i;
    typename std::list<T>::iterator const tmp;    //created an iterator called tmp

    if (ind>=this->size  || ind<0) {         // if the index is out of range we throw an exception.
        ExceptionIndexExceed exp;
        return exp;
    }
    else
        tmp=begin();                //we initiate the iterator to be begin()
    for (i=0;i<ind;i++)
    {
        tmp++;
    }
    return tmp;

}

template <class T>
Vec<T> Vec<T>::operator,(const Vec &rhs) const {

    int i;
    int length=rhs.size();

    for (i=0;i<length;i++)
    {
        push_back(rhs[i]);

    }

    return this;

}


template <class T>
Vec<T> Vec<T>::operator[](const Vec<unsigned int> &ind) const {

    int i;
    Vec<T>* tmp;
    tmp = new Vec<T>;

    for (i=0;i<ind.size();i++)
    {
        if (ind[i]<0 || ind[i]>this->size()) {
            ExceptionIndexExceed exp;
            throw exp;
        }
    }
            tmp->begin()=ind[0];
        for (i=0;i<ind.size();i++)
        {
            tmp->push_back(*this[ind[i]]);

        }
        return tmp;

}

template<class T>
Vec<T> operator*(const T &lhs, const Vec<T> &rhs) {

    int i;

    Vec<T>* tmp;
    tmp = new Vec<T>;

    if (rhs==0)     //we make sure the vector on the right is not empty if it is with throw
    {
        ExceptionEmptyOperand exp;
        throw exp;
    }

    for (i=0;i<rhs.size();i++)  // here we go through all the items in the vector and multiply them with the left side.
                                //we then push_back the new item into tmp and return it.
    {
        tmp->push_back(lhs*rhs[i]);
    }
    return tmp ;
}

template<class T>
ostream &operator<<(ostream &ro, const Vec<T> &v) {
    int i;
    if (v==0)
    {
        ExceptionEmptyOperand exp;
        throw exp;
    }

    ro << "(";

        for (i=0;i<v.size();i++)
        {
            ro << v[i] << "," << "  ";
        }
        ro << ")" << endl;

        return ro;
}

template<class T>
Vec<T> range(T start, unsigned int size) {

    Vec<T>* tmp;
    tmp = new Vec<T>;
    unsigned int i;

    if (size==0)
    {
        tmp =0;
        return tmp;
    }
    else
    {
        for(i=0;i<size;i++)
        {
            tmp->push_back(start+i);
        }

    }
    return *tmp;
}







