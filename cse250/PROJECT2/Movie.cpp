#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include "Movie.h"
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




