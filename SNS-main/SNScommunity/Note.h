#pragma once
#include <iostream>
#include <string>
#include <experimental/filesystem>
#include <fstream>
#include <stdlib.h>

using std::string;

class Note
{
public:
    string senderID;
    bool hasBeenOpened = false;
    string noteContent;
public:
    Note();
    ~Note();
    Note(const string& senderID, const string noteContent);
    Note(const string& senderID, bool hasBeenOpened, const string noteContent);
    void sendNote(const string& recipient);
    void send_note(const string& userid);
    
};
