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




void TestSameYear() {
    {
        Person person;
        person.ChangeFirstName(1999, "Ivan");
        person.ChangeLastName(1990, "Ivanov");
        person.ChangeFirstName(1999, "Petr");
        AssertEqual(person.GetFullName(1999), "Petr Ivanov");
    }
    {
        Person person;
        person.ChangeLastName(1900, "Ivanov");
        person.ChangeFirstName(1900, "Ivan");
        person.ChangeLastName(1900, "Petrov");
        AssertEqual(person.GetFullName(1900), "Ivan Petrov");
    }
}
void TestIncognito() {
    {
        Person person;
        AssertEqual(person.GetFullName(1999), "Incognito");
    }
    {
        Person person;
        person.ChangeFirstName(1999, "Ivan");
        person.ChangeLastName(1990, "Ivanov");
        AssertEqual(person.GetFullName(1850), "Incognito");
    }
    {
        Person person;
        person.ChangeFirstName(1990, "Ivan");
        person.ChangeLastName(1990, "Ivanov");
        AssertEqual(person.GetFullName(1989), "Incognito");
    }
    {
        Person person;
        person.ChangeFirstName(2010, "Ivan");
        person.ChangeFirstName(2006, "Petr");
        person.ChangeLastName(2002, "Ivanov");
        person.ChangeLastName(1990, "Petrov");
        AssertEqual(person.GetFullName(1981), "Incognito");
    }
}
void TestLastName() {
    {
        Person person;
        person.ChangeLastName(1990, "Ivanov");
        AssertEqual(person.GetFullName(1990), "Ivanov with unknown first name");
    }
    {
        Person person;
        person.ChangeLastName(1990, "Ivanov");
        AssertEqual(person.GetFullName(1999), "Ivanov with unknown first name");
    }
    {
        Person person;
        person.ChangeLastName(1990, "Ivanov");
        person.ChangeLastName(1999, "Petrov");
        AssertEqual(person.GetFullName(1999), "Petrov with unknown first name");
    }
    {
        Person person;
        person.ChangeLastName(1990, "Ivanov");
        person.ChangeLastName(2002, "Petrov");
        AssertEqual(person.GetFullName(2001), "Ivanov with unknown first name");
    }
}

void TestFirstName() {
    {
        Person person;
        person.ChangeFirstName(1990, "Ivan");
        AssertEqual(person.GetFullName(1990), "Ivan with unknown last name");
    }
    {
        Person person;
        person.ChangeFirstName(1990, "Ivan");
        AssertEqual(person.GetFullName(1999), "Ivan with unknown last name");
    }
    {
        Person person;
        person.ChangeFirstName(1990, "Ivan");
        person.ChangeFirstName(2002, "Petr");
        AssertEqual(person.GetFullName(2001), "Ivan with unknown last name");
    }
}

void TestAll() {
    {
        Person person;
        person.ChangeFirstName(1934, "Ivan");
        person.ChangeLastName(1940, "Ivanov");
        AssertEqual(person.GetFullName(1940), "Ivan Ivanov");
    }
    {
        Person person;
        person.ChangeFirstName(1990, "Ivan");
        person.ChangeFirstName(2006, "Petr");
        person.ChangeLastName(1940, "Ivanov");
        person.ChangeLastName(1954, "Petrov");
        AssertEqual(person.GetFullName(2010), "Petr Petrov");
    }
    {
        Person person;
        person.ChangeFirstName(1990, "Ivan");
        person.ChangeFirstName(2006, "Petr");
        person.ChangeLastName(1940, "Ivanov");
        person.ChangeLastName(1954, "Petrov");
        AssertEqual(person.GetFullName(2006), "Petr Petrov");
    }
    {
        Person person;
        person.ChangeFirstName(2010, "Ivan");
        person.ChangeFirstName(2006, "Petr");
        person.ChangeLastName(2002, "Ivanov");
        person.ChangeLastName(1990, "Petrov");
        AssertEqual(person.GetFullName(2006), "Petr Ivanov");
    }
    {
        Person person;
        person.ChangeFirstName(1990, "Ivan");
        person.ChangeFirstName(2006, "Petr");
        person.ChangeFirstName(1635, "Andrey");
        person.ChangeLastName(1940, "Ivanov");
        person.ChangeLastName(1954, "Petrov");
        person.ChangeLastName(1657, "Andreev");
        AssertEqual(person.GetFullName(1700), "Andrey Andreev");
    }


}


int main() {
    TestRunner runner;
    runner.RunTest(TestSameYear, "TestSameYear");
    runner.RunTest(TestIncognito, "TestIncognito");
    runner.RunTest(TestFirstName, "TestFirstName");
    runner.RunTest(TestLastName, "TestLastName");
    runner.RunTest(TestAll, "TestAll");
    // добавьте сюда свои тесты
    return 0;
}