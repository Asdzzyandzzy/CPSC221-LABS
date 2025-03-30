/**
 * @file		pa3.cpp
 * @author		CPSC 221
 * @description	Partial test of PA3 functionality
**/

#include "threetree.h"

int main() {

	// read in image
	PNG orig;
	orig.readFromFile("images-orig/small1.png");
	/*
	orig.readFromFile("images-orig/small2.png");
	orig.readFromFile("images-orig/colour.png");
	orig.readFromFile("images-orig/et-384x216.png");
	orig.readFromFile("images-orig/rolw-640x360.png");
	orig.readFromFile("images-orig/ccwe-854x480.png");
	*/

	// use it to build a ThreeTree (try other tolerances - use larger tolerances for large images)
	ThreeTree t(orig, 10.0);

	// copy the tree (to show you can)
	ThreeTree tCopy(t);

	// render the ThreeTree
	PNG pic = t.Render();

	// write it out
	pic.writeToFile("images-output/small1.png");

	return 0;
}
