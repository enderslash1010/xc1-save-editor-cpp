#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "SaveFile.h"
#include "ui_mainwindow.h"
#include "QExtendedWidget.h"

struct Mapping
{
    QList<int> keys;
    QList<QString> values;

    const QString at(int x) const noexcept
    {
        for(int i = 0; i < keys.count(); i++) if(keys.at(i) == x) return values.at(i);
        return "";
    }

    const int* at(QString x) const noexcept
    {
        for(int i = 0; i < values.count(); i++)
        {
            if(!QString::compare(values.at(i), x))
            {
                return &keys.at(i);
            }
        }
        return nullptr;
    }
};

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
    void connect(SaveFieldID sfID, QExtendedCheckBox* checkBox);
    void connect(SaveFieldID sfID, QExtendedComboBox* comboBox, const Mapping* mapping);

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
};
#endif // MAINWINDOW_H
