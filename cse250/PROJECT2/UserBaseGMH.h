/**
 * Class UserBase that holds all the users. Created by GMH for use in CSE250
 * Project 2.
 */
#ifndef USERBASE_H_
#define USERBASE_H_

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<cstdlib>
#include"UserGMH.h"
using namespace std;

class UserBase{
    
    vector<User>* users;
public:
    UserBase(string ignore) : users(new vector<User>())
    {
       inputFile();
       inputRatings();
    } // running input file for debugging
    
    /**
     * Inputs the u.user file into the vector users, and makes all the users from
     * the file that was given
     */
    void inputFile(){
        ifstream input("u.user");
        if(!input){
            cerr << "Cannot open file" << endl;
        }
        string str;
        while(getline(input,str)){   // loops the file line by line
            vector<string> lst;
            string temp_s;
            for(int i=0; i<str.size();i++){   // loops the string char by char
                char temp_c = str.at(i);
                if(temp_c=='|'){     // checks if the | is present and puts the word into lst
                    lst.push_back(temp_s);
                    temp_s = "";
                } else {
                    temp_s += temp_c;  // adds the char
                }
            }
            lst.push_back(temp_s);
            users->push_back(User(atoi(lst[0].c_str()),lst[1],lst[2],lst[3],lst[4]));
            str = "";
        }
        input.close();
    }
    /**
     * From the u.data files, tells the user what their ratings on movies were
     * based on movie id
     */
    void inputRatings(){
        ifstream input("u.data");
        if(!input){
            cerr << "Cannot open file" << endl;
        }
        string str;
        bool lookingForId = true;
        while(getline(input,str)&&str!=""){
            vector<string> lst;
            string temp_s;
            int id;
            for(int i = 0; i<str.size(); i++){
                char temp_c = str.at(i);
                if(temp_c=='\t'){
                    if(lookingForId){
                        id = atoi(temp_s.c_str());
                        lookingForId = false;
                        temp_s = "";
                    } else {
                        lst.push_back(temp_s);
                        temp_s = "";
                    }
                } else {
                    temp_s += temp_c;
                }
            }
            users->at(id-1).setRatingMovie(atoi(lst[0].c_str()),atoi(lst[1].c_str()));
            lookingForId = true;
        }
    }
    
    vector<User>* getUsers(){
        return users;
    }
};

#endif
