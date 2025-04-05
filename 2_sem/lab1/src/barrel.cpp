#include "barrel.hpp"
#include <iostream>

Barrel::Barrel(double volume, double alch){
    m_volume = volume;
    m_alch = alch/100 * volume;
}

double Barrel::concentration(){
    return m_alch/m_volume*100;
}

void Barrel::pour_in(Barrel& barrel){
    double pour_alch = m_alch /m_volume; //т.к. переливаем лишь 1л, то доля = объему в кружке
    m_volume -= 1;
    m_alch -= pour_alch;
    barrel.m_volume += 1;
    barrel.m_alch += pour_alch;
}