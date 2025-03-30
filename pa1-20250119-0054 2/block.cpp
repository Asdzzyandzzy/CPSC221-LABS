// block.cpp
#include "block.h"
#include <cmath>
#include <iostream>

int Block::Height() const {
    if (data.empty()) return 0;
    return data[0].size();
}

int Block::Width() const {
    return data.size();
}

void Block::Build(PNG &im, int x, int width) {
    int maxAvailable = im.width() - x;  // 最大可用宽度
    int actualWidth = std::min(width, maxAvailable); // 实际有效宽度
    if (actualWidth <= 0) {
        data.clear();
        return;
    }
    int height = im.height();
    data.resize(actualWidth); // 按实际宽度调整大小
    for (int i = 0; i < actualWidth; ++i) {
        data[i].resize(height);
        int imgX = x + i;
        for (int j = 0; j < height; ++j) {
            data[i][j] = *im.getPixel(imgX, j);
        }
    }
}

void Block::Render(PNG &im, int x) const {
    int w = Width();
    int h = Height();
    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            if (x + i < im.width() && j < im.height()) {
                *im.getPixel(x + i, j) = data[i][j];
            }
        }
    }
}