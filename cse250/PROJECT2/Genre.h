#ifndef GENRE_H_
#define GENRE_H_

#include <iostream>
using namespace std;

class Genre{

   friend class MovieBase;
   friend class Movie;
   string id, name;

   public:
   Genre(string,string);
};
#endif
