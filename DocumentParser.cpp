//
// Owner: Reece Iriye
//

#include "DocumentParser.h"

using namespace rapidjson;
using namespace std;


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// Actual Functions
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////


/*
 * Reads in the JSON File
 */
TheDocument DocumentParser::read_JSON(string filename) {
    // File io
    ifstream input(filename);

    // use filesystem to iterate through every single file
    IStreamWrapper isw(input);

    // Create RapidJSON Document object to parse IStreamWrapper
    rapidjson::Document d;
    d.ParseStream(isw);

    // Create document object
    TheDocument doc;

    // Use RapidJSON Document to capture person, organization, UUID, and title
    /// Load all the people into the document
    auto tmp1 = d["entities"]["persons"].GetArray();
    for (const auto & x : tmp1) {
        doc.addPerson(x["name"].GetString());
    }

    /// Load all the organizations into the document
    auto tmp2 = d["entities"]["organizations"].GetArray();
    for (const auto & x : tmp2) {
        doc.addOrganization(x["name"].GetString());
    }

    /// Load the UUID and Title into the document
    doc.setUuid(d["uuid"].GetString());
    doc.setTitle(d["title"].GetString());

    /// Clean the text then load it into the document
    doc.setText(
            remove_stop_words_and_stem(
                    tokenize(
                            to_lower(
                                    d["text"].GetString()),' ')));



    cout << doc.getTitle() << endl;




    // Close file
    input.close();


    return doc;

}

/*
 * Ensures all upper-case text is lower-case.
 */
string DocumentParser::to_lower(string text) {

    for (size_t i = 0; i < text.size(); ++i) {
        if (text[i] >= 'A' && text[i] <= 'Z')
            // ASCII number for 'a' is 97 and for 'A' is 65
            // Therefore, adding 32 to any lowercase letter will make an upper-case letter lower-case
            text[i] = text[i] + 32;
    }


    return text;
}



/*
 * Tokenize a string by a selected delimiter into a vector.
 */
vector<string> DocumentParser::tokenize(string text, char dlm) {

    vector<string> tmpVector;
    string tmpString;

    for (size_t i = 0; i < text.size(); ++i) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            tmpString = tmpString + text[i];
        }
        else if (text[i] == dlm) {
            tmpVector.push_back(tmpString);
            tmpString.clear();
        }
    }


    return tmpVector;

}

/*
 * Tokenize to a set.
 */
unordered_set<string> DocumentParser::tokenize_toSet(string text, char dlm) {
    unordered_set<string> tmpSet;
    string tmpString;

    for (size_t i = 0; i < text.size(); ++i) {
        if (text[i] != dlm) {
            tmpString = tmpString + text[i];
        }
        else {
            tmpSet.insert(tmpString);
            tmpString.clear();
        }
    }


    return tmpSet;

}


/*
 * Removes stop words
 * https://bitbucket.org/smassung/porter2_stemmer/src/master/main.cpp
 */
list<string> DocumentParser::remove_stop_words_and_stem(vector<string> origWords) {
    size_t n = origWords.size();
    list<string> newWords;
    unordered_set<string> stopWordsSet;

    ifstream stopwordReader("stopwords.csv");
    if (!stopwordReader.is_open()) {
        throw runtime_error("Stop words file is not open!");
    }
    else {
        stringstream buffer;
        buffer << stopwordReader.rdbuf(); // input file data into buffer

        stopwordReader.close();

        stopWordsSet = tokenize_toSet(buffer.str(), ',');

    }

    // Remove stop words and stem
    for (size_t i = 0; i < n; ++i) {
        string buffer = origWords[i];

        if(stopWordsSet.find(buffer) == stopWordsSet.end() && buffer != "") {

            Porter2Stemmer::stem(buffer);
            newWords.push_front(buffer);
        }
    }

    return newWords;
}


/*
 * Iterates through all JSON files in a folder and puts all
 * their information into a Document class
 */
list<TheDocument> DocumentParser::iterate_JSON(const string & folderName) {
    // recursive_director_iterator used to "access" folder at parameter -path-
    // we are using the recursive iterator so it will go into subfolders.
    // see: https://en.cppreference.com/w/cpp/filesystem/recursive_directory_iterator
    auto it = filesystem::recursive_directory_iterator(folderName);

    // Create Document library
    list<TheDocument> library;

    // Loop over every single JSON file
    for (const auto &entry : it) {
        cout << "--- " << setw(60) << left << entry.path().c_str() << " ---" << endl;

        // We only want to attempt to parse files that end with .json
        if (entry.is_regular_file() && entry.path().extension().string() == ".json")
            library.push_front(read_JSON(entry.path().string()));

    }


    return library;
}




