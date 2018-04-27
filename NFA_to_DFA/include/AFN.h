#ifndef AFN_H
#define AFN_H

#include <iostream>
#include <cstring>
#include <string.h>
#include <set>
#include <vector>
#include <iterator>
#include <math.h>
#include <queue>

#include <AFD.h>

using namespace std;

class AFN
{
    public:
        AFN(const int& x, const int& y);
        virtual ~AFN();
        AFD& turn_into_AFD ( );//Functia de transformare AFN -> AFD
        friend std::istream& operator>>(std::istream& in,AFN& afn);
        friend std::ostream& operator<<(std::ostream& out,AFN& afn);
    protected:
    private:
         vector < vector < set < int > > > transition; //Functia de tranzitie
         char* a; // Alfabetul de intrare
         bool* f; // Multimea Starilor Finale
         int nq; // Numarul de stari
         int na; // Numarul de cuvinte din alfabet
         int nt; // Numarul funtiilor de trazitie
};

#endif // AFN_H
