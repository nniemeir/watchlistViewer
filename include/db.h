#ifndef DB_H
#define DB_H

#include "QtSql/QSqlDatabase"
#include "qdir.h"
#include "qsqlerror.h"
#include <QtSql/QSqlQuery>

struct Film {
  QString title;
  int timesWatched;
  int lastWatched;
};

class DB {
public:
  static DB &instance() {
    static DB dbInst;
    return dbInst;
  }
  const QVector<Film> &getFilms();
  int readDatabase();

private:
  DB() {};
  QVector<Film> films;
};

#endif // DB_H
