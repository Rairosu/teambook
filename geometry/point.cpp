/*
 * This file contains realization of Point class.
 *
 * Requirements: "iostream", "cmath", "double_utils"
 */

class Point {
 public:
    double x;
    double y;
    Point() = default;
    Point(double x, double y) : x(x), y(y) {}

    void scan() {
        scanf("%lf %lf", &x, &y);
    }

    void print() const {
        printf("%.15lf %.15lf\n", x, y);
    }

    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }

    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y);
    }

    Point operator-() const {
        return Point(-x, -y);
    }

    Point operator*(double k) const {
        return Point(x * k, y * k);
    }

    Point operator/(double k) const {
        return Point(x / k, y / k);
    }

    bool operator==(const Point& other) const {
        return double_equal(x, other.x) && double_equal(y, other.y);
    }

    double operator%(const Point& other) const {
        return x * other.x + y * other.y;
    }

    double operator*(const Point& other) const {
        return x * other.y - y * other.x;
    }

    double Length() const {
        return sqrt(*this % (*this));
    }

    double DistTo(const Point& other) const {
        return (*this - other).Length();
    }

    double DistTo(const Point& first, const Point& second) const {
        double dist = first.DistTo(second);
        if (double_equal(dist, 0)) {
            return -1;
        }
        double area = (*this - first) * (*this - second);
        return fabs(area) / dist;
    }

    Point Normalize(double k = 1) const {
        double len = Length();
        if (double_equal(len, 0) ) {
            return Point();
        }
        return *this * (k / len);
    }

    Point GetH(const Point & A, const Point & B) const {
        Point C = *this;
        Point v = B - A;
        Point u = C - A;
        double k = v % u / v.Length();
        v = v.Normalize(k);
        Point H = A + v;
        return H;
    }
};
