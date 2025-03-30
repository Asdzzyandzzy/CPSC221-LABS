/**
 * @file        teststats.cpp
 * @author      CPSC 221
 * @description Basic tests for Stats
 *
 * THIS FILE WILL NOT BE SUBMITTED
**/

#include <iostream>

#include "stats.h"
#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include "cs221util/colour.h"

using namespace cs221util;
using namespace std;


/*****************************
* Test function declarations *
*****************************/

void Test1x1avg();
void Test1x1var();
void Test1x2_0_0__1_0avg();
void Test1x2_0_0__1_0var();
void Test1x2_1_0__1_0avg();
void Test1x2_1_0__1_0var();
void Test2x1_0_0__0_1avg();
void Test2x1_0_0__0_1var();
void Test2x1_0_1__0_1avg();
void Test2x1_0_1__0_1var();
void Test3x2_0_0__2_1avg();
void Test3x2_0_0__2_1var();
void Test3x2_0_1__1_1avg();
void Test3x2_0_1__1_1var();
void Test3x2_1_0__1_1avg();
void Test3x2_1_0__1_1var();
void Test3x4_1_1__2_3avg();
void Test3x4_1_1__2_3var();
void TestGetAvg();
void TestGetVar();

int main() {

    // call test functions
    TestGetAvg();
    TestGetVar();
    Test1x1avg();
    Test1x1var();
    Test1x2_0_0__1_0avg();
    Test1x2_0_0__1_0var();
    Test1x2_1_0__1_0avg();
    Test1x2_1_0__1_0var();
    Test2x1_0_0__0_1avg();
    Test2x1_0_0__0_1var();
    Test2x1_0_1__0_1avg();
    Test2x1_0_1__0_1var();
    Test3x2_0_0__2_1avg();
    Test3x2_0_0__2_1var();
    Test3x2_0_1__1_1avg();
    Test3x2_0_1__1_1var();
    Test3x2_1_0__1_1avg();
    Test3x2_1_0__1_1var();
    Test3x4_1_1__2_3avg();
    Test3x4_1_1__2_3var();

    return 0;
}

/********************************
* Test function implementations *
********************************/

void Test1x1avg() {
    cout << "1x1 avg" << endl;

    PNG im(1, 1);
    RGBAPixel* p = im.getPixel(0, 0);
    p->r = 100; p->g = 150; p->b = 200;
    Stats s(im);
    pair<int, int> ul(0, 0);

    if (s.GetAvg(ul, 1, 1) == *p) {
        cout << "Test case " << FG_GREEN << "passed" << FG_DEFAULT << "." << endl;
    }
    else {
        cout << "Test case " << FG_RED << "failed" << FG_DEFAULT << "." << endl;
    }
}

void Test1x1var() {
    cout << "1x1 var" << endl;

    PNG im(1, 1);
    RGBAPixel* p = im.getPixel(0, 0);
    p->r = 100; p->g = 150; p->b = 200;
    Stats s(im);
    pair<int, int> ul(0, 0);

    if (s.GetVar(ul, 1, 1) == 0) {
        cout << "Test case " << FG_GREEN << "passed" << FG_DEFAULT << "." << endl;
    }
    else {
        cout << "Test case " << FG_RED << "failed" << FG_DEFAULT << "." << endl;
    }
}

void Test1x2_0_0__1_0avg() {
    cout << "1x2,(0,0)(1,0) avg" << endl;

    PNG im(2, 1);
    RGBAPixel* p = im.getPixel(0, 0);
    p->r = 100; p->g = 150; p->b = 200;
    RGBAPixel* q = im.getPixel(1, 0);
    q->r = 50; q->g = 75; q->b = 100;
    Stats s(im);
    pair<int, int> ul(0, 0);

    RGBAPixel avg((p->r + q->r) / 2, (p->g + q->g) / 2, (p->b + q->b) / 2);

    if (s.GetAvg(ul, 2, 1) == avg) {
        cout << "Test case " << FG_GREEN << "passed" << FG_DEFAULT << "." << endl;
    }
    else {
        cout << "Test case " << FG_RED << "failed" << FG_DEFAULT << "." << endl;
    }
}

void Test1x2_0_0__1_0var() {
    cout << "1x2,(0,0)(1,0) var" << endl;

    PNG im(2, 1);
    RGBAPixel* p = im.getPixel(0, 0);
    p->r = 100; p->g = 150; p->b = 200;
    RGBAPixel* q = im.getPixel(1, 0);
    q->r = 50; q->g = 75; q->b = 100;
    Stats s(im);
    pair<int, int> ul(0, 0);

    if (9063 - s.GetVar(ul, 2, 1) <= 3 &&
        9063 - s.GetVar(ul, 2, 1) >= 0) {
        cout << "Test case " << FG_GREEN << "passed" << FG_DEFAULT << "." << endl;
    }
    else {
        cout << "Test case " << FG_RED << "failed" << FG_DEFAULT << "." << endl;
    }
}

void Test1x2_1_0__1_0avg() {
    cout << "1x2,(1,0)(1,0) avg" << endl;

    PNG im(2, 1);
    RGBAPixel* p = im.getPixel(0, 0);
    p->r = 100; p->g = 150; p->b = 200;
    RGBAPixel* q = im.getPixel(1, 0);
    q->r = 50; q->g = 75; q->b = 100;
    Stats s(im);
    pair<int, int> ul(1, 0);

    RGBAPixel avg((p->r + q->r) / 2, (p->g + q->g) / 2, (p->b + q->b) / 2);

    if (s.GetAvg(ul, 1, 1) == *q) {
        cout << "Test case " << FG_GREEN << "passed" << FG_DEFAULT << "." << endl;
    }
    else {
        cout << "Test case " << FG_RED << "failed" << FG_DEFAULT << "." << endl;
    }
}

void Test1x2_1_0__1_0var() {
    cout << "1x2,(1,0)(1,0) var" << endl;

    PNG im(2, 1);
    RGBAPixel* p = im.getPixel(0, 0);
    p->r = 100; p->g = 150; p->b = 200;
    RGBAPixel* q = im.getPixel(1, 0);
    q->r = 50; q->g = 75; q->b = 100;
    Stats s(im);
    pair<int, int> ul(1, 0);

    if (s.GetVar(ul, 1, 1) == 0) {
        cout << "Test case " << FG_GREEN << "passed" << FG_DEFAULT << "." << endl;
    }
    else {
        cout << "Test case " << FG_RED << "failed" << FG_DEFAULT << "." << endl;
    }
}

void Test2x1_0_0__0_1avg() {
    cout << "2x1,(0,0)(0,1) avg" << endl;

    PNG im(1, 2);
    RGBAPixel* p = im.getPixel(0, 0);
    p->r = 100; p->g = 150; p->b = 200;
    RGBAPixel* q = im.getPixel(0, 1);
    q->r = 50; q->g = 75; q->b = 100;
    Stats s(im);
    pair<int, int> ul(0, 0);

    RGBAPixel avg((p->r + q->r) / 2, (p->g + q->g) / 2, (p->b + q->b) / 2);

    if (s.GetAvg(ul, 1, 2) == avg) {
        cout << "Test case " << FG_GREEN << "passed" << FG_DEFAULT << "." << endl;
    }
    else {
        cout << "Test case " << FG_RED << "failed" << FG_DEFAULT << "." << endl;
    }
}

void Test2x1_0_0__0_1var() {
    cout << "2x1,(0,0)(0,1) var" << endl;

    PNG im(1, 2);
    RGBAPixel* p = im.getPixel(0, 0);
    p->r = 100; p->g = 150; p->b = 200;
    RGBAPixel* q = im.getPixel(0, 1);
    q->r = 50; q->g = 75; q->b = 100;
    Stats s(im);
    pair<int, int> ul(0, 0);

    RGBAPixel avg((p->r + q->r) / 2, (p->g + q->g) / 2, (p->b + q->b) / 2);

    if (9063 - s.GetVar(ul, 1, 2) <= 3 &&
        9063 - s.GetVar(ul, 1, 2) >= 0) {
        cout << "Test case " << FG_GREEN << "passed" << FG_DEFAULT << "." << endl;
    }
    else {
        cout << "Test case " << FG_RED << "failed" << FG_DEFAULT << "." << endl;
    }
}

void Test2x1_0_1__0_1avg() {
    cout << "2x1,(0,1)(0,1) avg" << endl;

    PNG im(1, 2);
    RGBAPixel* p = im.getPixel(0, 1);
    p->r = 100; p->g = 150; p->b = 200;
    RGBAPixel* q = im.getPixel(0, 1);
    q->r = 50; q->g = 75; q->b = 100;
    Stats s(im);
    pair<int, int> ul(0, 1);

    if (s.GetAvg(ul, 1, 1) == *q) {
        cout << "Test case " << FG_GREEN << "passed" << FG_DEFAULT << "." << endl;
    }
    else {
        cout << "Test case " << FG_RED << "failed" << FG_DEFAULT << "." << endl;
    }
}

void Test2x1_0_1__0_1var() {
    cout << "2x1,(0,1)(0,1) var" << endl;

    PNG im(1, 2);
    RGBAPixel* p = im.getPixel(0, 1);
    p->r = 100; p->g = 150; p->b = 200;
    RGBAPixel* q = im.getPixel(0, 1);
    q->r = 50; q->g = 75; q->b = 100;
    Stats s(im);
    pair<int, int> ul(0, 1);

    if (s.GetVar(ul, 1, 1) == 0) {
        cout << "Test case " << FG_GREEN << "passed" << FG_DEFAULT << "." << endl;
    }
    else {
        cout << "Test case " << FG_RED << "failed" << FG_DEFAULT << "." << endl;
    }
}

void Test3x2_0_0__2_1avg() {
    cout << "3x2,(0,0)(2,1) avg" << endl;

    PNG im(3, 2);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            RGBAPixel* p = im.getPixel(j, i);
            p->r = 100 * i; p->g = 100 * j; p->b = 100 * i + j;
        }
    }
    Stats s(im);
    pair<int, int> ul(0, 0);

    RGBAPixel p(50, 100, 51);

    if (s.GetAvg(ul, 3, 2) == p) {
        cout << "Test case " << FG_GREEN << "passed" << FG_DEFAULT << "." << endl;
    }
    else {
        cout << "Test case " << FG_RED << "failed" << FG_DEFAULT << "." << endl;
    }
}

void Test3x2_0_0__2_1var() {
    cout << "3x2,(0,0)(2,1) var" << endl;

    PNG im(3, 2);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            RGBAPixel* p = im.getPixel(j, i);
            p->r = 100 * i; p->g = 100 * j; p->b = 100 * i + j;
        }
    }
    Stats s(im);
    pair<int, int> ul(0, 0);

    if (70004 - s.GetVar(ul, 3, 2) <= 3 &&
        70004 - s.GetVar(ul, 3, 2) >= 0) {
        cout << "Test case " << FG_GREEN << "passed" << FG_DEFAULT << "." << endl;
    }
    else {
        cout << "Test case " << FG_RED << "failed" << FG_DEFAULT << "." << endl;
    }
}

void Test3x2_0_1__1_1avg() {
    cout << "3x2,(0,1)(1,1) avg" << endl;

    PNG im(3, 2);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            RGBAPixel* p = im.getPixel(j, i);
            p->r = 100 * i; p->g = 100 * j; p->b = 100 * i + j;
        }
    }
    Stats s(im);
    RGBAPixel p(100, 50, 100);
    pair<int, int> ul(0, 1);

    if (s.GetAvg(ul, 2, 1) == p) {
        cout << "Test case " << FG_GREEN << "passed" << FG_DEFAULT << "." << endl;
    }
    else {
        cout << "Test case " << FG_RED << "failed" << FG_DEFAULT << "." << endl;
    }
}

void Test3x2_0_1__1_1var() {
    cout << "3x2,(0,1)(1,1) var" << endl;

    PNG im(3, 2);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            RGBAPixel* p = im.getPixel(j, i);
            p->r = 100 * i; p->g = 100 * j; p->b = 100 * i + j;
        }
    }
    Stats s(im);
    pair<int, int> ul(0, 1);

    if (5001 - s.GetVar(ul, 2, 1) <= 3 &&
        5001 - s.GetVar(ul, 2, 1) >= 0) {
        cout << "Test case " << FG_GREEN << "passed" << FG_DEFAULT << "." << endl;
    }
    else {
        cout << "Test case " << FG_RED << "failed" << FG_DEFAULT << "." << endl;
    }
}

void Test3x2_1_0__1_1avg() {
    cout << "3x2,(1,0)(1,1) avg" << endl;

    PNG im(3, 2);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            RGBAPixel* p = im.getPixel(j, i);
            p->r = 100 * i; p->g = 100 * j; p->b = 100 * i + j;
        }
    }
    Stats s(im);
    pair<int, int> ul(1, 0);
    RGBAPixel p(50, 100, 51);

    if (s.GetAvg(ul, 1, 2) == p) {
        cout << "Test case " << FG_GREEN << "passed" << FG_DEFAULT << "." << endl;
    }
    else {
        cout << "Test case " << FG_RED << "failed" << FG_DEFAULT << "." << endl;
    }
}

void Test3x2_1_0__1_1var() {
    cout << "3x2,(1,0)(1,1) var" << endl;

    PNG im(3, 2);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            RGBAPixel* p = im.getPixel(j, i);
            p->r = 100 * i; p->g = 100 * j; p->b = 100 * i + j;
        }
    }
    Stats s(im);
    pair<int, int> ul(1, 0);

    if (10000 - s.GetVar(ul, 1, 2) <= 3 &&
        10000 - s.GetVar(ul, 1, 2) >= 0) {
        cout << "Test case " << FG_GREEN << "passed" << FG_DEFAULT << "." << endl;
    }
    else {
        cout << "Test case " << FG_RED << "failed" << FG_DEFAULT << "." << endl;
    }
}

void Test3x4_1_1__2_3avg() {
    cout << "3x4,(1,1)(2,3) avg" << endl;

    PNG im(3, 4);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            RGBAPixel* p = im.getPixel(j, i);
            p->r = 50 * i; p->g = 100 * j; p->b = 50 * i + j;
        }
    }
    Stats s(im);
    pair<int, int> ul(1, 1); pair<int, int> lr(2, 3);
    RGBAPixel p(100, 150, 101);

    if (s.GetAvg(ul, 2, 3) == p) {
        cout << "Test case " << FG_GREEN << "passed" << FG_DEFAULT << "." << endl;
    }
    else {
        cout << "Test case " << FG_RED << "failed" << FG_DEFAULT << "." << endl;
    }
}

void Test3x4_1_1__2_3var() {
    cout << "3x4,(1,1)(2,3) var" << endl;

    PNG im(3, 4);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            RGBAPixel* p = im.getPixel(j, i);
            p->r = 50 * i; p->g = 100 * j; p->b = 50 * i + j;
        }
    }
    Stats s(im);
    pair<int, int> ul(1, 1);

    if (35002 - s.GetVar(ul, 2, 3) <= 3 &&
        35002 - s.GetVar(ul, 2, 3) >= 0) {
        cout << "Test case " << FG_GREEN << "passed" << FG_DEFAULT << "." << endl;
    }
    else {
        cout << "Test case " << FG_RED << "failed" << FG_DEFAULT << "." << endl;
    }
}

void TestGetAvg() {
    cout << "GetAvg" << endl;

    PNG data; data.resize(2, 2);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            RGBAPixel* p = data.getPixel(i, j);
            p->r = 20 * i + 3 * j;
            p->g = 3 * i + 20 * j;
            p->b = 23 * i + 23 * j;
            p->a = 1.0;
        }
    }
    Stats s(data);
    pair<int, int> ul(0, 0);
    RGBAPixel result = s.GetAvg(ul, 2, 2);
    RGBAPixel expected(11, 11, 23);

    if (result == expected) {
        cout << "Test case " << FG_GREEN << "passed" << FG_DEFAULT << "." << endl;
    }
    else {
        cout << "Test case " << FG_RED << "failed" << FG_DEFAULT << "." << endl;
    }
}

void TestGetVar() {
    cout << "GetVar" << endl;

    PNG data; data.resize(2, 2);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            RGBAPixel* p = data.getPixel(i, j);
            p->r = 20 * i + 3 * j;
            p->g = 3 * i + 20 * j;
            p->b = 23 * i + 23 * j;
            p->a = 1.0;
        }
    }
    Stats s(data);
    pair<int, int> ul(0, 0);
    double result = s.GetVar(ul, 2, 2);

    if (result == 1876) {
        cout << "Test case " << FG_GREEN << "passed" << FG_DEFAULT << "." << endl;
    }
    else {
        cout << "Test case " << FG_RED << "failed" << FG_DEFAULT << "." << endl;
    }
}
