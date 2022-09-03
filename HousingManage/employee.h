#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QTextStream>
#include <qstring.h>
#include<qvector.h>
#include<qdatetime.h>
#include"fmember.h"

enum class Degree{ highSchool , bachelor , master , doctor};
enum class Position {professor , associateProfessor , lecturer , assistantTeacher };

QTextStream& operator<<( QTextStream & out , Degree d);
QTextStream& operator>>( QTextStream & in , Degree &d);
QTextStream& operator<<( QTextStream & out ,Position p);
QTextStream& operator>>( QTextStream & in ,Position &p);
class Employee
{
public:
    Employee();
    ~Employee();
    Employee(const Employee & em);
    Employee& operator= (const Employee& em);

    void SaveEmployee(QTextStream &aStream);
    void ReadEmployee(QTextStream &aStream);

    float CaculateIntergral();
    int getWorkMonth();
    QString getPosition();
    QString getDegree();
    void setPosition(int);
    void setPosition(QString);
    void setDegree(int);
    void setDegree(QString);

    QString getIntergral();

    QString WorkerNumber;
    QString Name;
    int age;
    QDate hireDate;
    Degree degree;
    Position position;
    double area;
    QString address;
    QVector<Fmember> familyMember;

    double intergral;
    int rank;

};

#endif // EMPLOYEE_H
