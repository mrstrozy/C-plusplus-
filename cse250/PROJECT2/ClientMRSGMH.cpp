#include "MovieBaseMRS.h"
#include "UserBaseGMH.h"
#include "UserGMH.h"
#include <iomanip>

using namespace std;

vector<Genre>* makeGenres(){
   vector<Genre>* temp = new vector<Genre>();
   temp->push_back(Genre("0","Action"));
   temp->push_back(Genre("1","Noir"));
   temp->push_back(Genre("2","Light"));
   temp->push_back(Genre("3","Serious"));
   temp->push_back(Genre("4","Fantasy"));
   temp->push_back(Genre("5","History"));
   return temp;
}
vector<Genre>* makeGlobalAverage(vector<Genre>* genres){
   vector<Genre>* temp = makeGenres();
   temp->at(0).addRating(genres->at(1).getAverage(),genres->at(1).getNumRatings());
   temp->at(0).addRating(genres->at(2).getAverage(),genres->at(2).getNumRatings());
   temp->at(0).addRating(genres->at(16).getAverage(),genres->at(16).getNumRatings());
   temp->at(0).addRating(genres->at(18).getAverage(),genres->at(18).getNumRatings());
   temp->at(1).addRating(genres->at(6).getAverage(),genres->at(6).getNumRatings());
   temp->at(1).addRating(genres->at(10).getAverage(),genres->at(10).getNumRatings());
   temp->at(1).addRating(genres->at(11).getAverage(),genres->at(11).getNumRatings());
   temp->at(1).addRating(genres->at(13).getAverage(),genres->at(13).getNumRatings());
   temp->at(2).addRating(genres->at(3).getAverage(),genres->at(3).getNumRatings());
   temp->at(2).addRating(genres->at(4).getAverage(),genres->at(4).getNumRatings());
   temp->at(2).addRating(genres->at(5).getAverage(),genres->at(5).getNumRatings());
   temp->at(2).addRating(genres->at(12).getAverage(),genres->at(12).getNumRatings());
   temp->at(3).addRating(genres->at(8).getAverage(),genres->at(8).getNumRatings());
   temp->at(3).addRating(genres->at(14).getAverage(),genres->at(14).getNumRatings());
   temp->at(4).addRating(genres->at(15).getAverage(),genres->at(15).getNumRatings());
   temp->at(4).addRating(genres->at(9).getAverage(),genres->at(9).getNumRatings());
   temp->at(5).addRating(genres->at(17).getAverage(),genres->at(17).getNumRatings());
   temp->at(5).addRating(genres->at(7).getAverage(),genres->at(7).getNumRatings());
   return temp;
}
   



int main(){
   vector<vector<Movie> > topMovies();
   MovieBase base("u.item","u.genre","u.data");
   UserBase user("ignored");
   vector<User>* allUsers = user.getUsers();
   vector<Genre>* globalGenres = makeGlobalAverage(base.getGenres());
   vector<Genre>* userGenres;
   for(int i = 0; i < allUsers->size();i++){
      vector<MovieRatings>* localRatings = allUsers->at(i).getRatings();
      
      for(int j = 0; j < localRatings->size();j++){//inside ratings which holds movieId and rating
         bool action = false;
         bool noir = false;
         bool light = false;
         bool serious = false;
         bool fantasy = false;
         bool history = false;
         int localMovieID = localRatings->at(j).movieId;

         Movie* currMovie = &(base.getMovies()->at(localMovieID-1));
         vector<Genre>* movieGenres = currMovie->getGenres();
         userGenres = makeGenres();
         for(int k = 0; k < movieGenres->size();k++){//look at each individual genre
            int id = movieGenres->at(k).getID();
            if(!action && (id == 1 || id == 2 || id == 16 || id == 18)){
               userGenres->at(0).addRating(localRatings->at(j).rating);
               action = true;
            }
            if(!noir && (id == 10 || id == 11 || id == 13)){
               userGenres->at(1).addRating(localRatings->at(j).rating);
               noir = true;
            }
            if(!light && (id == 3 || id == 4 || id == 5 || id == 12)){
               userGenres->at(2).addRating(localRatings->at(j).rating);
               light = true;
            }
            if(!serious && (id == 8 || id == 14)){
               userGenres->at(3).addRating(localRatings->at(j).rating);
               serious = true;
            }
            if(!fantasy && (id == 15 || id == 9)){
               userGenres->at(4).addRating(localRatings->at(j).rating);
               fantasy = true;
            }
            if(!history && (id == 17 || id == 7)){
               userGenres->at(5).addRating(localRatings->at(j).rating);
               history = true;
            }
         }
         //we have found the average for each genre for the user    
         
      }
         allUsers->at(i).setPrefFact("Action",userGenres->at(0).getAverage()/globalGenres->at(0).getAverage());
         allUsers->at(i).setPrefFact("Noir",userGenres->at(1).getAverage()/globalGenres->at(1).getAverage());
         allUsers->at(i).setPrefFact("Light",userGenres->at(2).getAverage()/globalGenres->at(2).getAverage());
         allUsers->at(i).setPrefFact("Serious",userGenres->at(3).getAverage()/globalGenres->at(3).getAverage());
         allUsers->at(i).setPrefFact("Fantasy",userGenres->at(4).getAverage()/globalGenres->at(4).getAverage());
         allUsers->at(i).setPrefFact("History",userGenres->at(5).getAverage()/globalGenres->at(5).getAverage());

   }
   
   return 0;
}
