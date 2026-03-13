#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <QWidget>
#include <QTabWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QFileDialog>
#include <QGroupBox>


#include "Controller.h"
#include <memory>

class UserInterface : public QWidget {
    Q_OBJECT

private:
    std::shared_ptr<MovieController> controller;

    // UI Layouts and Tabs
    QTabWidget* controlTabs;

    // Add tab
    QWidget* addTab;
    QLineEdit* addTitle, * addGenres, * addDirector, * addActors, * addRating, * addYear, * addDuration, * addPath;
    QTextEdit* addPlot, * addDescription;
    QCheckBox* addWatched;
    QPushButton* addBrowsePathBtn, * addConfirmBtn;

    // Update tab
    QWidget* updateTab;
    QLineEdit* updateTitle, * updateGenres, * updateDirector, * updateActors, * updateRating, * updateYear, * updateDuration, * updatePath;
    QTextEdit* updatePlot, * updateDescription;
    QCheckBox* updateWatched;
    QPushButton* updateBrowsePathBtn, * updateConfirmBtn;

    // Remove tab
    QWidget* removeTab;
    QLineEdit* removeTitle;
    QPushButton* removeConfirmBtn;

    // Filter tab
    QWidget* filterTab;
    QLineEdit* filterGenre, * filterDirector, * filterActor, * filterRating, * filterYear;
    QCheckBox* filterWatched;
    QPushButton* filterApplyAnd, * filterApplyOr;

    // Undo/Redo
    QPushButton* undoButton, * redoButton;

    // File controls
    QPushButton* loadButton, * saveButton;
    QLabel* fileLabel;

    // Movie table and details
    QTableWidget* movieTable;
    QLabel* movieDetailsLabel;

    // Setup methods
    void setupUI();
    void setupAddTab();
    void setupUpdateTab();
    void setupRemoveTab();
    void setupFilterTab();
    void setupUndoRedo(QVBoxLayout* parentLayout);
    void setupFileControls(QVBoxLayout* parentLayout);

    void populateTable(const std::vector<std::shared_ptr<Movie>>& movies);
    void showMovieDetails(int row);

private slots:
    void onAddMovie();
    void onUpdateMovie();
    void onRemoveMovie();
    void onApplyAndFilter();
    void onApplyOrFilter();
    void onUndo();
    void onRedo();
    void onBrowseAddPath();
    void onBrowseUpdatePath();
    void onLoadFile();
    void onSaveFile();
    void onTableSelectionChanged();

public:
    explicit UserInterface(std::shared_ptr<MovieController> controller, QWidget* parent = nullptr);
};

#endif // USERINTERFACE_H
