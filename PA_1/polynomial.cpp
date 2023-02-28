#include "polynomial.h"
#include <iostream>
using namespace std;
//note: you are not allowed to include any additional library, see also FAQ for what you can/cannot do
//write your code below and submit this file only

/*
g++ -std=c++11 -o a *.cpp
./a 
*/

Polynomial::Polynomial(){
    head = nullptr;
}

Polynomial::Polynomial(const Polynomial& another){
    head = new Term();
    head->coefficient = another.head->coefficient;
    head->exponent = another.head->exponent;
        
    Term* original_ptr = head;
    for(Term* copy_ptr = another.head->next; copy_ptr != nullptr; copy_ptr = copy_ptr->next, original_ptr = original_ptr->next){
        original_ptr->next = new Term();
        original_ptr->next->coefficient = copy_ptr->coefficient;
        original_ptr->next->exponent = copy_ptr->exponent;
    }
}

Polynomial::Polynomial(int array[], int arraySize){
    int start = 0;
    while(array[start] == 0){
        start++;
    }

    head = new Term();
    head->coefficient = array[start];
    head->exponent = arraySize - start - 1;

    Term* current_ptr = head;  
    for(int i = arraySize - start - 1; i > 0; i--){
        if(array[arraySize - i] == 0){
            continue;
        }

        else{
            current_ptr->next = new Term();
            current_ptr->next->coefficient = array[arraySize - i];
            current_ptr->next->exponent = i - 1;
            current_ptr = current_ptr->next;
        }
    }
    current_ptr->next = nullptr;
}

Polynomial::~Polynomial(){
    Term* current = head;
    Term* next = nullptr;
    
    while(current != nullptr){  
        next = current->next;
        delete current;
        current = next;    
    }

    head = nullptr;
}


void Polynomial::print() const{
    if(head == nullptr){
        cout<< "0";
        return;
    }

    for(Term* current_ptr = head; current_ptr != nullptr; current_ptr = current_ptr->next){
        if(current_ptr->exponent == 0){
            if(current_ptr->coefficient > 0){
                if(current_ptr != head){
                    cout<<" + ";
                    cout<< current_ptr->coefficient;
                } 

                else if(current_ptr == head){
                    cout<< current_ptr->coefficient;
                }
            }

            else if(current_ptr->coefficient < 0){
                if(current_ptr != head){
                    cout<<" - ";
                    cout<< (-1 * current_ptr->coefficient);
                }
                else if(current_ptr == head){
                    cout<< current_ptr->coefficient;
                }
            }   
        }

        else if(current_ptr->exponent != 0){
            if(current_ptr->exponent == 1){
                if(current_ptr->coefficient == 1){
                    if(current_ptr == head){
                        cout<< "x";
                    }
                    else if(current_ptr != head){
                    cout<< " + x"; 
                    }   
                }

                else if(current_ptr->coefficient == -1){
                    if(current_ptr == head){
                        cout<< "-x";
                    }
                    else if(current_ptr != head){
                    cout<< " - x"; 
                    }   
                }

                else if(current_ptr->coefficient > 1){
                    if(current_ptr == head){
                        cout<< current_ptr->coefficient << "*x";
                    }

                    else if(current_ptr != head){
                        cout<<" + ";
                        cout<< current_ptr->coefficient << "*x";
                    }   
                }

                else if(current_ptr->coefficient < -1){
                    if(current_ptr != head){
                        cout<<" - ";
                        cout<< (-1 * current_ptr->coefficient) << "*x";
                    }
                    else if(current_ptr == head){
                        cout<<"-";
                        cout<< (-1 * current_ptr->coefficient) << "*x";
                    }
                }
            }
            else{
                if(current_ptr->coefficient == 1){
                    if(current_ptr == head){
                        cout<< "x^" << current_ptr->exponent;
                    }
                    else if(current_ptr != head){
                    cout<< " + x^" << current_ptr->exponent; 
                    }   
                }

                else if(current_ptr->coefficient == -1){
                    if(current_ptr == head){
                        cout<< "-x^" << current_ptr->exponent;
                    }
                    else if(current_ptr != head){
                    cout<< " - x^" << current_ptr->exponent; 
                    }   
                }

                else if(current_ptr->coefficient > 1){
                    if(current_ptr == head){
                        cout<< current_ptr->coefficient << "*x^" << current_ptr->exponent;
                    }

                    else if(current_ptr != head){
                        cout<<" + ";
                        cout<< current_ptr->coefficient << "*x^" << current_ptr->exponent;
                    }   
                }

                else if(current_ptr->coefficient < -1){
                    if(current_ptr != head){
                        cout<<" - ";
                        cout<< (-1 * current_ptr->coefficient) << "*x^" << current_ptr->exponent;
                    }
                    else if(current_ptr == head){
                        cout<<"-";
                        cout<< (-1 * current_ptr->coefficient) << "*x^" << current_ptr->exponent;
                    }
                }
            }
        } 
    }
}

Polynomial Polynomial::add(const Polynomial& another) const{
    if(another.head == nullptr && head == nullptr){
        return (*this);
    }
    
    else if (another.head == nullptr){
        return (*this);
    }

    else if(head == nullptr){
        head->coefficient = another.head->coefficient;
        head->exponent = another.head->exponent;
            
        Term* current_ptr = head->next;
        for(Term* copy_ptr = another.head->next; copy_ptr != nullptr; copy_ptr = copy_ptr->next){
            current_ptr = new Term();
            current_ptr->coefficient = copy_ptr->coefficient;
            current_ptr->exponent = copy_ptr->exponent;
            current_ptr = current_ptr->next;
        }
        current_ptr = nullptr;
        return(*this);
    }

    else{
        int original_term = 0; 
        for(Term* temp = head; temp != nullptr; temp = temp->next, original_term++);
        int array[original_term] = {};
        
        int j = 0;
        for(Term* original_ptr = head; original_ptr != nullptr; original_ptr = original_ptr->next){
            int i = 1;
            
            for(Term* new_ptr = another.head; new_ptr != nullptr; new_ptr = new_ptr->next){                       
                if(original_ptr->exponent == new_ptr->exponent){
                    original_ptr->coefficient += new_ptr->coefficient;
                    array[j] = i;
                    j++;
                }
                i++;
            }      
        }

        int k = 1;
        for(Term* new_ptr = another.head; new_ptr != nullptr; new_ptr = new_ptr->next, k++){
            bool repeated = false;
            for(int i = 0; i < original_term; i++){
                if(array[i] == k){
                    repeated = true;
                }
            }

            if(repeated == true){
                continue;
            }

            else{   
                if(k == 1){
                    int original_co = head->coefficient;
                    int original_ex = head->exponent;

                    head->coefficient = new_ptr->coefficient;
                    head->exponent = new_ptr->exponent;

                    Term* temp = new Term();
                    temp->coefficient = original_co;
                    temp->exponent = original_ex;

                    temp->next = head->next; 
                    head->next = temp;
                }

                else{
                    for(Term* original_ptr = head; original_ptr != nullptr; original_ptr = original_ptr->next){
                        if(original_ptr->exponent == (new_ptr->exponent + 1)){
                            Term* temp = new Term();
                            temp->coefficient = new_ptr->coefficient;
                            temp->exponent = new_ptr->exponent;
                            temp->next = original_ptr->next;
                            original_ptr->next = temp;
                        }
                    }
                }
            }
        }

        while(head->coefficient == 0 && head->next != nullptr){
            head->coefficient = head->next->coefficient;
            head->exponent = head->next->exponent;                
            Term* temp_1 = head->next;
            head->next = head->next->next;
            delete temp_1;
        }

        if(head->coefficient == 0 && head->next == nullptr){
            Term* current = head;
            Term* next = nullptr;
            
            while(current != nullptr){  
                next = current->next;
                delete current;
                current = next;    
            }
        }

        return (*this);
    }
}

Polynomial Polynomial::subtract(const Polynomial& another) const{
    if(another.head == nullptr && head == nullptr){
        return (*this);
    }
    
    else if (another.head == nullptr){
        return (*this);
    }

    else if(head == nullptr){
        head->coefficient = (another.head->coefficient * -1);
        head->exponent = another.head->exponent;
            
        Term* current_ptr = head->next;
        for(Term* copy_ptr = another.head->next; copy_ptr != nullptr; copy_ptr = copy_ptr->next){
            current_ptr = new Term();
            current_ptr->coefficient = (copy_ptr->coefficient * -1);
            current_ptr->exponent = copy_ptr->exponent;
            current_ptr = current_ptr->next;
        }
        current_ptr = nullptr;
        return(*this);
    }

    else{
        int original_term = 0; 
        for(Term* temp = head; temp != nullptr; temp = temp->next, original_term++);
        int array[original_term] = {};

        int j = 0;
        for(Term* original_ptr = head; original_ptr != nullptr; original_ptr = original_ptr->next){
            int i = 1;
            for(Term* new_ptr = another.head; new_ptr != nullptr; new_ptr = new_ptr->next){                       
                if(original_ptr->exponent == new_ptr->exponent){
                    original_ptr->coefficient -= new_ptr->coefficient;
                    array[j] = i;
                    j++;
                }
                i++;
            }      
        }

        int k = 1;
        for(Term* new_ptr = another.head; new_ptr != nullptr; new_ptr = new_ptr->next, k++){
            bool repeated = false;
            for(int i = 0; i < original_term; i++){
                if(array[i] == k){
                    repeated = true;
                }
            }

            if(repeated == true){
                continue;
            }

            else{
                if(k == 1){
                    int original_co = head->coefficient;
                    int original_ex = head->exponent;

                    head->coefficient = (new_ptr->coefficient * -1);
                    head->exponent = new_ptr->exponent;

                    Term* temp = new Term();
                    temp->coefficient = original_co;
                    temp->exponent = original_ex;

                    temp->next = head->next; 
                    head->next = temp;
                }

                else{
                    for(Term* original_ptr = head; original_ptr != nullptr; original_ptr = original_ptr->next){
                        if(original_ptr->exponent == (new_ptr->exponent + 1)){
                            Term* temp = new Term();
                            temp->coefficient = (new_ptr->coefficient * -1);
                            temp->exponent = new_ptr->exponent;
                            temp->next = original_ptr->next;
                            original_ptr->next = temp;
                        }
                    }
                }
            }    
        }

        while(head->coefficient == 0 && head->next != nullptr){
            head->coefficient = head->next->coefficient;
            head->exponent = head->next->exponent;                
            Term* temp_1 = head->next;
            head->next = head->next->next;
            delete temp_1;
        }

        if(head->coefficient == 0 && head->next == nullptr){
            Term* current = head;
            Term* next = nullptr;
            
            while(current != nullptr){  
                next = current->next;
                delete current;
                current = next;    
            }
        } 

        return(*this);
    }
}

Polynomial Polynomial::multiply(const Polynomial& another) const{
    if(head == nullptr){
        return (*this);
    }

    else if (another.head == nullptr){
        Term* current = head;
        Term* next = nullptr;
        
        while(current != nullptr){  
            next = current->next;
            delete current;
            current = next;    
        }
        return (*this);
    }

    else{
        int original_term_num = 0;
        int multiply_term_num = 0;
        for(Term* original = head; original != nullptr; original = original->next, original_term_num++);
        for(Term* multiply = another.head; multiply != nullptr; multiply = multiply->next, multiply_term_num++);
        Term* result_array[original_term_num * multiply_term_num];

        int result_num = 0;
        for(Term* original = head; original != nullptr; original = original->next){
            for(Term* multiply = another.head; multiply != nullptr; multiply = multiply->next){
                result_array[result_num] = new Term();
                result_array[result_num]->coefficient = original->coefficient * multiply->coefficient;
                result_array[result_num]->exponent = original->exponent + multiply->exponent;
                result_num++;
            }
        }

        for(int i = 0; i < original_term_num * multiply_term_num; i++){
            for(int j = 0; j < original_term_num * multiply_term_num; j++){
                if(i != j && result_array[i]->exponent == result_array[j]->exponent){
                    result_array[i]->coefficient += result_array[j]->coefficient;
                    result_array[j]->exponent = -1;
                }
            }
        }

        int final_term_num = 0;
        for(int i = 0; i < original_term_num * multiply_term_num; i++){
            if(result_array[i]->coefficient != 0 || result_array[i]->exponent != -1){
                final_term_num++;
            }
        }


        if(final_term_num < original_term_num){
            Term* current_ptr = head;
            for(int i = 0; i < final_term_num; current_ptr = current_ptr->next, i++){ 
                for(int j = 0; j < original_term_num * multiply_term_num; j++){
                    if(result_array[j]->coefficient != 0 && result_array[j]->exponent != -1){
                        current_ptr->coefficient = result_array[j]->coefficient;
                        current_ptr->exponent = result_array[j]->exponent;
                        result_array[j]->exponent = -1;
                        break;
                    }
                }
            }

            for(int i = 0; i < (original_term_num - final_term_num); i++){
                Term* current_ptr_2 = head;
                while(current_ptr_2->next != nullptr){
                    current_ptr_2 = current_ptr_2->next;
                }
                delete current_ptr_2;
                current_ptr_2 = nullptr;
            }

            for(int i = 0; i < original_term_num * multiply_term_num; i++){
                delete result_array[i];
            }
            
            return (*this);
        }

        else if(final_term_num == original_term_num){
            for(Term* current_ptr = head; current_ptr != nullptr; current_ptr = current_ptr->next){
                for(int i = 0; i < original_term_num * multiply_term_num; i++){
                    if(result_array[i]->coefficient != 0 && result_array[i]->exponent != -1){
                        current_ptr->coefficient = result_array[i]->coefficient;
                        current_ptr->exponent = result_array[i]->exponent;
                        result_array[i]->exponent = -1;
                        break;
                    }
                }
            }

            for(int i = 0; i < original_term_num * multiply_term_num; i++){
                delete result_array[i];
            }
        }

            
        else if(final_term_num > original_term_num){
            for(Term* current_ptr = head; current_ptr != nullptr; current_ptr = current_ptr->next){
                for(int i = 0; i < original_term_num * multiply_term_num; i++){
                    if(result_array[i]->coefficient != 0 && result_array[i]->exponent != -1){
                        current_ptr->coefficient = result_array[i]->coefficient;
                        current_ptr->exponent = result_array[i]->exponent;
                        result_array[i]->exponent = -1;
                        break;
                    }
                }  
            }

            int count = 0;
            int num[original_term_num * multiply_term_num] = {};
            for(int i = 0; i < original_term_num * multiply_term_num; i++){
                if(result_array[i]->coefficient != 0 && result_array[i]->exponent != -1){
                    num[count] = i;
                    count++;
                }
            }
            
            for(int i = 0; i < count - 1; i++){
                result_array[num[i]]->next = result_array[num[i+1]]; 
            }
            result_array[num[count-1]]->next = nullptr;

            Term* temp = head;
            while(temp->next != nullptr){
                temp = temp->next;
            }
            temp->next = result_array[num[0]];

            for(int i = 0; i < original_term_num * multiply_term_num; i++){
                if(result_array[i]->coefficient == 0 || result_array[i]->exponent == -1)
                delete result_array[i];
            }
        }

       if(final_term_num > 1){      
            for(int i = 0; i < final_term_num; i++){
                Term* previous_ptr = head;
                for(Term* current_ptr = head->next; current_ptr != nullptr; current_ptr = current_ptr->next, previous_ptr = previous_ptr->next){
                    if(previous_ptr->exponent < current_ptr->exponent){
                        int temp_co = previous_ptr->coefficient;
                        int temp_ex = previous_ptr->exponent;
                        previous_ptr->coefficient = current_ptr->coefficient;
                        previous_ptr->exponent = current_ptr->exponent;
                        current_ptr->coefficient = temp_co;
                        current_ptr->exponent = temp_ex;
                    }    
                }
            }
        }

        return (*this);
    }
}

int Polynomial::evaluate(int valueOfX) const{
    if(head == nullptr){
        return 0;
    }

    else{
        int term_num = 0;
        for(Term* current_ptr = head; current_ptr != nullptr; current_ptr = current_ptr->next, term_num++);
        int term_result[term_num] = {};

        int result_num = 0;
        for(Term* current_ptr = head; current_ptr != nullptr; current_ptr = current_ptr->next){
            int result = 1;
            if(current_ptr->exponent == 0){
                result = 1 * current_ptr->coefficient;
            }

            else if(current_ptr->exponent == 1){
                result = valueOfX * current_ptr->coefficient;
            }

            else{
                result *= valueOfX;
                for(int i = 2; i <= current_ptr->exponent; i++){
                    result *= valueOfX;
                }
                result *= current_ptr->coefficient;
            }

            term_result[result_num] = result;
            result_num++;
        }

        int final_result = 0;
        for(int i = 0; i < result_num; i++){
            final_result += term_result[i];
        }
        
        return final_result;
    }
   
}

int Polynomial::compare(const Polynomial& another) const{
    Term* original = head;
    Term* compared = another.head;

    if(original == nullptr && compared != nullptr){
        return -1;
    }

    else if(original != nullptr && compared == nullptr){
        return 1;
    }

    else if(original == nullptr && compared == nullptr){
        return 0;
    }

    else{
        while(original != nullptr || compared != nullptr){
            if(original->exponent > compared->exponent){
                return 1;
            }

            else if(original->exponent < compared->exponent){
                return -1;
            }

            else if(original->exponent == compared->exponent){
                if(original->coefficient > compared->coefficient){
                    return 1;
                }

                else if(original->coefficient < compared->coefficient){
                    return -1;
                }
            }
            original = original->next;
            compared = compared->next;
        }

        if(original == nullptr && compared != nullptr){
            return -1;
        }

        else if(original != nullptr && compared == nullptr){
            return 1;
        }

        else{
            return 0;
        }
    }
}
