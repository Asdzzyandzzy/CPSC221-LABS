/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"
#include <algorithm>
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    ifstream words(filename);
    string word;
    if (words.is_open()) {
        while (getline(words, word)) {
            add_word_to_dict(word);
        }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    for (const string& word : words) {
        add_word_to_dict(word);
    }
}

/**
 * @param word The word to add to the dictionary
 * Adds the word as a (key, value) pair to the dictionary.
 * NOTE: word is the value. You will need to decide an appropriate key
 * for the word.
 */
void AnagramDict::add_word_to_dict(const std::string& word)
{
    /* Your code goes here! */

    string sorted_w = word;
    std::sort(sorted_w.begin(), sorted_w.end());

    // 2. 将原始单词插入到此排序形式对应的 vector 中
    dict[sorted_w].push_back(word);
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */

    // Stub value - remove when you are done
    // 1. 排序该 word 以得到其 key
    string key = word;
    std::sort(key.begin(), key.end());

    // 2. 在 dict 中查找该 key
    auto it = dict.find(key);
    if (it == dict.end()) {
        // 如果找不到，就返回空容器
        return vector<string>();
    }

    // 否则返回这个 key 下所有的 anagrams
    return it->second;
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> result;
    // 遍历字典，跳过只有 1 个元素的组
    for (auto const & entry : dict) {
        // 如果这一组里有两词以上，才是有效的 anagram group
        if (entry.second.size() > 1) {
            result.push_back(entry.second);
        }
    }
    return result;
}
