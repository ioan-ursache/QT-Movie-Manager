#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "Domain.h"
#include <vector>
#include <memory>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <fstream>
#include <sstream>

class MovieRepository {
protected:
    std::vector<std::shared_ptr<Movie>> movies;

public:
    MovieRepository() = default;
    virtual ~MovieRepository() = default;

    virtual void save() const = 0;
    virtual void load() = 0;

    virtual void addMovie(const Movie& movie);
    virtual void removeMovie(const std::string& title);
    virtual void updateMovie(const Movie& movie);
    virtual std::vector<std::shared_ptr<Movie>> getAllMovies() const;
    virtual std::shared_ptr<Movie> findMovieByTitle(const std::string& title) const;

    static std::shared_ptr<MovieRepository> createRepository(const std::string& path);
};

class MovieRepositoryCSV : public MovieRepository {
private:
    std::string filename;

public:
    explicit MovieRepositoryCSV(const std::string& filename);
    void save() const override;
    void load() override;
};

class MovieRepositoryJSON : public MovieRepository {
private:
    QString filename;

public:
    explicit MovieRepositoryJSON(const QString& filename);
    void save() const override;
    void load() override;
};

#endif // REPOSITORY_H
