#include <iostream>
#include <fstream>
#include <istream>
#include <regex>
#include "lex.h"
#include <map>
#include <iterator>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
extern ostream& operator<<(ostream& out, const Tok& tok) {
    map <Token, string> words;
    words[PRINT] = "PRINT";
    words[PRINTLN] = "PRINTLN";
    words[REPEAT] = "REPEAT";
    words[BEGIN] = "BEGIN";
    words[END] = "END";
    words[IDENT] = "IDENT(" + tok.GetLexeme() + ")";
    words[ICONST] = "ICONST(" + tok.GetLexeme() + ")";
    words[SCONST] = "SCONST(" + tok.GetLexeme() + ")";
    words[PLUS] = "PLUS";
    words[MINUS] = "MINUS";
    words[STAR] = "STAR";
    words[SLASH] = "SLASH";
    words[EQ] = "EQ";
    words[LPAREN] = "LPAREN";
    words[RPAREN] = "RPAREN";
    words[SC] = "SC";
    words[DONE] = "DONE";
    out << words[tok.GetToken()];
    return out;
}
int main (int argc, char* argv[]) {
    istream *in = &cin; //stdinput
    ifstream infile;
    Tok token;
    int tokenCount = 0;
    int fileCount = 0;
    int ln = 0; //linenumber
    bool atleastOneIDENT = false;
    bool vFlag = false;
    bool iconstFlag = false;
    //bool sconstFlag = false;
    bool idsFlag = false;
    for (int i = 1; i < argc; i++) {
      string command = argv[i];
      char dashcheck = command.at(0);
      if (dashcheck == '-') {
        if (command == "-v") {
           vFlag = true;
        }
        else if (command == "-iconsts") {
          iconstFlag = true;
        }
        else if (command == "-sconsts") {
          //sconstFlag = true;
        }
        else if (command == "-ids") {
          idsFlag = true;
        }
        else if (command != "-iconsts" && command != "-sconsts" && command != "-ids" && command != "-v") {
          cout << "UNRECOGNIZED FLAG " << command << endl;
          return 1;
        }

      } else {

        if (fileCount == 0) {
          infile.open(argv[i]);
          if (infile.is_open() == false) {
            cout << "CANNOT OPEN " << command << endl;
            return 1;
          }
          else if (infile.is_open() == true) {
            fileCount++;
            in = &infile;
              if (infile.peek() == std::ifstream::traits_type::eof()) { //peek() = checks what the next character
                                                                        //get() = checks and outputs the next character
                  cout << "Lines: " << ln << endl;                      //PEEK: HELLO
                                                                        //GET: HELLO think of it as a queue
                  return 1;
              }
          }

        }
        else {
          cout << "ONLY ONE FILENAME ALLOWED" << endl;
          return 1;
        }
      }
    }
    vector <Tok> tokens;
    while (!in->eof()) { //not poining to eof()
      Tok token = getNextToken(*in, ln); // PRINT PRINTLN MINA
      if (token.GetToken() != ERR && token.GetToken() != DONE) {
        tokenCount++; //2
        tokens.push_back(token); //vector: print, println
      }
      if (token.GetToken() == ERR) {
        ln++;
        cout << "Error on line " << ln << " (" << token.GetLexeme() << ")" << endl; // Error on line n (MINA)
        return 1;
      }
      if (token.GetToken() == IDENT) {
        atleastOneIDENT = true;
      }
    }
    if (vFlag == true) { //-v adfadklsfjklda
      for (auto i = tokens.begin(); i != tokens.end(); i++) {
        cout << *i << endl; //prints out tokens
      }
    }
    if (iconstFlag == true) { //33333 44444 5555 6666 
                              //ICONST(99999)
        vector<string> lexemes;
        for (auto i = tokens.begin(); i != tokens.end(); i++) {
            lexemes.push_back(i->GetLexeme());
            sort(lexemes.begin(), lexemes.end());
        }
    } //print it out in alphabetical order


    if (tokenCount != 0 && ln != 0) {
      cout << "Lines: " << ln << endl;
      cout << "Tokens: " << tokenCount << endl;
    }
    if (idsFlag == true && atleastOneIDENT) {
      vector<string> lexemes;
      for (auto i = tokens.begin(); i != tokens.end(); i++) {
          lexemes.push_back(i->GetLexeme());
          sort(lexemes.begin(), lexemes.end());
      }
        cout << "IDENTIFIERS: "; // a, here, yeah, think
        for (vector<string>::const_iterator i = lexemes.begin(); i != lexemes.end(); i++) {
            if (i == lexemes.end() - 1) {
                cout << *i;
            }
            else {
            cout << *i << ", ";
            }

        }
        cout << endl;

    }
    return 0;
}
