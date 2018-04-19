#ifndef MOVIEBASE_H_
#define MOVIEBASE_H_

#include <iostream>
#include "Movie.h"
#include "Genre.h"
using namespace std;

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
