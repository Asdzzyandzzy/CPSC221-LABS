/**
 * @file        threetree.h
 * @author      CPSC 221
 * @description Class definitions for Node and ThreeTree
 *
 * THIS FILE WILL NOT BE SUBMITTED
**/

#ifndef _THREETREE_H_
#define _THREETREE_H_

#include <utility>
#include <cmath>

#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include "stats.h"

using namespace std;
using namespace cs221util;

/**
 * The Node class would normally be private to the ThreeTree class via the
 * principle of encapsulation -- the end user does not need to know our
 * node-based implementation details. We have made the Node class public
 * here for convenience of debugging and grading.
**/
class Node {
public:
    Node(pair<int, int> ul, int w, int h, RGBAPixel average, double v); // constructor
    Node(Stats& s, pair<int, int> ul, int w, int h); // second constructor
    pair<int, int> upleft; // (x, y) coordinate of upper left rectangle corner
    int width;		// width and height of rectangular region
    int height;		// represented by Node in number of pixels
    RGBAPixel avg;	// average color of Node's region
    double var;		// variability over region  
    Node* A; // ptr to left / top subtree
    Node* B; // ptr to middle subtree
    Node* C; // ptr to right / bottom subtree
};

/**
 * ThreeTree: This is a class used in decomposing an image
 * into rectangles of similarly colored pixels.
**/
class ThreeTree {
public:

    /* BEGIN ============== Public functions (GIVEN) =================== */

    /**
     * Copy constructor for a ThreeTree.
     *
     * @param other the ThreeTree  we are copying.
    **/
    ThreeTree(const ThreeTree& other);

    /**
     * ThreeTree destructor.
     * Destroys all of the memory associated with the
     * current ThreeTree. This function should ensure that
     * memory does not leak on destruction of an ThreeTree.
    **/
    ~ThreeTree();

    /**
     * Overloaded assignment operator for ThreeTree.
     *
     * @param rhs The right hand side of the assignment statement.
    **/
    ThreeTree& operator=(const ThreeTree& rhs);

    /* END ================ Public functions (GIVEN) =================== */


    /* BEGIN ============== Public functions (YOU IMPLEMENT) =========== */

    /**
     * The ThreeTree represents the subimage from (0,0) to (w-1, h-1) where
     * w-1 and h-1 are the largest valid image coordinates of the original PNG.
     * Every node corresponds to a rectangle of pixels in the original PNG,
     * represented by an (x,y) pair for the upper left corner of the
     * square and two integers for the number of pixels on the width and
     * height dimensions of the rectangular region the node defines.
     *
     * The node's three children correspond to a partition
     * of the node's rectangular region into three approximately equal-size strips.
     *
     * If the rectangular region is taller than it is wide, the region is divided
     * into horizontal strips:
     *  +-------+
     *  |   A   |
     *  |       |
     *  +-------+
     *  |   B   |
     *  |       |    (Split tall)
     *  +-------+
     *  |   C   | 
     *  |       |
     *  +-------+
     * 
     * If the rectangular region is wider than it is tall, the region is divided
     * into vertical strips:
     *  +---------+---------+---------+
     *  |    A    |    B    |    C    |
     *  |         |         |         |    (Split wide)
     *  +---------+---------+---------+
     * 
     * Your regions are not guaranteed to have dimensions exactly divisible by 3.
     * If the dimensions of your rectangular region are 3p x q or q x 3p where 3p
     * represents the length of the long side, then your rectangular regions will
     * each have dimensions p x q (or q x p)
     * 
     * If the dimensions are (3p+1) x q, subregion B gets the extra pixel of size
     * while subregions A and C have dimensions p x q.
     * 
     * If the dimensions are (3p+2) x q, subregions A and C each get an extra pixel
     * of size, while subregion B has dimensions p x q.
     * 
     * If the region to be divided is a square, then apply the Split wide behaviour.
     * 
     * How would a 2 x 1 rectangle be split?
     * 
     * Then it recursively partitions Nodes, starting at the root and
     * until the Node's variability is at most tol or the Node is a single pixel.
     * 
     * Default tolerance is 0.0.
    **/
    ThreeTree(PNG& imIn, double tol = 0.0);

    /**
     * Render returns a PNG image consisting of rectangles defined
     * by the leaves in the ThreeTree.  Draws every leaf node's rectangle
     * onto a PNG canvas using the average color stored in the node.
    **/
    PNG Render() const;

    /**
     * Return the number of nodes in the tree.
     * You may want a private helper for this.
    **/
    int Size() const;

    /**
     * Return the number of leaf nodes in the tree.
     * You may want a private helper for this.
    **/
    int NumLeaves() const;

    /**
     * Rearranges the tree contents so that when rendered, the image appears
     * to be rotated 90 degrees clockwise.
     * You must preserve the invariant properties for each node's pointers:
     * pointer A refers to the left / top subtree (i.e. smallest x / y image coordinates)
     * pointer B refers to the middle subtree
     * pointer C refers to the right / bottom subtree (i.e. largest x / y image coordinates)
     *
     * You may want a recursive helper function for this.
    **/
    void RotateCW();

    /* END ================ Public functions (YOU IMPLEMENT) =========== */

private:
    /**
     * Private member variables.
     *
     * You must use these as specified in the description and may not rename them.
     * You may add more in threetree-private.h if you need them.
    **/

    Node* root; // pointer to the root of the ThreeTree

    /* BEGIN ============== Required private functions (YOU IMPLEMENT) ====== */

    /**
     * Destroys all dynamically allocated memory associated with the
     * current ThreeTree class.
     * You may want a recursive helper function for this one.
     */
    void Clear();

    /**
     * Copies the parameter other ThreeTree into the current ThreeTree.
     * Does not free any memory. Called by copy constructor and operator=.
     * You may want a recursive helper function for this one.
     * @param other The ThreeTree to be copied.
     */
    void Copy(const ThreeTree& other);

    /**
     * Private helper function for the constructor. Recursively builds
     * the tree according to the specification of the constructor.
     * @param s Contains the data used to calc avg and var
     * @param ul upper left point of current node's rectangle.
     * @param w,h are width and height of rectangle
     * @param tol is the allowed tolerance
     */
    Node* BuildTree(Stats& s, pair<int, int> ul, int w, int h, double tol);

    /* END ================ Required private functions (YOU IMPLEMENT) ====== */

    /******************************************************************
    * IF YOU HAVE WISH TO DEFINE ANY PRIVATE ATTRIBUTES OR FUNCTIONS, *
    * ADD THEM TO threetree-private.h                                 *
    ******************************************************************/

    #include "threetree-private.h"

};

#endif 
