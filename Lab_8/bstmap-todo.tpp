/*
g++ -std=c++11 -o lab8 *.cpp 
.\lab8
*/
//TODO: Return reference to value in this map corresponding to the provided key. 
//If the provided key does not exist, print an error message "Key is not in BSTMap" to std::cerr and terminate program using exit(-1).
// In practice, one should check if the map contains the key before calling this operator[]
template <typename K, typename V>
V& BSTMap<K, V>::operator[] (const K& k) {
    if(this->is_empty()){
        cout<<"Key is not in BSTMap"<<endl;
        exit(-1);
    }

    //base case 2
    if(root->data.key == k){
        return (root->data.value);
    }

    // Recursion on the left sub-tree
    else if (k < root->data.key){
        return root->left.operator[](k);
    }

    // Recursion on the right sub-tree
    else{                    
        return root->right.operator[](k);
    }
}


//TODO: Return value in this map corresponding to the provided key. 
//If the provided key does not exist, print an error message "Key is not in BSTMap" to std::cerr and terminate program using exit(-1).
// In practice, one should check if the map contains the key before calling this operator[]
template <typename K, typename V>
V BSTMap<K, V>::operator[](const K& k) const {
    if(this->is_empty()){
        cout<<"Key is not in BSTMap"<<endl;
        exit(-1);
    }

    //base case 2
    if(root->data.key == k){
        return (root->data.value);
    }

    // Recursion on the left sub-tree
    else if (k < root->data.key){
        return root->left.operator[](k);
    }

    // Recursion on the right sub-tree
    else{                    
        return root->right.operator[](k);
    }

} 


//TODO: Assignment constructor, pay attention to memory leak
//Before doing assignment, you need to first check whether this != &bst, 
//if the two pointers are equal then you need to do nothing. 
//You also need to clear the original Map before doing assignment, we will check memory leak in this lab.
template <typename K, typename V>
BSTMap<K, V>& BSTMap<K, V>::operator=(const BSTMap& bst) {    
    if(this == &bst){
        return *this;
    }

    if(this->is_empty()){
        this->root = new MapItem(*bst.root);
        return *this;
    }

    this->clear();
    this->root = new MapItem(*bst.root);
    return *this;
}


//TODO: Return number of items in this map
template <typename K, typename V>
int BSTMap<K, V>::size() const {
    //base case
    if(this->is_empty()){
        return 0;
    }

    return this->root->left.size() + this->root->right.size() + 1;

}


//TODO: Clear all items in BSTMap
template <typename K, typename V>
void BSTMap<K, V>::clear() {
    if(!this->is_empty())
    {   if(!this->root->left.is_empty()){
            delete this->root->left.root;
            this->root->left.root = nullptr;
        }

        if(!this->root->right.is_empty()){
            delete this->root->right.root;
            this->root->right.root = nullptr; 
        }

        if(this->root != nullptr){
            delete this->root;
            this->root =nullptr;
        }
    }
}


//TODO: In-Order Traversal
template <typename K, typename V>
ostream& operator<<(ostream& os, const BSTMap<K, V>& bst) {
    if(!bst.is_empty()){
        if(!bst.root->left.is_empty()){
            os<< bst.root->left;
            os<<" , ";
        }

        os<< "{"<< bst.root->data.key << ":" <<  bst.root->data.value << "}";
        //os<< "{"<< bst.root->data.key << ":" <<  bst[(bst.root->data.key)] << "}"; 

        if(!bst.root->right.is_empty()){
            os<<" , ";
            os<<bst.root->right;
        }
        return os;
    }

    return os;

}
