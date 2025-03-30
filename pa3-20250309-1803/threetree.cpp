/**
 * @file            threetree.cpp
 * @author          your CWL
 * @description     Implementation of ThreeTree functions
 *
 * THIS FILE WILL BE SUBMITTED
**/

#include "threetree.h"

/**
 * ThreeTree constructor given tolerance for variance.
**/
ThreeTree::ThreeTree(PNG& imIn, double tol) {
    /* Complete your implementation below */
    root = nullptr;
    Stats s(imIn);
    root = BuildTree(s, make_pair(0, 0), imIn.width(), imIn.height(), tol);
}

/**
 * Helper for the ThreeTree constructor.
**/
Node* ThreeTree::BuildTree(Stats& s, pair<int,int> ul, int w, int h, double tol) {
    if (w <= 0 || h <= 0) return nullptr;

    RGBAPixel avgColor = s.GetAvg(ul, w, h);
    double var = s.GetVar(ul, w, h);

    Node* node = new Node(ul, w, h, avgColor, var);

   
    
    if ((w == 1 && h == 1) || (tol > 0 && var <= tol)) {
        node->A = node->B = node->C = nullptr;
        return node;
    }
   
    bool splitVertical = (w >= h); 

    if (splitVertical) {
       
        int base = w / 3;
        int rem  = w % 3;

        
        int subW1 = base;
        int subW2 = base;
        int subW3 = base;
        if (rem == 1) {
            subW2++;
        } else if (rem == 2) {
            subW1++;
            subW3++;
        }

      
        node->A = BuildTree(s, ul, subW1, h, tol);

      
        pair<int,int> ulB(ul.first + subW1, ul.second);
        node->B = BuildTree(s, ulB, subW2, h, tol);

       
        pair<int,int> ulC(ul.first + subW1 + subW2, ul.second);
        node->C = BuildTree(s, ulC, subW3, h, tol);

    } else {
       
        int base = h / 3;
        int rem  = h % 3;

        int subH1 = base;
        int subH2 = base;
        int subH3 = base;
        if (rem == 1) {
            subH2++;
        } else if (rem == 2) {
            subH1++;
            subH3++;
        }

        node->A = BuildTree(s, ul, w, subH1, tol);

      
        pair<int,int> ulB(ul.first, ul.second + subH1);
        node->B = BuildTree(s, ulB, w, subH2, tol);

     
        pair<int,int> ulC(ul.first, ul.second + subH1 + subH2);
        node->C = BuildTree(s, ulC, w, subH3, tol);
    }

    return node;
}


/**
 * Render ThreeTree and return the resulting image.
**/
PNG ThreeTree::Render() const {
    if (!root) {
        return PNG();
    }

    PNG out;
    out.resize(root->width, root->height);
    RenderNode(root, out);
    return out;
}

void ThreeTree::RenderNode(Node* subroot, PNG & out) const {
    if (subroot == nullptr) {
        return;
    }
    if (!subroot->A && !subroot->B && !subroot->C) {
        int x0 = subroot->upleft.first;
        int y0 = subroot->upleft.second;
        for (int dy = 0; dy < subroot->height; dy++) {
            for (int dx = 0; dx < subroot->width; dx++) {
                RGBAPixel * px = out.getPixel(x0 + dx, y0 + dy);
                px->r = subroot->avg.r;
                px->g = subroot->avg.g;
                px->b = subroot->avg.b;
            }
        }
    } else {
        RenderNode(subroot->A, out);
        RenderNode(subroot->B, out);
        RenderNode(subroot->C, out);
    }
}

/**
 * Delete allocated memory.
**/
void ThreeTree::Clear() {
    /* Complete your implementation below */

    ClearHelper(root);
    root = nullptr;
    
}

void ThreeTree::ClearHelper(Node* subroot) {
    if (subroot == nullptr) {
        return;
    }
    ClearHelper(subroot->A);
    ClearHelper(subroot->B);
    ClearHelper(subroot->C);
    delete subroot;
}

/**
 * Copy other tree into this tree object.
**/
void ThreeTree::Copy(const ThreeTree& other) {
    /* Complete your implementation below */
    if (this == &other) {
        return;
    }
    root = nullptr;

    Clear();
    
    
    root = CopyHelper(other.root);
}

Node* ThreeTree::CopyHelper(const Node* otherRoot) {
    if (otherRoot == nullptr) {
        return nullptr;
    }

    Node* newNode = new Node(
        otherRoot->upleft,
        otherRoot->width,
        otherRoot->height,
        otherRoot->avg,
        otherRoot->var
    );

    newNode->A = CopyHelper(otherRoot->A);
    newNode->B = CopyHelper(otherRoot->B);
    newNode->C = CopyHelper(otherRoot->C);

    return newNode;
}

/**
 * Returns the number of nodes in the tree
**/
int ThreeTree::Size() const {
    return SizeHelper(root);
}

int ThreeTree::SizeHelper(const Node* subroot) const {
    if (!subroot) return 0;
    return 1 + SizeHelper(subroot->A)
             + SizeHelper(subroot->B)
             + SizeHelper(subroot->C);
}
/**
 * Returns the number of leaf nodes in the tree
**/
int ThreeTree::NumLeaves() const {
    return LeafHelper(root);
}

int ThreeTree::LeafHelper(const Node* subroot) const {
    if (!subroot) return 0;
    if (!subroot->A && !subroot->B && !subroot->C) {
        return 1;
    }
    return LeafHelper(subroot->A)
         + LeafHelper(subroot->B)
         + LeafHelper(subroot->C);
}

/**
 * Rearranges the tree contents so that when rendered, the image appears
 * to be rotated 90 degrees clockwise.
 * See threetree.h for specification details.
 *
 * You may want a recursive helper function for this.
**//**
 * 顺时针旋转整棵 ThreeTree 90 度，
 * 在保持节点 avg/var 不变的前提下，
 * 更新坐标和宽高，使其最终渲染结果正好是原图的 90° CW。
 *//**
 * 顺时针旋转整棵 ThreeTree 90 度。
 * 保持所有节点的 avg/var 不变，只更新它们的 (x,y,w,h)。
 *//**
 * 顺时针旋转整棵 ThreeTree 90°。
 * 
 * 要求：原先 root->width, root->height 分别是图像的
 *       (宽, 高)。旋转后得到 (高, 宽)。
 *       不重新计算 avg/var，只更新每个节点的 (upleft, width, height)。
 */
/**
 * Rearranges the tree contents so that when rendered, the image appears
 * to be rotated 90 degrees clockwise.
 * See threetree.h for specification details.
 *
 * You may want a recursive helper function for this.
**/
/**
 * Rearranges the tree contents so that when rendered,
 * the image appears to be rotated 90 degrees clockwise.
 * 
 * We do this by "re‐splitting" in the rotated orientation:
 * - The root now occupies (0,0) with size (newW × newH).
 * - If w >= h, we do a vertical 3-split; else horizontal 3-split.
 * - Recursively do the same for child nodes.
 */
 void ThreeTree::RotateCW() {
    if (!root) return;

    // 原图大小
    int originalWidth  = root->width;   // 例如 256
    int originalHeight = root->height;  // 例如 224

    // 旋转后，宽高交换
    int newWidth  = originalHeight; // 224
    int newHeight = originalWidth;  // 256

    // 从根节点开始，令它占据新的 (0,0,newWidth,newHeight)
    RotateCWHelper(root, 0, 0, newWidth, newHeight);
}

/**
 * 递归函数：将 node 安排到 (x,y,w,h) 这个新区域，
 * 并根据 w>=h 或 w<h 做三分，把子节点分配到各自的子区域。
 *
 * - **注意**：我们不再使用 node 原先的 (upleft,width,height)，
 *   而是用新的 (x,y,w,h) 覆盖它，然后再往子节点分配子区域。
 * - 这样最终在渲染时，树就会覆盖一块 "旋转过" 的区域，
 *   形成顺时针 90° 的效果。
 */
void ThreeTree::RotateCWHelper(Node* node, int x, int y, int w, int h) {
    if (!node) return;

    // 1) 直接用新参数覆盖此结点的 bounding box
    node->upleft = std::make_pair(x, y);
    node->width  = w;
    node->height = h;

    // 2) 若是叶子，无需再分割子节点
    if (!node->A && !node->B && !node->C) {
        return;
    }

    // 3) 否则基于新的 w,h 判断如何三分
    bool splitVertical = (w >= h); // 与 build 时相同的逻辑
    if (splitVertical) {
        // 垂直三分 (A/B/C 左中右)
        int base = w / 3;
        int r    = w % 3;
        int wA   = base + (r > 0 ? 1 : 0);
        int wB   = base + (r > 1 ? 1 : 0);
        int wC   = w - wA - wB;

        // A: 左
        RotateCWHelper(node->A, x,       y, wA, h);
        // B: 中
        RotateCWHelper(node->B, x+wA,    y, wB, h);
        // C: 右
        RotateCWHelper(node->C, x+wA+wB, y, wC, h);

    } else {
        // 水平三分 (A/B/C 上中下)
        int base = h / 3;
        int r    = h % 3;
        int hA   = base + (r > 0 ? 1 : 0);
        int hB   = base + (r > 1 ? 1 : 0);
        int hC   = h - hA - hB;

        // A: 上
        RotateCWHelper(node->A, x, y,       w, hA);
        // B: 中
        RotateCWHelper(node->B, x, y + hA,  w, hB);
        // C: 下
        RotateCWHelper(node->C, x, y + hA + hB, w, hC);
    }
}
