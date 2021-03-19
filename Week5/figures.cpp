#include <iostream>
#include<istream>
#include<sstream>
#include<iomanip>
#include<memory>
#include<vector>
#include <string>
#include<cmath>

#define PI 3.14

class Figure {
public:
    virtual std::string Name() = 0;
    virtual double Perimeter() = 0;
    virtual double Area() = 0;
};

class Triangle : public Figure {
public:
    Triangle(int& a_, int& b_, int& c_) : a(a_), b(b_), c(c_) {

    }
    std::string Name() override {
        return "TRIANGLE";
    }
    double Perimeter() override {
        return static_cast<double>(a) + b + c;
    }
    double Area() override {
        double p = (a + b + c) / 2.0;
        double S = p * (p - a) * (p - b) * (p - c);
        return sqrt(S);
    }

private:

    const int a;
    const int b;
    const int c;
};


class Rect : public Figure {
public:
    Rect(int& width_, int& height_) : width(width_), height(height_) {

    }
    std::string Name() override {
        return "RECT";
    }
    double Perimeter() override {
        return ((width + height) * 2.0);
    }
    double Area() override {
        return width * height;
    }
private:
    const int width;
    const int height;
};

class Circle : public Figure {
public:
    Circle(int& r) : radius(r) {

    }
    std::string Name() override {
        return "CIRCLE";
    }
    double Perimeter() override {
        return 2.0 * PI * radius;
    }
    double Area() override {
        return PI * radius * radius;
    }
private:
    const int radius;
};

std::shared_ptr<Figure> CreateFigure(std::istringstream& is) {
    std::string name;
    is >> name;
    if (name == "RECT") {
        int width = 0;
        int height = 0;
        is >> width >> height;
        return std::make_shared<Rect>(width,height);
    }
    else if (name == "TRIANGLE") {
        int a = 0, b=0, c=0;
        is >> a >> b>>c;
        return std::make_shared<Triangle>(a, b, c);
    }
    else if (name == "CIRCLE") {
        int r = 0;
        is >> r;
        return std::make_shared<Circle>(r);
    }
 }