#include <iostream>
#include <string>
#include "school-namespaces.h"

// TODO 1: Finish the definitions of variables and functions in different namespaces
// with the 'using' statement, the '::' operator, and namespace alias.
using std::string;
namespace sc = science;

// TODO 1.1: Complete the definition of events in CSE department.
string engineering::cse::events[] {
    "9:00 Making Machine Learning Automated and Trustworthy.",
    "11:00 The Next Frontier in Type Inference.",
    "14:00 AI-Human Teaming for Decision Making."
};


// TODO 1.2: Complete the definition of events in ECE department.
string engineering::ece::events[] {
    "15:00 2D Materials, from Academia to Industry.",
    "16:00 Bridging Vision and Language for Cross-Modal Understanding and Generation."
};


// TODO 1.3: Complete the definition of events in MATH department.
string science::math::events[] {
    "16:00 Rate of blow up in the thin obstacle problem."
};

// TODO 1.4: Complete the definition of events in Physics department.
string science::physics::events[] {
    "11:00 Interfacial Dynamics between a Hydrogel and a Fluid: Modeling and Simulation.",
    "14:00 Application of Flow Model to Theoretical Physics."
};

// Define events in School of Science. (No modification to this part.)
string sc::events[] {
    "10:00 A variational approach to describe the moduli space of minimal immersions in hyperbolic."
};

// Define show_events function for CSE department.
void engineering::cse::show_events() {
    std::cout << "Welcome to Department of CSE!" << std::endl;
    for (string s: engineering::cse::events){
        std::cout << s << std::endl;
    }
}

// Define show_events function for ECE department.
void engineering::ece::show_events() {
   std::cout << "Welcome to Department of ECE!" << std::endl;
    for (string s:engineering::ece::events){
        std::cout << s << std::endl;
    }
}

// Define show_events function for School of Engineering.
void engineering::show_events() {
    std::cout << "Welcome to School of Engineering!" << std::endl;
    // TODO 2: print events in both CSE and ECE departments (CSE first, ECE second).
    for (string s: engineering::cse::events){
        std::cout << s << std::endl;
    }
    for (string s:engineering::ece::events){
        std::cout << s << std::endl;
    }
}


// Define show_events function for MATH department.
void science::math::show_events() {
    std::cout << "Welcome to Department of Mathematics!" << std::endl;
    for (string s:science::math::events){
        std::cout << s << std::endl;
    }
}

// Define show_events function for Physics department.
void science::physics::show_events() {
    std::cout << "Welcome to Department of Physics!" << std::endl;
    for (string s:science::physics::events){
        std::cout << s << std::endl;
    }
}


// Define show_events function for School of Science.
void science::show_events() {
    std::cout << "Welcome to School of Science!" << std::endl;
    // TODO 3: print events in School of Science, MATH department, and Physics department
    // (School of Science first, MATH department second, Physics department third).
    for (string s: science::events){
        std::cout << s << std::endl;
    }
    for (string s:science::math::events){
        std::cout << s << std::endl;
    }
    for (string s:science::physics::events){
        std::cout << s << std::endl;
    }
}