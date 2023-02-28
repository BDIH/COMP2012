// TODO: Implement the member functions of SmartPtr (Part (A), except the output operator)
/*
g++ -std=c++11 -o pa3 main.cpp 
./pa3
*/
template<typename T>
SmartPtr<T>::SmartPtr():ptr{nullptr}, count{nullptr} {}

template<typename T>
SmartPtr<T>::SmartPtr(const T& val){
    ptr = new T(val);
    count = new unsigned int(1);
}

template<typename T>
SmartPtr<T>::SmartPtr(const SmartPtr<T>& that){
    ptr = that.ptr;
    count = that.count;
    if(that.count != nullptr){
        (*(that.count))++; 
    } 

}

template<typename T>
SmartPtr<T>::~SmartPtr(){
    if(count != nullptr){
        if(*(count) == 1){
            delete ptr;
            delete count;
            ptr = nullptr;
            count = nullptr;
        }  

        else{
            (*count)--;
        }
    }
}

template<typename T>
SmartPtr<T>& SmartPtr<T>::operator=(const SmartPtr<T>& that){
    if(count == nullptr && that.count != nullptr){
        ptr = that.ptr;
        count = that.count;
        (*count)++;
    }

    else if(count != nullptr){
        if((*count) == 1){
            delete ptr;
            delete count;  
            ptr = that.ptr;
            count = that.count;
            if(that.count != nullptr){
                (*count)++;
            } 
        }
        else{
            (*count)--;
            ptr = that.ptr;
            count = that.count;
            if(that.count != nullptr){
                (*count)++;
            }
        }
    }
    
    return (*this);
}

template<typename T>
void SmartPtr<T>::set(const T& val){
    if(count != nullptr){
        if((*count) == 1){
            delete ptr;    
            ptr = new T(val);
            (*count) = 1;
        }
        else{
            (*count)--;
            ptr = new T(val);
            count = new unsigned int(1);
        } 
    }

    else if(count == nullptr){
        ptr = new T(val);
        count = new unsigned int(1);
    }
}

template<typename T>
void SmartPtr<T>::unset(){
    if(count != nullptr){
        if((*count) == 1){
            delete ptr;
            delete count;
            ptr = nullptr;
            count = nullptr;
        }
        else{
            (*count)--;
            ptr = nullptr;
            count = nullptr;
        }
    }
}

template<typename T>
bool SmartPtr<T>::is_null() const{
    if(ptr == nullptr && count == nullptr){
        return true;
    }

    return false;
}

template<typename T>
bool SmartPtr<T>::operator==(const SmartPtr<T>& that) const{
    if(ptr == that.ptr){
        return true;
    }

    return false;
}

template<typename T>
bool SmartPtr<T>::operator!=(const SmartPtr<T>& that) const{
    if(ptr != that.ptr){
        return true;
    }

    return false;
}

template<typename T>
T& SmartPtr<T>::operator*() const{
    return (*ptr);
}

template<typename T>
T* SmartPtr<T>::operator->() const{
    return ptr;
}

