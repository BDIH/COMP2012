#include "Technician.h"

//TODO: Implement Technician.cpp
Technician::Technician(){}

Technician::Technician(int id, const string& name, char gender, const Date& entry_date, int num_projects, Department dept)
        :Employee(id, name, gender, entry_date, "Technician", dept), num_projects(num_projects) {}


Technician::~Technician(){
    cout << "Resign: Technician " << (this->name) << endl;
}

void Technician::calculate_salary(){
    this->salary =  10000 + 1000 * this->num_projects; 
}

void Technician::print_description() const{
    cout<< "ID: "<< this->id << ", Name: "<< this->name <<", Gender: "<< this->gender << ", Entry date: "<< 
    this->entry_date.year <<"-"<< this->entry_date.month <<"-"<< this->entry_date.day << ", Post: Technician, Group: " << enum_to_str(this->dept) <<
    ", Finished num_projects: " << this->num_projects <<endl;
}