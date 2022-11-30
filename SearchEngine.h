//
// Created by Reece Iriye on 11/6/22.
//

#ifndef FINALPROJEXAMPLES_SEARCHENGINE_H
#define FINALPROJEXAMPLES_SEARCHENGINE_H

#include "DocumentParser.h"



class SearchEngine {
private:
public:
    SearchEngine();

    void crawl(); // obtain database to search from
    void index(); // store data into the necessary data structure
    void rank(); // rank search terms by relevance
};





#endif //FINALPROJEXAMPLES_SEARCHENGINE_H
