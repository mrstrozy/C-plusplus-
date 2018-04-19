/*************************************************************************************************
**MovieBaseMRS.h by MRS for PROJECT 2 of CSE250 in Spring 2014.
**
**
*************************************************************************************************/
#ifndef GENRE_H_
#define GENRE_H_

#include <iostream>
using namespace std;

/**********************************
** This class is used just to hold
** the basic information of a genre.
** As seen, it holds the id of the
** genre as well as the name.
**
***********************************/
class Genre{

   friend class MovieBase;
   friend class Movie;
   string id, name;

   public:
   Genre(string,string);
};
#endif

#ifndef MOVIE_H_
#define MOVIE_H_

#include <iostream>
#include <vector>
using namespace std;

/*************************************************************************
** This class is used to hold the different information of each movie.
** This means that it holds the title, release date, video date, url,
** id, number of ratings, average rating, and genres it belongs to.
**
*************************************************************************/

class Movie{

   friend ostream& operator<< (ostream&,const Movie&);
   friend class MovieBase;
   int id, numRatings;
   double aveRating;
   string title, relDate, vidDate, url;
   vector<Genre>* myGenres;
   vector<int>* ratings;

   public:

   Movie(vector<string>*,vector<Genre>*);
   
/******************************************************************
** The function "addGenres" goes through each of the genre inputs.
** If the input is a 1, it adds that genre to the movie. If not,
** it ignores that genre.
*******************************************************************/
   void addGenres(vector<string>*,vector<Genre>*&);

/*******************************************************************
** The function "addRating" inputs a rating to be added to the movie.
** It then adds that new rating and computes the new average rating
** as well as increments the number of ratings variable.
*******************************************************************/
   void addRating(int);
};

#endif


#ifndef TESTBASE_H_
#define TESTBASE_H_

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;

//class Movie;
/**********************************************************************************
** This class is used to hold all of the movies that are inputted. The constructor
** takes in 3 strings. The first is the name of the movie file. The second if the 
** name of the genres file. The third is for the ratings file. In the constructor,
** the files are tested to make sure that they can be opened. After that, it inputs
** the genres and then the different movies and creates objects for each one.
***********************************************************************************/

class MovieBase{
   friend class Movie;
   friend ostream& operator<< (ostream&,const MovieBase&);
   ifstream* infp;
   ifstream* infilep;
   vector<Movie>* movies;
   vector<Genre>* genres;

   public:
/***********************************************************************************
** The MovieBase constructor creates the genres as well as the movies. It creates
** an ordered vector of movies and genres.
************************************************************************************/
   MovieBase(string,string,string);

/***********************************************************************************
** openMovieFile tests to make sure that the inputted movie file is valid and able
** to be opened. If it can be, it returns true. If not, it returns false.
************************************************************************************/
   bool openMovieFile(string);

/************************************************************************************
** openGenreFile tests to make sure that the inputted genre file is valid and able
** to be opened. If it can be, it returns true. If not, it returns false.
*************************************************************************************/
   bool openGenreFile(string);
/*************************************************************************************
** constructGenres inputs the genre file. From there it populates a vector of type
** Genre with all of the different found genres.
**************************************************************************************/
   void constructGenres();

/**************************************************************************************
** constructMovies inputs the movie file. It then populates a vector of type Movie with
** all of the different movies that are inputted. It then sorts the vector so that it is
** all ordered from least to greatest in movie id's. Lastly, it inputs user ratings and
** assigns them to the appropriate movie thus completing the movie database.
****************************************************************************************/
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

              
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <iomanip>
using namespace std;


Movie::Movie(vector<string>* info, vector<Genre>* genre): id(atoi(info->at(0).c_str())), title(info->at(1)), relDate(info->at(2)),
                                vidDate(info->at(3)), url(info->at(4)), numRatings(0), aveRating(0.00), ratings(new vector<int>())
   {
      addGenres(info,genre);

   }
void Movie::addGenres(vector<string>* info,vector<Genre>* &genres){
      int index = 0;
      for(int i = 5; i<info->size(); i++){
         if(info->at(i) == "1"){
            genres->push_back(genres->at(index));
         }
      index++;
      }
   }
void Movie::addRating(int newRating){
      ratings->push_back(newRating);
      numRatings++;
      aveRating = (aveRating*(numRatings-1) + newRating)/numRatings;
   }

ostream& operator<< (ostream& out, const Movie& movie){
   out << "ID: " << movie.id << " | Title: " << movie.title << " | Number of Ratings: " << movie.numRatings << " | Average Rating: "
       << setprecision(3) << movie.aveRating;
   return out;
}
#include <iostream>
#include <string>

using namespace std;

Genre::Genre(string id, string name) : id(id) , name(name) {}

