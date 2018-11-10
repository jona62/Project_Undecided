#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

const string INPUT_FILE ("index.html");
const string OUTPUT_FILE ("resultant.txt");
const string HTML_CLASS ("class");
const string HTML_ID ("id");
const stringstream DEFAULT_STR (" {\n\n}\n");

void readFile();
bool isOpeningTag(char);
bool isClosingTag(char);
void createCssTag(string);
void htmlTagIdentifier(const string&, string);

map<string, char> makeMap() {
    map<string, char> label;
    label["class"] = '.';
    label["id"] = '#';
    return label;
}

map<string, char> label = makeMap();

bool isOpeningTag(char ch) {
    return ch == '<';
}

bool isClosingTag(char ch) {
    return ch == '>';
}

void readFile() {
    fstream file;
    file.open(INPUT_FILE.c_str());
    char ch;
    string tag = "";
    bool tagIsOpen = false;
    while(file >> noskipws >> ch) {
        if(isOpeningTag(ch)) {
            tagIsOpen = true;
        }
        if(tagIsOpen) {
            if(!isClosingTag(ch) && !isOpeningTag(ch))
                tag += ch;
        }
        if(isClosingTag(ch)) {
            createCssTag(tag);
            tag = "";
            tagIsOpen = false;
        }
    }
}

void createCssTag(string tag) {
    htmlTagIdentifier(HTML_CLASS, tag);
    htmlTagIdentifier(HTML_ID, tag);
}

void htmlTagIdentifier(const string &tagName, string tag) {
    ofstream ofile;
    ofile.open(OUTPUT_FILE.c_str(), ios::app);
    size_t found = tag.find(tagName);
    if(found != string::npos) {

        int starting_index = found + tagName.length();
        bool tagIsOpen = false;
        bool isFirstQuote = true;
        string identifier = "";
        for(int i=starting_index; i < tag.length(); i++) {
            if(tag[i] == '"' && isFirstQuote) {
                tagIsOpen = !tagIsOpen;
                isFirstQuote = false;
                continue;
            }
            if(tagIsOpen) {
                if(tag[i] != '"') 
                    identifier += tag[i];
                if(tag[i] == '"') {
                    tagIsOpen = false;
                    // string s;
                    // s.push_back(label.find(identifier)->second);
                    ofile <<  label[identifier] + identifier + DEFAULT_STR.str();
                    identifier = "";
                }
            }
        }

    }
}

#endif //UTILS_H