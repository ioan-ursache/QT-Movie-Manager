#include "UserInterface.h"

UserInterface::UserInterface(std::shared_ptr<MovieController> controller, QWidget* parent)
    : QWidget(parent), controller(controller) {
    setupUI();
    populateTable(controller->getAllMovies());
}

void UserInterface::setupUI() {
    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    QVBoxLayout* leftPanel = new QVBoxLayout();
    controlTabs = new QTabWidget(this);

    setupAddTab();
    setupUpdateTab();
    setupRemoveTab();
    setupFilterTab();

    controlTabs->addTab(addTab, "Add");
    controlTabs->addTab(updateTab, "Update");
    controlTabs->addTab(removeTab, "Remove");
    controlTabs->addTab(filterTab, "Filter");

    leftPanel->addWidget(controlTabs);
    setupUndoRedo(leftPanel);
    setupFileControls(leftPanel);

    QVBoxLayout* rightPanel = new QVBoxLayout();
    movieTable = new QTableWidget(this);
    movieTable->setColumnCount(6);
    movieTable->setHorizontalHeaderLabels({ "Title", "Genres", "Director", "Actors", "Year", "Watched" });
    movieTable->horizontalHeader()->setStretchLastSection(true);
    movieTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    movieTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    movieTable->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(movieTable, &QTableWidget::cellClicked, this, &UserInterface::onTableSelectionChanged);

    movieDetailsLabel = new QLabel("<b>Select a movie to see details.</b>", this);
    movieDetailsLabel->setWordWrap(true);
    movieDetailsLabel->setMinimumHeight(100);
    movieDetailsLabel->setStyleSheet("border: 1px solid gray; padding: 6px;");

    rightPanel->addWidget(movieTable);
    rightPanel->addWidget(movieDetailsLabel);

    mainLayout->addLayout(leftPanel);
    mainLayout->addLayout(rightPanel);
    setLayout(mainLayout);
}


void UserInterface::setupUndoRedo(QVBoxLayout* parentLayout) {
    QGroupBox* undoRedoGroup = new QGroupBox("Undo/Redo", this);
    QHBoxLayout* layout = new QHBoxLayout(undoRedoGroup);
    undoButton = new QPushButton("Undo", this);
    redoButton = new QPushButton("Redo", this);
    layout->addWidget(undoButton);
    layout->addWidget(redoButton);
    parentLayout->addWidget(undoRedoGroup);

    connect(undoButton, &QPushButton::clicked, this, &UserInterface::onUndo);
    connect(redoButton, &QPushButton::clicked, this, &UserInterface::onRedo);
}

void UserInterface::setupFileControls(QVBoxLayout* parentLayout) {
    QGroupBox* fileGroup = new QGroupBox("File Controls", this);
    QVBoxLayout* layout = new QVBoxLayout(fileGroup);
    loadButton = new QPushButton("Load", this);
    saveButton = new QPushButton("Save", this);
    fileLabel = new QLabel("No file loaded.", this);

    layout->addWidget(loadButton);
    layout->addWidget(saveButton);
    layout->addWidget(fileLabel);
    parentLayout->addWidget(fileGroup);

    connect(loadButton, &QPushButton::clicked, this, &UserInterface::onLoadFile);
    connect(saveButton, &QPushButton::clicked, this, &UserInterface::onSaveFile);
}

void UserInterface::setupAddTab() {
    addTab = new QWidget(this);
    QFormLayout* layout = new QFormLayout(addTab);
    addTitle = new QLineEdit(this);
    addGenres = new QLineEdit(this);
    addDirector = new QLineEdit(this);
    addActors = new QLineEdit(this);
    addRating = new QLineEdit(this);
    addYear = new QLineEdit(this);
    addDuration = new QLineEdit(this);
    addPath = new QLineEdit(this);
    addPlot = new QTextEdit(this);
    addDescription = new QTextEdit(this);
    addWatched = new QCheckBox("Watched", this);
    addBrowsePathBtn = new QPushButton("Browse", this);
    addConfirmBtn = new QPushButton("Add", this);

    layout->addRow("Title:", addTitle);
    layout->addRow("Genres:", addGenres);
    layout->addRow("Director:", addDirector);
    layout->addRow("Actors:", addActors);
    layout->addRow("Rating:", addRating);
    layout->addRow("Year:", addYear);
    layout->addRow("Duration:", addDuration);
    layout->addRow("Path:", addPath);
    layout->addRow("", addBrowsePathBtn);
    layout->addRow("Plot:", addPlot);
    layout->addRow("Description:", addDescription);
    layout->addRow("", addWatched);
    layout->addRow("", addConfirmBtn);

    connect(addBrowsePathBtn, &QPushButton::clicked, this, &UserInterface::onBrowseAddPath);
    connect(addConfirmBtn, &QPushButton::clicked, this, &UserInterface::onAddMovie);
}

void UserInterface::setupUpdateTab() {
    updateTab = new QWidget(this);
    QFormLayout* layout = new QFormLayout(updateTab);
    updateTitle = new QLineEdit(this);
    updateGenres = new QLineEdit(this);
    updateDirector = new QLineEdit(this);
    updateActors = new QLineEdit(this);
    updateRating = new QLineEdit(this);
    updateYear = new QLineEdit(this);
    updateDuration = new QLineEdit(this);
    updatePath = new QLineEdit(this);
    updatePlot = new QTextEdit(this);
    updateDescription = new QTextEdit(this);
    updateWatched = new QCheckBox("Watched", this);
    updateBrowsePathBtn = new QPushButton("Browse", this);
    updateConfirmBtn = new QPushButton("Update", this);

    layout->addRow("Title:", updateTitle);
    layout->addRow("Genres:", updateGenres);
    layout->addRow("Director:", updateDirector);
    layout->addRow("Actors:", updateActors);
    layout->addRow("Rating:", updateRating);
    layout->addRow("Year:", updateYear);
    layout->addRow("Duration:", updateDuration);
    layout->addRow("Path:", updatePath);
    layout->addRow("", updateBrowsePathBtn);
    layout->addRow("Plot:", updatePlot);
    layout->addRow("Description:", updateDescription);
    layout->addRow("", updateWatched);
    layout->addRow("", updateConfirmBtn);

    connect(updateBrowsePathBtn, &QPushButton::clicked, this, &UserInterface::onBrowseUpdatePath);
    connect(updateConfirmBtn, &QPushButton::clicked, this, &UserInterface::onUpdateMovie);
}

void UserInterface::setupRemoveTab() {
    removeTab = new QWidget(this);
    QFormLayout* layout = new QFormLayout(removeTab);
    removeTitle = new QLineEdit(this);
    removeConfirmBtn = new QPushButton("Remove", this);
    layout->addRow("Title:", removeTitle);
    layout->addRow("", removeConfirmBtn);
    connect(removeConfirmBtn, &QPushButton::clicked, this, &UserInterface::onRemoveMovie);
}

void UserInterface::setupFilterTab() {
    filterTab = new QWidget(this);
    QFormLayout* layout = new QFormLayout(filterTab);
    filterGenre = new QLineEdit(this);
    filterDirector = new QLineEdit(this);
    filterActor = new QLineEdit(this);
    filterRating = new QLineEdit(this);
    filterYear = new QLineEdit(this);
    filterWatched = new QCheckBox("Watched", this);
    filterApplyAnd = new QPushButton("Apply AND", this);
    filterApplyOr = new QPushButton("Apply OR", this);

    layout->addRow("Genre:", filterGenre);
    layout->addRow("Director:", filterDirector);
    layout->addRow("Actor:", filterActor);
    layout->addRow("Rating:", filterRating);
    layout->addRow("Year:", filterYear);
    layout->addRow("", filterWatched);
    layout->addRow("", filterApplyAnd);
    layout->addRow("", filterApplyOr);

    connect(filterApplyAnd, &QPushButton::clicked, this, &UserInterface::onApplyAndFilter);
    connect(filterApplyOr, &QPushButton::clicked, this, &UserInterface::onApplyOrFilter);
}

void UserInterface::populateTable(const std::vector<std::shared_ptr<Movie>>& movies) {
    movieTable->setRowCount(static_cast<int>(movies.size()));
    for (int i = 0; i < movies.size(); ++i) {
        const auto& m = movies[i];
        movieTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(m->getTitle())));
        movieTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(m->getGenres().empty() ? "" : m->getGenres().front())));
        movieTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(m->getDirector())));
        movieTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(m->getActors().empty() ? "" : m->getActors().front())));
        movieTable->setItem(i, 4, new QTableWidgetItem(QString::number(m->getYearReleased())));
        movieTable->setItem(i, 5, new QTableWidgetItem(m->getIsWatched() ? "Yes" : "No"));
    }
    movieTable->resizeColumnsToContents();
}

void UserInterface::showMovieDetails(int row) {
    if (row < 0 || row >= movieTable->rowCount()) return;
    auto title = movieTable->item(row, 0)->text().toStdString();
    auto movie = controller->getAllMovies();
    for (const auto& m : movie) {
        if (m->getTitle() == title) {
            movieDetailsLabel->setText(QString::fromStdString(m->toString()));
            break;
        }
    }
}

// Helper: Convert comma-separated input into vector
static std::vector<std::string> splitCSV(const QString& input) {
    QStringList list = input.split(",", Qt::SkipEmptyParts);
    std::vector<std::string> result;
    for (const QString& s : list)
        result.push_back(s.trimmed().toStdString());
    return result;
}

// ========== Add ==========
void UserInterface::onAddMovie() {
    try {
        Movie m(
            addTitle->text().toStdString(),
            splitCSV(addGenres->text()),
            addDescription->toPlainText().toStdString(),
            addPlot->toPlainText().toStdString(),
            addDirector->text().toStdString(),
            splitCSV(addActors->text()),
            addRating->text().toStdString(),
            addPath->text().toStdString(),
            addDuration->text().toInt(),
            addYear->text().toInt(),
            addWatched->isChecked()
        );
        controller->addMovie(m);
        populateTable(controller->getAllMovies());
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Add Error", e.what());
    }
}

// ========== Update ==========
void UserInterface::onUpdateMovie() {
    try {
        auto existing = controller->getAllMovies();
        auto title = updateTitle->text().toStdString();
        auto movie = controller->getAllMovies();
        auto match = controller->getAllMovies();

        std::shared_ptr<Movie> found = nullptr;
        for (const auto& m : existing) {
            if (m->getTitle() == title) {
                found = m;
                break;
            }
        }
        if (!found) throw std::runtime_error("Movie not found.");

        // Only override if fields are not empty
        Movie updated = *found;
        if (!updateGenres->text().isEmpty()) updated.setGenres(splitCSV(updateGenres->text()));
        if (!updateDescription->toPlainText().isEmpty()) updated.setDescription(updateDescription->toPlainText().toStdString());
        if (!updatePlot->toPlainText().isEmpty()) updated.setPlot(updatePlot->toPlainText().toStdString());
        if (!updateDirector->text().isEmpty()) updated.setDirector(updateDirector->text().toStdString());
        if (!updateActors->text().isEmpty()) updated.setActors(splitCSV(updateActors->text()));
        if (!updateRating->text().isEmpty()) updated.setRating(updateRating->text().toStdString());
        if (!updatePath->text().isEmpty()) updated.setMoviePath(updatePath->text().toStdString());
        if (!updateDuration->text().isEmpty()) updated.setDuration(updateDuration->text().toInt());
        if (!updateYear->text().isEmpty()) updated.setYearReleased(updateYear->text().toInt());
        updated.setIsWatched(updateWatched->isChecked());

        controller->updateMovie(updated);
        populateTable(controller->getAllMovies());
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Update Error", e.what());
    }
}

// ========== Remove ==========
void UserInterface::onRemoveMovie() {
    try {
        controller->removeMovie(removeTitle->text().toStdString());
        populateTable(controller->getAllMovies());
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Remove Error", e.what());
    }
}

// ========== Browse Buttons ==========
void UserInterface::onBrowseAddPath() {
    QString path = QFileDialog::getOpenFileName(this, "Select Movie File", "", "Video Files (*.mp4 *.mkv)");
    if (!path.isEmpty()) addPath->setText(path);
}

void UserInterface::onBrowseUpdatePath() {
    QString path = QFileDialog::getOpenFileName(this, "Select Movie File", "", "Video Files (*.mp4 *.mkv)");
    if (!path.isEmpty()) updatePath->setText(path);
}

// ========== Undo/Redo ==========
void UserInterface::onUndo() {
    try {
        controller->undo();
        populateTable(controller->getAllMovies());
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Undo Error", e.what());
    }
}

void UserInterface::onRedo() {
    try {
        controller->redo();
        populateTable(controller->getAllMovies());
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Redo Error", e.what());
    }
}

// ========== File Load/Save ==========
void UserInterface::onLoadFile() {
    QString path = QFileDialog::getOpenFileName(this, "Load Repository", "", "CSV/JSON Files (*.csv *.json)");
    if (!path.isEmpty()) {
        try {
            auto repo = MovieRepository::createRepository(path.toStdString());
            repo->load();
            controller = std::make_shared<MovieController>(repo);
            populateTable(controller->getAllMovies());
            fileLabel->setText("Loaded: " + path);
        }
        catch (const std::exception& e) {
            QMessageBox::critical(this, "Load Error", e.what());
        }
    }
}

void UserInterface::onSaveFile() {
    QString path = QFileDialog::getSaveFileName(this, "Save Repository", "", "CSV/JSON Files (*.csv *.json)");
    if (!path.isEmpty()) {
        try {
            auto repo = MovieRepository::createRepository(path.toStdString());
            for (const auto& m : controller->getAllMovies())
                repo->addMovie(*m);
            repo->save();
            fileLabel->setText("Saved: " + path);
        }
        catch (const std::exception& e) {
            QMessageBox::critical(this, "Save Error", e.what());
        }
    }
}

// ========== Filtering ==========
void UserInterface::onApplyAndFilter() {
    auto filter = std::make_shared<AndCriteria>();
    if (!filterGenre->text().isEmpty())
        filter->add(std::make_shared<GenreCriteria>(filterGenre->text().toStdString()));
    if (!filterDirector->text().isEmpty())
        filter->add(std::make_shared<DirectorCriteria>(filterDirector->text().toStdString()));
    if (!filterActor->text().isEmpty())
        filter->add(std::make_shared<ActorCriteria>(filterActor->text().toStdString()));
    if (!filterRating->text().isEmpty())
        filter->add(std::make_shared<RatingCriteria>(filterRating->text().toStdString()));
    if (!filterYear->text().isEmpty())
        filter->add(std::make_shared<YearCriteria>(filterYear->text().toInt()));
    if (filterWatched->isChecked())
        filter->add(std::make_shared<WatchedCriteria>(true));

    auto result = controller->filterMovies(filter);
    populateTable(result);
}

void UserInterface::onApplyOrFilter() {
    auto filter = std::make_shared<OrCriteria>();
    if (!filterGenre->text().isEmpty())
        filter->add(std::make_shared<GenreCriteria>(filterGenre->text().toStdString()));
    if (!filterDirector->text().isEmpty())
        filter->add(std::make_shared<DirectorCriteria>(filterDirector->text().toStdString()));
    if (!filterActor->text().isEmpty())
        filter->add(std::make_shared<ActorCriteria>(filterActor->text().toStdString()));
    if (!filterRating->text().isEmpty())
        filter->add(std::make_shared<RatingCriteria>(filterRating->text().toStdString()));
    if (!filterYear->text().isEmpty())
        filter->add(std::make_shared<YearCriteria>(filterYear->text().toInt()));
    if (filterWatched->isChecked())
        filter->add(std::make_shared<WatchedCriteria>(true));

    auto result = controller->filterMovies(filter);
    populateTable(result);
}

// ========== Movie Selection ==========
void UserInterface::onTableSelectionChanged() {
    int row = movieTable->currentRow();
    if (row < 0 || row >= movieTable->rowCount()) return;

    QString title = movieTable->item(row, 0)->text();
    auto movies = controller->getAllMovies();
    for (const auto& m : movies) {
        if (QString::fromStdString(m->getTitle()) == title) {
            movieDetailsLabel->setText(QString::fromStdString(m->toString()));
            break;
        }
    }
}


