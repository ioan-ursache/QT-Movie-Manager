#ifndef DOMAIN_H  
#define DOMAIN_H  

#include <string>  
#include <iostream>  
#include <vector>  

class Movie {  
private:  
   std::string movieTitle;  
   std::vector<std::string> movieGenres;  
   std::string movieDescription;  
   std::string moviePlot;  
   std::string movieDirector;  
   std::vector<std::string> movieActors; // vector to store multiple actors  
   std::string movieRating;  
   std::string moviePath; // for storing the file path of the movie  
   int movieDuration = 0;
   int yearReleased = 0;
   bool isWatched = false; // default value is false  

public:  
	
   Movie() = default;

   // Constructor with parameters  
   Movie(const std::string& title, const std::vector<std::string>& genres, const std::string& description,  
       const std::string& plot, const std::string& director, const std::vector<std::string>& actors,  
       const std::string& rating, const std::string& path, int duration, int year, bool watched = false);  

   // Getters  
   std::string getTitle() const;  
   std::vector<std::string> getGenres() const;  
   std::string getDescription() const;  
   std::string getPlot() const;  
   std::string getDirector() const;  
   std::vector<std::string> getActors() const; // getter for actors  
   std::string getRating() const;  
   std::string getMoviePath() const;  
   int getDuration() const;  
   int getYearReleased() const;  
   bool getIsWatched() const;  

   // Setters  
   void setTitle(const std::string& title);  
   void setGenres(const std::vector<std::string>& genres);  
   void setDescription(const std::string& description);  
   void setPlot(const std::string& plot);  
   void setDirector(const std::string& director);  
   void setActors(const std::vector<std::string>& actors); // setter for actors  
   void setRating(const std::string& rating);  
   void setMoviePath(const std::string& path);  
   void setDuration(int duration);  
   void setYearReleased(int year);  
   void setIsWatched(bool watched);  

   // string conversion  
   std::string toString() const;  

   // overloaded operator for equality check + comparing two movies regardless of watched status  
   bool operator==(const Movie& other) const;  

};  

#endif // DOMAIN_H
