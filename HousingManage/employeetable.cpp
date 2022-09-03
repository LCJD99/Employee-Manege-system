#include "employeetable.h"
#include <qfile.h>
#include <QTextStream>
#include <QTextCodec>
#include<QDebug>

EmployeeTable::EmployeeTable(){}
EmployeeTable::~EmployeeTable(){}

void EmployeeTable::CalculateRank()
{
    for(int i = 0 ; i < m_employees.size() ; ++i){
        m_employees[i].CaculateIntergral();
        qDebug() << m_employees[i].intergral;
        RankMap[m_employees[i].intergral] = i;
        Ranks.push_back(m_employees[i].intergral);
    }
    qSort(Ranks.begin(),Ranks.end(),qGreater<double>());
    for(int i = 0 ; i < Ranks.size() ; ++i){
        qDebug() << i  + 1<< ' ' << Ranks[i] << "index" << RankMap[Ranks[i]];
        m_employees[RankMap[Ranks[i]]].rank = i+1 ;
   }
    for(int i = 0 ; i < m_employees.size() ; ++i){
        qDebug() << "in" << m_employees[i].intergral << " r" << m_employees[i].rank;
    }
}

bool EmployeeTable::ReadEmployeeFromFile(const QString &aReadFileName)
{
    QFile aFile(aReadFileName);
    if(!aFile.exists())
        return false;
    if(!aFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    QTextStream aStream(&aFile);
    aStream.setCodec(QTextCodec::codecForName("system"));

    m_employees.clear();

    int m_number;
    aStream>>m_number;
    Employee temp_employee;
    if(m_number>0)
    {
        for(int i=0; i<m_number; i++)
        {
            temp_employee.ReadEmployee(aStream);
            m_employees.push_back(temp_employee);
        }
    }
    aFile.close();
    return true;
}

bool EmployeeTable::SaveEmployeeToFile(const QString &aSaveFileName)
{
    QFile aFile(aSaveFileName);
    if(!aFile.open(QIODevice::WriteOnly| QIODevice::Text))
        return false;
    QTextStream aStream(&aFile);
    aStream.setCodec(QTextCodec::codecForName("system"));

    aStream << m_employees.size() << endl << endl;
    for(int i = 0 ; i <  m_employees.size(); ++i)
        m_employees[i].SaveEmployee(aStream);
    aFile.close();
    return true;
}

void EmployeeTable::AddEmployee(Employee & employee1)
{
    m_employees.push_back(employee1);
}

Employee &EmployeeTable::GetEmployee(int index)
{
    return m_employees[index];
}

int EmployeeTable::GetEmployeeNum()
{
    return m_employees.size();
}
