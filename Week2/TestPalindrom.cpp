#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

void AssertPalindrom(bool b, const string& hint) {
    AssertEqual(b, false, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        }
        catch (exception & e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        }
        catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

bool IsPalindrom(const string& str) {
    for (size_t i = 0; i < str.size() / 2; ++i) {
        if (str[i] != str[str.size() - i - 1]) {
            return false;
        }
    }
    return true;
}

void TestIsPalindrom() {
    Assert(IsPalindrom(""), "empty string");
    Assert(IsPalindrom("c"), "1symbol string");
    Assert(IsPalindrom(" "), "1space string");
    Assert(!IsPalindrom("gentleman"), "gentelman is not a palindrom");
    Assert(!IsPalindrom("Madam"), "Madam is not a palindrom");
    Assert(!IsPalindrom("madaM"), "madaM is not a palindrom");
    Assert(IsPalindrom("wasitacaroracatisaw"), "palindrom");
    Assert(!IsPalindrom("baobab"), "palindrom");
    Assert(!IsPalindrom("   AbA  "), "palindrom");
    Assert(!IsPalindrom("777778"), "PalindromeTest");
    Assert(IsPalindrom("777777"), "PalindromeTest");
    Assert(!IsPalindrom("wasitacarboracatisaw"), "not_palindrom");
    Assert(!IsPalindrom("madam ma dam"), "ignoring_spaces");
    Assert(!IsPalindrom(" madam"), "ignoring_first_symbol");
    Assert(!IsPalindrom(" #madam"), "ignoring_first_symbol");
    Assert(!IsPalindrom("leve"), "ignoring_last_symbol");
    Assert(!IsPalindrom("lleve"), "ignoring_last_symbol");
    Assert(!IsPalindrom("levee"), "ignoring_last_symbol");
    Assert(!IsPalindrom("  level   "), "ignoring_last_symbol");
    Assert(!IsPalindrom("   level  "), "ignoring_last_symbol");
}

int main() {
    TestRunner runner;
    runner.RunTest(TestIsPalindrom, "TestIsPalindrom");
    return 0;
}