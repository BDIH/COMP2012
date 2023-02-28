// TODO: Implement the output operator<< for Node
template <typename T> 
ostream& operator<<(ostream& os, const Node<T>& n){
    os<< "Node(" << *n << ",{";
    if(n.size() == 0 || n.degree() == 0){
        os<<"})";
    }
    
    else if(n.size() > 0){
        for(unsigned int i = 0; i < n.size(); i++){
            bool last = true;
            for(unsigned int j = i+1; j < n.size(); j++){
                if(n[j].is_null() == false){
                    last = false;
                    break;
                }
            }

            if(last == true){
                if((n[i]).is_null() == false){
                    os<< *(*n[i]) <<"})";
                    break;
                }
            }

            else if(last == false){
                if((n[i]).is_null() == false){
                    os<< *(*n[i]) << ",";
                }
            }
        }
    }
    return os;
}