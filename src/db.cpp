#include "db.h"

const QVector<Film> &DB::getFilms() { return films; }

int DB::readDatabase() {
  const QString name = "filmdb";
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", name);

  const QString homePath = QDir::homePath();
  const QString dbPath = homePath + "/.filmfs/films.db";
  db.setDatabaseName(dbPath);

  if (!db.open()) {
    qWarning() << "Failed to open database";
    QSqlDatabase::removeDatabase(name);
    return 1;
  }

  {
    QSqlQuery query(db);

    if (!query.exec("SELECT TITLE, WATCHCOUNT, LASTWATCHED FROM FILMS")) {
      qWarning() << "Query failed:" << query.lastError().text();
      db.close();
      return 1;
    }

    while (query.next()) {
      Film film;
      film.title = query.value("TITLE").toString();
      film.timesWatched = query.value("WATCHCOUNT").toInt();
      film.lastWatched = query.value("LASTWATCHED").toInt();
      films.append(film);
    }
    query.clear();
  }

  db.close();
  QSqlDatabase::removeDatabase(name);
  
  return 0;
}
