#include <QApplication>
#include <QMessageBox>
#include "UserInterface.h"
#include "Repository.h"
#include "Controller.h"
#include "Testing.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);  // Must be first

    Testing::runTests();

    try {
        // Create initial repository (can be changed by user via UI later)
        auto repository = MovieRepository::createRepository("CSVLib.csv");
        repository->load();

        auto controller = std::make_shared<MovieController>(repository);

        UserInterface ui(controller);
        ui.setWindowTitle("Movie Collection Manager");
        ui.resize(1000, 700);
        ui.show();

        return app.exec();
    }
    catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "Fatal Error", e.what());
        return 1;
    }

    return 0;

}
