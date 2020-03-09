#include <iostream>
#include <fstream>
using namespace std;
ifstream f("date.in");
ofstream g("date.out");
struct table {
    char *states;
    int nr;

};
struct tablenealoc {
    char states[1000];
    int nr;
};
int nr_s, nr_l, nr_sdfa, nr_finale, v_finaldfa[100], nr_finaledfa;
char vect_s[100], vect_l[100], vect_final[100];
table enfa[100][100], eclosure[100];
tablenealoc dfa[100][100];
void e_closure(table enfa[100][100],int nr_s,int nr_l,table eclosure[100]) {
    int i, j, k, poz, ok, m;
    int p;
    for (i = 0; i < nr_s; i++) {
             eclosure[i].nr = enfa[i][nr_l - 1].nr;
             eclosure[i].states = new char[eclosure[i].nr];
             for (k = 0; k < eclosure[i].nr; k++) {
                eclosure[i].states[k]=enfa[i][nr_l-1].states[k];
             }
             p = 0;
             while (p <= eclosure[i].nr) {

                    for (j = 0; j < nr_s; j++) {
                        if (vect_s[j] == eclosure[i].states[p]) {
                            poz=j;
                        }
                    }
                    for (k = 0; k < enfa[poz][nr_l - 1].nr; k++) {
                        if (enfa[poz][nr_l - 1].states[k] != '-') {
                            ok = 0;
                            for (m = 0; m < eclosure[i].nr  && ok == 0; m++) {
                                if(eclosure[i].states[m] == enfa[poz][nr_l - 1].states[k]) {
                                    ok = 1;
                                }
                            }
                            if (ok == 0) {
                                eclosure[i].states[eclosure[i].nr] = enfa[poz][nr_l - 1].states[k];
                                eclosure[i].nr++;
                            }
                         }

                     }
                     p++;
              }
              if(eclosure[i].states[eclosure[i].nr - 1] == '-') {
                   eclosure[i].states[eclosure[i].nr-1] = vect_s[i];
                   eclosure[i].nr = eclosure[i].nr - 1;
               }
               else eclosure[i].states[eclosure[i].nr] = vect_s[i];
              }



}
void ordonare(char s[1000], int nr)
{
    char aux;
    int i, j;
    for (i = 0; i < nr - 1; i++) {
         for(j = i + 1; j < nr; j++) {
            if (s[i] > s[j]) {
                aux = s[j];
                s[j] = s[i];
                s[i] = aux;
            }
         }
    }
}
void dfa_creaza(table enfa[100][100], int nr_s, int nr_l, table eclosure[100], tablenealoc dfa[100][100]) {
    int i, j, l, k, p, ok, m, poz, nr_sdfai, c, okf;
    l = 0;
    nr_sdfa = 0;
    dfa[nr_sdfa][0].nr = eclosure[0].nr + 1;
    for (i = 0; i <= eclosure[0].nr; i++) {
            dfa[nr_sdfa][0].states[i] = eclosure[0].states[i];
    }
    ordonare(dfa[0][0].states, dfa[0][0].nr);
    while(l <= nr_sdfa) {
        for (j = 1; j < nr_l; j++) {
            dfa[l][j].nr = 0;
            for (i = 0; i < dfa[l][0].nr; i++) {
                   for (k = 0; k < nr_s; k++) {
                      if (dfa[l][0].states[i] == vect_s[k]) {
                         poz = k;
                      }
                   }

                   for (k = 0; k < enfa[poz][j - 1].nr; k++) {
                          if(enfa[poz][j - 1].states[k] != '-') {
                                ok = 0;
                                for (p = 0;p < dfa[l][j].nr && ok == 0; p++) {
                                    if (dfa[l][j].states[p] == enfa[poz][j - 1].states[k]) {
                                        ok = 1;
                                    }
                                }
                                if (ok == 0) {
                                   dfa[l][j].states[dfa[l][j].nr] = enfa[poz][j - 1].states[k];
                                   dfa[l][j].nr++;
                               }
                           }

                 }
            }
        for (i = 0; i < dfa[l][j].nr; i++) {
                for (k = 0; k < nr_s; k++) {
                       if(dfa[l][j].states[i] == vect_s[k]) {
                          poz = k;
                       }
                }
                for (k = 0;k < eclosure[poz].nr; k++) {
                    ok = 0;
                    for (m = 0;m < dfa[l][j].nr && ok == 0; m++) {
                        if (dfa[l][j].states[m] == eclosure[poz].states[k]) {
                            ok = 1;
                        }
                    }
                    if (ok == 0) {
                        dfa[l][j].states[dfa[l][j].nr] = eclosure[poz].states[k];
                        dfa[l][j].nr++;

                     }
               }
        }
        ordonare(dfa[l][j].states, dfa[l][j].nr);
        nr_sdfai = nr_sdfa;
        okf = 1;
        for (k = 0; k <= nr_sdfai && okf == 1; k++) {
            if (dfa[k][0].nr == dfa[l][j].nr) {
                       ok = 0;
                       for (m = 0; m < dfa[l][j].nr; m++) {
                           if (dfa[k][0].states[m] != dfa[l][j].states[m]) {
                                 ok = 1;
                           }
                        }
             }
            if (ok == 0) {
                okf = 0;
            }
        }
        if (okf == 1) {
                nr_sdfa = nr_sdfa + 1;
                for (c = 0; c < dfa[l][j].nr; c++) {
                        dfa[nr_sdfa][0].nr=dfa[l][j].nr;
                }
                for (m = 0; m < dfa[l][j].nr; m++) {
                    dfa[nr_sdfa][0].states[m]=dfa[l][j].states[m];
                }
        }

        }


       l=l+1;
    }
}


int main()
{
    int i, j, k, p;
    f>>nr_s;
    for (i = 0; i < nr_s; i++) {
        f>>vect_s[i];
    }
    f>>nr_l;
    for (i = 0; i < nr_l; i++) {
        f>>vect_l[i];
    }
   g<<"STARILE E-AFN-ULUI SUNT: ";
   for (i = 0; i < nr_s; i++) {
        g<<vect_s[i]<<endl;

   }
   g<<"ALFABETUL ESTE :";
   for (i = 0; i < nr_l; i++) {
        g<<vect_l[i]<<endl;
   }
   g<<"STARILE FINALE SUNT :";
   f>>nr_finale;
   for (i = 0; i < nr_finale; i++) {
        f>>vect_final[i];
        g<<vect_final[i]<<" ";
    }
   g<<endl;
   for (i = 0; i < nr_s; i++) {
     for (j = 0; j < nr_l; j++) {
        f>>enfa[i][j].nr;
        if (enfa[i][j].nr == 0) {

            enfa[i][j].states = new char;
            enfa[i][j].states[0] = '-';
            enfa[i][j].nr = 1;
       }
       else {
          enfa[i][j].states = new char[enfa[i][j].nr];
          for (k = 0; k < enfa[i][j].nr; k++) {
                f>>enfa[i][j].states[k];
          }
      }
     }
  }
  for (i = 0; i < nr_s; i++) {
        for (j = 0; j < nr_l; j++) {
            for (k = 0; k < enfa[i][j].nr; k++) {

                g<<enfa[i][j].states[k]<<" ";
            }
            g<<" | ";
        }
       g<<endl;
  }
  e_closure(enfa, nr_s, nr_l, eclosure);
  for(i = 0; i < nr_s; i++) {
             g<<"e-closure "<<vect_s[i]<<" : ";
             for (j = 0; j <= eclosure[i].nr; j++)
             g<<eclosure[i].states[j]<<" ";
             g<<endl;
  }
  dfa_creaza(enfa, nr_s, nr_l, eclosure, dfa);
  g<<"TABELUL DFA :"<<endl;
  for (i = 0; i <= nr_sdfa; i++) {
      for (j = 0; j < nr_l; j++) {
          for (k = 0; k < dfa[i][j].nr;k++) {
                g<<dfa[i][j].states[k]<<" ";
          }
          g<<" | ";
      }
      g<<endl;
  }
  nr_finaledfa=0;

  for (i = 0; i <= nr_sdfa; i++) {
        for (j = 0; j < dfa[i][0].nr; j++) {
             for (p = 0; p < nr_finale; p++) {
                  if (vect_final[p] == dfa[i][0].states[j]) {
                        v_finaldfa[nr_finaledfa] = i;
                        nr_finaledfa++;

                    }
             }
        }

    }
   g<<"STARILE FINALE ALE DFA-ULUI SUNT : ";
   for (i = 0; i < nr_finaledfa; i++) {
        for (j = 0; j < dfa[v_finaldfa[i]][0].nr; j++) {
            g<<dfa[i][0].states[j];
        }
        g<<" ";
   }



    return 0;
}

