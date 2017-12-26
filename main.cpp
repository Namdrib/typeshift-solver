#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <unistd.h>
#include <vector>
using namespace std;

#include "helpers.cpp"
#include "typeshift_solver.h"

class config
{
public:
	bool clues;
	string dictionary; // file to which words are compared, should have one word per line
	string query;
	config()
	{
		clues = false;
	}
};

void usage(char *program)
{
	cout << "Usage:" << endl;
	cout << program << " [options]" << endl;
	cout << endl;

	cout << "Options:" << endl;
	cout << "  -c  : clues mode. keep taking input, removing spent letters (capital)" << endl;
	cout << "        e.g. inputting \"miNH\" will remove n from 3rd column, h from 4th" << endl;
	cout << "        helps to narrow down the search space" << endl;
	cout << "  -d  : dictionary (of words) to use" << endl;
	cout << "  -q  : input query. comma-separated strings, representing each column's letters" << endl;
	cout << "        e.g. \"ab,cd,ef\" (without quotes)" << endl;
	cout << "  -h  : show this help and exit" << endl;
	cout << endl;

	cout << "In clues mode, typing a command (defined as a string starting with \"> \") will" << endl;
	cout << "run a program-defined command. Run \"> help\" to see a list of available commands" << endl;
}

void parse_args(int argc, char** argv, config &c)
{
	// Default values
	c.clues = false;
	c.dictionary = "all_words.txt";
	// c.query = "lgm,iue,nad,rik,sda"; // first "fast five"
	c.query = "ost,niew,exno"; // three-letter numbers
	// c.query = "fnz,ioe,vunr,ero"; // four-letter numbers

	// Read arguments
	int ch;
	while ((ch = getopt(argc, argv, "hcd:q:")) != -1)
	{
		switch (ch)
		{
			case 'h':
				usage(argv[0]);
				exit(0);
				break;
			case 'c':
				c.clues = true;
				break;
			case 'd':
				c.dictionary = optarg;
				break;
			case 'q':
				c.query = optarg;
				break;
			default:
				usage(argv[0]);
				exit(1);
		}
	}
}

int main(int argc, char** argv)
{
	config c;
	parse_args(argc, argv, c);

	ifstream ifs(c.dictionary);
	if (!ifs.is_open())
	{
		cerr << "Error, unable to open " << c.dictionary << endl;
		return 1;
	}

	typeshift_solver ts(ifs);
	ifs.close();
	ts.build_letters(c.query);
	ts.build_words();
	ts.pretty_print_words();

	if (c.clues)
	{
		for (string input; getline(cin, input);)
		{
			ts.refresh(input);
			ts.build_words();
			ts.pretty_print_words();
		}

		cout << "Inputs exhausted" << endl;
	}
}
