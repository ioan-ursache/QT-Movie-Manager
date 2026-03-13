#include "Domain.h"

#include <numeric> // for std::accumulate
#include <sstream> // for std::ostringstream

// Constructor with parameters
Movie::Movie(const std::string& title, const std::vector<std::string>& genres, const std::string& description, const std::string& plot, const std::string& director, const std::vector<std::string>& actors, const std::string& rating, const std::string& path, int duration, int year, bool watched) {
	if (title.empty() || director.empty() || actors.empty() || path.empty() || duration <= 0 || year < 1880 || year > 2100) {
		throw std::invalid_argument("Invalid movie details provided.");
	}
	else {
		movieTitle = title;
		movieGenres = genres;
		movieDescription = description;
		moviePlot = plot;
		movieDirector = director;
		movieActors = actors; // using vector to store multiple actors
		movieRating = rating;
		moviePath = path;
		movieDuration = duration; // in minutes
		yearReleased = year;
		isWatched = watched; // default value is false
	}
}

// Getters
std::string Movie::getTitle() const { return movieTitle; }

std::vector<std::string> Movie::getGenres() const { return movieGenres; }

std::string Movie::getDescription() const { return movieDescription; }

std::string Movie::getPlot() const { return moviePlot; }

std::string Movie::getDirector() const { return movieDirector; }

std::vector<std::string> Movie::getActors() const { return movieActors; }

std::string Movie::getRating() const { return movieRating; }

int Movie::getDuration() const { return movieDuration; }

int Movie::getYearReleased() const { return yearReleased; }

std::string Movie::getMoviePath() const { return moviePath; }

bool Movie::getIsWatched() const { return isWatched; }

// Setters
void Movie::setTitle(const std::string& title) {
	if (title.empty()) {
		throw std::invalid_argument("Movie title cannot be empty.");
	}
	else {
		movieTitle = title;
	}
}

void Movie::setGenres(const std::vector<std::string>& genres) {
	movieGenres = genres;
}

void Movie::setDescription(const std::string& description) {
	movieDescription = description; 
}

void Movie::setPlot(const std::string& plot) { 
	moviePlot = plot; 
}

void Movie::setDirector(const std::string& director) { 
	if (director.empty()) {
		throw std::invalid_argument("Director name cannot be empty.");
	}
	else {
		movieDirector = director;
	}
}

void Movie::setActors(const std::vector<std::string>& actors) { 
	if (actors.empty()) {
		throw std::invalid_argument("Movie must have at least one actor.");
	}
	else {
		movieActors = actors;
	}

}

void Movie::setRating(const std::string& rating) { movieRating = rating; }

void Movie::setDuration(int duration) {
	if (duration <= 0) {
		throw std::invalid_argument("Movie duration must be a positive integer.");
	}
	else {
		movieDuration = duration;
	}
}

void Movie::setYearReleased(int year) {
	if (year < 1880 || year > 2100) {
		throw std::invalid_argument("Year released must be between 1880 and 2100.");
	}
	else {
		yearReleased = year;
	}
}

void Movie::setMoviePath(const std::string& path) { 
	if (path.empty()) {
		throw std::invalid_argument("Movie path cannot be empty.");
	}
	else if (path.find(".mp4") == std::string::npos) {
		throw std::invalid_argument("Movie path must point to a valid video file (.mp4).");
	}
	else
	moviePath = path; 
}

void Movie::setIsWatched(bool watched) { 
	isWatched = watched; 
}

std::string Movie::toString() const {
	std::ostringstream oss;
	oss << "Title: " <<  movieTitle <<  "\n";
	oss << "Genres: " << (movieGenres.empty() ? "None" : std::accumulate(movieGenres.begin(), movieGenres.end(), std::string(),
		[](const std::string& a, const std::string& b) {return a.empty() ? b : a + ", " + b;  })) << "\n";
	oss << "Description: " << movieDescription << "\n";
	oss << "Plot: " << moviePlot << "\n";
	oss << "Director: " << movieDirector << "\n";
	oss << "Actors: " << (movieActors.empty() ? "None" : std::accumulate(movieActors.begin(), movieActors.end(), std::string(),
		[](const std::string& a, const std::string& b) { return a.empty() ? b : a + ", " + b; })) << "\n";
	oss << "Rating: " << movieRating << "\n";
	oss << "Movie Path: " << moviePath << "\n";
	oss << "Duration: " << std::to_string(movieDuration) << " minutes\n";
	oss << "Year Released: " << std::to_string(yearReleased) << "\n";
	oss << "Watched: " << (isWatched ? "Yes" : "No");
	return oss.str();
}

// Overloaded operator for equality check
bool Movie::operator==(const Movie& other) const
{
	return movieTitle == other.movieTitle &&
		movieGenres == other.movieGenres &&
		movieDescription == other.movieDescription &&
		moviePlot == other.moviePlot &&
		movieDirector == other.movieDirector &&
		movieActors == other.movieActors &&
		movieRating == other.movieRating &&
		moviePath == other.moviePath &&
		movieDuration == other.movieDuration &&
		yearReleased == other.yearReleased;
}

