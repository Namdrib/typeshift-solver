#include "typeshift_solver.h"


// --- PUBLIC ---

typeshift_solver::typeshift_solver()
{
	;
}

typeshift_solver::typeshift_solver(ifstream &ifs)
{
	read_dictionary_words(ifs);
}

// Read words from an input stream (one word per line) to build into dictionary_words
// This dictionary will be used as a list of "real" words when building words
void typeshift_solver::read_dictionary_words(ifstream &ifs)
{
	dictionary_words.clear();
	for (string word; getline(ifs, word);)
	{
		transform(all(word), word.begin(), ::tolower);
		dictionary_words.insert(word);
	}
}

// Tokenise the input by ',' and treat each token as
// an element in `letters`. Ensure each token is sorted lexicographically
void typeshift_solver::build_letters(const string &input)
{
	stringstream ss(input);
	for (string element; getline(ss, element, ',');)
	{
		sort(all(element));
		letters.push_back(element);
	}
}

// Store the words in `dictionary_words` which are buildable
// using permutations of `letters`
// e.g. {"fnz", "eio", "nruv", "ero"} can yield:
// "four", "five", "nine", "zero" iff those words are in dictionary_words
void typeshift_solver::build_words()
{
	words.clear();
	build_words(0, "");
}

// Of the elements in `word`, print them on different lines
// according to their initial letter
// e.g. all words starting with 'a' on the first line (if there are any)
// all words starting with 'z' on the last line (if there are any)
// Letters without any corresponding words will be skipped
void typeshift_solver::pretty_print_words()
{
	size_t i = 0;
	for (char c = 'a'; c <= 'z'; c++)
	{
		bool output = false;
		while (i < words.size() && words[i][0] == c)
		{
			cout << words[i] << " ";
			i++;
			output = true;
		}
		if (output) cout << endl;
	}
	cout << endl;
}

// Given a new input (after having built letters), streamline the
// available letters based on the type of input given
// upper-case letters in input will be stripped from letters
// e.g. if input is "TeSt", t will be removed from letters[0] and S from letters[2]
void typeshift_solver::refresh(const string &input)
{
	// parse a command
	if (input.size() >= 2 && input[0] == '>' && input[1] == ' ')
	{
		string command = input.substr(2);
		parse_command(command);
		return;
	}
	if (input.size() != letters.size())
	{
		cerr << "Input size != letter size" << endl;
		return;
	}
	for (size_t i=0; i<input.size(); i++)
	{
		// upper-case: remove from letters[i]
		if (isupper(input[i]))
		{
			char c = tolower(input[i]);
			auto position = letters[i].find(c);
			if (position == string::npos)
			{
				cerr << letters[i] << " does not contain " << c << endl;
				return;
			}
			letters[i].erase(position, 1);
		}
		sort(all(letters[i]));
	}
}

// --- PRIVATE ---

// The recursive part of build_words()
void typeshift_solver::build_words(size_t index, string current_word)
{
	if (index >= letters.size())
	{
		if (dictionary_words.count(current_word) != 0)
		{
			words.push_back(current_word);
		}
		return;
	}

	for (size_t i=0; i<letters[index].size(); i++)
	{
		build_words(index+1, current_word + letters[index][i]);
	}
}


// Called by `refresh()` if the input starts with "> "
void typeshift_solver::parse_command(const string &command)
{
	if (command == "list" || command == "letters" || command == "show_letters")
	{
		cout << letters << endl;
	}
	else if (command == "help" || command == "commands")
	{
		cout << "list/letters/show_letters to see all current letters" << endl;
		cout << "help to show this message" << endl;
	}
	else
	{
		cout << command << " is not a valid command" << endl;
		cout << "see \"help\" for a list of commands to use" << endl;
	}
}
