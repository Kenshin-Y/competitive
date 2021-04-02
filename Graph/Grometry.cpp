/*
    @created : 2020-8
    @updated : 2021-3
    @description
        * とっとと作れやハム太郎
*/

#ifndef GEOMETRY
#define GEOMETRY
#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;
const double pi = acos(-1);
struct Point { double x,y;  };
Point operator+(Point a,Point b){ return {a.x+b.x,a.y+b.y};}
Point operator-(Point a,Point b){ return {a.x-b.x,a.y-b.y};}
Point operator*(double k,Point a){return {  k*a.x, k*a.y };}
Point operator/(double k,Point a){return {  a.x/k, a.y/k };}
double operator*(Point a,Point b){ return a.x*b.x+a.y*b.y; }
bool operator<(Point a,Point b){
    if(abs(a.x-b.x)>EPS) return a.x < b.x;
    return a.y + EPS < b.y;
}

#endif //GEOMETRY　
