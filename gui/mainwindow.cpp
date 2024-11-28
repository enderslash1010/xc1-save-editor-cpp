#include "mainwindow.h"
#include <QFileDialog>

#define SAVE_FIELD_PROPERTY "SaveField"

std::unordered_map<QObject*, const Mapping*> ComboBoxToMapping;

const Mapping PictureSlotMapping{
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13},
    {"None", "Shulk", "Reyn", "Fiora", "Dunban", "Sharla", "Riki", "Melia", "Seven", "Dickson", "Mumkhar", "Alvis", "Prologue Dunban", "Other Dunban"}
};

inline void MainWindow::connect(SaveFieldID sfID, QExtendedLineEdit* lineEdit, Type type)
{
    QObject::connect(lineEdit, &QLineEdit::editingFinished, this, &MainWindow::updateText);
    lineEdit->setProperty(SAVE_FIELD_PROPERTY, sfID);
    saveFieldMap.insert({sfID, {lineEdit, type}});
}

inline void MainWindow::connect(SaveFieldID sfID, QExtendedCheckBox* checkBox)
{
    QObject::connect(checkBox, &QCheckBox::checkStateChanged, this, &MainWindow::updateCheckBox);
    checkBox->setProperty(SAVE_FIELD_PROPERTY, sfID);
    saveFieldMap.insert({sfID, {checkBox, Type::BOOL_T}});
}

inline void MainWindow::connect(SaveFieldID sfID, QExtendedComboBox* comboBox, const Mapping* mapping)
{
    QObject::connect(comboBox->lineEdit(), &QLineEdit::editingFinished, this, &MainWindow::updateComboBox);
    comboBox->setProperty(SAVE_FIELD_PROPERTY, sfID);
    saveFieldMap.insert({sfID, {comboBox, Type::UINT_T}});

    ComboBoxToMapping.insert({comboBox, mapping});
    comboBox->addItems((*mapping).values);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::actionOpen);
    QObject::connect(ui->actionSave, &QAction::triggered, this, &MainWindow::actionSave);

    connect(THUMLevel, ui->THUMLevel, Type::UINT_T);
    connect(THUMNameString, ui->THUMNameString, Type::STRING_T);
    connect(THUMPlayTimeHours, ui->THUMPlayTimeHours, Type::UINT_T);
    connect(THUMPlayTimeMinutes, ui->THUMPlayTimeMinutes, Type::UINT_T);
    connect(THUMSaveTimeDay, ui->THUMSaveTimeDay, Type::UINT_T);
    connect(THUMSaveTimeMonth, ui->THUMSaveTimeMonth, Type::UINT_T);
    connect(THUMSaveTimeYear, ui->THUMSaveTimeYear, Type::UINT_T);
    connect(THUMNGPlusFlag, ui->THUMNGPlusFlag);
    connect(THUMSystemSaveFlag, ui->THUMSystemSaveFlag);
    connect(THUMPictureSlot1, ui->THUMPictureSlot1, &PictureSlotMapping);
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

// TODO: enable/disable fields

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
        saved = saveFile->setValue<unsigned int>(sfID, newText.toInt(&conversionOk));
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

void MainWindow::updateCheckBox()
{
    QObject* obj = sender();
    SaveFieldID sfID = (SaveFieldID)obj->property(SAVE_FIELD_PROPERTY).toInt();
    QString boolStr = this->getField(sfID);
    saveFile->setValue<boolean>(sfID, QString::compare(boolStr, "0"));
}

void MainWindow::updateComboBox()
{
    QObject* obj = sender();
    SaveFieldID sfID = (SaveFieldID)obj->property(SAVE_FIELD_PROPERTY).toInt();
    QExtendedWidget* comboBox = saveFieldMap.at(sfID).first;
    QString str = this->getField(sfID);

    const Mapping mapping = *ComboBoxToMapping.at(obj);

    if (saveFile != NULL)
    {
        bool ok;
        QString qstr = mapping.at(str.toInt(&ok));
        const int* qint = mapping.at(str);
        if ((QString::compare(qstr, "")))
        {
            if (ok)
            {
                comboBox->setField(qstr);
                saveFile->setValue(sfID, str.toInt());
            }
            else
            {
                if (qint != NULL)
                {
                    comboBox->setField(str);
                    saveFile->setValue(sfID, *qint);
                }
                else
                {
                    showStatusBarMessage("Invalid Input");
                }
            }
        }
        else if (!ok)
        {
            // comboBox->setField(str);
            // saveFile->setValue(sfID, *qint);
        }
        else
        {
            showStatusBarMessage("what");
        }
    }
}
