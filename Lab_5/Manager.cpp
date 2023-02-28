#include "Manager.h"

//TODO: Implement Manager.cpp
Manager::Manager() {};

Manager ::Manager(int id, const string& name, char gender, const Date& entry_date, Department dept)
        : Employee(id, name, gender, entry_date, "Manager", dept), num_staff(0)
        { 
            staffs = new Employee*[MAX_STAFF_NUM];
            for(int i = 0; i < MAX_STAFF_NUM; i++){
                staffs[i] = nullptr;
            }   
        }

Manager::~Manager() 
{
    for(int i = 0; i < MAX_STAFF_NUM; i++){
        delete staffs[i];
    }

    delete[] staffs;

    cout << "Resign: Manager " << (this->name) << endl;

}

void Manager::manage(Technician *t)
{
    for(int i = 0; i < MAX_STAFF_NUM; i++){
        if(staffs[i] == nullptr){
            staffs[i] = t;
            num_staff++;
            cout<< t->get_name() << " is managed by " << this->get_name()<< " now!" <<endl;
            break;
        }
    }


}

void Manager::calculate_salary()
{
    this->salary = 20000 + 2000 * this->num_staff;

}

void Manager::print_description() const 
{
    cout<< "ID: "<< this->id << ", Name: "<< this->name <<", Gender: "<< this->gender << ", Entry date: "<< 
    this->entry_date.year <<"-"<< this->entry_date.month <<"-"<< this->entry_date.day << ", Post: Manager, Group: " << enum_to_str(this->dept) <<endl;
}

void Manager::print_staff() const 
{
    cout<< this->get_name() << " is managing " << this->num_staff << " staffs: ";
    int i = 0;
    while (staffs[i] != nullptr)
    {
        if(staffs[i+1] == nullptr){
            cout<< staffs[i]->get_name() <<", "<<endl;
            break;
        }
        cout<< staffs[i]->get_name() << ", ";
        i++;
    }
}