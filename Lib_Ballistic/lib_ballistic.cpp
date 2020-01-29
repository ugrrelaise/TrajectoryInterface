#include "lib_ballistic.h"
#include <QDebug>
#include "Lib_Ballistic_global.h"

Lib_Ballistic::Lib_Ballistic()
{

}

int Lib_Ballistic::Calculate()
{

    int a = 10; int b= 5,c=0;

    c= a*b;
    return c;
}

void Lib_Ballistic::Test()
{
    qDebug() << "my_dll_15";
}

void Yazdir()
{
    Lib_Ballistic b;

    qDebug() << QString::number(b.Calculate());
}
