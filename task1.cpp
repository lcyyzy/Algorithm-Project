#include <iostream>
#include <stack>
using namespace std;

#define N 10000

struct edit
{
    enum {
        DEL,
        INS,
        SUB,
        NOP
    } type;

    char a;
    size_t pos;
    size_t length;
};

int main()
{
    string a, b;
    cin >> a >> b;

    int cost;
    size_t len_s = a.size();
    const char* s = a.c_str();
    size_t len_t = b.size();
    const char* t = b.c_str();

    static edit dd[N][N];
    edit* pe = NULL;
    /* base case: empty strings */
    for(size_t j=0; j<=len_t; j++) {
        pe = &dd[0][j];
        pe->length = j;
        pe->type = edit::INS;
        pe->a = t[j];
    }

    for(size_t i=0; i<=len_s; i++) {
        pe = &dd[i][0];
        pe->length = i;
        pe->type = edit::DEL;
        pe->a = t[i];
    }

    for(size_t j=1; j<=len_t; j++) {
        for(size_t i=1; i<=len_s; i++) {
            if (s[i-1] == t[j-1])
                cost = 0;
            else
                cost = 1;

            /* return minimum of delete char from s, delete char from t, and delete char from both */
            edit& r1 = dd[i - 1][j];
            edit& r2 = dd[i][j - 1];
            edit& r3 = dd[i - 1][j - 1];
            size_t s1, s2, s3;
            s1 = r1.length + 1;
            s2 = r2.length + 1;
            s3 = r3.length + cost;
            if(s1 <= s2 && s1 <= s3) {
                // r1
                pe = &dd[i][j];
                pe->type = edit::DEL;
                pe->pos = i-1;
                pe->a = s[i-1];
                pe->length = s1;
            } else if (s2 <= s1 && s2 <= s3) {
                // r2
                pe = &dd[i][j];
                pe->type = edit::INS;
                pe->pos = i;
                pe->a = t[j-1];
                pe->length = s2;
            } else {
                // r3
                pe = &dd[i][j];
                pe->length = s3;
                if(cost != 0) {
                    pe->type = edit::SUB;
                    pe->pos = i-1;
                    pe->a = t[j-1];
                } else {
                    pe->type = edit::NOP;
                }
            }

        }
    }
    size_t i, j;
    i = len_s; j = len_t;
    cout<< dd[i][j].length<<endl;
    stack<edit*> r;
    while (i > 0 || j > 0) {
        pe = &dd[i][j];
        switch (pe->type) {
            case edit::DEL:
                r.push(pe);
                i--;
                break;
            case edit::INS:
                r.push(pe);
                j--;
                break;
            case edit::NOP:
                i--;
                j--;
                break;
            case edit::SUB:
                r.push(pe);
                i--;
                j--;
                break;
        }
    }
    while (i > 0)
    {
        pe = &dd[i][j];
        r.push(pe);
        //cout<<"Rest"<<endl;
        i--;
    }
    while (j > 0)
    {
        pe = &dd[i][j];
        //S.push("INS " + ToStr(j - 1) + " " + B[j - 1]);
        r.push(pe);
        j--;
    }
    while (!r.empty()) {
        pe = r.top();
        switch (pe->type) {
            case edit::DEL:
                cout << "DEL "<< pe->pos << endl;
                break;
            case edit::INS:
                cout << "INS "<< pe->pos << ' ' << pe->a << endl;
                break;
            case edit::NOP:
                break;
            case edit::SUB:
                cout << "SUB "<< pe->pos << ' ' << pe->a << endl;
                break;
        }
        r.pop();
    }
    return 0;
}

