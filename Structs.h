#ifndef STRUCTS_H
#define STRUCTS_H

struct point{
    double x,y,z;
    point(double a, double b, double c): x(a), y(b), z(c){}
    point(): x(0), y(0), z(0){}
    bool operator <(const point& p) const {
        if (x < p.x) return true;
        else if (x > p.x) return false;
        if (y < p.y) return true;
        else if (y > p.y) return false;
        if (z < p.z) return true;
        return false;
    }
    bool operator >(const point& p) const {
        if (x > p.x) return true;
        else if (x > p.x) return false;
        if (y > p.y) return true;
        else if (y > p.y) return false;
        if (z > p.z) return true;
        return false;
    }
    bool operator ==(const point& p) const {
        return (x == p.x) && (y == p.y) && (z == p.z);
    }

    point operator - (const point &p) const {
        return point(this->x - p.x, this->y - p.y, this->z - p.z);
    }
    point operator + (const point &p) const {
        return point(this->x + p.x, this->y + p.y, this->z + p.z);
    }
};

#endif // STRUCTS_H
