/**
 * @file        testthreetree.cpp
 * @author      CPSC 221
 * @description Basic tests for ThreeTree
 *
 * THIS FILE WILL NOT BE SUBMITTED
**/

#include <iostream>

#include "cs221util/colour.h"

#include "threetree.h"


using namespace cs221util;
using namespace std;

/*****************************
* Test function declarations *
*****************************/

void TestBasicTreeConstructorRender();
void TestBasicTreeCopy();
void TestToleranceConstructionRender();
void TestSize();
void TestHighToleranceConstructionRender();
void TestHighToleranceSizeLeaves();
void TestHighToleranceRotateCWRender();

int main() {

    // call test functions
    TestBasicTreeConstructorRender();
    TestBasicTreeCopy();
    TestToleranceConstructionRender();
    TestSize();
    TestHighToleranceConstructionRender();
    TestHighToleranceSizeLeaves();
    TestHighToleranceRotateCWRender();

    return 0;
}

/********************************
* Test function implementations *
********************************/

void TestBasicTreeConstructorRender() {
    cout << "Basic constructor, Render" << endl;

    PNG img;
    img.readFromFile("images-orig/colour.png");

    ThreeTree t1(img); // defaults to tolerance=0.0

    PNG out = t1.Render();

    // REMOVE FOR TESTING
    //out.writeToFile("images-output/colour_render.png");

    if (out == img) {
        cout << "Test case " << FG_GREEN << "passed" << FG_DEFAULT << "." << endl;
    }
    else {
        cout << "Test case " << FG_RED << "failed" << FG_DEFAULT << "." << endl;
    }
}

void TestBasicTreeCopy() {
    cout << "Basic Copy" << endl;

    PNG img;
    img.readFromFile("images-orig/colour.png");

    ThreeTree t1(img);
    ThreeTree t1copy(t1);

    PNG out = t1copy.Render();

    if (out == img) {
        cout << "Test case " << FG_GREEN << "passed" << FG_DEFAULT << "." << endl;
    }
    else {
        cout << "Test case " << FG_RED << "failed" << FG_DEFAULT << "." << endl;
    }
}

void TestToleranceConstructionRender() {
    cout << "Tolerance constructor, Render" << endl;

    PNG img;
    img.readFromFile("images-orig/et-384x216.png");

    ThreeTree t1(img, 6000.0);
    PNG result = t1.Render();

    // REMOVE FOR TESTING
    //result.writeToFile("images-output/et_6000.png");

    PNG expected;
    expected.readFromFile("images-soln/et_6000.png");

    if (expected == result) {
        cout << "Test case " << FG_GREEN << "passed" << FG_DEFAULT << "." << endl;
    }
    else {
        cout << "Test case " << FG_RED << "failed" << FG_DEFAULT << "." << endl;
    }
}

void TestSize() {
    cout << "Size" << endl;

    PNG img;
    img.readFromFile("images-orig/et-384x216.png");

    ThreeTree t1(img, 6000.0);
    int result = t1.Size();

    // REMOVE FOR TESTING
    //cerr << "et-384x216 size = " << result << endl;

    int expected = 16378;

    if (expected == result) {
        cout << "Test case " << FG_GREEN << "passed" << FG_DEFAULT << "." << endl;
    }
    else {
        cout << "Test case " << FG_RED << "failed" << FG_DEFAULT << "." << endl;
    }
}

void TestHighToleranceConstructionRender() {
    cout << "High tolerance construction, Render" << endl;

    PNG img;
    img.readFromFile("images-orig/rolw-640x360.png");

    ThreeTree t1(img, 30800.0);
    PNG result = t1.Render();

    // REMOVE FOR TESTING
    //result.writeToFile("images-output/rolw_30800.png");

    PNG expected;
    expected.readFromFile("images-soln/rolw_30800.png");

    if (expected == result) {
        cout << "Test case " << FG_GREEN << "passed" << FG_DEFAULT << "." << endl;
    }
    else {
        cout << "Test case " << FG_RED << "failed" << FG_DEFAULT << "." << endl;
    }
}

void TestHighToleranceSizeLeaves() {
    cout << "High tolerance construction, Size, NumLeaves" << endl;

    PNG img;
    img.readFromFile("images-orig/rolw-640x360.png");

    ThreeTree t1(img, 30800.0);
    int resultsize = t1.Size();
    int resultleaves = t1.NumLeaves();

    // REMOVE FOR TESTING
    //cerr << "rolw_30800 size = " << resultsize << endl;
    //cerr << "rolw_30800 leaves = " << resultleaves << endl;

    int expectedsize = 38136;
    int expectedleaves = 24668;

    if (expectedsize == resultsize && expectedleaves == resultleaves) {
        cout << "Test case " << FG_GREEN << "passed" << FG_DEFAULT << "." << endl;
    }
    else {
        cout << "Test case " << FG_RED << "failed" << FG_DEFAULT << "." << endl;
    }
}

void TestHighToleranceRotateCWRender() {
    cout << "High tolerance construction, RotateCW, Render" << endl;

    PNG img;
    img.readFromFile("images-orig/ccwe-854x480.png");

    ThreeTree t1(img, 50800.0);
    t1.RotateCW();
    PNG result = t1.Render();

    // REMOVE FOR TESTING
    //result.writeToFile("images-output/ccwe_50800_rotate.png");

    PNG expected;
    expected.readFromFile("images-soln/ccwe_50800_rotate.png");

    if (expected == result) {
        cout << "Test case " << FG_GREEN << "passed" << FG_DEFAULT << "." << endl;
    }
    else {
        cout << "Test case " << FG_RED << "failed" << FG_DEFAULT << "." << endl;
    }
}
