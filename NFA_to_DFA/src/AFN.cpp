#include "AFN.h"

#define MAX_STATE 100
#define MAX_SYMBOL 100

AFN::AFN (const int& x, const int& y)
{
    //ctor
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
    }
    na = y;
    nq = x;
    nt = 0;
    cout << "NFA constructed ! \n";
}

AFN::~AFN()
{
    //dtor
    delete[] f;
    delete[] a;
    for (int i = 0; i < nq; i++)
        transition[i].clear ();
    transition.clear ();
    nq = na = nt = 0;
    cout << "NFA destructed ! \n";
}

AFD& AFN::turn_into_AFD ( )
{
    //Initializarea dimensiunii si alfabetului AFD-ului
    queue < set <int> > states_to_check; // Coada in care stocam starile/multimile de stari ale AFN-ului
    vector < set <int> > states; // Starile AFD-ului
    set < int > current_state; //Starea curenta pe care o verificam
    states.resize (0);
    current_state.insert (0);
    states_to_check.push (current_state);
    int numar_stari = 0;
    while (!states_to_check.empty ())
    {
        current_state = states_to_check.front ();
        states_to_check.pop ();
        int ok = 0;
        // Verificam daca starea nu a fost deja introdusa in AFD
        for (vector <set < int > >:: iterator i = states.begin (); i != states.end (); i++)
            if (*i == current_state)
            {
                ok = 1; break;
            }
        if (ok == 1) continue;
        for (int j = 0; j < na; j++)
        {
                set < int > s; // Starea in care duce litera curenta
                for (set<int>::iterator i = current_state.begin(); i != current_state.end (); i++ )
                {
                    if ( transition[*i][j].size () == 0)
                        continue;
                    for (set <int> :: iterator k = transition[*i][j].begin (); k!= transition [*i][j].end (); k++)
                        s.insert (*k);
                }
                if ( ! s.empty ())
                states_to_check.push (s);
        }
        numar_stari++;
        states.push_back (current_state);
    }
    AFD temp (numar_stari, na);
    strcpy ( temp.a, a);
    temp.transition.resize (temp.nq);
    for (int i = 0; i < temp.nq; i++)
    {
        temp.transition[i].resize (temp.na);
    }
    cout << "Multimea noua de stari : \n";
    for ( vector < set < int > > :: iterator i = states.begin (); i != states.end (); i++)
    {
        set < int > s = *i;
        cout << "{ ";
        for (set <int> :: iterator j = s.begin (); j != s.end(); j++   )
            cout << *j << "  ";
        cout << "} \n";
    }
    /*
      Avem un vector cu multimea de stari ale AFD-ului rezultat
      Pe baza acestuia von crea noua matrice pentru functiile de tranzitie
      Pentru fiecare stare/ multime de stari din vector atribuim un nou indice in AFD
    */
    for (int it = 0; it < temp.nq; it++ )
    {
        current_state = states[it];
        int stare_finala = 0;
        for (int j = 0; j < na; j++)
        {
                set < int > s;
                for (set<int>::iterator i = current_state.begin(); i != current_state.end (); i++ )
                {
                    if (f[*i] == true) stare_finala = 1;
                    if ( transition[*i][j].size () == 0)
                        continue;
                    for (set <int> :: iterator k = transition[*i][j].begin (); k!= transition [*i][j].end (); k++)
                          s.insert (*k);
                }
                // Cautam starea s obtinuta in vectorul de stari si o inseram in AFD
                if ( s.empty ())
                    temp.transition[it][j] = -1;
                else
                {
                    for (int k = 0; k < temp.nq; k++)
                    if ( s == states[k])
                    {
                        temp.transition[it][j] = k;
                        temp.nt ++;
                        break;
                    }
                }
        }
        temp.f[it] = stare_finala;
    }
    cout << temp;
    temp.check_if_well_defined();
    cout << "aaa : " << temp.check_word("aaa") << "\n";
    cout << "abaaaa : " << temp.check_word ("abaaaa")<< "\n";
    cout << "a : " << temp.check_word ("a") << "\n";
    cout << "\n";
    return temp;
}

std::istream& operator>>(std::istream& in, AFN& afn)
{
    in >> afn.nt;
    in >> afn.a;
    for (int i=0; i < afn.nq; i++)
    {
        in >> afn.f[i];
    }
    int q1, q2, poz;
    char c, *p;
    for (int i = 1; i <=  afn.nt; i++)
    {
        in >> q1 >> c >> q2;
        p = strchr (afn.a , c);
        if (p == NULL)
        {
            cout << "Eroare la citire ! \n";
            exit(0);
        }
        poz = p - afn.a;
        afn.transition[q1][poz].insert (q2);
    }
    return in;
}

std::ostream& operator<< (ostream& out, AFN& afn)
{
    out << "AFN are " << afn.nq << " stari \n";
    out << "Alfabetul de intrare este : " << afn.a << "\n";
    out << "Matricea functiilor de tranzitie este : \n";
    for (int i=0; i< afn.nq; i++)
    {
        for (int j=0; j< afn.na; j++)
        {
            if (afn.transition[i][j].empty())
                out << "-1 \t";
            else
            {
                out << "{ ";
                for (set<int>::iterator k = afn.transition[i][j].begin (); k != afn.transition[i][j].end (); k++)
                    out << *k << " ";
                out << "}";
            }

        }
        out<<"\n";
    }
    out << "Starile finale sunt : \n";
    for (int i=0; i < afn.nq; i++)
        if (afn.f[i] == 1)
        out<< i<< "\n";
    return out;
}
