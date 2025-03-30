/**
 * @file            stats.cpp
 * @author          your CWL
 * @description     Implementation of Stats functions
 *
 * THIS FILE WILL BE SUBMITTED
**/

#include "stats.h"

Stats::Stats(PNG& im) {
	/* Complete your implementation below */

	int w = im.width();
    int h = im.height();
    sumRed.resize(h, vector<int64_t>(w, 0));
    sumGreen.resize(h, vector<int64_t>(w, 0));
    sumBlue.resize(h, vector<int64_t>(w, 0));

    sqSumRed.resize(h, vector<int64_t>(w, 0));
    sqSumGreen.resize(h, vector<int64_t>(w, 0));
    sqSumBlue.resize(h, vector<int64_t>(w, 0));

    // 构建前缀和
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            RGBAPixel pixel = *im.getPixel(x, y);

            int64_t r = pixel.r;
            int64_t g = pixel.g;
            int64_t b = pixel.b;

           
            int64_t rVal = r;
            int64_t gVal = g;
            int64_t bVal = b;
            
            int64_t rSq = r * r;
            int64_t gSq = g * g;
            int64_t bSq = b * b;

            if (x > 0) {
                rVal += sumRed[y][x - 1];
                gVal += sumGreen[y][x - 1];
                bVal += sumBlue[y][x - 1];

                rSq += sqSumRed[y][x - 1];
                gSq += sqSumGreen[y][x - 1];
                bSq += sqSumBlue[y][x - 1];
            }
            if (y > 0) {
                rVal += sumRed[y - 1][x];
                gVal += sumGreen[y - 1][x];
                bVal += sumBlue[y - 1][x];

                rSq += sqSumRed[y - 1][x];
                gSq += sqSumGreen[y - 1][x];
                bSq += sqSumBlue[y - 1][x];
            }
            
            if (x > 0 && y > 0) {
                rVal -= sumRed[y - 1][x - 1];
                gVal -= sumGreen[y - 1][x - 1];
                bVal -= sumBlue[y - 1][x - 1];

                rSq -= sqSumRed[y - 1][x - 1];
                gSq -= sqSumGreen[y - 1][x - 1];
                bSq -= sqSumBlue[y - 1][x - 1];
            }

            sumRed[y][x] = rVal;
            sumGreen[y][x] = gVal;
            sumBlue[y][x] = bVal;

            sqSumRed[y][x] = rSq;
            sqSumGreen[y][x] = gSq;
            sqSumBlue[y][x] = bSq;
        }
    }
}


int64_t Stats::GetSum(char channel, pair<int, int> ul, int w, int h) {
	int x1 = ul.first;
    int y1 = ul.second;
    int x2 = x1 + w - 1;
    int y2 = y1 + h - 1;

    
    const auto & prefix = (channel == 'r') ? sumRed
                         : (channel == 'g') ? sumGreen
                         : sumBlue;  

    int64_t total = prefix[y2][x2];
    if (x1 > 0)     total -= prefix[y2][x1 - 1];
    if (y1 > 0)     total -= prefix[y1 - 1][x2];
    if (x1 > 0 && y1 > 0) total += prefix[y1 - 1][x1 - 1];

    return total;
}

int64_t Stats::GetSumSq(char channel, pair<int, int> ul, int w, int h) {
	int x1 = ul.first;
    int y1 = ul.second;
    int x2 = x1 + w - 1;
    int y2 = y1 + h - 1;

   
    const auto & prefix = (channel == 'r') ? sqSumRed
                         : (channel == 'g') ? sqSumGreen
                         : sqSumBlue; 

    int64_t total = prefix[y2][x2];
    if (x1 > 0)     total -= prefix[y2][x1 - 1];
    if (y1 > 0)     total -= prefix[y1 - 1][x2];
    if (x1 > 0 && y1 > 0) total += prefix[y1 - 1][x1 - 1];

    return total;
}

/**
 * Given a rectangle, compute its sum of squared deviations from mean, over all color channels.
 * See written specification for a description of this function.
**/
double Stats::GetVar(pair<int, int> ul, int w, int h) {
	int64_t sumR = GetSum('r', ul, w, h);
    int64_t sumG = GetSum('g', ul, w, h);
    int64_t sumB = GetSum('b', ul, w, h);

    int64_t sqR = GetSumSq('r', ul, w, h);
    int64_t sqG = GetSumSq('g', ul, w, h);
    int64_t sqB = GetSumSq('b', ul, w, h);

    int area = w * h;

   
    double varR = (double)sqR - ((double)sumR * (double)sumR) / (double)area;
    double varG = (double)sqG - ((double)sumG * (double)sumG) / (double)area;
    double varB = (double)sqB - ((double)sumB * (double)sumB) / (double)area;

    return varR + varG + varB;
}


RGBAPixel Stats::GetAvg(pair<int, int> ul, int w, int h) {
	int64_t sumR = GetSum('r', ul, w, h);
    int64_t sumG = GetSum('g', ul, w, h);
    int64_t sumB = GetSum('b', ul, w, h);

    int area = w * h;
   
    int rAvg = (int)(sumR / area);
    int gAvg = (int)(sumG / area);
    int bAvg = (int)(sumB / area);

    return RGBAPixel(rAvg, gAvg, bAvg);
}

/****************************************************************
* IF YOU HAVE DEFINED ANY PRIVATE FUNCTIONS IN stats-private.h, *
* ADD YOUR IMPLEMENTATIONS BELOW                                *
****************************************************************/

