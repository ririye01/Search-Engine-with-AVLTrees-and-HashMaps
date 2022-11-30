//
// Created by Reece Iriye on 11/6/22.
//

#ifndef FINALPROJEXAMPLES_DOCUMENTPARSER_H
#define FINALPROJEXAMPLES_DOCUMENTPARSER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <list>

#include "DSAVLTree.h"
#include "Document.h"
#include "porter2_stemmer.h"

// Document parsers needed for our JSON files
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"


class DocumentParser {
private:
//    string filename;
public:
    DocumentParser() = default;
    ~DocumentParser() = default;
    DocumentParser &operator=(const DocumentParser & rhs);

//    const string &getFilename() const;
//    void setFilename(const string &filename);

    TheDocument read_JSON(string filename);
    string to_lower(string text);
    vector<string> tokenize(string text, char dlm);
    unordered_set<string> tokenize_toSet(string text, char dlm);
    list<string> remove_stop_words_and_stem(vector<string> origWords);
    list<TheDocument> iterate_JSON(const string & folderName);



};


#endif //FINALPROJEXAMPLES_DOCUMENTPARSER_H
