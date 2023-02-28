// TODO: Implement the member functions of Node (Part (B), except the output operator)
//             and the graph operations (Part (C))
template<typename T>
Node<T>::Node(const T& val){
   this->val = val;
   out = nullptr;
   capacity = 0;
   size_p = 0;
}

template<typename T>
Node<T>::Node(const Node<T>& that){
    val = that.val;
    out = nullptr;
    capacity = 0;
    size_p = 0;
}

template<typename T>
Node<T>::~Node(){
    if(out != nullptr){
        delete[] out;
        out = nullptr;  
    }
}

template<typename T>
T& Node<T>::operator*(){
    return val;
}

template<typename T>
const T& Node<T>::operator*() const{
    return val;
}

template<typename T>
unsigned int Node<T>::degree() const{
    unsigned int degree_count = 0;
    for(unsigned int i = 0 ; i < size_p; i++){
        if(out[i].is_null() == false){
            degree_count++;
        }
    }
    return degree_count;
}

template<typename T>
unsigned int Node<T>::size() const{
    return size_p;
}

template<typename T>
SmartPtr<Node<T>> Node<T>::operator[](unsigned int i) const{
    return out[i];
}

template<typename T>
void Node<T>::add(SmartPtr<Node<T>> n){
    if(n.is_null() == false){
        bool exist = false;
        for(unsigned int i = 0; i < capacity; i++){
            if(out[i] == n){
                exist = true;
                break;
            }
        }
    
        if(exist == false){
            if(&(*(*n)) != &(this->val)){
                if(capacity == size_p){
                    if(capacity == 0 && size_p == 0){
                        out = new SmartPtr<Node<T>>[init_capacity];
                        capacity = init_capacity;
                        out[0] = n;
                        size_p++;
                    }

                    else if(capacity*2 >= init_capacity){
                        SmartPtr<Node<T>>* temp = new SmartPtr<Node<T>>[capacity * 2];
                        for(unsigned int i = 0; i < capacity; i++){
                            temp[i] = out[i];
                        }
                        temp[capacity] = n;
                        delete[] out;
                        out = temp;
                        capacity = capacity*2;
                        size_p++;
                    }

                    else if(capacity*2 < init_capacity){
                        SmartPtr<Node<T>>* temp = new SmartPtr<Node<T>>[init_capacity];
                        for(unsigned int i = 0; i < capacity; i++){
                            temp[i] = out[i];
                        }
                        temp[capacity] = n;
                        delete[] out;
                        out = temp;
                        capacity = init_capacity;
                        size_p++;
                    }
                }

                else if(capacity > size_p){
                    out[size_p] = n;
                    size_p++;
                }
            }
            
        }
    }
}

template<typename T>
void Node<T>::remove(SmartPtr<Node<T>> n){
    for(unsigned int i = 0; i < size_p; i++){
        if(out[i] == n){
            if(n.is_null() == false){
                out[i].unset();
            }
        }
    }
}

template<typename T>        
bool Node<T>::exists(SmartPtr<Node<T>> n) const{
    if(n.is_null() == true){
        return false;
    }

    for(unsigned int i = 0; i < size_p; i++){
        if(out[i] == n){
            if(n.is_null() == false){
                return true;
            }
        }
    }

    return false;
}
        
template<typename T>
SmartPtr<Node<T>> Node<T>::find(T val) const{
    for(unsigned int i = 0; i < size_p; i++){
        if((*(*(out[i]))) == val){
            return out[i];
        }
    }

    return SmartPtr<Node<T>>();
}


//Part (C) Graph operations
template <typename T> 
SmartPtr<Node<T>> new_node(const T& val){
    Node<T> newNode(val);
    SmartPtr<Node<T>> new_sp(val);
    return new_sp;
}

template <typename T> 
void remove_node(SmartPtr<Node<T>> n){
    if(n.is_null() == false){
        for(unsigned int i = 0; i < (*n).size(); i++){
            if(((*n)[i]).is_null() == false){
                remove_edge(n, (*n)[i]);
            }
        }
        
    }
}

template <typename T> 
void add_edge(SmartPtr<Node<T>> n1, SmartPtr<Node<T>> n2){
    if(n1.is_null() == false && n2.is_null() == false && n1 != n2){
        if(((*n1).exists(n2)) == false && ((*n2).exists(n1)) == false){
            (*n1).add(n2);
            (*n2).add(n1);
        }
    }
}

template <typename T> 
void remove_edge(SmartPtr<Node<T>> n1, SmartPtr<Node<T>> n2){
    if(n1.is_null() == false && n2.is_null() == false && n1 != n2){
        if(((*n1).exists(n2)) == true && ((*n2).exists(n1)) == true){
            (*n1).remove(n2);
            (*n2).remove(n1);
        }
    }
}

template <typename T> 
void remove_graph(SmartPtr<Node<T>> root){
    if(root.is_null() ==true){
        return;
    }
    else if(root.is_null() == false){
        for(unsigned int i = 0; i < (*root).size(); i++){
            if(((*root)[i]).is_null() == false){
                SmartPtr<Node<T>> temp = (*root)[i];
                remove_edge(root, (*root)[i]);
                remove_graph(temp);
            }   

            else if((*root)[i].is_null() == true){
                continue;
            }
        }
    }
}

//Helper functions for find() and reachable()
template <typename T>
void help_find(SmartPtr<Node<T>> root, T val, vector<SmartPtr<Node<T>>>& array, bool& found){
    if(root.is_null() == false){
        array.emplace_back(root);

        if(*(*root) == val){
            found = true;
            return;
        }

        for(unsigned int i = 0; i < (*root).size(); i++){
            if(((*root)[i]).is_null() == false){
                bool exist = false;
                for(unsigned int j = 0; j < array.size(); j++){
                    if(array[j] == (*root)[i]){
                        exist = true;
                        break;
                    }
                }

                if(exist == false){
                    help_find((*root)[i], val, array, found); 
                }

                else if(exist == true){
                    continue;
                }
            }   
        }
    }
    
    return;
}

template <typename T>
void help_reach(SmartPtr<Node<T>> root, SmartPtr<Node<T>>& dest, vector<SmartPtr<Node<T>>>& array, bool& reachable){
    if(root.is_null() == false){
        array.emplace_back(root);
        
        if(root == dest){
            reachable = true;
            return;
        }

        for(unsigned int i = 0; i < (*root).size(); i++){
            if(((*root)[i]).is_null() == false){
                bool exist = false;
                for(unsigned int j = 0; j < array.size(); j++){
                    if(array[j] == (*root)[i]){
                        exist = true;
                        break;
                    }
                }

                if(exist == false){
                    help_reach((*root)[i], dest, array, reachable); 
                }

                else if(exist == true){
                    continue;
                }
            }   
        }
    }
    
    return;
}
//End of helper functions

template <typename T> 
SmartPtr<Node<T>> find(SmartPtr<Node<T>> root, T val){
    vector<SmartPtr<Node<T>>> array;
    bool found = false;
    help_find(root, val, array, found);
    if(found){
        for(unsigned int i = 0; i < array.size(); i++){
            if(*(*(array[i])) == val){
                return array[i];
            }
        }
    }

    return SmartPtr<Node<T>>();
}

template <typename T> 
bool reachable(SmartPtr<Node<T>> root, SmartPtr<Node<T>> dest){
    if(root.is_null() == true || dest.is_null() == true){
        return false;
    }

    vector<SmartPtr<Node<T>>> array;
    bool reachable = false;
    help_reach(root, dest, array, reachable);
    return reachable;
}



