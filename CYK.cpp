#include <fstream>
#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <set>
using namespace std;
 
 
map<string, set<string> > id_to_prod;
map<string, set<string> > prod_to_id;
string initial;
 
void generate_grammar() {
    string line, production;
    int i = 0;
    while (getline(cin, line) && line.size() > 0) {
        stringstream ss(line);
        string id;
        ss >> id;
        if (!i++) initial = id;
        while (ss >> production) {
            id_to_prod[id].insert(production);
            prod_to_id[production].insert(id);
        }
    }
}
 
void print_grammar() {
    cout << "Gramática:\n";
    for (map<string, set<string> >::iterator it = id_to_prod.begin(); it != id_to_prod.end(); it++) {
        cout << it -> first << " -> ";
        int i = 0;
        for (set<string>::iterator it2 = (it -> second).begin(); it2 != (it -> second).end(); it2++) {
            if (i++) cout << " | ";
            cout << *it2;
        }
        cout << endl;
    }
}

void print_table(vector<vector<set<string> > > table) {
    for (int i = 0; i < table.size(); i++) {
        for (int j = 0; j < table[i].size(); j++) {
            for (set<string>::iterator it = table[i][j].begin(); it != table[i][j].end(); it++) {
                cout << *it << ",";
            }
            cout << "\t\t";
        }
        cout << '\n';
    }
}

int main () {
    string s;
    generate_grammar();
    print_grammar();
    cout << "Ingrese la cadena:\n";
    cin >> s;
    int n = s.size();
    vector<vector<set<string> > > table(n, vector<set<string> >(n, set<string>()));
 
    for (int i = 0; i < n; i++) { //ababa
        string x = "";
        x += s[i];
        set<string> res = prod_to_id[x];
        for (set<string>::iterator it = res.begin(); it != res.end(); it++) {
            table[i][i].insert(*it);
        }
    }
    string concat;
    for (int j = 1; j < n; j++) { //recorre en horizontal
        for (int i = j - 1; i >= 0; i--) { //
            for (int k = i; k < j; k++) { //
                set<string> a = table[i][k];
                set<string> b = table[k+1][j];
                // cout << "comparing: (" << i << "," << k << ") and (" << (k+1) << "," << j << ") to (" << i << "," << j << ")" << endl;
                if (!a.empty() && !b.empty()) {
                    for (set<string>::iterator it1 = a.begin(); it1 != a.end(); it1++) {
                        string p = *it1;
                        for (set<string>::iterator it2 = b.begin(); it2 != b.end(); it2++) {
                            string q = *it2;
                            string concat = p + q;
                            // cout << "concat = " << concat << endl;
                            set<string> concat_id = prod_to_id[concat];
                            for (set<string>::iterator it3 = concat_id.begin(); it3 != concat_id.end(); it3++) {
                                table[i][j].insert(*it3);
                            }
                           /* for (set<string>::iterator it3 = table[i][j].begin(); it3 != table[i][j].end(); it3++) {
                                cout <<  *it3 << ",";
                            } 
                            cout << endl; */
                        }
                    }
                }
            }
            /*
            cout << endl;
            */
        }
    }
    print_table(table);
    bool accepted = false;
    set<string> cadena = table[0][n-1];
    for (set<string>::iterator it = cadena.begin(); it != cadena.end(); it++) {
        accepted = (*it == initial);
        cout << *it << endl;
        if (accepted) {
            break;
        }
    }
    cout << (accepted ? "Cadena aceptada" : "Cadena rechazada") << endl;
    return 0;
}