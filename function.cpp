#include <iostream>
#include <fstream>
#include <istream>
#include <regex>
#include "lex.h"                          // FILE:
#include <map>                            // th$+is  print
#include <iterator>
#include <string>
using namespace std;
Tok getNextToken(istream& in, int& linenumber) {

    // LEXEME START aka first letter
  	char userChar = in.get(); //gets next available character
    // DEALING WITH WHITESPACE


    while ((userChar == '/' && in.peek() == '/') || userChar == ' ' || userChar == '\t' || userChar == '\n') {
      if (userChar == '/' && in.peek() == '/') { //discard all characters til newline appears
        while (userChar != '\n') {
          userChar = '\0';
          userChar = in.get();
        }
      }
      if (userChar == '\n') {
        linenumber++;
      }
      userChar = '\0';
      userChar = in.get();
      if (in.eof()) {
        Tok token(DONE, "", linenumber);
        return token;
        
      }
    }
    string userString(1, userChar); //turns into string in order for regex_match to work
    
    // REGEX
  	regex keywords("(print)|(println)|(repeat)|(begin)|(end)"); //keywords
  	regex identifier("[a-zA-Z][a-zA-Z0-9]*"); //IDENT
  	regex integerconstant("[(\\+)|(\\-)]?[0-9]+");//ICONST
  	regex stringconstant(R"((".*?[^\\]"))"); //SCONST
  	regex operators("(\\+)|(\\-)|(\\*)|(/)|(=)|(\\()|(\\))|(;)"); //OPERATORS

    // KEYWORD MAP
  	map <string, Token> keywordDictionary;
  	keywordDictionary["print"] = PRINT;
  	keywordDictionary["println"] = PRINTLN;
  	keywordDictionary["repeat"] = REPEAT;
  	keywordDictionary["begin"] = BEGIN;
  	keywordDictionary["end"] = END;
    
    // OPERATOR MAP
    map<string, Token> operatorDictionary;
    operatorDictionary["+"] = PLUS;
    operatorDictionary["-"] = MINUS;
    operatorDictionary["*"] = STAR;
    operatorDictionary["/"] = SLASH;
    operatorDictionary["="] = EQ;
    operatorDictionary["("] = LPAREN;
    operatorDictionary[")"] = RPAREN;
    operatorDictionary[";"] = SC;
    
    
    // INTEGER CONSTANT 
    if (isdigit(userChar)) {
        while (isdigit(in.peek())) {
            userString += in.get();
        }
        if (regex_match(userString.begin(), userString.end(), integerconstant)) {
            Tok token(ICONST, userString, linenumber);
            return token;
        }
    }                                                                       // Userstring += in.function
    // STRING CONSTANT
    // bat "hello" words there                                              //Peek       Get (works like a queue)
    if (userChar == '"') { //peek shows you, get actually outputs it        //inte      nte
      while(in.peek() != '"' && in.peek() != '\n') { 
        if (in.peek() == '\\') {
          userString += in.get();
        }
               
        userString += in.get();                   
      }
      userString += in.get();
      if (regex_match(userString.begin(), userString.end(), stringconstant)) {
        Tok token(SCONST, userString, linenumber);
        return token;
      }
    }
    
    //IDENT OR KEYWORD       
  	if (isalpha(userChar)) {
      
      // FINISH LEXEME
    	while (isalpha(in.peek()) || isdigit(in.peek())) { // solely just to get a lexeme and finishing it
      		userString += in.get();
      } 
      // ITS A KEYWORD
      if (regex_match(userString.begin(), userString.end(), keywords)) {
        Tok token(keywordDictionary[userString], userString, linenumber);
        return token;
      }
      // ITS AN IDENT
      if (regex_match(userString.begin(), userString.end(), identifier)) {
        Tok token(IDENT, userString, linenumber);
        return token;
      }

    }
    
    // OPERATOR
    if (regex_match(userString.begin(), userString.end(), operators)) {
      Tok token(operatorDictionary[userString], userString, linenumber);
      return token;  
    }
    
    Tok token (ERR, userString, linenumber);
    return token;

}