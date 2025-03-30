/**
 * @file        threetree-private.h
 * @author      CPSC 221
 * @description Declaration of private attributes and/or functions for ThreeTree
 *
 * Add your declarations in this file. There is no need to qualify them with a class name,
 * as this file is entirely included into line 196 of threetree.h
 *
 * THIS FILE WILL BE SUBMITTED
**/




void ClearHelper(Node* subroot);


Node* CopyHelper(const Node* otherRoot);


int SizeHelper(const Node* subroot) const;


int LeafHelper(const Node* subroot) const;


void RenderNode(Node* subroot, PNG & out) const;

void RotateCWHelper(Node* node, int x, int y, int w, int h);

