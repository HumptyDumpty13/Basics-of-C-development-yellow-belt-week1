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

int GetDistinctRealRootCount(double a, double b, double c) {


  //// найдём дискриминант
  //  double D = B * B - 4 * A * C;
  //  int counter = 0;
  //  // если A равно нулю, то уравнение линейное: Bx + C = 0
  //  if (A == 0) {

  //      // Bx = -C => x = -C / B
  //      if (B != 0) {
  //          ++counter;
  //          //cout << -C / B << endl;
  //      }
  //      // если B равно нулю, корней нет

  //  }
  //  else if (D == 0) {  // случай с нулевым дискриминантом

  // // корень ровно один
  //      ++counter;
  //      //cout << -B / (2 * A) << endl;

  //  }
  //  else if (D > 0) {  // в случае с положительным дискриминантом корня два

  //      counter += 2;
  //      double r1 = (-B + sqrt(D)) / (2 * A);
  //      double r2 = (-B - sqrt(D)) / (2 * A);

  //     // cout << r1 << " " << r2 << endl;

  //  }
  //  return counter;
  //  // если дискриминант отрицателен, действительных корней нет
}

void TestRootCount() {
    AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0);
    AssertEqual(GetDistinctRealRootCount(1, 1, 1), 0);
    AssertEqual(GetDistinctRealRootCount(-1, -1, -1), 0);
    AssertEqual(GetDistinctRealRootCount(0, 5, 4), 1);
    AssertEqual(GetDistinctRealRootCount(0, -1, 1), 1);
    AssertEqual(GetDistinctRealRootCount(4, -5, 0), 2);
    AssertEqual(GetDistinctRealRootCount(1, 4, 4), 1);
    AssertEqual(GetDistinctRealRootCount(1, 0, 4), 0);
    AssertEqual(GetDistinctRealRootCount(1, 0, 1), 0);
    AssertEqual(GetDistinctRealRootCount(-1, 0, 0), 1);
}

int main() {
    TestRunner runner;
    runner.RunTest(TestRootCount, "TestRootCount");

    return 0;
}