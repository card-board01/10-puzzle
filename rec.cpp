#include <iostream>
#include <vector>
using namespace std;

#define debug1(x1) std::cout << #x1 << ": " << (x1) << std::endl;
#define debug2(x1, x2) std::cout << #x1 << ": " << (x1) << "	" << #x2 << ": " << (x2) << std::endl;
#define debug3(x1, x2, x3) std::cout << #x1 << ": " << (x1) << "	" << #x2 << ": " << (x2) << "	" << #x3 << ": " << (x3) << std::endl;

constexpr double eps = 0.0001;

// to print vector easily
template<typename T>
ostream &operator<<(ostream &os, std::vector<T> &vec) {
    os << "[";
    for(int i = 0; i < vec.size(); i++) {
        os << vec[i] << (i + 1 == vec.size() ? "" : " ");
    }
    os << "]";
    return os;
}

vector<pair<string, double>> recursion(vector<double> operands) {
    // debug1(operands);
    int n = (int) operands.size();

    if(n == 1) {
        int val = operands[0];
        string str = to_string(val);
        return { { str, val } };      // initializer list
    }

    vector<pair<string, double>> res;
    for(int i = 1; i < n; i++) {
        // decompose vector operands into l/r
        vector<double> l;
        vector<double> r;
        copy(operands.begin(), operands.begin() + i, back_inserter(l));
        copy(operands.begin() + i, operands.end(), back_inserter(r));

        // debug1(l);
        // debug1(r);
        // cout << "---------" << endl;

        vector<pair<string, double>> left = recursion(l);
        vector<pair<string, double>> right = recursion(r);

        // combine two factors
        for(int left_i = 0; left_i < left.size(); left_i++) {
            for(int right_i = 0; right_i < right.size(); right_i++) {
                auto [left_str, left_val] = left[left_i];
                auto [right_str, right_val] = right[right_i];

                string res_str;
                double res_val;

                // add
                res_str = "(" + left_str + " " + "+" + " " + right_str + ")";
                res_val = left_val + right_val;
                res.push_back({res_str, res_val});

                // subtract
                res_str = "(" + left_str + " " + "-" + " " + right_str + ")";
                res_val = left_val - right_val;
                res.push_back({res_str, res_val});

                // multiply 
                res_str = "(" + left_str + " " + "*" + " " + right_str + ")";
                res_val = left_val * right_val;
                res.push_back({res_str, res_val});

                // divide
                res_str = "(" + left_str + " " + "/" + " " + right_str + ")";
                res_val = left_val / right_val;
                res.push_back({res_str, res_val});
            }
        }
    }
    return res;
}

int main()
{
    vector<double> in = {1, 2, 3, 4};
    auto data = recursion(in);

    for(auto d : data) {
        auto [str, val] = d;
        if(abs(val - 10) < eps) {
            cout << str << " is 10." << endl;
        }
    }

    return 0;
}