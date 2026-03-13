#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Repository.h"
#include <memory>
#include <stack>
#include <vector>
#include <string>

// ==============================
// Command Pattern
// ==============================

class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() = default;
};

class AddMovieCommand : public Command {
private:
    std::shared_ptr<MovieRepository> repo;
    Movie movie;
public:
    AddMovieCommand(std::shared_ptr<MovieRepository> repo, const Movie& movie);
    void execute() override;
    void undo() override;
};

class RemoveMovieCommand : public Command {
private:
    std::shared_ptr<MovieRepository> repo;
    Movie removedMovie;
public:
    RemoveMovieCommand(std::shared_ptr<MovieRepository> repo, const Movie& movie);
    void execute() override;
    void undo() override;
};

class UpdateMovieCommand : public Command {
private:
    std::shared_ptr<MovieRepository> repo;
    Movie oldMovie;
    Movie newMovie;
public:
    UpdateMovieCommand(std::shared_ptr<MovieRepository> repo, const Movie& oldMovie, const Movie& newMovie);
    void execute() override;
    void undo() override;
};

class MarkWatchedCommand : public Command {
private:
    std::shared_ptr<MovieRepository> repo;
    std::string title;
    bool previousState;
    bool newState;
public:
    MarkWatchedCommand(std::shared_ptr<MovieRepository> repo, const std::string& title, bool newState);
    void execute() override;
    void undo() override;
};

// ==============================
// Filtering Design Pattern (with AND / OR)
// ==============================

class MovieCriteria {
public:
    virtual bool matches(const std::shared_ptr<Movie>& movie) const = 0;
    virtual ~MovieCriteria() = default;
};

class GenreCriteria : public MovieCriteria {
private:
    std::string genre;
public:
    explicit GenreCriteria(const std::string& genre);
    bool matches(const std::shared_ptr<Movie>& movie) const override;
};

class ActorCriteria : public MovieCriteria {
private:
    std::string actor;
public:
    explicit ActorCriteria(const std::string& actor);
    bool matches(const std::shared_ptr<Movie>& movie) const override;
};

class DirectorCriteria : public MovieCriteria {
private:
    std::string director;
public:
    explicit DirectorCriteria(const std::string& director);
    bool matches(const std::shared_ptr<Movie>& movie) const override;
};

class RatingCriteria : public MovieCriteria {
private:
    std::string rating;
public:
    explicit RatingCriteria(const std::string& rating);
    bool matches(const std::shared_ptr<Movie>& movie) const override;
};

class YearCriteria : public MovieCriteria {
private:
    int year;
public:
    explicit YearCriteria(int year);
    bool matches(const std::shared_ptr<Movie>& movie) const override;
};

class WatchedCriteria : public MovieCriteria {
private:
    bool isWatched;
public:
    explicit WatchedCriteria(bool isWatched);
    bool matches(const std::shared_ptr<Movie>& movie) const override;
};

// === Composite Criteria ===

class AndCriteria : public MovieCriteria {
private:
    std::vector<std::shared_ptr<MovieCriteria>> conditions;
public:
    void add(const std::shared_ptr<MovieCriteria>& crit);
    bool matches(const std::shared_ptr<Movie>& movie) const override;
};

class OrCriteria : public MovieCriteria {
private:
    std::vector<std::shared_ptr<MovieCriteria>> conditions;
public:
    void add(const std::shared_ptr<MovieCriteria>& crit);
    bool matches(const std::shared_ptr<Movie>& movie) const override;
};

// ==============================
// Controller Class
// ==============================

class MovieController {
private:
    std::shared_ptr<MovieRepository> repository;

    std::stack<std::shared_ptr<Command>> undoStack;
    std::stack<std::shared_ptr<Command>> redoStack;

public:
    explicit MovieController(std::shared_ptr<MovieRepository> repo);

    void addMovie(const Movie& movie);
    void removeMovie(const std::string& title);
    void updateMovie(const Movie& movie);

    void markAsWatched(const std::string& title);
    void markAsUnwatched(const std::string& title);

    std::vector<std::shared_ptr<Movie>> getAllMovies() const;

    void undo();
    void redo();

    void loadMovies();
    void saveMovies();

	// Advanced filter using criteria composition. It does not modify the repository.
    std::vector<std::shared_ptr<Movie>> filterMovies(const std::shared_ptr<MovieCriteria>& criteria) const;
};

#endif // CONTROLLER_H
