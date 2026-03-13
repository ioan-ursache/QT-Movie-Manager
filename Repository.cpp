#include "Repository.h"
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <QFile>
#include <QJsonValue>
#include <QTextStream>

// Base MovieRepository

void MovieRepository::addMovie(const Movie& movie) {
    if (findMovieByTitle(movie.getTitle()) != nullptr) {
        throw std::runtime_error("Movie already exists.");
    }
    movies.push_back(std::make_shared<Movie>(movie));
}

void MovieRepository::removeMovie(const std::string& title) {
    auto it = std::remove_if(movies.begin(), movies.end(),
        [&](const std::shared_ptr<Movie>& m) {
            return m->getTitle() == title;
        });
    if (it == movies.end()) {
        throw std::runtime_error("Movie not found.");
    }
    movies.erase(it, movies.end());
}

void MovieRepository::updateMovie(const Movie& movie) {
    for (auto& m : movies) {
        if (m->getTitle() == movie.getTitle()) {
            *m = movie;
            return;
        }
    }
    throw std::runtime_error("Movie not found for update.");
}

std::vector<std::shared_ptr<Movie>> MovieRepository::getAllMovies() const {
    return movies;
}

std::shared_ptr<Movie> MovieRepository::findMovieByTitle(const std::string& title) const {
    for (const auto& m : movies) {
        if (m->getTitle() == title) {
            return m;
        }
    }
    return nullptr;
}

std::shared_ptr<MovieRepository> MovieRepository::createRepository(const std::string& path) {
    if (path.ends_with(".csv")) {
        return std::make_shared<MovieRepositoryCSV>(path);  // OK: std::string
    }
    else if (path.ends_with(".json")) {
        return std::make_shared<MovieRepositoryJSON>(QString::fromStdString(path));  // FIXED
    }
    else {
        throw std::runtime_error("Unsupported file type. Use .csv or .json");
    }
}




// CSV Repository

MovieRepositoryCSV::MovieRepositoryCSV(const std::string& filename) : filename(filename) {}

void MovieRepositoryCSV::save() const {
    std::ofstream out(filename);
    if (!out.is_open()) throw std::runtime_error("Could not open file for writing.");

    for (const auto& m : movies) {
        out << m->getTitle() << ";"
            << m->getDescription() << ";"
            << m->getPlot() << ";"
            << m->getDirector() << ";"
            << m->getRating() << ";"
            << m->getMoviePath() << ";"
            << m->getDuration() << ";"
            << m->getYearReleased() << ";"
            << m->getIsWatched() << ";";

        // genres
        for (const auto& g : m->getGenres()) out << g << ",";
        out << ";";

        // actors
        for (const auto& a : m->getActors()) out << a << ",";
        out << "\n";
    }
}

void MovieRepositoryCSV::load() {
    movies.clear();
    std::ifstream in(filename);
    if (!in.is_open()) throw std::runtime_error("Could not open file for reading.");

    std::string line;
    while (std::getline(in, line)) {
        std::stringstream ss(line);
        std::string title, desc, plot, director, rating, path, durationStr, yearStr, watchedStr, genresStr, actorsStr;

        std::getline(ss, title, ';');
        std::getline(ss, desc, ';');
        std::getline(ss, plot, ';');
        std::getline(ss, director, ';');
        std::getline(ss, rating, ';');
        std::getline(ss, path, ';');
        std::getline(ss, durationStr, ';');
        std::getline(ss, yearStr, ';');
        std::getline(ss, watchedStr, ';');
        std::getline(ss, genresStr, ';');
        std::getline(ss, actorsStr, ';');

        int duration = std::stoi(durationStr);
        int year = std::stoi(yearStr);
        bool watched = (watchedStr == "1");

        std::vector<std::string> genres, actors;
        std::stringstream gss(genresStr), ass(actorsStr);
        std::string token;

        while (std::getline(gss, token, ',')) {
            if (!token.empty()) genres.push_back(token);
        }
        while (std::getline(ass, token, ',')) {
            if (!token.empty()) actors.push_back(token);
        }

        Movie m(title, genres, desc, plot, director, actors, rating, path, duration, year, watched);
        movies.push_back(std::make_shared<Movie>(m));
    }
}

//  JSON Repository 

MovieRepositoryJSON::MovieRepositoryJSON(const QString& filename) : filename(filename) {}

void MovieRepositoryJSON::save() const {
    QJsonArray movieArray;
    for (const auto& m : movies) {
        QJsonObject obj;
        obj["title"] = QString::fromStdString(m->getTitle());
        obj["description"] = QString::fromStdString(m->getDescription());
        obj["plot"] = QString::fromStdString(m->getPlot());
        obj["director"] = QString::fromStdString(m->getDirector());
        obj["rating"] = QString::fromStdString(m->getRating());
        obj["path"] = QString::fromStdString(m->getMoviePath());
        obj["duration"] = m->getDuration();
        obj["year"] = m->getYearReleased();
        obj["watched"] = m->getIsWatched();

        QJsonArray genres;
        for (const auto& g : m->getGenres()) {
            genres.append(QString::fromStdString(g));
        }
        obj["genres"] = genres;

        QJsonArray actors;
        for (const auto& a : m->getActors()) {
            actors.append(QString::fromStdString(a));
        }
        obj["actors"] = actors;

        movieArray.append(obj);
    }

    QJsonDocument doc(movieArray);
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        throw std::runtime_error("Unable to open JSON file for writing.");
    }
    file.write(doc.toJson());
    file.close();
}

void MovieRepositoryJSON::load() {
    movies.clear();
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        throw std::runtime_error("Unable to open JSON file for reading.");
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray array = doc.array();

    for (const auto& value : array) {
        QJsonObject obj = value.toObject();

        std::string title = obj["title"].toString().toStdString();
        std::string desc = obj["description"].toString().toStdString();
        std::string plot = obj["plot"].toString().toStdString();
        std::string director = obj["director"].toString().toStdString();
        std::string rating = obj["rating"].toString().toStdString();
        std::string path = obj["path"].toString().toStdString();
        int duration = obj["duration"].toInt();
        int year = obj["year"].toInt();
        bool watched = obj["watched"].toBool();

        std::vector<std::string> genres, actors;
        for (const auto& g : obj["genres"].toArray()) {
            genres.push_back(g.toString().toStdString());
        }
        for (const auto& a : obj["actors"].toArray()) {
            actors.push_back(a.toString().toStdString());
        }

        Movie m(title, genres, desc, plot, director, actors, rating, path, duration, year, watched);
        movies.push_back(std::make_shared<Movie>(m));
    }
}
