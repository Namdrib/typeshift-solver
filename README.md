# typeshift-solver

## Requirements
- make (optional if you can hand-compile)
- C++11

A command-line (somewhat) interactive program that can be used to attempt to provide solutions to the word game [TypeShift](http://playtypeshift.com/) by calculating every permutation of the provided letters and displaying those which may be valid.

This program does not use the Merriam-Webster dictionary, and so may not produce all the correct answers. Some convenient dictionaries are provided [here](https://github.com/dolph/dictionary) (not my work).

The user may load their own dictionaries, provided it fits the same format the program reads (all lower-case, one word per line, line terminated with "\n")

## Usage
If the user is given a board like [this](https://upload.wikimedia.org/wikipedia/en/thumb/2/2b/TypeShiftScreenshot.png/220px-TypeShiftScreenshot.png) (taken from Wikipedia's article for this game), they could run the program like:

```
./main -q swdcf,oali,xnru,eokdb,osy
```

as a result, the program should print something like:

```
candy canes carbo carbs cards cares carks cines cires clubs clues condo cones coney conks conky corby cords cores corks corky coxes
dandy darbs dares darks darky daubs dauby dines dinks dinky dirks dorks dorky
fanes fanos fards fares faros faxes finds fines finks finos fires fixes flubs flues fluky fonds forbs forby fordo fords fores forks forky foxes
sands sandy sanes sards sarks sarky saros saxes sines sinks sires sixes slubs slues sones sorbs sords sores souks
wands wanes waney wards wares warks wauks waxes winds windy wines winey winks winos wires wonks wonky words wordy works
```

which the user may then use as a reference for a large number of valid words (again, the result depends on the dictionary used by the user). The query string (string after the `-q` does not need to be in alphabetical order - the program takes care of that automatically)

If the program is run in "clues mode" (denoted by running with the `-c` switch), where some letters disappear if they are no longer of use, the user can provide more information about removed words. 
To do so, the user can keep tying words into the terminal. Words entered with capital letters, such as "THis" or "tHiS", etc. will remove such letters from the appropriate column and re-build the list of possible words.

For example, in the first strawberry puzzle, after getting "vista", the game blocks out "v" from the first column and "a" from the last column. The user can then write "VistA" into the terminal to remove the v and a from their correct columns, and the potential words will be rebuilt. 

```
$ ./main -c -q ckv,iha,oms,stke,kela
camel caste choke chose
kiosk
vista

VistA // the user input
camel caste choke chose
kiosk
// note vista is now gone
```

This feature is more useful on larger puzzles where there are more words that are not part of the puzzle. 

The user can run `./main -h` to see other help messages.


Credits to Zach Gage for creating the original game
