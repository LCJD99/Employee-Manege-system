#include "fmember.h"

QTextStream& operator<<( QTextStream & out , Sex s){
    int t;
    switch (s) {
    case Sex::man:
        t =0;
        break;
    case Sex::woman:
        t = 1;
        break;
    }
    out << t;
    return out;

}
QTextStream& operator>>( QTextStream & in , Sex &s){
    int t;
    in >> t;
    switch(t){
    case 0:
        s = Sex::man;
        break;
    case 1:
        s = Sex::woman;
        break;
    }
    return in;

}

Fmember::Fmember(){
    name = "";
    sex = Sex::man;
    age = 0;
    relationship = "";
}

Fmember::~Fmember(){}

void Fmember::SaveFmember(QTextStream &aStream){
    aStream <<  name << ' ' << sex << ' ' << age << ' ' << relationship << endl;
}
void Fmember::ReadFmember(QTextStream &aStream){
    aStream >>  name>> sex>>  age >> relationship ;
}

QString Fmember::getSex()
{
    switch (sex) {
    case Sex::man:
        return "男";

    case Sex::woman:
        return "女";

    }
}

void Fmember::setSex(QString str)
{
    if(str == "男") sex =Sex::man;
    else sex = Sex::woman;
}




