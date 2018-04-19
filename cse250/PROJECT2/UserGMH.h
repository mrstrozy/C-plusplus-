/**
* The user class that holds strings of its id, age, gender, occupation
* zipcode and ratings for movies. Made by GMH for use in CSE250 for Project2
*/
#ifndef USER_H_
#define USER_H_

#include<iostream>
#include<string>
#include<vector>
using namespace std;


/**
 * Holds the movie id and rating for that movie and used to add to a vector
 * so that the user knows what movies it rated
 */
struct MovieRatings{
    int movieId;
    int rating;
} movieId, rating;

struct PreferenceFactor{
    string genre;
    double pF;
} genre, pF;


class User{
  friend class UserBase;
   int userId;
   string age;
   string gender;
   string occupation;
   vector<PreferenceFactor>* pFp;
   string zipCode;
   vector<MovieRatings>* ratings;
 public:   
   User(int u, string a, string g, string occ, string zip)
    : ratings(new vector<MovieRatings>())
    , pFp(new vector<PreferenceFactor>())
   {
      userId=u;
      age=a;
      gender=g;
      occupation=occ;
      zipCode=zip;
   }
   /**
   * Going to tell the user what it rated each movie and store it in a map
   */   
    void setRatingMovie(int movie, int rating){
        MovieRatings temp;
        temp.movieId = movie;
        temp.rating = rating;
        ratings->push_back(temp);
    }
    
    /**
    * Setting the preference factor for the genre given by a string
    */
    void setPrefFact(string g, double i){
        PreferenceFactor temp;
        temp.genre = g;
        temp.pF = i;
        pFp->push_back(temp);
    }
    
    /**
    * Getter for the ratings vector
    */
    vector<MovieRatings>* getRatings(){
        return ratings;
    }
    
    vector<PreferenceFactor>* getPrefFact(){
        return pFp;
    }
    
    int getUserId(){
        return userId;
    }
};


#endif
