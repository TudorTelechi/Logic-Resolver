
/* Pentru functionarea perfecta a programului trebuie sa introducem
* expresia logica direct in codul acestuia (linia 120+ la moment
 @daca mai fac modificari o sa se schimbe@) ^^
 Mentiune >>>> Pentru efectuarea in ordine a operatiilor trebuie sa
 punem paranteze in functie de ordinea acestora
*/

#include <iostream>
#include <map>

using namespace std;

map<char, bool> extrageVariabilile(string expresie) {
  map<char, bool> multimeVariabile;
  for (int i = 0; i < expresie.size(); i++) {
    if (expresie[i] >= 'a' && expresie[i] <= 'z') {
      multimeVariabile[expresie[i]] = false;
    }
  }

  return multimeVariabile;
}

bool evalueaza(map<char, bool> &variabile, char *expresie) {
  int p = false;

  if (expresie[0] == '!') {
    expresie++;
    return !evalueaza(variabile, expresie);
  } else if (expresie[0] >= 'a' && expresie[0] <= 'z') {
    p = variabile[expresie[0]];
    expresie++;
  } else if (*expresie == '(') {
    expresie++;
    p = evalueaza(variabile, expresie);
    expresie++;
  }

  // al doilea operator
  if (*expresie == '|') {
    expresie++;

    bool q = evalueaza(variabile, expresie);
    return p || q;
  } else if (expresie[0] == '&') {
    expresie++;

    bool q = evalueaza(variabile, expresie);
    return p && q;
  } else if (expresie[0] == '-') {
    // -> implicatia
    expresie += 2;

    bool q = evalueaza(variabile, expresie);
    return !p || q;
  } else if (expresie[0] == '<') {
    // <->
    expresie += 3;

    bool q = evalueaza(variabile, expresie);
    return (!p || q) && (!q || p);
  }

  return p;
}

void ruleazaTabelaDeAdevar(map<char, bool> variabile, string expresie) {
  cout << expresie << endl << endl << endl;

  for (auto it = variabile.begin(); it != variabile.end(); it++)
    cout << it->first << " ";

  cout << endl;
  cout << "--------------------------------------------------------------------"
       << endl;
  int contor = 0;
  int contor1 = 0;

  for (int valoareVariabile = 0; valoareVariabile < (1 << variabile.size());
       valoareVariabile++) {
    int bit = 0;

    for (auto it = variabile.begin(); it != variabile.end(); it++) {
      it->second = valoareVariabile & (1 << bit++);
      cout << it->second << " ";
    }

    auto result = evalueaza(variabile, &expresie[0]);
    cout << "| " << (int)result << endl;
    contor1++;

    if (result == 1) {

      contor = contor + result;
    }
  }
  cout << "Numarul popozitiilor adevarate este : " << contor;
  cout << "\n";
  cout << "Numarul propozitiilor totale este : " << contor1;
  cout << "\n";

  if (contor == contor1) {
    cout << "TAUTOLOGIE ";
    cout << "\n";
  }
  if (contor != 0) {
    cout << "SATISFIABILA";
    cout << "\n";
  }
  if (contor != 0 && contor != contor1) {
    cout << "CONTINGENTA";
    cout << "\n";
  }
  if (contor == 0) {
    cout << "NESATISFIABILA";
  }
}

int main() {
  string expresie = "(p->(!q))";
  ruleazaTabelaDeAdevar(extrageVariabilile(expresie), expresie);
  return 0;
}
