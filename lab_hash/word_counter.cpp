/**
 * @file word_counter.cpp
 * Implementation of the WordFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Spring 2012
 */

using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::pair;
using std::string;
using std::vector;

template <template <class K, class V> class Dict>
WordFreq<Dict>::WordFreq(const string& filename) : dict(256) {
    /**
     * @todo Implement this function.
     * @see char_counter.cpp if you're having trouble.
     */
    TextFile infile(filename);
    while (infile.good()) {
        std::string word = infile.getNextWord();

        // if the file parser returns empty strings occasionally, you can guard:
        if (!word.empty()) {
            // Increase count by 1
            dict[word] = dict[word] + 1;
        }
    }
}

template <template <class K, class V> class Dict>
vector<pair<string, int>> WordFreq<Dict>::getWords(int threshold) {
    vector<pair<string, int>> ret;
    /**
     * @todo Implement this function.
     * @see char_counter.cpp if you're having trouble.
     */

    // The HashTable supports iteration from begin() to end()
    for (auto it = dict.begin(); it != dict.end(); it++) {
        // *it is a std::pair<std::string, int>
        if (it->second >= threshold) {
            ret.push_back(*it);
        }
    }

    return ret;
}
