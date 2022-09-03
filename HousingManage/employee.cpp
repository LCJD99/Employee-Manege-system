#include "employee.h"
#include<QDebug>
QTextStream& operator<<(QTextStream & out , Degree d){
    int t;
    switch (d) {
    case Degree::highSchool:
        t =0;
        break;
    case Degree::bachelor:
        t = 1;
        break;
    case Degree::master:
        t =2;
        break;
    case Degree::doctor:
        t =3;
        break;
    }
    out << t;
    return out;
}

QTextStream& operator>>(QTextStream & in , Degree &d){
    int t;
    in >> t;
    qDebug() << "degree" << t;
    switch (t) {
    case 0:
        d = Degree::highSchool;
        break;
    case 1:
        d = Degree::bachelor;
        break;
    case 2:
        d = Degree::master;
        break;
    case 3:
        d = Degree::doctor;
        break;
    }
    return in;
}

QTextStream& operator<<(QTextStream & out ,Position p){
    int t;
    switch (p) {
    case Position::professor:
        t =0;
        break;
    case Position::associateProfessor:
        t = 1;
        break;
    case Position::lecturer:
        t =2;
        break;
    case Position::assistantTeacher:
        t =3;
        break;
    }
    out << t;
    return out;
}
QTextStream& operator>>( QTextStream & in ,Position &p){
    int t;
    in >> t;
    qDebug() << "Position" << t;
    switch (t) {
    case 0:
        p = Position::professor;
        break;
    case 1:
        p = Position::associateProfessor;
        break;
    case 2:
        p = Position::lecturer;
        break;
    case 3:
        p = Position::assistantTeacher;
        break;
    }
    return in;
}

Employee::Employee(){
    WorkerNumber= "";
    Name = "";
    hireDate = QDate(1900 , 1 ,1);
    degree = Degree::highSchool;
    position = Position::assistantTeacher;
    area = 0;
    address = "1";
    intergral = -1;
    rank = -1;
}

Employee::~Employee(){}

Employee::Employee(const Employee & em){
    WorkerNumber = em.WorkerNumber;
    Name = em.Name;
    age = em.age;
    hireDate = em.hireDate;
    degree = em.degree;
    position = em.position;
    area = em.area;
    address = em.address;
    familyMember = em.familyMember;
    intergral = em.intergral;
    rank = em.rank;
}
Employee& Employee::operator= (const Employee& em){
    WorkerNumber = em.WorkerNumber;
    Name = em.Name;
    age = em.age;
    hireDate = em.hireDate;
    degree = em.degree;
    position = em.position;
    area = em.area;
    address = em.address;
    familyMember = em.familyMember;
    intergral = em.intergral;
    rank = em.rank;
    return *this;
}

void Employee::SaveEmployee(QTextStream &aStream){
    aStream << WorkerNumber<<'\n';
    aStream << Name<<'\n';
    aStream << age<<'\n';\
    aStream << hireDate.year()<<" "<<hireDate.month()<<" "<<hireDate.day()<<'\n';
    aStream << degree<<'\n';
    aStream << position<<'\n';
    aStream << area<<'\n';
    aStream << address<<'\n';
    aStream << familyMember.size() << endl;
    for(int i = 0 ; i < familyMember.size() ; ++i){
        familyMember[i].SaveFmember(aStream);
    }
}
void Employee::ReadEmployee(QTextStream &aStream){

    aStream >> WorkerNumber ;
    qDebug() << "WorkerNumber" << WorkerNumber;
    aStream >> Name ;
    qDebug() << "Name" << Name;
    aStream >> age ;
    int year, month, day;
    aStream>>year>>month>>day;
    hireDate.setDate(year, month, day);
    qDebug() << "Y" << year << "M" << month << "D" << day;
    aStream >> degree ;
    qDebug() << "degree" << getDegree();
    aStream >> position ;
    qDebug() << "position" << getPosition();
    aStream >> area >> address;
    qDebug() << "area" << area ;
    qDebug() << "address" << address;
    int s1;
    aStream >> s1;
    qDebug() << "size" << s1;
    familyMember.clear();
    familyMember.resize(s1);
    for(int i = 0 ; i < s1 ; ++i){
        familyMember[i].ReadFmember(aStream);
    }

}

float Employee::CaculateIntergral()
{
    float ret = 0;
    switch (position) {
    case Position::professor :
        ret += 20;
        break;
    case Position::associateProfessor :
        ret += 16;
        break;
    case Position::lecturer :
        ret += 12;
        break;
    case Position::assistantTeacher :
        ret += 8;
        break;
    }

    int t = getWorkMonth();
    ret += t * 0.0416;

    ret += age * 0.1;

    switch(degree){
    case Degree::bachelor:
        ret+=2;
        break;
    case Degree::master:
        ret += 3.25;
        break;
    case Degree::doctor:
        ret += 4.5;
        break;
    default:
        break;
    }

    ret += area * 0.1;

    ret += familyMember.size() * 2;

    intergral = ret;
    return ret;

}

int Employee::getWorkMonth()
{
    QDate d1 = QDate::currentDate();
    int d = hireDate.daysTo(d1);
    return d / 30;
}

QString Employee::getDegree()
{
    switch (degree) {
    case Degree::highSchool:
        return "高中";

    case Degree::bachelor:
        return "本科";

    case Degree::master:
        return "硕士";

    case Degree::doctor:
        return "博士";

    }
}

QString Employee::getPosition()
{
    switch (position) {
    case Position::professor:
        return "教授";

    case Position::associateProfessor:
        return "副教授";

    case Position::lecturer:
        return "讲师";
    case Position::assistantTeacher:
        return "助教";
    }
}

void Employee::setPosition(int p)
{
    switch (p) {
    case 0:
        position = Position::professor;
        break;
    case 1:
        position = Position::associateProfessor;
        break;
    case 2:
        position = Position::lecturer;
        break;
    case 3:
        position = Position::assistantTeacher;
        break;
    }
}

void Employee::setPosition(QString p)
{
    if(p == "教授") position = Position::professor;
    else if(p == "副教授" ) position = Position::associateProfessor;
    else if(p == "讲师") position = Position::lecturer;
    else if(p == "助教") position = Position::assistantTeacher;
}

void Employee::setDegree(int i)
{
    switch (i) {
    case 0:
        degree = Degree::highSchool;
        break;
    case 1:
        degree = Degree::bachelor;
        break;
    case 2:
        degree = Degree::master;
        break;
    case 3:
        degree = Degree::doctor;
        break;
    }
}

void Employee::setDegree(QString d)
{
    if(d == "高中") degree = Degree::highSchool;
    else if(d == "本科" ) degree = Degree::bachelor;
    else if(d == "硕士") degree = Degree::master;
    else if(d == "博士") degree = Degree::doctor;
}

QString Employee::getIntergral()
{
    return QString::number(intergral);
}
