//
//  main.cpp
//  ICPC Asia Regional Hangzhou Online
//
//  Created by Skylar Zheng on 9/23/14.
//  Copyright (c) 2014 Skylar Zheng. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#define rep(i,n) for(int i=0;i<(n);i++)
typedef long long ll;

using namespace std;

const int iDimension = 3;

class Point
{
public:
	double x[iDimension];
	Point() {}
	Point(double x0, double x1, double x2) {x[0]=x0;x[1]=x1;x[2]=x2;}
	void init() {rep(i, iDimension) scanf("%lf", &x[i]);};
	void print() {rep(i, iDimension) printf(i==iDimension-1?"%.6f":"%.6f ", x[i]);};
	double getLen()
	{
		double res=0;
		rep(i, iDimension) res+=x[i]*x[i];
		return sqrt(res);
	};
	double dist(Point b)
	{
		double res=0;
		rep(i, iDimension) res+=(x[i]-b.x[i])*(x[i]-b.x[i]);
		return sqrt(res);
	}
	Point operator + (Point &b)
    {
		Point res;
		rep(i, iDimension) res.x[i]=x[i]+b.x[i];
		return res;
    }
	Point operator - (Point &b)
    {
		Point res;
		rep(i, iDimension) res.x[i]=x[i]-b.x[i];
		return res;
    }
    Point operator /(double k)
    {
		Point res;
		rep(i, iDimension) res.x[i]=x[i]/k;
		return res;
    }
    Point operator *(double k)
    {
		Point res;
		rep(i, iDimension) res.x[i]=x[i]*k;
		return res;
    }
    double operator *(const Point &b)
    {
		double res=0;
		rep(i, iDimension) res+=x[i]*b.x[i];
		return res;
    }
    Point operator ^(const Point &b)
    {
        return Point(x[1]*b.x[2]-x[2]*b.x[1], x[2]*b.x[0]-x[0]*b.x[2], x[0]*b.x[1]-x[1] * b.x[0]);
    }
};

class Line
{
public:
    Point p1, p2;
	Line() {}
	Line(Point p1, Point p2):p1(p1), p2(p2) {}
	void init() {p1.init();p2.init();};
	double dist(Point b) {return fabs(((b-p1)^(b-p2)).getLen())/getLen();};
	double dist(Line b, Point &tmp) {
		tmp = (p1-p2)^(b.p1-b.p2);
		return fabs((p1-b.p1)*tmp)/tmp.getLen();
	}
	double getLen() {return p1.dist(p2);};
//	Point getNearestPoint(Line b);
	void print(char c) {p1.print();putchar(' ');p2.print();putchar(c);};
//	Point get(double a);
};

class Plane
{
public:
	Point p1, p2, p3;
    Plane(){}
    Plane(Point p1, Point p2, Point p3):p1(p1),p2(p2),p3(p3) {}
	Point intersection(Line l)
	{
		Point res = normalVector();
		double t = (res.x[0]*(p1.x[0]-l.p1.x[0])+res.x[1]*(p1.x[1]-l.p1.x[1])+res.x[2]*(p1.x[2]-l.p1.x[2]))
		/(res.x[0]*(l.p2.x[0]-l.p1.x[0])+res.x[1]*(l.p2.x[1]-l.p1.x[1])+res.x[2]*(l.p2.x[2]-l.p1.x[2]));
		res.x[0] = l.p1.x[0] + (l.p2.x[0] - l.p1.x[0]) * t;
		res.x[1] = l.p1.x[1] + (l.p2.x[1] - l.p1.x[1]) * t;
		res.x[2] = l.p1.x[2] + (l.p2.x[2] - l.p1.x[2]) * t;
		return res;
	};
	Point normalVector() {return (p1-p2)^(p2-p3);};
};
Line getNearestLine(Line A, Line B)
{
	Line res;
	Point d1=A.p1-A.p2;
	Point d2=B.p1-B.p2;
	double t1 = ((B.p1-A.p1)^d2 )*(d1^d2);
	t1 /= (d1^d2).getLen()*(d1^d2).getLen();
	double t2 = ((B.p1-A.p1)^d1 )*(d1^d2);
	t2 /= (d1^d2).getLen()*(d1^d2).getLen();
	return Line(d1*t1+A.p1, d2*t2+B.p1);
}

int main()
{
//	freopen("input", "r", stdin);
//	freopen("output", "w", stdout);
	int iCase;
	Line l[2];
	scanf("%d", &iCase);
	rep(Case, iCase) {
		l[0].init();l[1].init();
		Point normal;
		printf("%.6f\n", l[0].dist(l[1], normal));
		Line ans = getNearestLine(l[0], l[1]);
		ans.print('\n');
	}
	return 0;
}