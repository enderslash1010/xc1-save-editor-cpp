#include "mainwindow.h"
#include <QFileDialog>

#define SAVE_FIELD_PROPERTY "SaveField"

std::unordered_map<QExtendedWidget*, const Mapping*> ComboBoxToMapping;

// TODO: make these easier to read? more similar to 'hashmap' init
const Mapping PlayerMapping
{
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13},
    {"None", "Shulk", "Reyn", "Fiora", "Dunban", "Sharla", "Riki", "Melia", "Seven", "Dickson", "Mumkhar", "Alvis", "Prologue Dunban", "Other Dunban"}
};

const Mapping MapMapping
{
    {0x0, 0x010001, 0x010002, 0x010003, 0x010004, 0x020004, 0x010005, 0x010006, 0x010007, 0x010008, 0x010009, 0x010010, 0x010011, 0x010012, 0x020012, 0x010013, 0x010014, 0x010015, 0x010016, 0x020016, 0x010017, 0x010019, 0x010020, 0x010021, 0x010022, 0x010023, 0x010024, 0x020001},
    {
     "Title Screen (ma0000)", "Colony 9 (ma0101)", "Tephra Cave (ma0201)", "Bionis' Leg (ma0301)", "Colony 6 (ma0401)",
     "Ether Mine (ma0402)", "Satorl Marsh (ma0501)", "Makna Forest (ma0601)", "Frontier Village (ma0701)", "Bionis' Shoulder (ma0801)",
     "High Entia Tomb (ma0901)", "Eryth Sea (ma1001)", "Alcamoth (ma1101)", "Prison Island (ma1201)", "Fallen Prison Island (ma1202)",
     "Valak Mountain (ma1301)", "Sword Valley (ma1401)", "Galahad Fortress (ma1501)", "Fallen Arm (ma1601)", "Beta Fallen Arm (ma1602)",
     "Mechonis Field (ma1701)", "Agniratha (ma1901)", "Central Factory (ma2001)", "Bionis' Interior (ma2101)", "Memory Space (ma2201)",
     "Mechonis Core (ma2301)", "Junks (ma2401)", "Post-Game Colony 9 (ma0102)"
    }
};

const Mapping MapStringMapping
    {
        {0x30303030, 0x30313031, 0x30323031, 0x30333031, 0x30343031, 0x30343032, 0x30353031, 0x30363031, 0x30373031, 0x30383031, 0x30393031, 0x31303031, 0x31313031, 0x31323031, 0x31323032, 0x31333031, 0x31343031, 0x31353031, 0x31363031, 0x31363032, 0x31373031, 0x31393031, 0x32303031, 0x32313031, 0x32323031, 0x32333031, 0x32343031, 0x30313032},
        {
            "Title Screen (ma0000)", "Colony 9 (ma0101)", "Tephra Cave (ma0201)", "Bionis' Leg (ma0301)", "Colony 6 (ma0401)",
            "Ether Mine (ma0402)", "Satorl Marsh (ma0501)", "Makna Forest (ma0601)", "Frontier Village (ma0701)", "Bionis' Shoulder (ma0801)",
            "High Entia Tomb (ma0901)", "Eryth Sea (ma1001)", "Alcamoth (ma1101)", "Prison Island (ma1201)", "Fallen Prison Island (ma1202)",
            "Valak Mountain (ma1301)", "Sword Valley (ma1401)", "Galahad Fortress (ma1501)", "Fallen Arm (ma1601)", "Beta Fallen Arm (ma1602)",
            "Mechonis Field (ma1701)", "Agniratha (ma1901)", "Central Factory (ma2001)", "Bionis' Interior (ma2101)", "Memory Space (ma2201)",
            "Mechonis Core (ma2301)", "Junks (ma2401)", "Post-Game Colony 9 (ma0102)"
        }
    };

inline void MainWindow::connect(SaveFieldID sfID, QExtendedLineEdit* lineEdit, Type type)
{
    Q_ASSERT(QObject::connect(lineEdit, &QLineEdit::editingFinished, this, &MainWindow::updateText));
    lineEdit->setProperty(SAVE_FIELD_PROPERTY, sfID);
    saveFieldMap.insert({sfID, {lineEdit, type}});
}

inline void MainWindow::connect(SaveFieldID sfID, QExtendedCheckBox* checkBox)
{
    Q_ASSERT(QObject::connect(checkBox, &QCheckBox::stateChanged, this, &MainWindow::updateCheckBox));
    checkBox->setProperty(SAVE_FIELD_PROPERTY, sfID);
    saveFieldMap.insert({sfID, {checkBox, Type::BOOL_T}});
}

inline void MainWindow::connect(SaveFieldID sfID, QExtendedComboBox* comboBox, const Mapping* mapping)
{
    if (comboBox->lineEdit() != nullptr)
    {
        QObject::connect(comboBox->lineEdit(), &QLineEdit::editingFinished, this, &MainWindow::updateComboBox);
        comboBox->lineEdit()->setProperty(SAVE_FIELD_PROPERTY, sfID);
    }
    else
    {
        QObject::connect(comboBox, &QComboBox::currentTextChanged, this, &MainWindow::updateComboBox);
        comboBox->setProperty(SAVE_FIELD_PROPERTY, sfID);
    }

    saveFieldMap.insert({sfID, {comboBox, Type::STRING_T}});

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
    connect(THUMPictureSlot1, ui->THUMPictureSlot1, &PlayerMapping);
    connect(THUMPictureSlot2, ui->THUMPictureSlot2, &PlayerMapping);
    connect(THUMPictureSlot3, ui->THUMPictureSlot3, &PlayerMapping);
    connect(THUMPictureSlot4, ui->THUMPictureSlot4, &PlayerMapping);
    connect(THUMPictureSlot5, ui->THUMPictureSlot5, &PlayerMapping);
    connect(THUMPictureSlot6, ui->THUMPictureSlot6, &PlayerMapping);
    connect(THUMPictureSlot7, ui->THUMPictureSlot7, &PlayerMapping);

    connect(FLAGScenarioID, ui->FLAGScenarioID, Type::UINT_T);

    connect(GAMEMapNum, ui->GAMEMapNum, &MapMapping);
    connect(GAMEMapNumString, ui->GAMEMapNumString, &MapStringMapping);
    connect(GAMEPlayer1, ui->GAMEPlayer1, &PlayerMapping);
    connect(GAMEPlayer2, ui->GAMEPlayer2, &PlayerMapping);
    connect(GAMEPlayer3, ui->GAMEPlayer3, &PlayerMapping);
    connect(GAMEPlayer4, ui->GAMEPlayer4, &PlayerMapping);
    connect(GAMEPlayer5, ui->GAMEPlayer5, &PlayerMapping);
    connect(GAMEPlayer6, ui->GAMEPlayer6, &PlayerMapping);
    connect(GAMEPlayer7, ui->GAMEPlayer7, &PlayerMapping);

    for (int i = 0; i < LAST_INDEX; i++) setFieldEnabled((SaveFieldID)i, false);
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

    if (saveFile != nullptr)
    {
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
        {
            if (ComboBoxToMapping.find(widget) != ComboBoxToMapping.end())
            {
                const Mapping mapping = *ComboBoxToMapping.at(widget);
                unsigned int value = saveFile->getValue<unsigned int>(sfID);
                const QString str = mapping.at(value);
                if (str != "") widget->setField(str);
                else widget->setField(QString::number(value));
            }
            else
            {
                widget->setField(QString::fromStdString(saveFile->getValue<std::string>(sfID)));
            }
        }
        break;
        case TPL_T:
            // TODO
            break;
        case ARRAY_T:
            // TODO
            break;
        }
    }
}

void MainWindow::setFieldEnabled(SaveFieldID sfID, bool enabled)
{
    if (this->saveFieldMap.find(sfID) == this->saveFieldMap.end()) return;
    QExtendedWidget* widget = this->saveFieldMap.at(sfID).first;
    widget->setFieldEnabled(enabled);
}

void MainWindow::actionOpen()
{
    QString fileName = QFileDialog::getOpenFileName();
    try {
        saveFile = new SaveFile(fileName.toStdString());

        for (int i = 0; i < LAST_INDEX; i++)
        {
            setField((SaveFieldID)i);
            setFieldEnabled((SaveFieldID)i, true);
        }

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
        if (!conversionOk) saved = saveFile->setValue<unsigned int>(sfID, newText.toUInt(&conversionOk));
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
    saveFile->setValue<bool>(sfID, QString::compare(boolStr, "0"));
}

void MainWindow::updateComboBox()
{
    QObject* obj = sender();
    SaveFieldID sfID = (SaveFieldID)obj->property(SAVE_FIELD_PROPERTY).toInt();
    QExtendedWidget* comboBox = saveFieldMap.at(sfID).first;
    QString comboBoxText = this->getField(sfID);

    if (saveFile != NULL)
    {
        const Mapping mapping = *ComboBoxToMapping.at(comboBox);

        bool isInt, isUInt;
        int textToInt = comboBoxText.toInt(&isInt);
        unsigned int textToUInt = comboBoxText.toUInt(&isUInt);
        const int* mappingIntPtr = mapping.at(comboBoxText);

        if (mappingIntPtr != NULL)
        {
            saveFile->setValue(sfID, *mappingIntPtr);
            this->setField(sfID);
        }
        else if (isInt)
        {
            saveFile->setValue<unsigned int>(sfID, textToInt);
        }
        else if (isUInt)
        {
            saveFile->setValue<unsigned int>(sfID, textToUInt);
        }
        else
        {
            showStatusBarMessage("Invalid input");
        }
        this->setField(sfID);
    }
}
