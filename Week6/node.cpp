#include "node.h"

    bool EmptyNode::Evaluate(const Date& d, const std::string& e) const {
        return true;
    }

    DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& d) : c(cmp), date(d) {
    }
    bool DateComparisonNode::Evaluate(const Date& d, const std::string& e) const {
        if (c == Comparison::Less) {
            return d < date;
        }
        else if (c == Comparison::LessOrEqual) {
            return d <= date;
        }
        else if (c == Comparison::Greater) {
            return d > date;
        }
        else if (c == Comparison::GreaterOrEqual) {
            return d >= date;
        }
        else if (c == Comparison::Equal) {
            return d == date;
        }
            return d != date;
    }
    EventComparisonNode::EventComparisonNode(const Comparison& cmp, const std::string& e) : c(cmp), event(e) {
    }

    bool EventComparisonNode::Evaluate(const Date& d, const std::string& e) const {
        if (c == Comparison::Less) {
            return e < event;
        }
        else if (c == Comparison::LessOrEqual) {
            return e <= event;
        }
        else if (c == Comparison::Greater) {
            return e > event;
        }
        else if (c == Comparison::GreaterOrEqual) {
            return e >= event;
        }
        else if (c == Comparison::Equal) {
            return e == event;
        }
            return e != event;
    }

    LogicalOperationNode::LogicalOperationNode(const LogicalOperation& op, const std::shared_ptr<const Node>& l, const std::shared_ptr<const Node>& r) :
        l(op), left(l), right(r) {
    }
    bool LogicalOperationNode::Evaluate(const Date& d, const std::string& e) const {
        if (l == LogicalOperation::And) {
            return (left->Evaluate(d, e) && right->Evaluate(d, e));
        }

            return (left->Evaluate(d, e) || right->Evaluate(d, e));

    }