#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "../include/SaveFile.h"
#include "QExtendedWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::unordered_map<SaveFieldID, std::pair<QExtendedWidget*, Type>> saveFieldMap;

    SaveFile *saveFile = NULL;

    void setField(SaveFieldID sfID);
    QString getField(SaveFieldID sfID);

private slots:
    void actionOpen();
    void actionSave();

    void updateText();
};
#endif // MAINWINDOW_H
