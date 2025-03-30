/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    /// @todo Update to return the index you are choosing to be your root.
    return 0;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the left child.

    return 2 * currentIdx + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the right child.

    return 2 * currentIdx + 2;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    /// @todo Update to return the index of the parent.

    return (currentIdx - 1) / 2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    /// @todo Update to return whether the given node has a child

    return leftChild(currentIdx) < _elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the child with highest priority
    ///   as defined by higherPriority()

    // Return the child with higher priority (depending on the Compare functor).
    // First, check if there is no right child. If so, left child is the only child.
    size_t left = leftChild(currentIdx);
    size_t right = rightChild(currentIdx);
    
    // If there is no right child, the left child is the only option.
    if (right >= _elems.size()) {
        return left;
    }
    
    // Otherwise, compare left vs. right with the higherPriority() functor.
    // higherPriority(x, y) == true means x should come before y in the heap.
    if (higherPriority(_elems[left], _elems[right])) {
        return left;
    } else {
        return right;
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    /// @todo Implement the heapifyDown algorithm.

    // We "sink" the node at currentIdx down the tree until the heap property is restored.
    if (!hasAChild(currentIdx)) {
        // If there are no children, nothing to do.
        return;
    }
    // Identify which child has higher priority.
    size_t childIdx = maxPriorityChild(currentIdx);

    // If the child has higher priority than the current node, swap and recurse down.
    if (higherPriority(_elems[childIdx], _elems[currentIdx])) {
        std::swap(_elems[currentIdx], _elems[childIdx]);
        heapifyDown(childIdx);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    /// @todo Depending on your implementation, this function may or may
    ///   not need modifying
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    /// @todo Construct a heap using the buildHeap algorithm
    /// Your algorithm should use heapifyDown() so that it constructs
    /// the same heap as our test case.
    _elems = elems;

    // The last non-leaf node is parent(_elems.size() - 1).
    if (!_elems.empty()) {
        for (int i = parent(_elems.size() - 1); i >= 0; i--) {
            heapifyDown(i);
        }
    }

}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    /// @todo Remove, and return, the element with highest priority

    if (empty()) {
        throw std::out_of_range("Cannot pop() from an empty heap.");
    }

    // The element to return
    T highestPriorityElem = _elems[root()];

    // Move the last element to the root position
    std::swap(_elems[root()], _elems[_elems.size() - 1]);
    _elems.pop_back();

    // Re-heapify down from the root
    if (!empty()) {
        heapifyDown(root());
    }

    return highestPriorityElem;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    /// @todo Return, but do not remove, the element with highest priority

    if (empty()) {
        throw std::out_of_range("Cannot peek() an empty heap.");
    }
    return _elems[root()];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    /// @todo Add elem to the heap

    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    /// @todo Determine if the heap is empty

    return _elems.empty();
}
