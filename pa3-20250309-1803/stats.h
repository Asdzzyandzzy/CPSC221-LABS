/**
 * @file        stats.h
 * @author      CPSC 221
 * @description Class definitions for Stats class to support ThreeTree construction
 *
 * THIS FILE WILL NOT BE SUBMITTED
**/

#ifndef _STATS_H_
#define _STATS_H_

#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include <utility>
#include <cmath>
#include <vector>

using namespace std;
using namespace cs221util;

class Stats {
	private:
		/**
		 * 2D vectors to store the sums and squared sums of each colour channel.
		 * Data type is 64-bit integer since these values can be large enough to
		 * overflow a 32-bit type for large images.
		 * For example, a pure white 240 x 160 image will already overflow a 32-bit
		 * value in the sumsq vectors.
		**/
		vector<vector<int64_t>> sumRed;
		vector<vector<int64_t>> sumGreen;
		vector<vector<int64_t>> sumBlue;
		vector<vector<int64_t>> sumsqRed;
		vector<vector<int64_t>> sumsqGreen;
		vector<vector<int64_t>> sumsqBlue;

		/**
		 * Returns the sums of all pixel values in one color channel.
		 * Useful in computing the average color of a rectangle.
		 * @param channel is one of r, g, or b
		 * @param ul is (x,y) of the upper left corner of the rectangle
		 * @param w,h are the width and height of the rectangle
		**/
		int64_t GetSum(char channel, pair<int, int> ul, int w, int h);

		/**
		 * Returns the sums of squares of all pixel values in one color
		 * channel.
		 * Useful in computing the variance of a rectangle
		 * @param channel is one of r, g, or b
		 * @param ul is (x,y) of the upper left corner of the rectangle
		 * @param w,h are the width and height of the rectangle
		**/
		int64_t GetSumSq(char channel, pair<int, int> ul, int w, int h);

	public:

		/**
		 * Initialize the private vectors so that, for each color, entry
		 * (x,y) is the sum of that color value in the rectangle from
		 * (0,0) to (x,y). Similarly, for each color, the sumSq vector
		 * entry (x,y) is the sum of that color squared over all image
		 * pixels from (0,0) to (x,y).
		**/
		Stats(PNG& im);

		/**
		 * Given a rectangle, compute its sum of squared deviations from avg,
		 * over all pixels and all color channels.
		 * @param ul is (x,y) of the upper left corner of the rectangle
		 * @param w,h are the width and height of the rectangle
		**/
		double GetVar(pair<int, int> ul, int w, int h);

		/**
		 * Given a rectangle, return the average color value over the rectangle
		 * as a pixel.
		 * Each color component of the pixel is the average value of that
		 * component over the rectangle.
		 * @param ul is (x,y) of the upper left corner of the rectangle
		 * @param w,h are the width and height of the rectangle
		**/
		RGBAPixel GetAvg(pair<int, int> ul, int w, int h);

	private:

		/******************************************************************
		* IF YOU HAVE WISH TO DEFINE ANY PRIVATE ATTRIBUTES OR FUNCTIONS, *
		* ADD THEM TO stats-private.h                                    *
		******************************************************************/

		#include "stats-private.h"
};

#endif
