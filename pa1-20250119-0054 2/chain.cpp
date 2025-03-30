#include "chain.h"
#include <cmath>
#include <iostream>


// PA1 functions
// Complete all of the missing implementation
// and submit this file for grading.

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain() {
	/* your code here */
	Clear();
    
}

/**
 * Inserts a new node after the node pointed to by p in the
 * chain (so p->next is the new node) and returns a pointer to
 * the newly created node.
 * If p is NULL, inserts a new head node to the chain.
 * This function **SHOULD** create a new Node and increase length_.
 *
 * @param p = The new node should be pointed to by p->next.
 *            If p is NULL, the new node becomes the head of the chain.
 * @param ndata = The data to be inserted.
 */
Chain::Node * Chain::InsertAfter(Node * p, const Block &ndata) {
	/* your code here */
    Node* newNode = new Node(ndata);
    if (!p) {
        newNode->next = head_;
        newNode->prev = nullptr;
        if (head_) head_->prev = newNode;
        head_ = newNode;
    } else {
        newNode->next = p->next;
        newNode->prev = p;
        if (p->next) p->next->prev = newNode;
        p->next = newNode;
    }
    length_++;
    return newNode;
}

/**
 * Swaps the position in the chain of the two nodes pointed to
 * by p and q.
 * If p or q is NULL or p==q, do nothing.
 * Change the chain's head pointer if necessary.
 */
void Chain::Swap(Node *p, Node *q) {
	/* your code here */
    if (!p || !q || p == q) return;

    // Handle adjacent nodes
    if (p->next == q) {
        p->next = q->next;
        q->prev = p->prev;
        if (p->prev) p->prev->next = q;
        q->next = p;
        p->prev = q;
        if (p->next) p->next->prev = p;
        if (head_ == p) head_ = q;
    } else if (q->next == p) {
        Swap(q, p);
    } else {
        // Swap non-adjacent nodes
        Node* pPrev = p->prev;
        Node* pNext = p->next;
        Node* qPrev = q->prev;
        Node* qNext = q->next;

        p->prev = qPrev;
        p->next = qNext;
        q->prev = pPrev;
        q->next = pNext;

        if (pPrev) pPrev->next = q;
        if (pNext) pNext->prev = q;
        if (qPrev) qPrev->next = p;
        if (qNext) qNext->prev = p;

        if (head_ == p) head_ = q;
        else if (head_ == q) head_ = p;
    }
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::Clear() {
	/* your code here */
    Node *current = head_;
    while (current != nullptr) {
        Node *next = current->next;
        delete current;
        current = next;
    }
    head_ = nullptr;
    length_ = 0;
    
}

/**
 * Makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::Copy(Chain const &other) {
	/* your code here */
    Clear();
    if (!other.head_) return;

    head_ = new Node(other.head_->data);
    head_->prev = nullptr;
    Node* current = head_;
    Node* otherCurrent = other.head_->next;

    while (otherCurrent) {
        Node* newNode = new Node(otherCurrent->data);
        current->next = newNode;
        newNode->prev = current;
        current = newNode;
        otherCurrent = otherCurrent->next;
    }
    length_ = other.length_;
	
}

/**
 * Takes the current chain and renders it into a
 * correctly sized PNG. The blocks in the chain
 * are placed in the image left to right in order
 * of their occurrence in the chain.
 */
PNG Chain::Render() {
    /* your code here */
    int totalWidth = 0;
    int height = head_ ? head_->data.Height() : 0;
    Node* current = head_;
    while (current) {
        totalWidth += current->data.Width();
        current = current->next;
    }

    PNG result(totalWidth, height);
    int x = 0;
    current = head_;
    while (current) {
        current->data.Render(result, x);
        x += current->data.Width();
        current = current->next;
    }
    return result;
}

/* Modifies the current chain:
 * 1) Find the node with the first (leftmost) block in the unscrambled
 *    image and move it to the head of the chain.
 *	This block is the one whose closest match (to the left) is the
 *	largest.  That is, the distance (using distanceTo) to this block
 *	is big for all other blocks.
 *	For each block B, find the distanceTo B from every other block
 *	and take the minimum of these distances as B's "value".
 *	Choose the block B with the maximum value over all blocks and
 *	swap its node to the head of the chain.
 *
 * 2) Starting with the (just found) first block B, find the node with
 *    the block that is the closest match to follow B (to the right)
 *    among the remaining blocks, move (swap) it to follow B's node,
 *    then repeat to unscramble the chain/image.
 */
void Chain::Unscramble() {
	/* your code here */
	if (!head_ || length_ <= 1) return;

    // Step 1: Find block with maximum minimal distance
    Node* bestNode = head_;
    double maxMinDist = -1.0;
    Node* current = head_;

    while (current) {
        double minDist = INFINITY;
        Node* other = head_;
        while (other) {
            if (other != current) {
                double dist = other->data.DistanceTo(current->data);
                if (dist < minDist) minDist = dist;
            }
            other = other->next;
        }
        if (minDist > maxMinDist) {
            maxMinDist = minDist;
            bestNode = current;
        }
        current = current->next;
    }

    if (bestNode != head_) {
        // Move bestNode to head by swapping
        Swap(head_, bestNode);
    }

    // Step 2: Reorder remaining blocks
    Node* last = head_;
    while (last->next) {
        Node* closest = last->next;
        double minDist = last->data.DistanceTo(closest->data);
        Node* curr = closest->next;

        while (curr) {
            double dist = last->data.DistanceTo(curr->data);
            if (dist < minDist) {
                minDist = dist;
                closest = curr;
            }
            curr = curr->next;
        }

        if (closest != last->next) {
            // Remove closest from current position
            if (closest->prev)
                closest->prev->next = closest->next;
            if (closest->next)
                closest->next->prev = closest->prev;

            // Insert closest after last
            Node* oldNext = last->next;
            last->next = closest;
            closest->prev = last;
            closest->next = oldNext;
            if (oldNext)
                oldNext->prev = closest;
        }
        last = last->next;
    }


    
}

/**************************************************
* IF YOU HAVE DECLARED PRIVATE FUNCTIONS IN       *
* chain-private.h, COMPLETE THEIR IMPLEMENTATIONS *
* HERE                                            *
**************************************************/

