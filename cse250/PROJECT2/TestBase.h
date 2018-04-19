/****************************
**
**
**
*****************************/
#ifndef TESTBASE_H_
#define TESTBASE_H_

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "MovieBase.h"
using namespace std;

//class Movie;

class MovieBase{
   friend class Movie;
   friend ostream& operator<< (ostream&,const MovieBase&);
   ifstream* infp;
   ifstream* infilep;
   vector<Movie>* movies;
   vector<Genre>* genres;

   public:
   MovieBase(string,string,string);
   bool openMovieFile(string);
   bool openGenreFile(string);
   void constructGenres();
   void constructMovies(string);
};
#endif


   MovieBase::MovieBase(string movieFileName,string genreFileName,string ratingsFile):
      movies(new vector<Movie>()) ,genres(new vector<Genre>())
   {
      if(openMovieFile(movieFileName) && openGenreFile(genreFileName)){
         constructGenres();
         constructMovies(ratingsFile);
    } else {
         cout << "In MovieBase: Could not open either Movie file or Genre file" << endl;
      }
   }
   
   bool MovieBase::openMovieFile(string name){

      infp = new ifstream(name.c_str(), ios_base::in);
      if (! infp->is_open()) {
         cerr << "Unable to open file: " << name << endl;
         return false;
      }
      return true;

   }

   bool MovieBase::openGenreFile(string name){
      infilep = new ifstream(name.c_str(), ios_base::in);
      if(! infilep->is_open()) {
         cerr << "Unable to open file: " << name << endl;
         return false;
      }
      return true;
   }
   
   

   void MovieBase::constructGenres(){

   vector<string>* data = new vector<string>();
   string line, ins;

   while(getline(*infilep,line)){
      data->clear();
      ins = "";
      if(line != ""){
         for(int i = 0; i < line.length();i++){
            if(line[i] == '|'){
               data->push_back(ins);
               ins = "";
          } else {
               ins += line[i];
            }
         }
         data->push_back(ins);

         //All info for Genre has been collected, now to make the Genre Object
         genres->push_back(Genre(data->at(1),data->at(0)));      
         }
      }

   infilep->close();
   }
   void MovieBase::constructMovies(string ratings){

      string line, ins;
      vector<string>* data = new vector<string>();
      vector<Movie>* tempMovies = new vector<Movie>();
      while(getline(*infp,line)){

         data->clear();
         ins = "";
         for(int i = 0;i<line.length();i++){
            if(line[i] == '|'){
               data->push_back(ins);
               ins = "";
            }
            else {
               ins += line[i];
            }
         }
         data->push_back(ins);

         //All information gathering has been done, now to make the actual Movie object         
         tempMovies->push_back(Movie(data,genres));
      }
      //Now to organize the movies vector in order by movie id
      for(int i = 0; i < tempMovies->size();i++){
         if(tempMovies->at(i).id = i + 1){
            movies->push_back(tempMovies->at(i));
         }
      }/*
      for(int i = 0; i < movies->size();i++){
         cout << "Movie: " << movies->at(i).id << " \"" << movies->at(i).title << "\"" << endl;
      }*/
      infp->close();
      //Lastly give each movie its average rating
      ifstream* in = new ifstream(ratings.c_str(),ios_base::in);
      int i = 0;
      int movieID;

      //Read in the ratings for each movie from the ratings file
      while(*in >> line){
         if(i == 4){
            i = 0;
         }
         if(i == 1){
            movieID = atoi(line.c_str());
         }
         if(i == 2){
            movies->at(movieID-1).addRating(atoi(line.c_str()));
         }
         i++;  
      }
      in->close(); 
   }

ostream& operator<< (ostream& out, const MovieBase& base){
   for(int i = 0; i < base.movies->size();i++){
      cout << base.movies->at(i) << endl;
   }
   return out;
}

              
   /*           movie id | movie title | release date | video release date |
              IMDb URL | unknown | Action | Adventure | Animation |
              Children's | Comedy | Crime | Documentary | Drama | Fantasy |
              Film-Noir | Horror | Musical | Mystery | Romance | Sci-Fi |
              Thriller | War | Western |
              The last 19 fields are the genres, a 1 indicates the movie
              is of that genre, a 0 indicates it is not; movies can be in
              several genres at once.
              The movie ids are the ones used in the u.data data set.
 */

