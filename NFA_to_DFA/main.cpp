#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <set>
#include <utility>
#include <queue>

#include <AFN.h>
#include <AFD.h>
using namespace std;

ifstream fin ("AFN2.in");
ofstream fout ("AFD.out");

int main()
{
    int x, y;
    fin >> x >> y;
    AFN afn (x ,y);
    fin >> afn;
    cout << afn;
    //AFD afd, afd2 (x, y);
    //afd = afd2;
    //afd =
    afn.turn_into_AFD();
    //cout << afd;
return 0;
}
