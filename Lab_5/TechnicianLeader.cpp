#include "TechnicianLeader.h"

//TODO: Implement TechnicianLeader.cpp
TechnicianLeader::TechnicianLeader() {}
        
TechnicianLeader::TechnicianLeader(int id, const string& name, char gender, const Date& entry_date, int num_projects, Department dept)
                :Technician(id, name, gender, entry_date, num_projects, dept) { this->post = "Technician Leader"; }

TechnicianLeader::~TechnicianLeader(){
    cout << "Resign: TechnicianLeader " << (this->name) << endl;
}
        
void TechnicianLeader::calculate_salary(){
    this->salary = 20000 + 1500 * this->num_projects;
}

void TechnicianLeader::print_description() const{
    cout<< "ID: "<< this->id << ", Name: "<< this->name <<", Gender: "<< this->gender << ", Entry date: "<< 
    this->entry_date.year <<"-"<< this->entry_date.month <<"-"<< this->entry_date.day << ", Post: Technician Leader, Group: " << enum_to_str(this->dept) <<
    ", Finished num_projects: " << this->num_projects <<endl;
}