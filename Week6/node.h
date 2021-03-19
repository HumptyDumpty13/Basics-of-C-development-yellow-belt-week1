#pragma once

#include "date.h"
#include<memory>


enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual,
};

enum class LogicalOperation {
    And,
    Or,
};

class Node {
public:
    virtual bool Evaluate(const Date& d, const std::string& e) const = 0;
};

class EmptyNode : public Node {
public:
    bool Evaluate(const Date& d, const std::string& e) const;
};


class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison& cmp, const Date& d);
    bool Evaluate(const Date& d, const std::string& e) const;
private:
    Comparison c;
    Date date;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison& cmp, const std::string& e);
    bool Evaluate(const Date& d, const std::string& e) const;
private:
    Comparison c;
    std::string event;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(const LogicalOperation& op, const std::shared_ptr<const Node>& l, const std::shared_ptr<const Node>& r);
    bool Evaluate(const Date& d, const std::string& e) const;
private:
    LogicalOperation l;
    std::shared_ptr<const Node> left, right;
};