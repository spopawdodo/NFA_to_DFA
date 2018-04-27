#ifndef AFD_H
#define AFD_H

#include <iostream>
#include <string.h>
#include <vector>
#include <iterator>

using namespace std;

class AFD
{
    public:
        // FUNCTII
        AFD();
        AFD(const int& x, const int& y);
        virtual ~AFD();
        AFD(const AFD& afd); //ctor copiere
        AFD& operator=(const AFD& afd); //supraincarcare =
        void check_if_well_defined();
        bool check_word (char c[]);
        friend std::ostream& operator << (ostream& out, AFD& afd);
        //COMPONENTELE AFD
        vector < vector < int > >  transition ;
        char* a; // Alfabetul de intrare
        bool* f; // Multimea Starilor Finale
        int nq; // Numarul de stari
        int na; // Numarul de cuvinte din alfabet
        int nt; // Numarul funtiilor de trazitie
    protected:
    private:

};

#endif // AFD_H
