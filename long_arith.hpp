
#include <vector>
#include <string>
#include <iostream>
#include <sstream>


using namespace std;


namespace long_arith {

/* Utility method to process carry bit for addition
 *
 */
void sortout_carry_radix(int& v, int& carry, int radix) {
    if (v < radix) {
        carry = 0;
    }
    else if (v == radix) {
        carry = 1;
        v = 0;
    }
    else {
        carry = 1;
        v = v - radix;
    }
}

/* Adds two long numbers together
 *
 */
string add(const string& s1, const string& s2) {
    int carry = 0;

    const int radix = 10;
    int ps1 = s1.length() - 1;
    int ps2 = s2.length() - 1;

    string result = "";

    while(ps1 >= 0 && ps2 >= 0) {
        int v = int(s1[ps1] - '0') + int(s2[ps2] - '0') + carry;
        sortout_carry_radix(v, carry, radix);
        result = char(v + '0') + result;

        --ps1;
        --ps2;
    }

    while(ps1 >= 0) {
        int v = int(s1[ps1] - '0') + carry;
        sortout_carry_radix(v, carry, radix);
        result = char(v + '0') + result;

        --ps1;
    }

    while(ps2 >= 0) {
        int v = int(s2[ps2] - '0') + carry;
        sortout_carry_radix(v, carry, radix);
        result = char(v + '0') + result;

        --ps2;
    }

    if (carry > 0)
        result = "1" + result;

    return result;
}


/* Multiplys two long numbers
 *
 */
string mul(const string& s1, const string& s2) {

    int l1 = s1.length();
    int l2 = s2.length();

    vector<string> tmp;

    for (int i1 = 1; i1 <= l1; ++i1) {
        int idx1 = l1 - i1;
        for (int i2 = 1; i2 <= l2; ++i2) {
            int idx2 = l2 - i2;

            int v = int(s1[idx1] - '0') * int(s2[idx2] - '0');
            if (v) {
                stringstream ss;
                ss << v;
                for (int z = 0; z < (i1 - 1 + i2 - 1); ++z)
                    ss << '0';

                tmp.push_back(ss.str());
            }
        }
    }

    string result = "0";
    for (int i = 0; i < tmp.size(); ++i)
        result = add(result, tmp[i]);

    return result;
}


}   // namespace long_arith
