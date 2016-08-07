#ifndef __DICTIONARY_H
#define __DICTIONARY_H

#include <fstream>
#include <string>
#include <unordered_set>

class Dictionary {
public:
	typedef std::string Word;
	typedef std::unordered_set<Word> WordSet;

	Dictionary(WordSet &&words) noexcept : words_(words) {}

	Dictionary(const std::string &path) {
		std::ifstream fs(path);
		std::string line;

		while (std::getline(fs, line)) {
			words_.insert(line);
		}
	}

	bool has(const std::string &word) {
		return words_.find(word) != words_.end();
	}

private:
	WordSet words_;
};

#endif