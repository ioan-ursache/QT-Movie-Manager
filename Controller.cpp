#include "Controller.h"
#include <stdexcept>
#include <algorithm>

// ==============================
// Command Implementations
// ==============================

AddMovieCommand::AddMovieCommand(std::shared_ptr<MovieRepository> repo, const Movie& movie)
    : repo(repo), movie(movie) {
}

void AddMovieCommand::execute() {
    repo->addMovie(movie);
}

void AddMovieCommand::undo() {
    repo->removeMovie(movie.getTitle());
}

RemoveMovieCommand::RemoveMovieCommand(std::shared_ptr<MovieRepository> repo, const Movie& movie)
    : repo(repo), removedMovie(movie) {
}

void RemoveMovieCommand::execute() {
    repo->removeMovie(removedMovie.getTitle());
}

void RemoveMovieCommand::undo() {
    repo->addMovie(removedMovie);
}

UpdateMovieCommand::UpdateMovieCommand(std::shared_ptr<MovieRepository> repo, const Movie& oldMovie, const Movie& newMovie)
    : repo(repo), oldMovie(oldMovie), newMovie(newMovie) {
}

void UpdateMovieCommand::execute() {
    repo->updateMovie(newMovie);
}

void UpdateMovieCommand::undo() {
    repo->updateMovie(oldMovie);
}

MarkWatchedCommand::MarkWatchedCommand(std::shared_ptr<MovieRepository> repo, const std::string& title, bool newState)
    : repo(repo), title(title), newState(newState) {
    auto movie = repo->findMovieByTitle(title);
    if (!movie) throw std::runtime_error("Movie not found for mark watched/unwatched.");
    previousState = movie->getIsWatched();
}

void MarkWatchedCommand::execute() {
    auto movie = repo->findMovieByTitle(title);
    if (movie) movie->setIsWatched(newState);
}

void MarkWatchedCommand::undo() {
    auto movie = repo->findMovieByTitle(title);
    if (movie) movie->setIsWatched(previousState);
}

// ==============================
// Filter Implementations
// ==============================

GenreCriteria::GenreCriteria(const std::string& genre) : genre(genre) {}

bool GenreCriteria::matches(const std::shared_ptr<Movie>& movie) const {
    for (const auto& g : movie->getGenres()) {
        if (g == genre) return true;
    }
    return false;
}

ActorCriteria::ActorCriteria(const std::string& actor) : actor(actor) {}

bool ActorCriteria::matches(const std::shared_ptr<Movie>& movie) const {
    for (const auto& a : movie->getActors()) {
        if (a == actor) return true;
    }
    return false;
}

DirectorCriteria::DirectorCriteria(const std::string& director) : director(director) {}

bool DirectorCriteria::matches(const std::shared_ptr<Movie>& movie) const {
    return movie->getDirector() == director;
}

RatingCriteria::RatingCriteria(const std::string& rating) : rating(rating) {}

bool RatingCriteria::matches(const std::shared_ptr<Movie>& movie) const {
    return movie->getRating() == rating;
}

YearCriteria::YearCriteria(int year) : year(year) {}

bool YearCriteria::matches(const std::shared_ptr<Movie>& movie) const {
    return movie->getYearReleased() == year;
}

WatchedCriteria::WatchedCriteria(bool isWatched) : isWatched(isWatched) {}

bool WatchedCriteria::matches(const std::shared_ptr<Movie>& movie) const {
    return movie->getIsWatched() == isWatched;
}

// Composite AND
void AndCriteria::add(const std::shared_ptr<MovieCriteria>& crit) {
    conditions.push_back(crit);
}

bool AndCriteria::matches(const std::shared_ptr<Movie>& movie) const {
    for (const auto& c : conditions) {
        if (!c->matches(movie)) return false;
    }
    return true;
}

// Composite OR
void OrCriteria::add(const std::shared_ptr<MovieCriteria>& crit) {
    conditions.push_back(crit);
}

bool OrCriteria::matches(const std::shared_ptr<Movie>& movie) const {
    for (const auto& c : conditions) {
        if (c->matches(movie)) return true;
    }
    return false;
}

// ==============================
// Controller Implementation
// ==============================

MovieController::MovieController(std::shared_ptr<MovieRepository> repo)
    : repository(repo) {
}

void MovieController::addMovie(const Movie& movie) {
    auto cmd = std::make_shared<AddMovieCommand>(repository, movie);
    cmd->execute();
    undoStack.push(cmd);
    while (!redoStack.empty()) redoStack.pop();
}

void MovieController::removeMovie(const std::string& title) {
    auto movie = repository->findMovieByTitle(title);
    if (!movie) throw std::runtime_error("Movie not found.");
    auto cmd = std::make_shared<RemoveMovieCommand>(repository, *movie);
    cmd->execute();
    undoStack.push(cmd);
    while (!redoStack.empty()) redoStack.pop();
}

void MovieController::updateMovie(const Movie& movie) {
    auto oldMovie = repository->findMovieByTitle(movie.getTitle());
    if (!oldMovie) throw std::runtime_error("Movie not found.");
    auto cmd = std::make_shared<UpdateMovieCommand>(repository, *oldMovie, movie);
    cmd->execute();
    undoStack.push(cmd);
    while (!redoStack.empty()) redoStack.pop();
}

void MovieController::markAsWatched(const std::string& title) {
    auto cmd = std::make_shared<MarkWatchedCommand>(repository, title, true);
    cmd->execute();
    undoStack.push(cmd);
    while (!redoStack.empty()) redoStack.pop();
}

void MovieController::markAsUnwatched(const std::string& title) {
    auto cmd = std::make_shared<MarkWatchedCommand>(repository, title, false);
    cmd->execute();
    undoStack.push(cmd);
    while (!redoStack.empty()) redoStack.pop();
}

std::vector<std::shared_ptr<Movie>> MovieController::getAllMovies() const {
    return repository->getAllMovies();
}

void MovieController::undo() {
    if (undoStack.empty()) throw std::runtime_error("Nothing to undo.");
    auto cmd = undoStack.top(); undoStack.pop();
    cmd->undo();
    redoStack.push(cmd);
}

void MovieController::redo() {
    if (redoStack.empty()) throw std::runtime_error("Nothing to redo.");
    auto cmd = redoStack.top(); redoStack.pop();
    cmd->execute();
    undoStack.push(cmd);
}

void MovieController::loadMovies()
{
	repository->load();
	// Optionally, you can clear the undo/redo stacks after loading
	while (!undoStack.empty()) undoStack.pop();
	while (!redoStack.empty()) redoStack.pop();
}

void MovieController::saveMovies()
{
	repository->save();
	// Optionally, you can clear the undo/redo stacks after saving
	while (!undoStack.empty()) undoStack.pop();
	while (!redoStack.empty()) redoStack.pop();
}


std::vector<std::shared_ptr<Movie>> MovieController::filterMovies(const std::shared_ptr<MovieCriteria>& criteria) const {
    std::vector<std::shared_ptr<Movie>> result;
    for (const auto& movie : repository->getAllMovies()) {
        if (criteria->matches(movie)) {
            result.push_back(movie);
        }
    }
    return result;
}
