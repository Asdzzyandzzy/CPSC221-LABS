/**
 * @file schashtable.cpp
 * Implementation of the SCHashTable class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */

#include "schashtable.h"

using hashes::hash;
using std::list;
using std::pair;

template <class K, class V>
SCHashTable<K, V>::SCHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new list<pair<K, V>>[size];
    elems = 0;
}

template <class K, class V>
SCHashTable<K, V>::~SCHashTable()
{
    delete[] table;
}

template <class K, class V>
SCHashTable<K, V> const& SCHashTable<K, V>::
operator=(SCHashTable<K, V> const& rhs)
{
    if (this != &rhs) {
        delete[] table;
        table = new list<pair<K, V>>[rhs.size];
        for (size_t i = 0; i < rhs.size; i++)
            table[i] = rhs.table[i];
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
SCHashTable<K, V>::SCHashTable(SCHashTable<K, V> const& other)
{
    table = new list<pair<K, V>>[other.size];
    for (size_t i = 0; i < other.size; i++)
        table[i] = other.table[i];
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void SCHashTable<K, V>::insert(K const& key, V const& value)
{
    ++elems;
    if (shouldResize())
        resizeTable();
    pair<K, V> p(key, value);
    size_t idx = hash(key, size);
    table[idx].push_front(p);
}

template <class K, class V>
void SCHashTable<K, V>::remove(K const& key)
{
    typename list<pair<K, V>>::iterator it;
    /**
     * @todo Implement this function.
     *
     * Please read the note in the lab spec about list iterators and the
     * erase() function on std::list!
     */

     // Hash the key to find its bucket
     size_t idx = hashes::hash(key, size);

     // Reference to the linked list at that bucket
     auto& bucket = table[idx];
 
     // Iterate through the bucket to find the (key, value) pair
     for (auto it = bucket.begin(); it != bucket.end(); it++) {
         if (it->first == key) {
             // Erase the pair and decrement the number of elements
             bucket.erase(it);
             elems--;
             return;  // We're done once we find and remove the key
         }
     }
}

template <class K, class V>
V SCHashTable<K, V>::find(K const& key) const
{
    size_t idx = hash(key, size);
    typename list<pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return it->second;
    }
    return V();
}

template <class K, class V>
V& SCHashTable<K, V>::operator[](K const& key)
{
    size_t idx = hash(key, size);
    typename list<pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return it->second;
    }

    ++elems;
    if (shouldResize())
        resizeTable();

    idx = hash(key, size);
    pair<K, V> p(key, V());
    table[idx].push_front(p);
    return table[idx].front().second;
}

template <class K, class V>
bool SCHashTable<K, V>::keyExists(K const& key) const
{
    size_t idx = hash(key, size);
    typename list<pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return true;
    }
    return false;
}

template <class K, class V>
void SCHashTable<K, V>::clear()
{
    delete[] table;
    table = new list<pair<K, V>>[17];
    size = 17;
    elems = 0;
}

template <class K, class V>
void SCHashTable<K, V>::resizeTable()
{
    typename list<pair<K, V>>::iterator it;
    /**
     * @todo Implement this function.
     *
     * Please read the note in the spec about list iterators!
     * The size of the table should be the closest prime to size * 2.
     *
     * @hint Use findPrime()!
     */
     // Double the current size and find the next prime
    size_t newSize = findPrime(size * 2);

    // Allocate a new table of lists
    std::list<std::pair<K, V>>* newTable = new std::list<std::pair<K, V>>[newSize];

    // Re-hash all existing elements
    for (size_t i = 0; i < size; i++) {
        // For each (key, value) pair in the old bucket
        for (auto& kv : table[i]) {
            // Compute its new index in newTable
            size_t newIdx = hashes::hash(kv.first, newSize);

            // Insert at front (or back) of the new bucket
            newTable[newIdx].push_front(kv);
        }
    }

    // Delete the old table
    delete[] table;

    // Update the table to the new one
    table = newTable;
    size = newSize;
}
