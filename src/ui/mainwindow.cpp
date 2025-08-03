#include "mainwindow.h"
#include "db.h"
#include "src/ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  importStylesheet();

  if (DB::instance().readDatabase() == 1) {
    QCoreApplication::exit(1);
  }

  populate_entries("");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::importStylesheet() {
  QFile file(":/stylesheets/stylesheet.qss");
  if (!file.open(QFile::ReadOnly)) {
    qWarning() << "Failed to open stylesheet file:" << file.errorString();
    return;
  }

  QString styleSheet = QLatin1String(file.readAll());

  qApp->setStyleSheet(styleSheet);
}

void MainWindow::populate_entries(QString pattern) {
  const QVector<Film> &films = DB::instance().getFilms();
  for (unsigned int i = 0; i < films.size(); i++) {
    bool match = pattern.isEmpty() ||
                 films[i].title.contains(pattern, Qt::CaseInsensitive);
    if (match) {
      ui->entries->addItem(films[i].title);
    }
  }
}

void MainWindow::on_entries_currentItemChanged(QListWidgetItem *current,
                                               QListWidgetItem *previous) {
  if (current == nullptr) {
    return;
  }

  const QVector<Film> &films = DB::instance().getFilms();

  int index = 0;
  if (!ui->entrySearch->text().isEmpty()) {
    QString currentTitle = current->text();
    for (unsigned int i = 0; i < films.size(); i++) {
      if (currentTitle == films[i].title) {
        index = i;
        break;
      }
    }
  } else {
    index = ui->entries->currentRow();
  }

  ui->titleContents->setText(films[index].title);
  ui->timesWatchedContents->setText(QString::number(films[index].timesWatched));
  ui->lastWatchedContents->setText(QString::number(films[index].lastWatched));
}

void MainWindow::on_entrySearch_textEdited(const QString &arg1) {
  ui->entries->clear();
  populate_entries(arg1);
}
