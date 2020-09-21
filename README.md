lexical-analyzer produces a lexical analysis function, and a program to test it. The lexical analyzer function must have the following calling signature:
            Tok getTok(istream& in, int& linenumber);
            
Lexical Rules:
- Token IDENT: Language has identifiers, which are defined to be a letter followed by zero or more letters or numbers.
- Token ICONST: Language has integer constants, which are defined to be one or more digits with an optional leading sign 
- Token SCONST: Language has string constants, which are double-quoted sequence of characters, all on the same line.
- A string constant can include escape sequences: a backslash followed by a character.The sequence \n should be interpreted as a newline. The sequence \\ should beinterpreted as a backslash. All other escapes should simply be interpreted as thecharacter after the backslash.
- Reserved Keywords: The language has reserved the keywords print, println, repeat, begin, end. They will beTokens PRINT PRINTLN REPEAT BEGIN END.
- Operators: The language has several operators. They are + - * = / ( )  which will be Tokens PLUSMINUS STAR SLASH EQ LPAREN RPAREN
- Semicolon: The language will recognized a semicolon as the token SC
- A comment is all characters from // to the end of the line; it is ignored and is not returnedas a token. NOTE that a // in the middle of a SCONST is NOT a comment!
- Error: An error will be denoted by the token ERR. If getTok returns ERR, the program should print “Error on line N ({lexeme})”, where N is the linenumber for the token and lexeme is the lexeme from the token, and it should stop running.
- Done: End of file will be denoted by the token DONE.
- The program should repeatedly call getTok until it returns DONE or ERR. If it returns DONE, the program prints summary information, then handles -sconst, -iconst and -ids, in that order. Summary information is as follows:
Lines: L
Tokens: N


Note that any error detected by the lexical analyzer should result in the ERR token, with the lexeme value equal to the string recognized when the error was detected.


The test code is a main() program that takes several command line flags:
- "-v" : if present, every token is printed when it is seen
- "-iconsts" : if present, print out all the unique integer constants inalphabetical order
- "-sconsts" : if present, prints out all the unique integer constants innumeric order
- "-ids" : if present, print out all of the unique identifiers in alphabetical order

An optional filename argument may be passed to main. If present, your program should openand read from that filename; otherwise read from standard in.

The -sconsts option should cause the program to print STRINGS: on a line by itself, followed byevery unique string constant found, one string per line, in alphabetical order. If there are noSCONSTs in the input, then nothing is printed.

The -iconsts option should cause the program to print INTEGERS: on a line by itself, followedby every unique integer constant found, one integer per line, in numeric order. If there are no ICONSTs in the input, then nothing is printed.

The -ids option should cause the program to print IDENTIFIERS: followed by acomma-separated list of every identifier found, in alphabetical order. If there are no IDENTs inthe input, then nothing is printed.
