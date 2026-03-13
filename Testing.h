#ifndef TESTING_H
#define TESTING_H

#include "Domain.h"
#include "Repository.h"
#include "Controller.h"
#include <crtdbg.h>
#include <cassert>

// Domain Testing
class MovieTesting {
private:
	void testMovieConstructor();
	void testMovieGetters_Setters();
	void testMovieStr();
	void testMovieEq();
public:
	void testMovie();
}; // checked

// CSV Repository Testing
class CSVRepoTesting {
private:
	void testCSVRepoAdd();
	void testCSVRepoRemove();
	void testCSVRepoUpdate();
	void testCSVRepoGetAll();
	void testCSVRepoFindByTitle();
	void testCSVSave();
	void testCSVLoad();
public:
	void testCSVRepo();
}; // checked

// JSON Repository Testing
class JSONRepoTesting {
private:
	void testJSONRepoAdd();
	void testJSONRepoRemove();
	void testJSONRepoUpdate();
	void testJSONRepoGetAll();
	void testJSONRepoFindByTitle();
	void testJSONSave();
	void testJSONLoad();
public:
	void testJSONRepo();
}; // checked

// Movie Controller Testing
class MovieControllerTesting {
private:
	void testAddRemove();
	void testUpdate();
	void testMarkWatched();
	void testUndoRedo();
	void testFiltering();

public:
	void testMovieControlling();
}; // checked


class Testing {
public:
	static void runTests() {
		MovieTesting movieTest;
		movieTest.testMovie();

		CSVRepoTesting csvRepoTest;
		csvRepoTest.testCSVRepo();

		JSONRepoTesting jsonRepoTest;
		jsonRepoTest.testJSONRepo();

		MovieControllerTesting controllerTest;
		controllerTest.testMovieControlling();


		_CrtDumpMemoryLeaks();
		std::cout << "All tests passed successfully!" << std::endl;
	}
};

#endif // TESTING_H

