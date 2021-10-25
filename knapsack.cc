#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iterator>
#include <windows.h>
#include <bits/stdc++.h>
using namespace std;

void knapSack(int n, int W, vector<int> values, vector<int> weights){
    //main processing of the algorithm
    int M[n+1][W+1];
    for(int i=0;i<=n;i++){
        for (int w=0;w<=W;w++){
            if (i==0)
                M[0][w] = 0;
            else if (w!=0)
                M[i][w] = -1;
        }
        M[i][0]=0;
    }
    for(int i=1;i<=n;i++){
        for (int w=1;w<=W;w++){
            if (weights[i]>w)
                M[i][w]=M[i-1][w];
            else
                M[i][w]=std::max(M[i-1][w],values[i]+M[i-1][w-weights[i]]);
        }
    }
    //end of main process
    cout << "\nRows: subset of items 1,...,i\nColumns: weight limit w\n\nKnapsack value table:\n\n   | ";
    int temp = -1,width = 5;

    for (int w=0;w<=W;w++){
            cout << w << " ";
            temp = w;  //next 4 lines format table nicely using white-spaces
            if (temp==0)
                temp = 1;
            width+=2+log10(temp);
            for (int j=floor(log10(temp));j<floor(log10(M[n][W]));j++){
                cout << " ";
                width++;
            }
    }
    cout << "\n";
    while(width>0){
        cout<<"-";
        width--;
    }
    cout << "\n";
    for(int i=0;i<=n;i++){  // print out knapsack value table
        cout << " " << i << " | ";
        for (int w=0;w<=W;w++){
            cout << M[i][w] << " ";
            temp = M[i][w];  //next 4 lines format table nicely using whitespaces
            if (temp==0)
                temp = 1;
            for (int j=floor(log10(temp));j<floor(log10(M[n][W]));j++)
                cout << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    string sb = "{";
    int i=n,w=W,listLen=0;
    //calculate the items that achieve optimal value
    while(i>0){
        cout << "(" << i << ", " << w << ") -> ";
        if (weights[i]<=w)
            if (M[i-1][w]<M[i][w]+M[i-1][weights[i]]){
                if (listLen > 0)
                    sb.append(", " + to_string(i));
                else
                    sb.append(to_string(i));
                w-=weights[i];
                listLen++;
            }
        i--;
    }
    cout << "(0, 0)\n";
    sb.append("}");
    cout << "\nA value of " << M[n][W] << " can be achieved using item(s) " << sb << "\n\n";
}

int main()
{
    int j=0,W=0;
    vector<int> input;
    ifstream file("knapsack.txt");
    int n = std::count(std::istreambuf_iterator<char>(file),
             std::istreambuf_iterator<char>(), '\n')+1;
    file.clear();
    file.seekg(0, file.beg);
    string str[n+1], temp="";

    cout << ".___..  ..___  .  ..  ..__..__  __..__. __ .  .  .__ .__ .__..__ .   .___.  ."
"\n  |  |__|[__   |_/ |\\ |[__][__)(__ [__]/  `|_/   [__)[__)|  |[__)|   [__ |\\/|"
"\n  |  |  |[___  |  \\| \\||  ||   .__)|  |\\__.|  \\  |   |  \\|__|[__)|___[___|  |\n"
"\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@BQQ#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
"\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@6   QW   #@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
"\n@@@@@@@@@@@@@@@@@@@@@@@@@@@B   @@@@    8@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
"\n@@@@@@@@@@@@@@@@@@@@@@@@@@@DhSDqt1L]v***v]xxv?rrr?v7ltP8@@@@@@@@@@@@@@@@@@@@@"
"\n@@@@@@@@@@@@@@@@@@@@@@@#gm]!-                           <#@@@@@@@@@@@@@@@@@@@"
"\n@@@@@@@@@@@@@@@@@@@@6c^.                                 ~B@@@@@@@@@@@@@@@@@@"
"\n@@@@@@@@@@@@@@@@@DY-                                      `Q@@@@@@@@@@@@@@@@@"
"\n@@@@@@@@@@@@@@@@G=!x?,                                     ~0@@@@@@@@@@@@@@@@"
"\n@@@@@@@@@@@@@@@Q=_,,~Yl^`                                   .d@@@@@@@@@@@@@@@"
"\n@@@@@@@@@@@@@@0^-___,,=vJ;                                  `-N@@@@@@@@@@@@@@"
"\n@@@@@@@@@@@@@P_..--___,,~t?                 ``..---..`````````,Q@@@@@@@@@@@@@"
"\n@@@@@@@@@@@@Q_`....--___,^m-         `.,\"\"\"\"\"\"\",__,,\"\"::::,.```~#@@@@@@@@@@@@"
"\n@@@@@@@@@@@@q`````...---_,Lc`    .'::'-```````````````````._::::r#@@@@@@@@@@@"
"\n@@@@@@@@@@@@q ``````...---^hx``,:\".``````````````````````````````Y@@@@@@@@@@@"
"\n@@@@@@@@@@@@S   ``````....\"xmc*_`````````````````````````````````.G@@@@@@@@@@"
"\n@@@@@@@@@@@@P     ``````..,~wXhr``````````````````_vv,````````````,B@@@@@@@@@"
"\n@@@@@@@@@@@@w       `````._.?oI0<````````````````!  _ !````````````0@@@@@@@@@"
"\n@@@@@@@@@@@@c         ```._`-xwDR*```````````````\\ |M| ]``````````^#@@@@@@@@@"
"\n@@@@@@@@@@@@0oclYxr~-`   -.```=WD0V_```````````````._.``````````.v#@@@@@@@@@@"
"\n@@@@@@@@@@@@0eoztzztft1]|*`````cKdMe7*=.``````````````````````,^t@@@@@@@@@@@@"
"\n@@@@@@@@@@@@c-:~^^rLIfott1   ``lzwY:*xJwVl]v?r*^;~!====!;*|Yx7Lrc@@@@@@@@@@@@"
"\n@@@@@@@@@@@@l       `-=*?*    `VtXv```._:~^*rr??vx]7YYLxoaeq|;^^7@@@@@@@@@@@@"
"\n@@@@@@@@@@@@Y            .    -htP*`````...--____,,\"\"::=?hzm1~;<*Q@@@@@@@@@@@"
"\n@@@@@@@@@@@@r            .    =qtS^```````...--____,,\"\":;Pztz!~~;q@@@@@@@@@@@"
"\n@@@@@@@@@@@Q.            .    !qtS=   ```````...--___,,,^fttPr!!~c@@@@@@@@@@@"
"\n@@@@@@@@@@@]             .    ;GtP\"     ```````...--____vttzfl==!7@@@@@@@@@@@"
"\n@@@@@@@@@@0`             .    vozP\"       ```````...---_xtttw1::=?@@@@@@@@@@@"
"\n@@@@@@@@@@r             ``   `wttP\"          ``````...--]ttzax\"\":*#@@@@@@@@@@"
"\n@@@@@@@@@d              .    |ettP\"           ```````...Yttze=,,,?@@@@@@@@@@@"
"\n@@@@@@@@@]             .    `wtttf_              ``````:fttf|___,w@@@@@@@@@@@"
"\n@@@@@@@@@?            .`    *mztXv                 ```.Jtte?..-:o#@@@@@@@@@@@"
"\n@@@@@@@@@7           `.    `Vttzc`                   `lXze?``:t#@@@@@@@@@@@@@"
"\n@@@@@@@@@@0J:        .    .cItzw_                   `cItXv;LZ#@@@@@@@@@@@@@@@"
"\n@@@@@@@@@@@@@a=`    ``   -JwtI2:     `,<?x}cVJtIhPZ6R####@@@@@@@@@@@@@@@@@@@@"
"\n@@@@@@@@@@@@@@@#gS7_    ;2tzIx`  ,?tD#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
"\n@@@@@@@@@@@@@@@@@@@#V**oSaKdz]VGQ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << " ";
    Sleep(5000);
    if (file.is_open()) {
        while (std::getline(file, str[j])) {
            stringstream ss (str[j]);
            std::istream_iterator<std::string> begin(ss);
            std::istream_iterator<std::string> end;
            std::vector<std::string> vstrings(begin, end);
            std::copy(vstrings.begin(), vstrings.end(), std::ostream_iterator<std::string>(std::cout, ""));
            system("cls");
            for(int i=0; i<vstrings.size(); i++){
                input.push_back(std::stoi(vstrings[i]));
            }
            j++;
        }
        file.close();
    }
    int k = input.size()/2;
    int maxVal = k;
    std::vector<int> weights, values;
    values.push_back(0);
    weights.push_back(0);
    for (int i = 0; i < input.size(); i++){
        maxVal = max(maxVal,input[i]);
        if(i<k)
            values.push_back(input[i]);
        else if (i<input.size()-1)
            weights.push_back(input[i]);
        else
            W=input[i];
    }
    floor(log10(maxVal));
    cout << "Items:   {";
    for (int i = 1; i < k; i++){
        cout << i << ", ";
        for (int j=floor(log10(i));j<floor(log10(maxVal));j++)
            cout << " ";
    }
    cout << k << "}\nValues:  {";
    for (int i = 1; i < k; i++){
        cout << values[i] << ", ";
        for (int j=floor(log10(values[i]));j<floor(log10(maxVal));j++)
            cout << " ";
    }
    cout << values[k] << "}\nWeights: {";
    for (int i = 1; i < k; i++){
        cout << weights[i] << ", ";
        for (int j=floor(log10(weights[i]));j<floor(log10(maxVal));j++)
            cout << " ";
    }
    cout << weights[k] << "}\nWeight limit = " << W << ", Number of items = " << k << "\n\n";
    knapSack(k,W,values,weights);
    return 0;
}
