#include "Workplace.h"
#include "exceptions.h"
#include <iostream>
#include <vector>
namespace mtm
{
    

    Employee* Workplace::FindEmployee(int employee_id)
    {
        for(std::set<Manager*, CompareManager> ::iterator i = managers.begin(); i !=
        managers.end(); ++i)
        {
            Employee* employee1 = (*i)->getEmployee(employee_id);
            if(employee1 != nullptr)
            {
                return employee1;
            }
        }
        return nullptr;
    }

    std::set<Manager*, CompareManager>& Workplace::getManagers()
    {
        return managers;
    }


    int Workplace::getManagersSalary() const
    {
        return salary_of_managers;
    }
    int Workplace::getWorkersSalary()const
    {
        return salary_of_employees;
    }
    std::string Workplace::getName()const
    {
        return name;
    }
    int Workplace::getId()const
    {
        return id;
    }
    
    void Workplace::hireManager(Manager* manager)
    {
        if((managers.find(manager)) != managers.end()) // managers is empty
        {
            throw ManagerAlreadyHired();
        }
        
        if(manager->getHired() == true)
        {
            throw CanNotHireManager();
        }

        managers.insert(manager);
        manager->setHired(true);
        manager->setSalary(this->salary_of_managers);
        manager->updateEmployeesSalaryAfterFire(salary_of_employees);
    }

    void Workplace::fireEmployee(int employee_id, int manager_id)
    {

        Manager temp_manager(manager_id,"a","a",1);
        if(managers.find(&temp_manager) == managers.end())
        {
            throw ManagerIsNotHired();
        }

        Manager* manager_in_workplace = *(managers.find(&temp_manager));
        if(manager_in_workplace->isEmployeeIn(employee_id) == true)
        {
            manager_in_workplace->findEmployeeAndDeduceSalary(employee_id, -(this->salary_of_employees));
        }
        manager_in_workplace->removeEmployee(employee_id);
    }

    void Workplace::fireManager(int manager_id)
    {    
        Manager temp_manager(manager_id,"a","a",1);
        if(managers.find(&temp_manager) == managers.end())
        {
            throw ManagerIsNotHired();
        }
        
        Manager* manager_in_workplace = *(managers.find(&temp_manager));
        manager_in_workplace->setHired(false);
        manager_in_workplace->updateEmployeesSalaryAfterFire(-(this->getWorkersSalary()));
        manager_in_workplace->setSalary(-(this->getManagersSalary()));

        managers.erase(&temp_manager);
    }

    std::ostream& operator<<(std::ostream& stream, const Workplace& work_place)
    {
        stream << "Workplace name - " << work_place.getName() ;
        
        if(work_place.managers.size() == 0)
        {
            stream <<std::endl;
            return stream;
        }

        stream << " Groups:" << std::endl;
        
        for(std::set<Manager*, mtm::CompareCitizens>::iterator i = work_place.managers.begin(); i !=
        work_place.managers.end(); ++i)
        {
            stream << "Manager ";
            (*i)->printLong(stream) ;
        } 
  
        return stream;
    }

    bool Workplace::isWorkingHere(int employee_id)
    {
        bool found = false;
        for(std::set<Manager*, CompareManager> ::iterator i = managers.begin(); i !=
        managers.end(); ++i)
        {
            found = (*i)->isEmployeeIn(employee_id);
        }
        return found;
    }


}