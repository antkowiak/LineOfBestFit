/**
 *
 * Copyright (c) 2016 Ryan Antkowiak 
 * All rights reserved.
 * It is provided AS_IS, WITHOUT ANY WARRANTY either expressed or implied.
 * You may study, use, and modify it for any non-commercial purpose.
 * You may distribute it non-commercially as long as you retain this notice.
 * For a commercial license, contact .
 *
 * @author Ryan Antkowiak 
 *
 *
 * Simple program that calculates a "Line of Best Fit" using the "Least Square Method."
 *
 **/

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// The type to use for numbers
typedef double TNumber;

// A line consists of a slope and a y-intercept
struct Line
{
    Line() : slope(0), y_intercept(0) {}
    Line(const TNumber & s, const TNumber & yInt) : slope(s), y_intercept(yInt) {}

    std::string toString() const
    {
        std::stringstream ss;
        ss << "y = (" << slope << " * x) + (" << y_intercept << ")";
        return ss.str();
    }

    TNumber slope;
    TNumber y_intercept;
};

// 2-dimensional point (x, y)
struct Point
{
    Point() : x(0), y(0) {}
    Point(const TNumber & x0, const TNumber & y0) : x(x0), y(y0) {}

    std::string toString() const
    {
        std::stringstream ss;
        ss << "(" << x << ", " << y << ")";
        return ss.str();
    }

    TNumber x;
    TNumber y;
};

// Calculate a line of best fit, using the least square method
Line CalculateLineOfBestFit(const std::vector<Point> & points)
{
    if (points.empty())
    {
        return Line();
    }

    TNumber totalX = 0;
    TNumber totalY = 0;

    for (std::vector<Point>::const_iterator i = points.begin() ; i != points.end() ; ++i)
    {
        totalX += i->x;
        totalY += i->y;
    }

    TNumber meanX = totalX / static_cast<TNumber>(points.size());
    TNumber meanY = totalY / static_cast<TNumber>(points.size());

    TNumber sumDeviationProducts = 0;
    TNumber sumXDeviationSquared = 0;

    for (std::vector<Point>::const_iterator i = points.begin() ; i != points.end() ; ++i)
    {
        TNumber xDeviation = (i->x - meanX);
        TNumber yDeviation = (i->y - meanY);

        sumDeviationProducts += (xDeviation * yDeviation);
        sumXDeviationSquared += (xDeviation * xDeviation);
    }

    if (sumXDeviationSquared == 0)
    {
        return Line();
    }

    TNumber slope = sumDeviationProducts / sumXDeviationSquared;
    TNumber yInt = meanY - (slope * meanX);

    return Line(slope, yInt);
}


int main(int argc, char * argv[])
{
    std::vector<Point> points;
    points.push_back(Point(1,1.5));
    points.push_back(Point(2,2.5));
    points.push_back(Point(3,3.25));

    Line line = CalculateLineOfBestFit(points);

    std::cout << line.toString() << std::endl;

    return 0;
}
