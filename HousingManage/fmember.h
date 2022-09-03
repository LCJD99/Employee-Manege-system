#ifndef FMEMBER_H
#define FMEMBER_H
#include <QTextStream>
#include <qstring.h>

enum class Sex {man , woman};
QTextStream& operator<<( QTextStream & out , Sex s);
QTextStream& operator>>( QTextStream & in , Sex &s);


class Fmember
{
public:
    Fmember();
    ~Fmember();

    void SaveFmember(QTextStream &aStream);
    void ReadFmember(QTextStream &aStream);

    QString getSex();
    void setSex(QString);


    QString name;
    Sex sex;
    int age;
    QString relationship;
};

#endif // FMEMBER_H
