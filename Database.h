//
// Created by Alden Cressy on 11/28/22.
//

#ifndef FINALPROJEXAMPLES_DATABASE_H
#define FINALPROJEXAMPLES_DATABASE_H

#include <functional>

#include "DSHashTable.h"
#include "Document.h"


class Database {
private:
    DSHashTable<string, pair<TheDocument, size_t>> wordDatabase;
    DSHashTable<string,TheDocument> peopleDatabase;
    DSHashTable<string,TheDocument> organizationDatabase;
    list<string> library;

    /*
     * TO DO:
     *  Use DSHashTable to store individual words, people, and organizations,
     *  and map them to the documents in which they belong. Also, specifically
     *  for text, ensure that we use std::pair to indicate the number of appearances
     *  for each word
     */

};

#endif //FINALPROJEXAMPLES_DATABASE_H
