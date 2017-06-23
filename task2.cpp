#include <iostream>
#include<algorithm>
#include <stack>
#include <string>
#include <cstdlib>
#include <string.h>
#include <sstream>
#include <cstdio>

using namespace std;

#define N 10000
#define M 10000

int la, lb;
int edit[M][M];
stack<string> S;



string ToStr(int i) {
    stringstream ss;
    ss<<i;
    return ss.str();
}

static int f[M][M] = {0};
static int patht[N][M] = {0};
static int patht2[N][M] = {0};
static string debruijn[M];
//static int adjacent[M][M] = {0};
static string adpath1[M];
static string adpath2[M];
static string new_adpath[N];
static int minimum[M] = {0};
static int minrow[M] = {0};
string resultb;

/*int distance(string a, string b)
{
    int la, lb;
    la = a.length();
    lb = b.length();

    for (int i = 0; i <= la; i++)
        f[i][0] = i;
    for (int j = 0; j <= lb; j++)
        f[0][j] = j;

    for (int i = 1; i <= la; i++) {
        for (int j = 1; j <= lb; j++) {
            f[i][j] = f[i - 1][j] + 1;
            if (f[i][j - 1] + 1 < f[i][j]) {
                f[i][j] = f[i][j - 1] + 1;
            }
            if (a[i - 1] == b[j - 1]) {
                if (f[i - 1][j - 1] < f[i][j]) {
                    f[i][j] = f[i - 1][j - 1];
                }
            } else {
                if (f[i - 1][j - 1] + 1 < f[i][j]) {
                    f[i][j] = f[i - 1][j - 1] + 1;
                }
            }
        }
    }
    return f[la][lb];
}*/

/*int connect(string a, string b)
{
    for (int i = 1, j = 0; i < a.length(); i++, j++) {
        if (a[i] != b[j])
            return 0;
    }
    return 1;
}*/

int main()
{
    clock_t start = clock();
    string a;
    int nodes;
    freopen("task2.in","r", stdin);
    //freopen("task2.out","w", stdout);
    cin >> a;
    cin >> nodes;
    for (int i = 0; i < nodes; i++) {
        cin >> debruijn[i];
    }
    /*for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            if (connect(debruijn[i], debruijn[j]) == 1) {
                adjacent[i][j] = 1;
                firstad[i][j] = 1;
            }
        }
    }*/

    /*for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            cout << adjacent[i][j];
        }
        cout << endl;
    }*/
    //cout << a << endl;
    int la = a.length();
    int lb = debruijn[0].length();
    string a_split[10000];
    for (int i = 0; i < la; i++) {
        a_split[i] =a.substr(0, i);
        //cout << a_split[i] << endl;
    }

    //int lb = debruijn[0].length();
    
    for (int i = 0; i < nodes; i++) {
        //cout << "patht " << i << endl;
        //cout << "QAQAQAQAQAQQ" << endl;
        //int lb;
        //lb = debruijn[i].length();

        for (int j = 0; j <= la; j++)
            f[j][0] = j;
        for (int k = 0; k <= lb; k++)
            f[0][k] = k;

        /*
            edit[i][j] description;
            0: from edit[i - 1][j]
            1: from edit[i][j - 1]
            2: from edit[i - 1][j - 1] (a[i] == b[j])
            3: from edit[i - 1][j - 1] (a[i] != b[j])
         */

        for (int j = 1; j <= la; j++) {
            for (int k = 1; k <= lb; k++) {
                f[j][k] = f[j - 1][k] + 1;
                if (f[j][k - 1] + 1 < f[j][k]) {
                    f[j][k] = f[j][k - 1] + 1;
                }
                if (a[j - 1] == debruijn[i][k - 1]) {
                    if (f[j - 1][k - 1] < f[j][k]) {
                        f[j][k] = f[j - 1][k - 1];
                    }
                } else {
                    if (f[j - 1][k - 1] + 1 < f[j][k]) {
                        f[j][k] = f[j - 1][k - 1] + 1;
                    }
                }
            }
            patht[i][j] = f[j][lb];
        }
        //cout << endl;
    }
    int count = 0;

    

    int rows = nodes;
    int loop = 0;

    while (1) {
        loop++;
        cout << loop << endl;
        int flag = 0;
        //count ++;
        //calculate rows
        //char new_node;

        if (loop == 1) {
            for (int i = 0; i < nodes; i++) {
                adpath1[i] = debruijn[i];
                //cout << adpath1[i] << endl;
            }
        }
        else {
            for (int i = 0; i < rows; i++) {
                adpath1[i] = adpath2[i];
                //cout << adpath1[i] << endl;
            }
        }
        //cout << "judge start" << endl;

        int new_rows = 0;
        for (int j = 0; j < rows; j++) {
            //cout << "judge " << j;
            for (int i = 0; i < nodes; i++) {
                
                if (adpath1[j].substr(loop, loop + lb - 1) == debruijn[i].substr(0, lb - 1)) {
                    new_adpath[new_rows++] = adpath1[j] + debruijn[i][lb - 1];
                    //cout << debruijn[i][lb - 1] << endl;
                    flag = 1;
                }
                
                /*if ((adpath1[j] + 'A').substr(loop, lb + loop) == debruijn[i]) {
                    new_adpath[new_rows++] = adpath1[j] + 'A';
                    flag = 1;
                }
                if ((adpath1[j] + 'C').substr(loop, lb + loop) == debruijn[i]) {
                    new_adpath[new_rows++] = adpath1[j] + 'C';
                    flag = 1;
                }
                if ((adpath1[j] + 'T').substr(loop, lb + loop) == debruijn[i]) {
                    new_adpath[new_rows++] = adpath1[j] + 'T';
                    flag = 1;
                }
                if ((adpath1[j] + 'G').substr(loop, lb + loop) == debruijn[i]) {
                    new_adpath[new_rows++] = adpath1[j] + 'G';
                    flag = 1;
                }*/
            }
        }
        //cout << "judge finished" << endl;
        if (flag == 0)
            break;
        for (int i = 0; i < new_rows; i++) {
            adpath2[i] = new_adpath[i];
            //cout << adpath[loop][i] << endl;
        }

        /*for (int i = 0; i < nodes; i++) {
            for (int j = 0; j < nodes; j++) {
                if (adjacent[i][j] == 1) {
                    //adpath[rows] = adpath[i]+ debruijn[j][debruijn[j].length() - 1];
                    //rows ++;
                    flag = 1;
                }
            }
        }

        if (flag == 0)
            break;*/

        /*int temp[M] = {0};
        for (int i = 0; i < nodes; i++) {
            for (int k = 0; k < nodes; k ++)
                temp[k] = 0;
            for (int j = 0; j < nodes; j++) {//当前行的每个元素
                for(int k = 0; k < nodes; k++) {
                    temp[k] += adjacent[i][j] * firstad[j][k];
                }
            }
            for (int k = 0; k < nodes; k++) {
                adtemp[i][k] = temp[k];
            }
        }*/
        /*for (int i = 0; i < nodes; i++) {
            for (int j = 0; j < nodes; j++) {
                adjacent[i][j] = adtemp[i][j];
                cout << adjacent[i][j];
            }
            cout << endl;
        }*/

        for (int i = 0; i < new_rows; i++) {
            patht2[i][0] = loop + lb;
        }
        int tempindex;
        //TODO: What is adpath
        for (int i = 0; i < new_rows; i++) {
            for (int j = 0; j < rows; j++) {
                if (adpath1[j] == adpath2[i].substr(0, adpath2[i].length() - 1))
                    tempindex = j;
            }
            for (int j = 1; j < la + 1; j++) {
                //patht2[i][j] = min(patht2[i][j - 1] + 1, patht[i][j] + 1, patht[i][j-1] + 1);
                patht2[i][j] = patht[tempindex][j] + 1;
                if (patht2[i][j - 1] + 1 < patht2[i][j]) {
                    patht2[i][j] = patht2[i][j - 1] + 1;
                }
                if (adpath2[i][adpath2[i].length() - 1] == a[j - 1]) {
                    if (patht[tempindex][j - 1] < patht2[i][j]) {
                        patht2[i][j] = patht[tempindex][j - 1];
                    }
                } else {
                    if (patht[tempindex][j - 1] + 1 < patht2[i][j]) {
                        patht2[i][j] = patht[tempindex][j - 1] + 1;
                    }
                }
            }
        }
        rows = new_rows;


        /*for (int i = 0; i < rows; i++) {
            for (int j = 1; j < a.length() + 1; j++) {
                cout << patht2[i][j];
            }
            cout << endl;
        }*/

        if (loop == 1) {
            minimum[0] = patht[0][la - 1];
            for (int i = 0 ;i < nodes; i++) {
                if (patht[i][la - 1] < minimum[0]) {
                    minimum[0] = patht2[i][la - 1];
                    minrow[0] = i;
                }
            }
        }
        minimum[loop] = patht2[0][la - 1];
        for (int i = 0 ;i < rows; i++) {
            if (patht2[i][la - 1] < minimum[loop]) {
                minimum[loop] = patht2[i][la - 1];
                minrow[loop] = i;
            }
        }
        //patht = patht2;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < la; j++) {
                patht[i][j] = patht2[i][j];
            }
        }
        int mini = minimum[0];
        if (minimum[loop] <= mini) {
            //mini = minimum[i];
            resultb = adpath2[minrow[loop]];
        }
    }
    //cout << a << endl;
    cout << resultb << endl;



    //a = 'AACCATCG';
    //resultb = 'ACGCATG';
    la = a.length();
    lb = resultb.length();

    //cout<<la<<endl;
    //cout<<lb<<endl;
    for (int i = 0; i <= la; i++)
        f[i][0] = i;
    for (int j = 0; j <= lb; j++)
        f[0][j]=j;

    /*
        edit[i][j] description;
        0: from edit[i - 1][j]
        1: from edit[i][j - 1]
        2: from edit[i - 1][j - 1] (a[i] == b[j])
        3: from edit[i - 1][j - 1] (a[i] != b[j])
     */

    for (int i = 1; i <= la; i++)
        for (int j = 1; j <= lb; j++)
        {
            f[i][j] = f[i - 1][j] + 1;
            edit[i][j] = 0;

            if (f[i][j - 1] + 1 < f[i][j])
            {
                f[i][j] = f[i][j - 1] + 1;
                edit[i][j] = 1;
            }

            if (a[i - 1] == resultb[j - 1])
            {
                if (f[i - 1][j - 1] < f[i][j])
                {
                    f[i][j] = f[i - 1][j - 1];
                    edit[i][j] = 2;
                }
            }
            else
            {
                if (f[i - 1][j - 1] + 1 < f[i][j])
                {
                    f[i][j] = f[i - 1][j - 1] + 1;
                    edit[i][j] = 3;
                }
            }
        }



    cout<<f[la][lb]<<endl;
    int i, j;
    i = la; j = lb;

    /*
        edit[i][j] description;
        0: from edit[i - 1][j] delete i
        1: from edit[i][j - 1] increas i
        2: from edit[i - 1][j - 1] (a[i] == b[j])  //no operation
        3: from edit[i - 1][j - 1] (a[i] != b[j])  // replace i with j
     */


    //S.clear();

    while (i > 0 || j > 0) {

        string str = "";

        if (edit[i][j] == 0) {
            //	str  = "DEL " + ToStr((j));
            str = "DEL " + ToStr(i - 1);
            S.push(str);
            i--;
            continue;
        }
        if (edit[i][j] == 1) {
            //	S.push("INS " + ToStr(j - 1)  + " " + B[j - 1]);
            S.push("INS " + ToStr(i)  + " " + resultb[j - 1]);
            j--;
        }
        if (edit[i][j] == 2) {
            i--;
            j--;
        }
        if (edit[i][j] == 3) {
            //	S.push("SUB " + ToStr((j - 1))+ " " + B[j - 1]);
            S.push("SUB " + ToStr((i - 1))+ " " + resultb[j - 1]);
            i--;
            j--;
        }
    }

    while (i > 0)
    {
        S.push("DEL " + ToStr(i - 1));
        //cout<<"Rest"<<endl;
        i--;
    }

    while (j > 0)
    {
        //S.push("INS " + ToStr(j - 1) + " " + B[j - 1]);
        S.push("INS " + ToStr(0) + " " + resultb[j - 1]);
        j--;
    }



    while (!S.empty()) {
        cout<<S.top()<<endl;
        S.pop();
    }
    clock_t end = clock();
    //cout << "Running time is : " << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;
    return 0;
}


