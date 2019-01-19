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


push_back(el);

}


template <class T>
void Vec<T>::push_back(T el) {

    vals_.push_back(el);
    return;
}

template <class T>
unsigned int Vec<T>::size() const {
    typename std::list<T>::const_iterator this_it;
    int i=0;
    for (this_it=this->begin();this_it!=this->end();this_it++){i++;}
    return i;



}

template <class T>
Vec<T> Vec<T>::operator+(const Vec &rhs) const {

    Vec<T>* tmp;
    tmp = new Vec<T>;
    typename std::list<T>::iterator tmp_it = tmp->vals_.begin();
    typename std::list<T>::const_iterator rhs_it = rhs.begin();
    typename std::list<T>::const_iterator this_it = this->begin();
    int i;

    if(*this_it==0 || *rhs_it==0)
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
            *tmp_it=*this_it+*rhs_it;
            rhs_it++;
        }
    }
    return *this;
}

template <class T>
Vec<T> Vec<T>::operator*(const T &rhs) const {

    Vec<T>* tmp;
    tmp = new Vec<T>;
    typename std::list<T>::const_iterator this_it = this->begin();
    typename std::list<T>::iterator tmp_it = tmp->vals_.begin();
    int i;

    if(*this_it==0)
    {
        ExceptionEmptyOperand exp;
        throw exp;
    }

    else
    {
        for (this_it=this->begin(); this_it!=this->end(); this_it++) {


            *tmp_it=*this_it*rhs;

        }
    }
    return *tmp;
}


template <class T>
T& Vec<T>::operator[](unsigned int ind) {

    typename std::list<T>::iterator this_it;
    typename std::list<T>::iterator tmp;    //created an iterator called tmp

    if (ind>=this->size()  || ind<0) {         // if the index is out of range we throw an exception.
        ExceptionIndexExceed exp ;
        throw exp;
    }
    else

        for (this_it=this->vals_.begin();this_it!=this->vals_.end();this_it++)
        {
        }
            return *this_it;

}

template <class T>
const T& Vec<T>::operator[](unsigned int ind) const {


    typename std::list<T>::const_iterator this_it;
    typename std::list<T>::iterator const tmp;    //created an iterator called tmp

    if (ind>=this->size()  || ind<0) {         // if the index is out of range we throw an exception.
        ExceptionIndexExceed exp;
        throw exp;
    }
    else

    for (this_it=this->begin();this_it!=this->end();this_it++)
    {
    }
    return *this_it;

}

template <class T>
Vec<T> Vec<T>::operator,(const Vec &rhs) const {
    Vec<T>* tmp;
    tmp = new Vec<T>;
    typename std::list<T>::const_iterator this_it;
    typename std::list<T>::iterator tmp_it=tmp->vals_.begin();
    typename std::list<T>::const_iterator rhs_it;
        for (this_it=this->begin();this_it!=this->end();this_it++)
    {
            *tmp_it=*this_it;
            tmp_it++;
    }
        for (rhs_it=rhs.begin();rhs_it!=rhs.end();rhs_it++)
        {
            *tmp_it=*rhs_it;
            tmp_it++;

        }


    return *tmp;
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
    Vec<T> * out;
    out = new Vec<T>;
    typename std::list<T>::const_iterator rhs_it = rhs.begin();
    Vec<T>* tmp;
    tmp = new Vec<T>;

    if (*rhs_it==0)     //we make sure the vector on the right is not empty if it is with throw
    {
        ExceptionEmptyOperand exp;
        throw exp;
    }

    for (i=0;i<rhs.size();i++)  // here we go through all the items in the vector and multiply them with the left side.
                                //we then push_back the new item into tmp and return it.
    {
        tmp->push_back(lhs*rhs[i]);
    }
    return *tmp ;
}

template<class T>
ostream &operator<<(ostream &ro, const Vec<T> &v) {
    typename std::list<T>::const_iterator v_it = v.begin();
    int i;
    if (v.size()==0)
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







