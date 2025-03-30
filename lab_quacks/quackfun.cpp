/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

namespace QuackFun {

    /**
     * Sums items in a stack.
     * @param s A stack holding values to sum.
     * @return The sum of all the elements in the stack, leaving the original
     *  stack in the same state (unchanged).
     *
     * @note You may modify the stack as long as you restore it to its original
     *  values.
     * @note You may use only two local variables of type T in your function.
     *  Note that this function is templatized on the stack's type, so stacks of
     *  objects overloading the + operator can be summed.
     * @note We are using the Standard Template Library (STL) stack in this
     *  problem. Its pop function works a bit differently from the stack we
     *  built. Try searching for "stl stack" to learn how to use it.
     * @hint Think recursively!
     */
    template <typename T>
    T sum(stack<T>& s)
    {
        

        if (s.empty()) {
            return T(); 
        }

    
        T topVal = s.top();
        s.pop();               

        T sumOfRest = sum(s);   
        s.push(topVal);         


        // Your code here
        return topVal + sumOfRest; // stub return value (0 for primitive types). Change this!
                    // Note: T() is the default value for objects, and 0 for
                    // primitive types
    }

    /**
     * Reverses even sized blocks of items in the queue. Blocks start at size
     * one and increase for each subsequent block.
     * @param q A queue of items to be scrambled
     *
     * @note Any "leftover" numbers should be handled as if their block was
     *  complete.
     * @note We are using the Standard Template Library (STL) queue in this
     *  problem. Its pop function works a bit differently from the stack we
     *  built. Try searching for "stl stack" to learn how to use it.
     * @hint You'll want to make a local stack variable.
     */
    template <typename T>
    void scramble(queue<T>& q)
    {
        stack<T> s;
            int n = q.size();       // 队列原本有 n 个元素
    int processed = 0;      // 已处理元素个数
    int blockSize = 1;      // 初始块大小从 1 开始

    // 当还没处理完所有 n 个元素时，继续处理
    while (processed < n) {
        // 本次要处理的块大小不能超过剩余未处理元素 (n - processed)
        int chunk = blockSize;
        if (chunk > n - processed) {
            chunk = n - processed;
        }
        
        if (blockSize % 2 == 1) {
            // 奇数块：保持顺序
            for (int i = 0; i < chunk; i++) {
                // 出队 -> 直接再入队尾，相当于队列旋转
                T frontVal = q.front();
                q.pop();
                q.push(frontVal);
            }
        } else {
            // 偶数块：翻转顺序
            // 先把 chunk 个元素转移到栈里
            for (int i = 0; i < chunk; i++) {
                T frontVal = q.front();
                q.pop();
                s.push(frontVal);
            }
            // 再从栈里弹回队列，这样就实现了翻转
            for (int i = 0; i < chunk; i++) {
                T topVal = s.top();
                s.pop();
                q.push(topVal);
            }
        }

        // 这一块处理完后，更新统计并让块大小加一
        processed += chunk;
        blockSize++;
    }
    }

    /**
     * @return true if the parameter stack and queue contain only elements of
     *  exactly the same values in exactly the same order; false, otherwise.
     *
     * @note You may assume the stack and queue contain the same number of items!
     * @note There are restrictions for writing this function.
     * - Your function may not use any loops
     * - In your function you may only declare ONE local boolean variable to use in
     *   your return statement, and you may only declare TWO local variables of
     *   parametrized type T to use however you wish.
     * - No other local variables can be used.
     * - After execution of verifySame, the stack and queue must be unchanged. Be
     *   sure to comment your code VERY well.
     */
    template <typename T>
    bool verifySame(stack<T>& s, queue<T>& q)
    {
        bool retval = true; // optional
        //T temp1; // rename me
        //T temp2; // rename :)

        return retval;
    }
}
