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
   friend ostream& operator<< (ostream&,const Genre&);
   string name;
   int id, numRatings;
   double aveRating;

   public:
   Genre(string,string);
   void addRating(int);
   void addRating(double,int);
   void setAverage(double);
   int getID();
   double getAverage();
   int getNumRatings();
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
   vector<Genre>* getGenres();
   bool containsGenre(Genre&);
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
   vector<Movie>* getMovies();
   vector<Genre>* getGenres();
   void constructMovies(string);
};
#endif


   MovieBase::MovieBase(string movie, string genre, string ratings):
      movies(new vector<Movie>()) ,genres(new vector<Genre>())
   {

      if(openMovieFile(movie) && openGenreFile(genre)){
         constructGenres();
         constructMovies(ratings);
    } else {
         cout << "In MovieBase: Could not open either Movie file or Genre file" << endl;
      }
   }
   vector<Genre>* MovieBase::getGenres(){ return genres;}
   
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
   
   
   vector<Movie>* MovieBase:: getMovies(){return movies;}
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
         for(int j = i; j < tempMovies->size();j++){
            if(tempMovies->at(i).id == j + 1){
               movies->push_back(tempMovies->at(j));
            }
         }
      }

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
      
      //Compute the average rating for each genre

      for(int i = 0; i < movies->size();i++){
         for(int j = 0; j < genres->size();j++){
            if(movies->at(i).containsGenre(genres->at(j))){
               genres->at(j).addRating(movies->at(i).aveRating,movies->at(i).numRatings); 
            }
         }
      }
   }

ostream& operator<< (ostream& out, const MovieBase& base){
   for(int i = 0; i < base.movies->size();i++){
      cout << base.movies->at(i) << endl;
   }
   for(int i = 0; i < base.genres->size();i++){
      cout << base.genres->at(i) << endl;
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
                                vidDate(info->at(3)), url(info->at(4)), numRatings(0), aveRating(0.00), ratings(new vector<int>()),
                                myGenres(new vector<Genre>())
   {
      addGenres(info,genre);

   }
void Movie::addGenres(vector<string>* info,vector<Genre>* &genres){
      int index = 0;
      for(int i = 5; i<info->size(); i++){
         if(info->at(i) == "1"){
            myGenres->push_back(genres->at(index));
         }
      index++;
      }
   }
vector<Genre>* Movie::getGenres(){return myGenres;}
void Movie::addRating(int newRating){
      ratings->push_back(newRating);
      numRatings++;
      aveRating = (aveRating*(numRatings-1) + newRating)/numRatings;
   }
bool Movie::containsGenre(Genre& searchGenre){
   for(int i = 0; i < myGenres->size();i++){
      if(myGenres->at(i).id == searchGenre.id){
         return true;
      }
   } 
}
ostream& operator<< (ostream& out, const Movie& movie){
   out << movie.title;
   return out;
}
#include <iostream>
#include <string>

using namespace std;

Genre::Genre(string id, string name) : id(atoi(id.c_str())) , name(name), aveRating(0), numRatings(0) {}

void Genre::addRating(int rating){

   numRatings++;
   aveRating = (aveRating*(numRatings-1)+rating)/numRatings;
}
void Genre::addRating(double newRating, int prevRatings){
   double fullValueRating;
   double oldValue = numRatings*aveRating;
   fullValueRating = newRating*prevRatings;
   numRatings = numRatings + prevRatings;
   aveRating = (fullValueRating + oldValue)/numRatings;
}
int Genre::getNumRatings(){return numRatings;}   
double Genre::getAverage(){return aveRating;}
void Genre::setAverage(double newAve){ aveRating = newAve;}
int Genre::getID(){return id;}
ostream& operator<< (ostream& out, const Genre& genre){
   out << "Genre: " << genre.name << "(" << genre.id << ") || Average Rating: " << genre.aveRating;
   return out;
}
