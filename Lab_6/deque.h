#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include <sstream>

using namespace std;

template <typename T>
class BiLNode {
public:
    T data {};
    BiLNode<T> *next {nullptr};
    BiLNode<T> *prev {nullptr};
    BiLNode(T input) {
        data = input;
        next = nullptr;
        prev = nullptr;
    }
};

template <typename T>
class Deque {
private:
    BiLNode<T> *head {nullptr};
    BiLNode<T> *tail {nullptr};
    int size {0};
public:
    Deque() = default;
    ~Deque() {
        BiLNode <T>* tmp = head;
        while(tmp != nullptr) {
            tmp = tmp->next;
            delete head;
            head = tmp;
        }
    }

    void push_back(const T& value) {
        if(head == nullptr) {
            head = new BiLNode<T> (value);
            tail = head;
        } else {
            BiLNode<T> *tmp = new BiLNode<T> (value);
            tmp->prev = tail;
            tail->next = tmp;
            tail = tmp;
        }
        size++;
    }

    void push_front(const T& value) {
        if(head == nullptr) {
            head = new BiLNode<T> (value);
            tail = head;
        } else {
            BiLNode<T> *tmp = new BiLNode<T> (value);
            tmp->next = head;
            head->prev = tmp;
            head = tmp;
        }
        size++;
    }

    T pop_back() {
        if (head == nullptr) {
            cout << "Nothing in deque!";
        }
        if (head->next == nullptr) {
            T tmp = head->data;
            delete head;
            head = nullptr;
            size--;
            return tmp;
        }
        T tmp = tail->data;
        BiLNode<T> *bftail = tail->prev;
        delete tail;
        tail = bftail;
        tail->next = nullptr;
        size--;
        return tmp;
    }

    T pop_front() {
        if (head == nullptr) {
            cout << "Nothing in deque!";
        }
        if (head->next == nullptr) {
            T tmp = head->data;
            delete head;
            head = nullptr;
            size--;
            return tmp;
        }
        T tmp = head->data;
        BiLNode<T> *afhead = head->next;
        delete head;
        head = afhead;
        head->prev = nullptr;
        size--;
        return tmp;
    }

    void clear() {
        while(size>0) this->pop_back();
    }

    // TODO 1: overload operator==
    bool operator==(const Deque& q_compared) const {
        BiLNode<T>* ptr_compared = q_compared.head;
        if(q_compared.size == this->size){
            for(BiLNode<T>* temp_ptr = this->head; temp_ptr != nullptr; temp_ptr = temp_ptr->next, ptr_compared = ptr_compared->next){
                if(temp_ptr->data != ptr_compared->data){
                    return false;
                }
            }
            
            if(ptr_compared == nullptr){
                return true;
            }
        }

        return false;
    }

    // TODO 2: overload operator=
    const Deque<T>& operator=(const Deque<T>& input_q){
        if((*this) == input_q){
            return (*this);
        }

        this->clear();

        BiLNode<T>* temp_ptr = input_q.head;
        while(temp_ptr != nullptr){
            this->push_back(temp_ptr->data);
            temp_ptr = temp_ptr->next;
        }

        return (*this);
    }
    // TODO 3: overload operator+
    Deque<T> operator+(const Deque<T>& input_q){
        Deque<T> result;
        if(this->size == 0 && input_q.size == 0){
            return result;
        }
        
        for(BiLNode<T>* temp_ptr = this->head; temp_ptr != nullptr; temp_ptr = temp_ptr->next){
            result.push_back(temp_ptr->data);
        }

        for(BiLNode<T>* temp_ptr = input_q.head; temp_ptr != nullptr; temp_ptr = temp_ptr->next){
            result.push_back(temp_ptr->data);
        }

        return result;
    }

    // TODO 4: overload operator<<
    friend ostream& operator<<(ostream& os, const Deque<T>& input_q){
        BiLNode<T>* current_ptr = input_q.head;
        while(current_ptr != nullptr){
            if(current_ptr == input_q.head){
                os<< "[" << current_ptr->data << "<-->";
            }

            else if(current_ptr->next == nullptr){
                os<< current_ptr->data << "]";
            }

            else{
                os<< current_ptr->data << "<-->";
            }

            current_ptr =current_ptr->next;
        }

        return os;
    }

};

#endif