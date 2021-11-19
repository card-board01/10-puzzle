#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <cctype>
#include <algorithm>
#include <iomanip>
using namespace std;
using ll = long long;
using ld = long double;

#define debug1(x1) std::cout << #x1 << ": " << (x1) << std::endl;
#define debug2(x1, x2) std::cout << #x1 << ": " << (x1) << "	" << #x2 << ": " << (x2) << std::endl;
#define debug3(x1, x2, x3) std::cout << #x1 << ": " << (x1) << "	" << #x2 << ": " << (x2) << "	" << #x3 << ": " << (x3) << std::endl;

const double eps = 0.001;


bool isOperator(string s) {
    return s == "+" || s == "-" || s == "*" || s == "/";
} 

struct Tree {
    int value;
    Tree *parent, *left, *right;
};

// calculate RPN 
double readRPN(string rpn) {
    stack<double> todo;
    stringstream ss(rpn);
    string s;
    while(getline(ss, s, ' ')) {
        if(!isOperator(s)) {
            double a = stod(s);
            todo.push(a);
            continue;
        }

        double b = todo.top(); todo.pop();
        double a = todo.top(); todo.pop();

        if(s == "+") todo.push(a + b);
        if(s == "-") todo.push(a - b);
        if(s == "*") todo.push(a * b);
        if(s == "/") todo.push(a / b);

    }

    double ans = todo.top();
    todo.pop();
    return ans;
}


double readRPN(queue<string> q) {
    int n = q.size();
    stack<double> todo;

    while(!q.empty()) {
        string s = q.front();
        q.pop();
        if(!isOperator(s)) {
            double a = stod(s);
            todo.push(a);
            continue;
        }
        double b = todo.top(); todo.pop();
        double a = todo.top(); todo.pop();

        if(s == "+") todo.push(a + b);
        if(s == "-") todo.push(a - b);
        if(s == "*") todo.push(a * b);
        if(s == "/") todo.push(a / b);
    }

    double ans = todo.top();
    todo.pop();
    return ans;
}


vector<string> generateRPN(vector<int> v, vector<string> o) {
    vector<string> rpn;
    string a = to_string(v[0]);
    string b = to_string(v[1]);
    string c = to_string(v[2]);
    string d = to_string(v[3]);

    string p = o[0];
    string q = o[1];
    string r = o[2];

    string s1 = a + " " + b + " " + p + " " + c + " " + q + " " + d + " " + r;
    string s2 = a + " " + b + " " + c + " " + p + " " + q + " " + d + " " + r;
    string s3 = a + " " + b + " " + p + " " + c + " " + d + " " + q + " " + r;
    string s4 = a + " " + b + " " + c + " " + p + " " + d + " " + q + " " + r;
    string s5 = a + " " + b + " " + c + " " + d + " " + p + " " + q + " " + r;

    rpn.push_back(s1);
    rpn.push_back(s2);
    rpn.push_back(s3);
    rpn.push_back(s4);
    rpn.push_back(s5);

    return rpn;
}

// RPN to formula
string decodeRPN(string rpn) {
    stack<string> todo;
    stringstream ss(rpn);
    string s;
    while(getline(ss, s, ' ')) {
        if(!isOperator(s)) {
            todo.push(s);
        }
        if(isOperator(s)) {
            string b = todo.top(); todo.pop();
            string a = todo.top(); todo.pop();

            string formula = "(" + a + " " + s + " " + b + ")";
            todo.push(formula);

        }
    }

    string res = todo.top();
    todo.pop();
    res.pop_back(); res.erase(0, 1);    // remove outermost (  )
    return res;
}


int main()
{
    // string in = "3 4 2 * 1 5 - / +";
    string in = "3 2 + 1 5 + *";
    in = "3 7 4 / - 8 *";
    queue<string> que;

    string s;
    stringstream ss{in};
    while(getline(ss, s, ' ')) {
        que.push(s);
    }

    // cout << in << endl;
    // double res = readRPN(que);
    // cout << res << endl;

    double goal = 10;
    vector<int> v;
    v = {1, 1, 9, 9};
    // v = {1, 2, 3, 4};

    for(int i = 0; i < 4; i++) {
        cin >> v[i];
        if(v[i] < 0 || 9 < v[i]) {
            cerr << "Invalid value. [0-9]" << endl;
            exit(EXIT_FAILURE);
        }
    }

    vector<string> o = {"+", "-", "*", "/"};
    sort(v.begin(), v.end());

    vector<string> ans;
    set<string> st;

    do {
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                for(int k = 0; k < 4; k++) {
                    vector<string> opr;
                    opr.push_back(o[i]);
                    opr.push_back(o[j]);
                    opr.push_back(o[k]);

                    vector<string> rpns;
                    rpns = generateRPN(v, opr);

                    for(string t : rpns) {
                        if(abs(readRPN(t) - goal) < eps) {
                            ans.push_back(t);
                            st.insert(t);
                        }
                    }

                }
            }
        }

    } while(next_permutation(v.begin(), v.end()));


    int n = ans.size();
    int m = st.size();
    if(n >= 2) cout << "There are " << n << " answers." << endl;
    if(n == 1) cout << "There is only one answer!!" << endl;
    if(n == 0) cout << "There is no answer." << endl;
    // cout << "st.size(); " << m << endl;
    int cnt = 0;
    bool all = false;
    for(string t : ans) {
        cout << t << "\t\t" << decodeRPN(t) << endl;
        cnt++;
        n--;

        if(cnt % 10 == 0 && n != 0 && !all) {
            cout << "Show more [y/n/all]: ";
            string input;
            cin >> input;
            if(input == "n" or input == "N") return 0;
            if(input == "all") all = true;
        }
    }

    return 0;
}