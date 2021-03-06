
/*****************************************************************************
 
 Copyright (C) 2011 by Bernard Geyer
 
 http://bernardgeyer.com/
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 *****************************************************************************/

#ifndef _HSYMBOLS
#define _HSYMBOLS

#include <string>
#include <vector>
#include <map>

//--------------------------------------------------------------
//							HARFANG SYMBOLS
//--------------------------------------------------------------

// Terminology :
// The meaning of words like dictionary, list etc... is the general meaning of this terms by average humans
// and not specific computer data structures. The way they are called has only to do with their function,
// not their implementation.

// A harfang symbol is a concept that is represented internally by a positive integer number called "ID" and a type (also a number).
// The ID is generated by a counter that is incremented each time a new symbol is created.
// The type represents the type of symbol.
// The symbols are stored in a symbol list.

// Each symbol can be associated with a word in a dictionary.
// Dictionaries of different languages can share the same symbol.
// Different entries in a dictionary can share the same symbol.
// The name of the dictionary has to be in english.
// The user can select the dictionary he wants to communicate with harfang

// Symbols are associated with harfang events
// They represent event names (type 1) or named parameters of events

//--------------------------------------------------------------

struct hSymbol {
	unsigned int ID;
	unsigned int type;
};

const int H_SYMBOL		  = 0;	// It's an unspecified symbol
const int H_OBJECT_SYMBOL = 1;  // It's the symbol of an object
const int H_EVENT_SYMBOL  = 2;	// It's the symbol of an event

struct hDictionary {
	std::string name;
	std::map <std::string, hSymbol> symbols;
};

//--------------------------------------------------------------

class hSymbols {
public:
	hSymbols();
	// Create a symbol list and its default dictionary

	hDictionary * getDictionary(std::string name);
	// Return the adress of a dictionary or NULL if not found.

	hDictionary * getSelectedDictionary(void);
	// Return the adress of the dictionary actually selected.

	void addDictionary(std::string name);
	// Create a new dictionary. Does nothing if it already exists.

	void selectDictionary(std::string name);
	// Select a dictionary. Does nothing if the dictionary doesn't exist

	void listDictionaries(void);
	// List all the dictionaries in a symbol list (for tests)

	hSymbol getSymbol(std::string dictName, std::string symName);
	// - Test if a dictionary exists or return 0
	// - Test if a symbol exists in the dictionary
	// - Return the symbol or an empty symbol if not found
	// DictName == NULL means default dictionary
	
	hSymbol aliasSymbol(std::string newDictName, std::string newSymName, std::string oldDictName, std::string oldSymName);
	// Make an alias of a symbol
	// old is the original, new is the symbol to create
	// Different dictionaries means translate
	// Same dictionary means synonym
	// Return the symbol

	hSymbol genSym(std::string dictName, std::string symName);
	// More general function
	// - Test if a dictionary exists or return 0
	// - Test if a symbol exists in the dictionary
	// - Create a new symbol if it does not exist
	// - Return the symbol

	std::string symbolName(std::string dictName, unsigned int ID);
	// Return the name associated with the symbol at ID

	void listSymbols(std::string dictName);
	// List all the symbols in a symbol list (for tests)

	//------------------------------------

protected:
	hSymbol createSymbol(std::string dictName, std::string symNameD, unsigned int type);
	// This is a helper function used by the system.
	// User function to create symbols is 'genSym'.
	
	// Create a symbol of a certain type.
	// - Test if a dictionary exists or return 0
	// - Create a new symbol in it
	// - Return the symbol
	
	//------------------------------------

	hDictionary* selectedDictionary;

private:
	std::vector<hDictionary*> dictionaries;
	unsigned int lastID;
};

#endif // _HSYMBOLS
