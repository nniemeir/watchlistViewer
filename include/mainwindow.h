#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidget>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_entries_currentItemChanged(QListWidgetItem *current,
                                     QListWidgetItem *previous);
  void on_entrySearch_textEdited(const QString &arg1);

private:
  Ui::MainWindow *ui;
  void importStylesheet();
  void populate_entries(QString pattern);
};

#endif // MAINWINDOW_H
