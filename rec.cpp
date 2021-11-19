#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
using ll = long long;
using ld = long double;

#define debug1(x1) std::cout << #x1 << ": " << (x1) << std::endl;
#define debug2(x1, x2) std::cout << #x1 << ": " << (x1) << "	" << #x2 << ": " << (x2) << std::endl;
#define debug3(x1, x2, x3) std::cout << #x1 << ": " << (x1) << "	" << #x2 << ": " << (x2) << "	" << #x3 << ": " << (x3) << std::endl;

const double eps = 0.0001;

vector<pair<string, double>> recursion(vector<double> operands) {
    int n = (int) operands.size();

    debug1(n);
    cout << "operands is ";
    for(auto  x : operands) cout << x << " ";
    cout << endl;
    cout << "-----" << endl;

    if(n == 1) {
        int v = operands[0];
        return { { to_string(v), v} };      // initializer list
    }

    cout << "aaaa" << endl;

    vector<pair<string, double>> res;
    for(int i = 1; i < n; i++) {
        vector<double> l;
        vector<double> r;
        copy(operands.begin(), operands.begin() + i, back_inserter(l));
        copy(operands.begin() + i, operands.end(), back_inserter(r));

        cout << "l is " << endl;
        for(auto x : l) debug1(x);
        cout << endl;
        cout << "r is " << endl;
        for(auto x : r) debug1(x);
        cout << endl;
        cout << "---------" << endl;

        vector<pair<string, double>> left = recursion(l);
        vector<pair<string, double>> right = recursion(r);



        for(int left_i = 0; left_i < left.size(); left_i++) {
            for(int right_i = 0; right_i < right.size(); right_i++) {
                auto [ls, lv] = left[left_i];
                auto [rs, rv] = right[right_i];

                debug2(ls, lv);
                debug2(rs, rv);

                string sres = "(" + ls + " " + "+" + " " + rs + ")";
                double vres = lv + rv;
                res.push_back({sres, vres});
                sres = "(" + ls + " " + "-" + " " + rs + ")";
                vres = lv - rv;
                res.push_back({sres, vres});
                sres = "(" + ls + " " + "*" + " " + rs + ")";
                vres = lv * rv;
                res.push_back({sres, vres});
                sres = "(" + ls + " " + "/" + " " + rs + ")";
                vres = lv / rv;
                res.push_back({sres, vres});
            }
        }

        // return {{ "stop" , 0}};

    }

    return res;
}

int main()
{
    vector<double> in = {1, 2, 3, 4};
    auto data = recursion(in);

    for(auto d : data) {
        auto [s, v] = d;
        // debug2(s, v);

        if(abs(v - 10) < eps) {
            cout << s << " is 10." << endl;
        }

    }


    vector<double> L, R;
    for(int i = 1; i < in.size(); i++) {
        copy(in.begin(), in.begin() + i, back_inserter(L));
        copy(in.begin() + i, in.end(), back_inserter(R));
    }





    return 0;
}