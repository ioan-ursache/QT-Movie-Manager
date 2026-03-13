#include "Testing.h"

// Movie Testing Implementation

void MovieTesting::testMovieConstructor()
{
    Movie dummy;
    assert(dummy.getTitle().empty());
	assert(dummy.getGenres().empty());
	assert(dummy.getDescription().empty());
	assert(dummy.getPlot().empty());
	assert(dummy.getDirector().empty());
	assert(dummy.getActors().empty());
	assert(dummy.getRating().empty());
	assert(dummy.getMoviePath().empty());
	assert(dummy.getDuration() == 0);
	assert(dummy.getYearReleased() == 0);
	assert(dummy.getIsWatched() == false);
	Movie inception("Inception", { "Sci-Fi", "Thriller" }, "A mind-bending thriller",
		"A thief who steals corporate secrets through the use of dream-sharing technology is given the inverse task of planting an idea into the mind of a CEO.",
		"Christopher Nolan", { "Leonardo DiCaprio", "Joseph Gordon-Levitt", "Elliot Page" }, "PG-13",
		"/path/to/inception.mp4", 148, 2010);
	assert(inception.getTitle() == "Inception");
	assert(inception.getGenres() == std::vector<std::string>({ "Sci-Fi", "Thriller" }));
	assert(inception.getDescription() == "A mind-bending thriller");
	assert(inception.getPlot() == "A thief who steals corporate secrets through the use of dream-sharing technology is given the inverse task of planting an idea into the mind of a CEO.");
	assert(inception.getDirector() == "Christopher Nolan");
	assert(inception.getActors() == std::vector<std::string>({ "Leonardo DiCaprio", "Joseph Gordon-Levitt", "Elliot Page" }));
	assert(inception.getRating() == "PG-13");
	assert(inception.getMoviePath() == "/path/to/inception.mp4");
	assert(inception.getDuration() == 148);
	assert(inception.getYearReleased() == 2010);
	assert(inception.getIsWatched() == false);

}

void MovieTesting::testMovieGetters_Setters()
{
	Movie dummy;
	dummy.setTitle("Dummy Movie");
	assert(dummy.getTitle() == "Dummy Movie");
	dummy.setGenres({ "Action", "Adventure" });
	assert(dummy.getGenres() == std::vector<std::string>({ "Action", "Adventure" }));
	dummy.setDescription("A dummy movie for testing.");
	assert(dummy.getDescription() == "A dummy movie for testing.");
	dummy.setPlot("This is a plot of a dummy movie.");
	assert(dummy.getPlot() == "This is a plot of a dummy movie.");
	dummy.setDirector("John Doe");
	assert(dummy.getDirector() == "John Doe");
	dummy.setActors({ "Actor One", "Actor Two" });
	assert(dummy.getActors() == std::vector<std::string>({ "Actor One", "Actor Two" }));
	dummy.setRating("PG-13");
	assert(dummy.getRating() == "PG-13");
	dummy.setMoviePath("/path/to/dummy.mp4");
	assert(dummy.getMoviePath() == "/path/to/dummy.mp4");
	dummy.setDuration(120);
	assert(dummy.getDuration() == 120);
	dummy.setYearReleased(2023);
	assert(dummy.getYearReleased() == 2023);
	dummy.setIsWatched(true);
	assert(dummy.getIsWatched() == true);
}

void MovieTesting::testMovieStr()
{
	Movie dummy("Dummy Movie", { "Action", "Adventure" }, "A dummy movie for testing.",
		"This is a plot of a dummy movie.", "John Doe", { "Actor One", "Actor Two" }, "PG-13",
		"/path/to/dummy.mp4", 120, 2023);

	std::string expectedStr = "Title: Dummy Movie\nGenres: Action, Adventure\nDescription: A dummy movie for testing.\n"
		"Plot: This is a plot of a dummy movie.\nDirector: John Doe\nActors: Actor One, Actor Two\n"
		"Rating: PG-13\nMovie Path: /path/to/dummy.mp4\nDuration: 120 minutes\nYear Released: 2023\nWatched: No";

	assert(dummy.toString() == expectedStr);
}


void MovieTesting::testMovieEq()
{
	Movie movie1("Movie One", { "Genre1" }, "Description1", "Plot1", "Director1",
		{ "Actor1" }, "PG-13", "/path/to/movie1.mp4", 120, 2020);
	Movie movie2("Movie One", { "Genre1" }, "Description1", "Plot1", "Director1",
		{ "Actor1" }, "PG-13", "/path/to/movie1.mp4", 120, 2020);
	Movie movie3("Movie Two", { "Genre2" }, "Description2", "Plot2", "Director2",
		{ "Actor2" }, "R", "/path/to/movie2.mp4", 150, 2021);
	assert(movie1 == movie2); // Should be equal
	assert(!(movie1 == movie3)); // Should not be equal
}

void MovieTesting::testMovie()
{
	testMovieConstructor();
	testMovieGetters_Setters();
	testMovieStr();
	testMovieEq();
	std::cout << "Movie tests passed" << std::endl;
	assert(true); // If all tests pass, this will be true
}

// CSV Repository Testing Implementation

void CSVRepoTesting::testCSVRepoAdd()
{
	MovieRepositoryCSV repo("repoTest.csv");
	Movie movie("Test Movie", { "Action" }, "A test movie", "Test plot", "Test Director",
		{ "Test Actor" }, "PG-13", "/path/to/test.mp4", 120, 2023);
	repo.addMovie(movie);
	assert(repo.getAllMovies().size() == 1);
	assert(repo.getAllMovies()[0]->getTitle() == "Test Movie");
}

void CSVRepoTesting::testCSVRepoRemove()
{
	MovieRepositoryCSV repo("repoTest.csv");
	Movie movie("Test Movie", { "Action" }, "A test movie", "Test plot", "Test Director",
		{ "Test Actor" }, "PG-13", "/path/to/test.mp4", 120, 2023);
	repo.addMovie(movie);
	repo.removeMovie("Test Movie");
	assert(repo.getAllMovies().empty());
}

void CSVRepoTesting::testCSVRepoUpdate()
{
	MovieRepositoryCSV repo("repoTest.csv");
	Movie movie("Test Movie", { "Action" }, "A test movie", "Test plot", "Test Director",
		{ "Test Actor" }, "PG-13", "/path/to/test.mp4", 120, 2023);
	repo.addMovie(movie);
	movie.setDescription("Updated description");
	repo.updateMovie(movie);
	assert(repo.getAllMovies()[0]->getDescription() == "Updated description");
}

void CSVRepoTesting::testCSVRepoGetAll()
{
	MovieRepositoryCSV repo("repoTest.csv");
	Movie movie1("Test Movie 1", { "Action" }, "A test movie 1", "Test plot 1", "Test Director 1",
		{ "Test Actor 1" }, "PG-13", "/path/to/test1.mp4", 120, 2023);
	Movie movie2("Test Movie 2", { "Drama" }, "A test movie 2", "Test plot 2", "Test Director 2",
		{ "Test Actor 2" }, "R", "/path/to/test2.mp4", 150, 2024);
	repo.addMovie(movie1);
	repo.addMovie(movie2);
	assert(repo.getAllMovies().size() == 2);
}

void CSVRepoTesting::testCSVRepoFindByTitle()
{
	MovieRepositoryCSV repo("repoTest.csv");
	Movie movie("Test Movie", { "Action" }, "A test movie", "Test plot", "Test Director",
		{ "Test Actor" }, "PG-13", "/path/to/test.mp4", 120, 2023);
	repo.addMovie(movie);
	auto foundMovie = repo.findMovieByTitle("Test Movie");
	assert(foundMovie != nullptr);
	assert(foundMovie->getTitle() == "Test Movie");
	assert(repo.findMovieByTitle("Nonexistent Movie") == nullptr);
}

void CSVRepoTesting::testCSVSave()
{
	MovieRepositoryCSV repo("repoTest.csv");
	Movie movie("Test Movie", { "Action" }, "A test movie", "Test plot", "Test Director",
		{ "Test Actor" }, "PG-13", "/path/to/test.mp4", 120, 2023);
	repo.addMovie(movie);
	repo.save();
	assert(true); // If save does not throw an exception, this will be true
}

void CSVRepoTesting::testCSVLoad()
{
	MovieRepositoryCSV repo("repoTest.csv");
	repo.load();
	assert(repo.getAllMovies().size() > 0); // Assuming the file has been populated with movies
}

void CSVRepoTesting::testCSVRepo()
{
	testCSVRepoAdd();
	testCSVRepoRemove();
	testCSVRepoUpdate();
	testCSVRepoGetAll();
	testCSVRepoFindByTitle();
	testCSVSave();
	testCSVLoad();
	std::cout << "CSV Repo tests passed" << std::endl;
	assert(true); // If all tests pass, this will be true
}

// JSON Repository Testing Implementation

void JSONRepoTesting::testJSONRepoAdd()
{
	MovieRepositoryJSON repo("repoTest.json");
	Movie movie("Test Movie", { "Action" }, "A test movie", "Test plot", "Test Director",
		{ "Test Actor" }, "PG-13", "/path/to/test.mp4", 120, 2023);
	repo.addMovie(movie);
	assert(repo.getAllMovies().size() == 1);
	assert(repo.getAllMovies()[0]->getTitle() == "Test Movie");
}

void JSONRepoTesting::testJSONRepoRemove()
{
	MovieRepositoryJSON repo("repoTest.json");
	Movie movie("Test Movie", { "Action" }, "A test movie", "Test plot", "Test Director",
		{ "Test Actor" }, "PG-13", "/path/to/test.mp4", 120, 2023);
	repo.addMovie(movie);
	repo.removeMovie("Test Movie");
	assert(repo.getAllMovies().empty());
}

void JSONRepoTesting::testJSONRepoUpdate()
{
	MovieRepositoryJSON repo("repoTest.json");
	Movie movie("Test Movie", { "Action" }, "A test movie", "Test plot", "Test Director",
		{ "Test Actor" }, "PG-13", "/path/to/test.mp4", 120, 2023);
	repo.addMovie(movie);
	movie.setDescription("Updated description");
	repo.updateMovie(movie);
	assert(repo.getAllMovies()[0]->getDescription() == "Updated description");
}

void JSONRepoTesting::testJSONRepoGetAll()
{
	MovieRepositoryJSON repo("repoTest.json");
	Movie movie1("Test Movie 1", { "Action" }, "A test movie 1", "Test plot 1", "Test Director 1",
		{ "Test Actor 1" }, "PG-13", "/path/to/test1.mp4", 120, 2023);
	Movie movie2("Test Movie 2", { "Drama" }, "A test movie 2", "Test plot 2", "Test Director 2",
		{ "Test Actor 2" }, "R", "/path/to/test2.mp4", 150, 2024);
	repo.addMovie(movie1);
	repo.addMovie(movie2);
	assert(repo.getAllMovies().size() == 2);
}

void JSONRepoTesting::testJSONRepoFindByTitle()
{
	MovieRepositoryJSON repo("repoTest.json");
	Movie movie("Test Movie", { "Action" }, "A test movie", "Test plot", "Test Director",
		{ "Test Actor" }, "PG-13", "/path/to/test.mp4", 120, 2023);
	repo.addMovie(movie);
	auto foundMovie = repo.findMovieByTitle("Test Movie");
	assert(foundMovie != nullptr);
	assert(foundMovie->getTitle() == "Test Movie");
	assert(repo.findMovieByTitle("Nonexistent Movie") == nullptr);
}

void JSONRepoTesting::testJSONSave()
{
	MovieRepositoryJSON repo("repoTest.json");
	Movie movie("Test Movie", { "Action" }, "A test movie", "Test plot", "Test Director",
		{ "Test Actor" }, "PG-13", "/path/to/test.mp4", 120, 2023);
	repo.addMovie(movie);
	repo.save();
	assert(true); // If save does not throw an exception, this will be true
}

void JSONRepoTesting::testJSONLoad()
{
	MovieRepositoryJSON repo("repoTest.json");
	repo.load();
	assert(repo.getAllMovies().size() > 0); // Assuming the file has been populated with movies
}

void JSONRepoTesting::testJSONRepo()
{
	testJSONRepoAdd();
	testJSONRepoRemove();
	testJSONRepoUpdate();
	testJSONRepoGetAll();
	testJSONRepoFindByTitle();
	testJSONSave();
	testJSONLoad();
	std::cout << "JSON Repo tests passed" << std::endl;
	assert(true); // If all tests pass, this will be true
}

void MovieControllerTesting::testAddRemove()
{
	MovieRepositoryCSV repo("repoTest.csv");
	MovieController controller(std::make_shared<MovieRepositoryCSV>(repo));
	// Test adding a movie
	Movie movie1("Test Movie 1", { "Action" }, "A test movie 1", "Test plot 1", "Test Director 1",
		{ "Test Actor 1" }, "PG-13", "/path/to/test1.mp4", 120, 2023);
	controller.addMovie(movie1);
	assert(controller.getAllMovies().size() == 1);
	assert(controller.getAllMovies()[0]->getTitle() == "Test Movie 1");
	// Test removing a movie
	controller.removeMovie("Test Movie 1");
	assert(controller.getAllMovies().empty());
}

void MovieControllerTesting::testUpdate()
{
	MovieRepositoryCSV repo("repoTest.csv");
	MovieController controller(std::make_shared<MovieRepositoryCSV>(repo));
	// Test adding a movie
	Movie movie1("Test Movie 1", { "Action" }, "A test movie 1", "Test plot 1", "Test Director 1",
		{ "Test Actor 1" }, "PG-13", "/path/to/test1.mp4", 120, 2023);
	controller.addMovie(movie1);
	// Test updating the movie
	movie1.setDescription("Updated description");
	controller.updateMovie(movie1);
	assert(controller.getAllMovies()[0]->getDescription() == "Updated description");
}

void MovieControllerTesting::testMarkWatched()
{
	MovieRepositoryCSV repo("repoTest.csv");
	MovieController controller(std::make_shared<MovieRepositoryCSV>(repo));
	// Test adding a movie
	Movie movie1("Test Movie 1", { "Action" }, "A test movie 1", "Test plot 1", "Test Director 1",
		{ "Test Actor 1" }, "PG-13", "/path/to/test1.mp4", 120, 2023);
	controller.addMovie(movie1);
	// Test marking the movie as watched
	controller.markAsWatched("Test Movie 1");
	assert(controller.getAllMovies()[0]->getIsWatched() == true);
	// Test marking the movie as unwatched
	controller.markAsUnwatched("Test Movie 1");
	assert(controller.getAllMovies()[0]->getIsWatched() == false);
}

void MovieControllerTesting::testUndoRedo()
{
	MovieRepositoryCSV repo("repoTest.csv");
	MovieController controller(std::make_shared<MovieRepositoryCSV>(repo));
	// Test adding a movie
	Movie movie1("Test Movie 1", { "Action" }, "A test movie 1", "Test plot 1", "Test Director 1",
		{ "Test Actor 1" }, "PG-13", "/path/to/test1.mp4", 120, 2023);
	controller.addMovie(movie1);
	assert(controller.getAllMovies().size() == 1);
	// Undo the add operation
	controller.undo();
	assert(controller.getAllMovies().empty());
	// Redo the add operation
	controller.redo();
	assert(controller.getAllMovies().size() == 1);
	assert(controller.getAllMovies()[0]->getTitle() == "Test Movie 1");
}

void MovieControllerTesting::testFiltering()
{
	// Setup: use in-memory repository for simplicity
	auto repo = std::make_shared<MovieRepositoryCSV>("repoTest.csv");
	MovieController controller(repo);

	Movie movie1("Test Movie 1", { "Action" }, "", "", "Director A",
		{ "Actor A" }, "PG-13", "test1.mp4", 120, 2023);

	Movie movie2("Test Movie 2", { "Drama" }, "", "", "Director B",
		{ "Actor B" }, "R", "test2.mp4", 150, 2024);

	Movie movie3("Test Movie 3", { "Action", "Drama" }, "", "", "Director A",
		{ "Actor A", "Actor C" }, "PG", "test3.mp4", 90, 2023);

	controller.addMovie(movie1);
	controller.addMovie(movie2);
	controller.addMovie(movie3);

	// Test filtering by single genre
	auto genreFilter = std::make_shared<GenreCriteria>("Action");
	auto actionMovies = controller.filterMovies(genreFilter);
	assert(actionMovies.size() == 2); // movie1 and movie3

	// Test filtering by year
	auto yearFilter = std::make_shared<YearCriteria>(2024);
	auto yearResults = controller.filterMovies(yearFilter);
	assert(yearResults.size() == 1 && yearResults[0]->getTitle() == "Test Movie 2");

	// Test filtering by actor
	auto actorFilter = std::make_shared<ActorCriteria>("Actor C");
	auto actorResults = controller.filterMovies(actorFilter);
	assert(actorResults.size() == 1 && actorResults[0]->getTitle() == "Test Movie 3");

	// Test AND composite: Genre Action AND Director A
	auto andFilter = std::make_shared<AndCriteria>();
	andFilter->add(std::make_shared<GenreCriteria>("Action"));
	andFilter->add(std::make_shared<DirectorCriteria>("Director A"));
	auto andResults = controller.filterMovies(andFilter);
	assert(andResults.size() == 2); // movie1 and movie3

	// Test OR composite: Genre Drama OR Year 2024
	auto orFilter = std::make_shared<OrCriteria>();
	orFilter->add(std::make_shared<GenreCriteria>("Drama"));
	orFilter->add(std::make_shared<YearCriteria>(2024));
	auto orResults = controller.filterMovies(orFilter);
    assert(orResults.size() == 2); 

	std::cout << "Filter tests passed successfully.\n";
}


void MovieControllerTesting::testMovieControlling()
{
	testAddRemove();
	testUpdate();
	testMarkWatched();
	testUndoRedo();
	testFiltering();
	std::cout << "Movie Controller tests passed" << std::endl;
	assert(true); // If all tests pass, this will be true
}

