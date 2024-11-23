#include "mainwindow.h"
#include <QFileDialog>

#define SAVE_FIELD_PROPERTY "SaveField"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::actionOpen);
    QObject::connect(ui->actionSave, &QAction::triggered, this, &MainWindow::actionSave);

    QObject::connect(ui->THUMLevel, &QLineEdit::editingFinished, this, &MainWindow::updateText);
    ui->THUMLevel->setProperty(SAVE_FIELD_PROPERTY, THUMLevel);
    saveFieldMap.insert({THUMLevel, {ui->THUMLevel, Type::INT_T}});

    QObject::connect(ui->THUMNameString, &QLineEdit::editingFinished, this, &MainWindow::updateText);
    ui->THUMNameString->setProperty(SAVE_FIELD_PROPERTY, THUMNameString);
    saveFieldMap.insert({THUMNameString, {ui->THUMNameString, Type::STRING_T}});
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::showStatusBarMessage(std::string str)
{
    ui->statusbar->showMessage(QString::fromStdString(str));
}

QString MainWindow::getField(SaveFieldID sfID)
{
    return this->saveFieldMap.at(sfID).first->getField();
}

void MainWindow::setField(SaveFieldID sfID)
{
    if (this->saveFieldMap.find(sfID) == this->saveFieldMap.end()) return;

    QExtendedWidget* widget = this->saveFieldMap.at(sfID).first;
    Type type = this->saveFieldMap.at(sfID).second;

    switch (type)
    {
    case UINT_T:
        widget->setField(QString::number(saveFile->getValue<unsigned int>(sfID)));
        break;
    case INT_T:
        widget->setField(QString::number(saveFile->getValue<int>(sfID)));
        break;
    case BOOL_T:
        widget->setField(QString::number(saveFile->getValue<bool>(sfID)));
        break;
    case FLOAT_T:
        widget->setField(QString::number(saveFile->getValue<float>(sfID)));
        break;
    case STRING_T:
        widget->setField(QString::fromStdString(saveFile->getValue<std::string>(sfID)));
        break;
    case TPL_T:
        // TODO
        break;
    case ARRAY_T:
        // TODO
        break;
    }
}

void MainWindow::actionOpen()
{
    QString fileName = QFileDialog::getOpenFileName();
    try {
        saveFile = new SaveFile(fileName.toStdString());

        for (int i = 0; i < LAST_INDEX; i++) setField((SaveFieldID)i);

        showStatusBarMessage("Successfully opened " + fileName.toStdString());
    } catch (std::runtime_error e) {
        showStatusBarMessage(e.what());
    }
}

void MainWindow::actionSave()
{
    if (saveFile != NULL)
    {
        saveFile->saveToFile();
        showStatusBarMessage("Saved to file " + saveFile->getFileName());
    }
    else
    {
        showStatusBarMessage("No save file opened");
    }
}

void MainWindow::updateText()
{
    QObject* obj = sender();
    SaveFieldID sfID = (SaveFieldID)obj->property(SAVE_FIELD_PROPERTY).toInt();
    Type type = saveFieldMap.at(sfID).second;
    QString newText = this->getField(sfID);

    std::vector<uint8_t> previousBytes = saveFile->getRawBytes(sfID);

    bool conversionOk = true;
    bool saved = true;
    switch (type)
    {
    case UINT_T:
        saved = saveFile->setValue(sfID, newText.toUInt(&conversionOk));
        break;
    case INT_T:
        saved = saveFile->setValue(sfID, newText.toInt(&conversionOk));
        break;
    case BOOL_T:
        saved = saveFile->setValue(sfID, newText.toInt(&conversionOk) == 0 ? false : true);
        break;
    case FLOAT_T:
        saved = saveFile->setValue(sfID, newText.toFloat(&conversionOk));
        break;
    case STRING_T:
        saved = saveFile->setValue(sfID, newText.toStdString());
        break;
    case TPL_T:
        // TODO
        break;
    case ARRAY_T:
        // TODO
        break;
    }

    if (!conversionOk)
    {
        saveFile->setValue(sfID, previousBytes);
        showStatusBarMessage("Invalid input");
    }
    if (!saved) showStatusBarMessage("Value out of range");
    this->setField(sfID);
}
