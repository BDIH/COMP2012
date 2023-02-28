#include <iostream>
#include "school-namespaces.h"

// Note: You are supposed to insert new lines in this file, but not modify/delete existing lines!
// TODO 1: Specify namespaces to be used in this file.
using std::cout;
using std::endl;
using std::cin;

void QueryEvents() {
    cout << "Select the school: 1. School of Engineering; 2. School of Science:";
    char choice;
    while(cin >> choice) {
        if (choice == '1' || choice == '2')
            break;
        else
            cout << "Select from 1 or 2." << endl;
    }

    if(choice == '1') {
        cout << "Select the department: 1. Department of CSE; 2. Department of ECE; 3. All Departments:";
        // TODO 2: Call the corresponding print_events function according to input.
        char choice;
        while (cin >> choice){
            if(choice == '1' || choice == '2' || choice == '3'){
                break;
            }
            else{
                cout << "Invalid input." << endl;
            }
        }

        if(choice == '1'){
            engineering::cse::show_events();
        }

        if(choice == '2'){
            engineering::ece::show_events();
        }

        if(choice == '3'){
            engineering::show_events();
        }
        
    }
    else {
        cout << "Select the department: 1. Department of Mathematics; 2. Department of Physics; 3. All Departments:";
        // TODO 3: Call the corresponding print_events function according to input.
        char choice;
        while (cin >> choice){
            if(choice == '1' || choice == '2' || choice == '3'){
                break;
            }
            else{
                cout << "Invalid input." << endl;
            }
        }

        if(choice == '1'){
            science::math::show_events();
        }

        if(choice == '2'){
            science::physics::show_events();
        }

        if(choice == '3'){
            science::show_events();
        }                        
    }
}