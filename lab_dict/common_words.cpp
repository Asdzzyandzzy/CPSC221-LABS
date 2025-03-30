/**
 * @file common_words.cpp
 * Implementation of the CommonWords class.
 *
 * @author Zach Widder
 * @date Fall 2014
 */

#include "common_words.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::feof;

string remove_punct(const string& str)
{
    string ret;
    std::remove_copy_if(str.begin(), str.end(), std::back_inserter(ret),
                        [](int c) { return std::ispunct(c); });
    return ret;
}

CommonWords::CommonWords(const vector<string>& filenames)
{
    // initialize all member variables
    init_file_word_maps(filenames);
    init_common();
}

void CommonWords::init_file_word_maps(const vector<string>& filenames)
{
    // make the length of file_word_maps the same as the length of filenames
    file_word_maps.resize(filenames.size());

    // go through all files
    for (size_t i = 0; i < filenames.size(); i++) {
        // get the corresponding vector of words that represents the current file
        vector<string> words = file_to_vector(filenames[i]);


        for (const auto& w : words) {
            file_word_maps[i][w]++;
        }
    }
}

void CommonWords::init_common()
{
    for (size_t i = 0; i < file_word_maps.size(); i++) {
        // file_word_maps[i] 是一个 map<string, int>
        for (auto const& kv : file_word_maps[i]) {
            // 只要该单词在 file i 中出现过，就说明它在这个文件出现了
            // 因此 common[word] 自增 1
            common[kv.first] += 1;
        }
    }

}

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. The vector contains all words that appear
 * in each file >= n times.
 */
vector<string> CommonWords::get_common_words(unsigned int n) const
{
    vector<string> out;
    size_t total_files = file_word_maps.size();

    // 遍历 common，检查单词是否在所有文件中都出现
    for (auto const& entry : common) {
        const string& candidate = entry.first;
        // 如果一个单词只出现在一部分文件中，就没必要检查次数了
        if (entry.second == total_files) {
            // 进一步判断：在所有文件中出现次数是否都 >= n
            bool meets_requirement = true;
            for (size_t j = 0; j < total_files; j++) {
                // 查找该词在第 j 个文件的出现次数
                auto look = file_word_maps[j].find(candidate);
                // 如果该词在此文件找不到，或者出现次数不足 n
                if (look == file_word_maps[j].end() || look->second < n) {
                    meets_requirement = false;
                    break;
                }
            }

            // 如果所有文件都满足 >= n，则加进结果
            if (meets_requirement) {
                out.push_back(candidate);
            }
        }
    }
    return out;
}

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector<string> CommonWords::file_to_vector(const string& filename) const
{
    ifstream words(filename);
    vector<string> out;

    if (words.is_open()) {
        std::istream_iterator<string> word_iter(words);
        while (!words.eof()) {
            out.push_back(remove_punct(*word_iter));
            ++word_iter;
        }
    }
    return out;
}
