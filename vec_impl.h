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

void Vec<T>::push_back(T el) {

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



