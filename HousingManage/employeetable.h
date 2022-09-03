#ifndef EMPLOYEETABLE_H
#define EMPLOYEETABLE_H
#include<QVector>
#include<QMap>
#include"employee.h"

class EmployeeTable
{
public:
    EmployeeTable();
    ~EmployeeTable();
    void CalculateRank();

    bool ReadEmployeeFromFile(const QString &aReadFileName);
    bool SaveEmployeeToFile(const QString &aSaveFileName);

    void AddEmployee(Employee & );
    Employee & GetEmployee(int index);
    int GetEmployeeNum();

    QMap<double,int> RankMap;
    QVector<double> Ranks;
    QVector<Employee> m_employees;

};

#endif // EMPLOYEETABLE_H
