//
// Created by josh on 1/13/19.
//

#ifndef HW5_VEC_IMPL_H
#define HW5_VEC_IMPL_H


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
Vec<T>::Vec(const T &el) { //TODO don't you need to initialize 'vals_'?


push_back(el);

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
    return *this;
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


            this[i] = this[i] * rhs[i]; //TODO i think rhs (which is T) isn't an array and so don't have index i.

        }
    }
    return *this;
}


template <class T>
T& Vec<T>::operator[](unsigned int ind) {
    int i;
    typename std::list<T>::iterator tmp;    //created an iterator called tmp

    if (ind>=this->size  || ind<0) {         // if the index is out of range we throw an exception.
        ExceptionIndexExceed exp;
        throw exp;
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
        throw exp;
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

    this->end()=rhs.begin();
    return *this;
}


template <class T>
Vec<T> Vec<T>::operator[](const Vec<unsigned int> &ind) const {
    int i;
    Vec<T>* out;
    out = new Vec<T>;
    typename std::list<T>::iterator out_it = out->vals_.begin();
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
            *out_it=*this_it;
            ++out_it;
            this_it=this->begin();
        }

        return *out_it;

}

template<class T>
Vec<T> operator*(const T &lhs, const Vec<T> &rhs) {

    int i;
    typename std::list<T>::iterator out_it = out->vals_.begin();
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
    if (v==(T)0)
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


#endif //HW5_VEC_IMPL_H





