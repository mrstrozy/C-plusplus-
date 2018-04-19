#ifndef MOVIE_H_
#define MOVIE_H_

#include <iostream>
#include "Genre.h"
using namespace std;

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
   void addGenres(vector<string>*,vector<Genre>*&);
   void addRating(int);
};

#endif
