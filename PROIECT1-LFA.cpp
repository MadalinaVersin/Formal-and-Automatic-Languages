/*nrs-numarul de stari
  nrsf-numarul de stari finale;
  q0-starea initiala;
  nrl-numarul de litere ale alfabetului folosit ;
  nrt-numarul de tranzitii;
  nrc-numarul de siruri de caractere care se  citesc;
  */
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
ifstream f("fisier.in");
ofstream g("fisier.out");
int main()
{
    int q0, nrs, nrsf, nrl, i, q1, q2, ok, vl, p, l, poz, j;
    f>>nrs;
    f>>q0;
    f>>nrsf;

    int finale[nrsf];

    for (i = 0; i < nrsf; i++) {
        f>>finale[i];
    }

    f>>nrl;

    char litere[nrl];

    for ( i = 0; i < nrl; i++) {
        f>>litere[i];
        }



    int m[nrs][nrl], nrt;

    for (i = 0; i < nrs; i++) {
          for (j = 0; j < nrl; j++) {
                m[i][j]=-1;
          }
    }

    f>>nrt;

    char c;

    for (i = 0; i < nrt; i++) {
            f>>q1>>c>>q2;

             for (j = 0; j < nrl; j++) {
                    if (litere[j] == c) {
                            m[q1][j]=q2;
                    }
             }
        }


    int nrc;
    char cvid[2];

    f>>nrc;
    f.get();
    f.get(cvid,2);
    f.get();
    char sir[100];

    for (i = 0; i < nrc; i++) {
         q1 = q0;
         f.get(sir, 100);
         ok = 0;
         if (strcmp(sir, cvid) == 0) {
                for(j = 0; j < nrsf; j++) {
                    if(q0 == finale[j]) {
                           g<<sir<<" -true"<<endl;
                           ok = 1;
                       }
                 }
                if (ok == 0) {
                        g<<sir<<" -false"<<endl;
                }
           }
          else {

            for (j = 0; j < strlen(sir) && ok == 0; j++) {
                vl = 0;
                for (p = 0; p < nrl; p++) {
                    if (sir[j] == litere[p]) {
                       vl = 1;
                       poz = p;
                     }
                }
                if (vl == 0) {
                     ok = 1;
                  }
                if (m[q1][poz] == -1) {
                   ok = 1;
                 }
                q1 = m[q1][poz];
         }

         int verif = 0;
         if (j == strlen(sir) && ok == 0) {
                 verif = 0;

                 for (l = 0; l < nrsf; l++) {
                        if (q1 == finale[l]) {
                            g<<sir<<" -true"<<endl;
                            verif = 1;
                         }
                 }
                 if (verif == 0) {
                     g<<sir<<" -false"<<endl;
                 }
            }
         else {
                g<<sir<<" -false"<<endl;
         }


        }
       f.get();
     }



    return 0;
}
