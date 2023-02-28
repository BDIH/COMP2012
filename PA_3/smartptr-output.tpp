// TODO: Implement the output operator<< for SmartPtr
template <typename T>
ostream& operator<<(ostream& os, const SmartPtr<T>& sp){
    if(sp.is_null() == true){
        return (os<< "SmartPtr()");
    }

    else{
        return (os<< "SmartPtr(" << *(sp.ptr) << "," << *(sp.count) << ")");
    }
}