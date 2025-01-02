#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "SaveFile.h"
#include "ui_mainwindow.h"
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

    void connect(SaveFieldID sfID, QExtendedLineEdit* lineEdit, Type type);
    void connect(SaveFieldID sfID, QExtendedCheckBox* checkBox, bool invert);
    void connect(SaveFieldID sfID, QExtendedComboBox* comboBox, const Mapping* mapping);
    void connect(SaveFieldID sfID, QExtendedComboBox* thisComboBox, QExtendedComboBox* sourceComboBox, std::vector<const Mapping*>& dynamicMapping);
    void connect(SaveFieldID sfID, QExtendedRadioButtons* radioButtonFrame, std::unordered_map<QString, QRadioButton*>& rbs);
    void connect(SaveFieldID sfID, QExtendedSlider* slider, int start, int spacing, int count);

    void setField(SaveFieldID sfID);
    QString getField(SaveFieldID sfID);
    void setFieldEnabled(SaveFieldID sfID, bool enabled);

    void showStatusBarMessage(std::string str);

private slots:
    void actionOpen();
    void actionSave();

    void updateText();
    void updateCheckBox();
    void updateComboBox();
    void updateRadioButton();
    void updateSlider();

    void updateChildMapping();
};
#endif // MAINWINDOW_H
