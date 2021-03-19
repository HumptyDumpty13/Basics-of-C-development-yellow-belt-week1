#include <iostream>
#include <string>
#include <vector>
#include<memory>

using namespace std;

class Human {
public:
    Human(const string& name, const string& type) : Name(name), Type(type) {
    }

    virtual void Walk(const string& destination) const = 0;

    string GetType() const {
        return Type;
    }
    string GetName() const {
        return Name;
    }

private:
    const string Type;
    const string Name;
};


class Student : public Human {
public:

    Student(const string& name, const string& favouriteSong) : Human(name, "Student"), FavouriteSong(favouriteSong) {
    }

    void Learn() const {
        cout << "Student: " << GetName() << " learns" << endl;
    }

    void Walk(const string& destination) const override {
        cout << "Student: " << GetName() << " walks to: " << destination << endl;
        SingSong();
    }

    void SingSong() const {
        cout << "Student: " << GetName() << " sings a song: " << FavouriteSong << endl;
    }

private:
    const string FavouriteSong;
};


class Teacher : public Human {
public:

    Teacher(const string& name, const string& subject) : Human(name, "Teacher"), Subject(subject) {
    }

    void Teach() const {
        cout << "Teacher: " << GetName() << " teaches: " << Subject << endl;
    }

    void Walk(const string& destination) const override {
        cout << "Teacher: " << GetName() << " walks to: " << destination << endl;
    }
private:
    const string Subject;
};


class Policeman : public Human {
public:
    Policeman(const string& name) : Human(name, "Policeman") {
    }

    void Check(const Human& h) const {
        cout << "Policeman: " << GetName() << " checks " << h.GetType() <<". "<<h.GetType() <<"'s name is: " << h.GetName() << endl;
    }

    void Walk(const string& destination) const override {
        cout << "Policeman: " << GetName() << " walks to: " << destination << endl;
    }
};

void VisitPlaces(const Human& h, const vector<string>& places) {
    for (const auto& p : places) {
        h.Walk(p);
    }
}

int main() {
    vector<shared_ptr<Human>> humans = {
        make_shared<Teacher>("Jim", "Math"),
        make_shared<Student>("Ann", "We will rock you"),
        make_shared<Policeman>("Bob")
    };
    for (const auto& h : humans) {
        VisitPlaces(*h, { "Moscow", "London" });
    }
    Policeman p("Gary");
    for (const auto& h : humans) {
        p.Check(*h);
    }
    return 0;
}