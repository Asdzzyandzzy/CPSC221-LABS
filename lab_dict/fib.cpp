/**
 * @file fib.cpp
 * Contains Fibonacci-number generating functions both utilizing and not
 * utilizing memoization.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "fib.h"
#include <map>

using std::map;

/**
 * Calculates the nth Fibonacci number where the zeroth is defined to be
 * 0.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long fib(unsigned long n)
{
    /* Your code goes here! */

    // Stub value - remove when you are done
    if (n < 2) {
        return n;  // fib(0) = 0, fib(1) = 1
    }
    return fib(n - 1) + fib(n - 2);
}

/**
 * Calculates the nth Fibonacci number where the zeroth is defined to be
 * 0. This version utilizes memoization.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long memoized_fib(unsigned long n)
{
    /* Your code goes here! */

    // Stub value - remove when you are done
    static map<unsigned long, unsigned long> memo = {
        {0, 0},  // fib(0)
        {1, 1}   // fib(1)
    };

    // Check if we've already computed fib(n)
    auto lookup = memo.find(n);
    if (lookup != memo.end()) {
        // If we have a stored value, return it immediately
        return lookup->second;
    }

    // Otherwise, compute it recursively and store in memo
    unsigned long result = memoized_fib(n - 1) + memoized_fib(n - 2);
    memo[n] = result;

    return result;
}
