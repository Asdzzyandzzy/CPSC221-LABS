/**
 * @file            threetree-given.cpp
 * @author          your CWL
 * @description     Given implementation of ThreeTree functions
 *
 * THIS FILE WILL NOT BE SUBMITTED
**/

#include "threetree.h"

/**
 * First Node constructor, given.
**/
Node::Node(pair<int, int> ul, int w, int h, RGBAPixel average, double v)
    :upleft(ul), width(w), height(h), avg(average), var(v), A(nullptr), B(nullptr), C(nullptr)
{}

/**
 * Second Node constructor, given.
**/
Node::Node(Stats& s, pair<int, int> ul, int w, int h)
    :upleft(ul), width(w), height(h), A(nullptr), B(nullptr), C(nullptr) {
    avg = s.GetAvg(ul, w, h);
    var = s.GetVar(ul, w, h);
}

/**
 * ThreeTree destructor, given.
**/
ThreeTree::~ThreeTree() {
    Clear();
}

/**
 * ThreeTree copy constructor, given.
**/
ThreeTree::ThreeTree(const ThreeTree& other) {
    Copy(other);
}

/**
 * ThreeTree assignment operator, given.
**/
ThreeTree& ThreeTree::operator=(const ThreeTree& rhs) {
    if (this != &rhs) {
        Clear();
        Copy(rhs);
    }
    return *this;
}