#ifndef TYPESHIFT_SOLVER_H
#define TYPESHIFT_SOLVER_H

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <sstream>
#include <unistd.h>
#include <vector>
using namespace std;

#include "helpers.cpp"

class typeshift_solver
{
private:
	// The nth element of `letters` should be a possible nth element of a word
	// Letters may have varying-length elements (e.g. 1 length for [0], 4 for [1])
	// such as: {"i", "fnst"} => "if", "in", "is", "it"
	vector<string> letters;

	// Elements of words are words in `dictionary_words` which can be formed
	// with various permutations of the elements in `letters`
	vector<string> words;

	// The set of words to be used as a lookup table. 
	// Keeps track of what is considered a "real" word
	set<string> dictionary_words;

public:
	typeshift_solver();

	typeshift_solver(ifstream &ifs);

	// Read words from an input stream (one word per line) to build into `dictionary_words`
	void read_dictionary_words(ifstream &ifs);

	// Tokenise the input by ',' and treat each token as
	// an element in `letters`. Ensure each token is sorted lexicographically
	void build_letters(const string &input);

	// Store the words in `dictionary_words` which are buildable
	// using permutations of `letters`
	// e.g. {"fnz", "eio", "nruv", "ero"} can yield:
	// "four", "five", "nine", "zero" iff those words are in dictionary_words
	void build_words();

	// Of the elements in `word`, print them on different lines
	// according to their initial letter
	// e.g. all words starting with 'a' on the first line (if there are any)
	// all words starting with 'z' on the last line (if there are any)
	// Letters without any corresponding words will be skipped
	void pretty_print_words();

	// Given a new input (after having built letters), streamline the
	// available letters based on the type of input given
	// upper-case letters in input will be stripped from letters
	// e.g. if input is "TeSt", t will be removed from letters[0] and S from letters[2]
	void refresh(const string &input);

private:
	// The recursive part of build_words()
	void build_words(size_t index, string current_word);

	// Called by `refresh()` if the input starts with "> "
	void parse_command(const string &command);
};

#endif // TYPESHIFT_SOLVER_H
