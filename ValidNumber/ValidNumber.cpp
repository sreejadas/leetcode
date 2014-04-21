//============================================================================
// Valid Number
// Validate if a given string is numeric.
//
// Some examples:
// "0" => true
// " 0.1 " => true
// "abc" => false
// "1 a" => false
// "2e10" => true
// Note: It is intended for the problem statement to be ambiguous. You should
// gather all requirements up front before implementing one.
//
// Complexity:
// Regular Expression: depending on language
// Finite State Machine: O(n) time, O(1) space
//============================================================================

#include <iostream>
#include <cstring>
#include <regex>

using namespace std;

enum Type {
    Invalid,
    Space,
    Sign,
    Digit,
    Dot,
    Exp
};

// Invalid Space Sign Digit Dot Exp
int table[9][6] = {
    { -1, 0, 1, 2, 3, -1 },        // state 0: leading space
    { -1, -1, -1, 2, 3, -1 },      // state 1: first sign
    { -1, 8, -1, 2, 4, 5 },        // state 2: integer (123)
    { -1, -1, -1, 4, -1, -1 },     // state 3: first dot (.)
    { -1, 8, -1, 4, -1, 5 },       // state 4: decimal (123. or .123 or 123.123)
    { -1, -1, 6, 7, -1, -1 },      // state 5: e notation
    { -1, -1, -1, 7, -1, -1 },     // state 6: second sign
    { -1, 8, -1, 7, -1, -1 },      // state 7: exponent (123)
    { -1, 8, -1, -1, -1, -1 },     // state 8: trailing space
};

class Solution {
public:
    bool isNumber(const char *s) {
        return isNumber3(s);
    }

    bool isNumber1(const char *s) {
        Type type = Type::Invalid;
        int state = 0;
        for (; *s != '\0'; s++) {
            if (*s == ' ') type = Type::Space;
            else if (*s == '+' || *s == '-') type = Type::Sign;
            else if (*s >= '0' && *s <= '9') type = Type::Digit;
            else if (*s == '.') type = Type::Dot;
            else if (*s == 'e' || *s == 'E') type = Type::Exp;
            else return false;
            state = table[state][type];
            if (state == -1) return false;
        }
        return (state == 2 || state == 4 || state == 7 || state == 8);
    }

    bool isNumber2(const char *s) {
        regex r("^\\s*[+-]?(\\d+|\\d*\\.\\d+|\\d+\\.\\d*)([eE][+-]?\\d+)?\\s*$");
        return regex_match(s, r);
    }

    bool isNumber3(const char *s) {
        if (s == NULL) return false;
        skipWhiteSpaces(s);
        skipSign(s);
        bool b1 = skipDigits(s);
        skipDot(s);
        bool b2 = skipDigits(s);
        if (!b1 && !b2) return false;
        if (skipExp(s)) {
            skipSign(s);
            if (!skipDigits(s)) return false;
        }
        skipWhiteSpaces(s);
        return  *s == '\0';
    }

private:
    void skipWhiteSpaces(const char *& s) {
        while (*s != '\0' && isspace(*s)) s++;
    }

    void skipSign(const char *& s) {
        if (*s != '\0' && (*s == '+' || *s == '-')) s++;
    }

    void skipDot(const char *& s) {
        if (*s != '\0' && (*s == '.')) s++;
    }

    int skipDigits(const char *& s) {
        bool res = false;
        while (*s != '\0' && isdigit(*s)) s++, res = true;
        return res;
    }

    bool skipExp(const char *& s) {
        bool res = false;
        if (*s != '\0' && (*s == 'e' || *s == 'E')) s++, res = true;
        return res;
    }
};

int main() {
    Solution sol;
    cout << sol.isNumber("0") << "," << 1 << endl;
    cout << sol.isNumber(" 0.1 ") << "," << 1 << endl;
    cout << sol.isNumber("abc") << "," << 0 << endl;
    cout << sol.isNumber("1 a") << "," << 0 << endl;
    cout << sol.isNumber("2e10") << "," << 1 << endl;
    cout << sol.isNumber("6+1") << "," << 0 << endl;
    cout << sol.isNumber("3.") << "," << 1 << endl;
    cout << sol.isNumber(".3") << "," << 1 << endl;
    cout << sol.isNumber(".") << "," << 0 << endl;
    cout << sol.isNumber("..") << "," << 0 << endl;
    cout << sol.isNumber(". ") << "," << 0 << endl;
    cout << sol.isNumber("+.8") << "," << 1 << endl;
    return 0;
}