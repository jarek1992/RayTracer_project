#pragma once

class interval {
public:
    double min, max;

    //default inteval constructor is empty
    interval()
        : min(+infinity)
        , max(-infinity) 
    {}
    //parametrical constructor with interval min and max
    interval(double min, double max)
        : min(min)
        , max(max)
    {}
    //return size of interval
    double size() const {
        return max - min;
    }
    //check if interval contains x 
    bool contains(double x) const {
        return min <= x && x <= max;
    }
    bool surrounds(double x) const {
        return min < x && max > x;
    }
    static const interval empty, universe;
};

const interval interval::empty = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);