#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <stack>
#include "Structs.h"
#include <limits.h>

using namespace std;

size_t n;
vector<point> points;
stack<point> shell;
point mainPoint(INT_MAX, INT_MAX, INT_MAX);
bool pointCmp(point p1, point p2){
    point v1 = p1 - mainPoint;
    point v2 = p2 - mainPoint;
    if (p1 == mainPoint){
        return true;
    }
    if (p2 == mainPoint){
        return false;
    }
    return ((v1.z / v1.x) < (v2.z / v2.x));
}

void input(){
    FILE *input = fopen("inputLarge.brs", "r");
    //FILE *input = fopen("input.brs", "r");
    if (input == NULL){
        printf("file not open\n");
    }

    fscanf(input, "%d", &n);
    for(size_t i = 0; i < n; ++i){
        point tmpPoint;
        fscanf(input, "%lf %lf %lf", &tmpPoint.x, &tmpPoint.y, &tmpPoint.z);
        points.push_back(tmpPoint);
        if (tmpPoint < mainPoint){
            mainPoint = tmpPoint;
        }
    }
    std::sort(points.begin(), points.end(), pointCmp);
    fclose(input);
}

static double vectorMultScolar(const point &p1, const point &p2) {
    return p1.x*p2.x + p1.y*p2.y + p1.z*p2.z;
}

bool isLeftTurn(const point &p1, const point &p2, const point &p3){
    point v1 = p2 - p1;
    point v2 = p3 - p1;
    v1 = point(-v1.z, 0, v1.x);
    return (vectorMultScolar(v1, v2) > 0);
}

void buildShell(){
    shell.push(points[0]);
    shell.push(points[1]);
    for(size_t i = 2; i < n; ++i) {
        point p3 = points[i];
        point p2 = shell.top();
        shell.pop();
        point p1 = shell.top();
        while(!isLeftTurn(p1, p2, p3) ){
            p2 = p1;
            shell.pop();
            if (!shell.empty()){
                p1 = shell.top();
            } else {
                break;
            }
        }
        shell.push(p2);
        shell.push(p3);
    }
}

void output(){
    FILE* out = fopen("output.brs", "w");
    int pointsCount = shell.size();
    fprintf(out, "%d\n", pointsCount);
    while(!shell.empty()){
        point p = shell.top();
        fprintf(out, "%.15lf %.15lf %.15lf\n", p.x, p.y, p.z);
        shell.pop();
    }
    size_t trianglesCount = pointsCount - 2;
    fprintf(out, "%d\n", trianglesCount);
    for(size_t i = 0; i < trianglesCount; ++i){
        fprintf(out, "%d %d %d\n", 0, i+1, i+2);
    }
    fclose(out);
}

int main()
{
    input();
    buildShell();
    output();
    return 0;
}

