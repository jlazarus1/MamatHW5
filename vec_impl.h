//
// Created by josh on 1/13/19.
//

#ifndef HW5_VEC_IMPL_H
#define HW5_VEC_IMPL_H

#include <cmath>
#include "complex.h"


// Implementing the Exception classes as asked.

const char* ExceptionIndexExceed::what()  const throw(){

    return "index exeeds operand dimensions";

}

const char* ExceptionWrongDimensions::what() const throw(){

    return "operand dimensions must agree";

}


const char* ExceptionEmptyOperand::what() const throw(){

    return "empty operand";

}


//Implementing class vec methods.

//implementing constructor.
template <class T>
Vec<T>::Vec(const T &el) {


push_back(el);

}

//implementing push_back

template <class T>
void Vec<T>::push_back(T el) {

    vals_.push_back(el);
    return;

}


//function name: size() - returns size of vector.
template <class T>
unsigned int Vec<T>::size() const {
    typename std::list<T>::const_iterator this_it;
    int i=0;
    for (this_it=this->begin();this_it!=this->end();this_it++){i++;}
    return i;
}


//operator +
template <class T>
Vec<T> Vec<T>::operator+(const Vec &rhs) const {

    if (this->size()!= rhs.size())
    {
        ExceptionWrongDimensions exp;
        throw  exp;
    }

    Vec<T> tmp;
    typename std::list<T>::const_iterator rhs_it = rhs.begin();
    typename std::list<T>::const_iterator this_it;

    if(this->size()==0 || rhs.size()==0)
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
        for (this_it=this->begin(); this_it!=this->end(); this_it++) {
            tmp.push_back(*this_it+*rhs_it);
            rhs_it++;
        }
    }

    return tmp;
}


//Operator *
template <class T>
Vec<T> Vec<T>::operator*(const T &rhs) const {

    Vec<T> tmp;

    typename std::list<T>::const_iterator this_it;

    if(this->size()==0)
    {
        ExceptionEmptyOperand exp;
        throw exp;
    }

    else
    {
        for (this_it=this->begin(); this_it!=this->end(); this_it++) {


            tmp.push_back(rhs*(*this_it));

        }
    }
    return tmp;
}


//Operator [] - recieves an index and returns the value by reference.
template <class T>
T& Vec<T>::operator[](unsigned int ind) {

    typename std::list<T>::iterator this_it=this->vals_.begin();
    unsigned int i;
    if (ind>=this->size()  || ind<0) {         // if the index is out of range we throw an exception.
        ExceptionIndexExceed exp ;
        throw exp;
    }
    else

        for (i=0;i<ind;i++)
        {
            this_it++;
        }
            return *this_it;

}


//Operator [] - same as above just for const T
template <class T>
const T& Vec<T>::operator[](unsigned int ind) const {

    unsigned int i;
    typename std::list<T>::const_iterator this_it=this->begin();


    if (ind>=this->size()  || ind<0) {         // if the index is out of range we throw an exception.
        ExceptionIndexExceed exp;
        throw exp;
    }
    else

    for (i=0;i<ind;i++)
    {
        this_it++;
    }
    return *this_it;

}


//Operator ,
template <class T>
Vec<T> Vec<T>::operator,(const Vec &rhs) const {
    Vec<T> tmp;

    typename std::list<T>::const_iterator this_it;
    typename std::list<T>::const_iterator rhs_it;
        for (this_it=this->begin();this_it!=this->end();this_it++)
    {
            tmp.push_back(*this_it);
    }
        for (rhs_it=rhs.begin();rhs_it!=rhs.end();rhs_it++)
        {
            tmp.push_back(*rhs_it);

        }


    return tmp;
}



//Operator[] - for recieveing a vector of indeces
template <class T>
Vec<T> Vec<T>::operator[](const Vec<unsigned int> &ind) const {
    unsigned int i;
    Vec<T> out;
    typename std::list<T>::const_iterator this_it = this->begin();
    typename std::list<unsigned int>::const_iterator ind_it;
    for (i=0;i<ind.size();i++)
    {
        if (ind[i]<0 || ind[i]>this->size()) {
            ExceptionIndexExceed exp;
            throw exp;
        }
    }
        for (ind_it=ind.begin();ind_it!=ind.end();++ind_it  )
        {
            std::advance(this_it,*ind_it);
            out.push_back(*this_it);
            this_it=this->begin();
        }

        return out;

}


//Operator* - multiplying T and a vector. 
template<class T>
Vec<T> operator*(const T &lhs, const Vec<T>& rhs) {

    typename std::list<T>::const_iterator rhs_it;
    Vec<T> tmp;

    if (rhs.size()==0)     //we make sure the vector on the right is not empty if it is with throw
    {
        ExceptionEmptyOperand exp;
        throw exp;
    }

    for (rhs_it=rhs.begin();rhs_it!=rhs.end();rhs_it++)  // here we go through all the items in the vector and multiply them with the left side.
                                //we then push_back the new item into tmp and return it.
    {
        tmp.push_back(lhs*(*rhs_it));
    }
    return tmp ;
}


//ostream - printing a vector. 
template<class T>
ostream &operator<<(ostream &ro, const Vec<T> &v) {
    typename std::list<T>::const_iterator v_it;
    unsigned int count=0;
    if (v.size()==0)
    {
        ExceptionEmptyOperand exp;
        throw exp;
    }

    ro << "(";

        for (v_it=v.begin();v_it!=v.end();v_it++)
        {
            if (count==v.size()-1)
                ro << *v_it;
            else {
                ro << *v_it << "," << "\t";
                count++;
            }
        }
        ro << ")";

        return ro;
}


//Function - range. returns a vector of size and first value start.
template<class T>
Vec<T> range(T start, unsigned int size) {

    Vec<T> tmp ;
    T x(1);

    if (size==0)
    {
        return tmp;
    }
    else
    {
        for(unsigned int i=0;i<size;i++)
        {
            tmp.push_back(start);
            start = start+x;
        }

    }
    return tmp;
}


//class norm_inf_comp: class that returns the norm inf comp of a vector. 
template <class T>
class norm_inf_comp {
public:
    bool operator()(Vec<T> Ls, Vec<T> Rh) const {
        double maxL (abs(Ls[0]));
        for (unsigned int i = 1; i < Ls.size(); i++) {
            if (abs(Ls[i]) > maxL) maxL = abs(Ls[i]);
        }
        double maxR (abs(Rh[0]));
        for (unsigned int i = 1; i < Rh.size(); i++) {
            if (abs(Rh[i]) > maxR) maxR = abs(Rh[i]);
        }
        return maxL < maxR;
    };
};




#endif //HW5_VEC_IMPL_H



