#include "AFD.h"

#define MAX_STATE 100
#define MAX_SYMBOL 100

AFD::AFD()
{
    // constructor default
    a = new char [0];
    f= new bool [0];
    transition.resize (1);
    transition[0].resize (0, -1);
    nq = na = nt = 0;
    cout << "Default AFD constructed ! \n";
}

AFD::AFD(const int& x, const int& y)
{
    //ctor

    /**
    * Constructor DFA cu 2 parametrii
    * @param x reprezinta un integer, numarul de stari
    * @param y reprezinta un integer, dimensiunea alfabetului
    */

    if (x > MAX_STATE || y > MAX_SYMBOL)
    {
        cout << "OVERFLOW";
        exit (0);
    }
    a = new char [y+1];
    f = new bool [x];
    transition.resize (x);
    for (int i = 0; i < x; i++)
    {
        f[i] = false;
        transition[i].resize (y);
        // Initial matricea nu indica nici o stare
        for (int j = 0; j < y; j++)
            transition[i][j] = -1;
    }
    na  = y;
    nq  = x;
    nt  = 0;
    cout << "AFD constructed ! \n";
}

AFD::~AFD()
{
    //dtor
    delete[] f;
    delete[] a;
    for (int i = 0; i < nq; i++)
        transition[i].clear ();
    transition.clear ();
    nq = na = nt = 0;
    cout << "AFD destructed ! \n";
}

AFD::AFD(const AFD& afd)
{
    //copy constructor
    na = afd.na;
    nq = afd.nq;
    nt = afd.nt;
    strcpy ( a, afd.a);
    f = new bool (nq);
    transition.resize (nq);
    for (int i = 0; i < nq; i++ )

    for (int i = 0; i < nq; i++ )
    {
        transition [i].resize (na);
        f[i] = afd.f[i];
        for (int j = 0; j < na; j++)
            transition[i][j] = afd.transition[i][j];
    }
}


void AFD::check_if_well_defined ()
{
    //Verifica daca in DFA exista functii de iesire
    int ok_f = 0, ok_q0 = 0;
    for (int i = 0; i < nq; i++)
    {
        if (f[i] == true)
        {
            ok_f = 1;
            break;
        }
    }
    for (int i = 0; i < na; i++)
    {
        if (transition[0][i] != -1)
        {
            ok_q0 = 1;
            break;
        }
    }
    if (ok_f == 0 || ok_q0 == 0)
    {
        cout << "Eroare : DFA nu are stari finale! \n";
        exit(0);
    }
    cout << "DFA initializat corect" << "\n";
}

bool AFD::check_word(char c[])
{
    /**
    * Verifica daca un cuvant introdus apartine limbajului DFA-ului
    * @param c reprezinta cuvantul introdus
    */

    //Cuvantul Nul
    if (c == '\0')
    {
        if (f[0] == 1)
            return 1;
        return 0;
    }

    int len = strlen(c);
    int current_state = 0, poz;
    char *p;
    for (int i = 0; i < len; i++)
    {
        p = strchr( a, c[i]);
        if (p == NULL)
            return 0;

        poz = p - a;
        if (transition[current_state][poz] != -1)
            current_state = transition[current_state][poz];
        else
            return 0;
    }
    if (f[current_state] == 1)
        return 1;
    return 0;
}

AFD& AFD::operator=(const AFD& afd)
{
    if ( &afd == this)
        return *this;
    na = afd.na;
    nq = afd.nq;
    nt = afd.nt;
    strcpy ( a, afd.a);
    f = new bool (nq);
    transition.resize (nq);
    for (int i = 0; i < nq; i++)
    {
        transition [i].resize (na);
        f[i] = afd.f[i];
        for (int j = 0; j < na; j++)
            transition[i][j] = afd.transition[i][j];
    }
    return *this;
}

std::ostream& operator << (ostream& out, AFD& afd)
{
    //Functie de Afisare
    out << "DFA are " << afd.nq << " stari \n";
    out << "Alfabetul de intrare este : " << afd.a << "\n";
    out << "Matricea functiilor de tranzitie este : \n";
    for (int i = 0; i < afd.nq ; i++)
    {
        for (int j = 0; j < afd.na ; j++)
            out << afd.transition[i][j] << " ";
        out << "\n";
    }
    out << "Starile finale sunt : ";
    for (int i = 0; i < afd.nq; i++)
        if (afd.f[i] == true) out << i << " ";
    out << "\n";
    return out;
}
