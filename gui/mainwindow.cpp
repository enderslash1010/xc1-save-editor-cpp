#include "mainwindow.h"
#include <QFileDialog>
#include <iostream>

#define SAVE_FIELD_PROPERTY "SaveField"

// TODO: make these easier to read? more similar to 'hashmap' init
const Mapping PlayerMapping
{
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13},
    {"None", "Shulk", "Reyn", "Fiora", "Dunban", "Sharla", "Riki", "Melia", "Seven", "Dickson", "Mumkhar", "Alvis", "Prologue Dunban", "Other Dunban"}
};

const Mapping MapMapping
{
    {0x0, 0x0101, 0x0201, 0x0301, 0x0401, 0x0402, 0x0501, 0x0601, 0x0701, 0x0801, 0x0901, 0x0A01, 0x0B01, 0x0C01, 0x0C02, 0x0D01, 0x0E01, 0x0F01, 0x1001, 0x1002, 0x1101, 0x1301, 0x1401, 0x1501, 0x1601, 0x1701, 0x1801, 0x0102},
    {
        "Title Screen (ma0000)", "Colony 9 (ma0101)", "Tephra Cave (ma0201)", "Bionis' Leg (ma0301)", "Colony 6 (ma0401)",
        "Ether Mine (ma0402)", "Satorl Marsh (ma0501)", "Makna Forest (ma0601)", "Frontier Village (ma0701)", "Bionis' Shoulder (ma0801)",
        "High Entia Tomb (ma0901)", "Eryth Sea (ma1001)", "Alcamoth (ma1101)", "Prison Island (ma1201)", "Fallen Prison Island (ma1202)",
        "Valak Mountain (ma1301)", "Sword Valley (ma1401)", "Galahad Fortress (ma1501)", "Fallen Arm (ma1601)", "Beta Fallen Arm (ma1602)",
        "Mechonis Field (ma1701)", "Agniratha (ma1901)", "Central Factory (ma2001)", "Bionis' Interior (ma2101)", "Memory Space (ma2201)",
        "Mechonis Core (ma2301)", "Junks (ma2401)", "Post-Game Colony 9 (ma0102)"
    }
};

const Mapping MapGapMapping
    {
        {0x0, 0x010001, 0x020001, 0x030001, 0x040001, 0x040002, 0x050001, 0x060001, 0x070001, 0x080001, 0x090001, 0x0A0001, 0x0B0001, 0x0C0001, 0x0C0002, 0x0D0001, 0x0E0001, 0x0F0001, 0x100001, 0x100002, 0x110001, 0x130001, 0x140001, 0x150001, 0x160001, 0x170001, 0x180001, 0x010002},
        {
            "Title Screen (ma0000)", "Colony 9 (ma0101)", "Tephra Cave (ma0201)", "Bionis' Leg (ma0301)", "Colony 6 (ma0401)",
            "Ether Mine (ma0402)", "Satorl Marsh (ma0501)", "Makna Forest (ma0601)", "Frontier Village (ma0701)", "Bionis' Shoulder (ma0801)",
            "High Entia Tomb (ma0901)", "Eryth Sea (ma1001)", "Alcamoth (ma1101)", "Prison Island (ma1201)", "Fallen Prison Island (ma1202)",
            "Valak Mountain (ma1301)", "Sword Valley (ma1401)", "Galahad Fortress (ma1501)", "Fallen Arm (ma1601)", "Beta Fallen Arm (ma1602)",
            "Mechonis Field (ma1701)", "Agniratha (ma1901)", "Central Factory (ma2001)", "Bionis' Interior (ma2101)", "Memory Space (ma2201)",
            "Mechonis Core (ma2301)", "Junks (ma2401)", "Post-Game Colony 9 (ma0102)"
        }
    };

const Mapping MapReverseGapMapping
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

const Mapping ForegroundWeatherMapping
{
    {1, 2, 3, 4, 5, 6, 9, 10, 11, 12, 14},
    {"Clear", "Rain", "Storm", "Snow", "Blizzard", "Heatwave", "Dense Fog", "Sandstorm", "Shooting Stars", "Slumber", "Rebirth"}
};

// Colony 9, Ether Mine, High Entia Tomb, Galahad Fortress, Mechonis Field, Central Factory, Agniratha, Junks, Memory Space, Title Screen, Frontier Village
const Mapping NoBackgroundWeatherMapping
{
    {0},
    {"Clear"}
};

// Tephra Cave, Bionis' Leg, Colony 6, Fallen Arm, Beta Fallen Arm
const Mapping RainBackgroundWeatherMapping
{
    {0, 1, 2},
    {"Clear", "Rain", "Storm"}
};

// Satorl Marsh
const Mapping FogBackgroundWeatherMapping
{
    {0, 2},
    {"Clear", "Dense Fog"}
};

// Bionis Interior
const Mapping SlumberBackgroundWeatherMapping
{
    {0, 1},
    {"Clear", "Slumber"}
};

// Makna Forest
const Mapping HeatwaveBackgroundWeatherMapping
{
    {0, 1, 2},
    {"Clear", "Heatwave", "Rain"}
};

// Eryth Sea, Alcamoth, Prison Island
// TODO: is there difference between prison island maps?
const Mapping StarsBackgroundWeatherMapping
{
    {0, 1, 2},
    {"Clear", "Storm", "Shooting Stars"}
};

// Valak Mountain
const Mapping BlizzardBackgroundWeatherMapping
{
    {0, 1, 2},
    {"Clear", "Snow", "Blizzard"}
};

// Sword Valley
const Mapping SandstormBackgroundWeatherMapping
{
    {0, 1},
    {"Clear", "Sandstorm"}
};

// Mechonis Core
// TODO: there's no clear weather?
const Mapping RebirthBackgroundWeatherMapping
{
    {1},
    {"Rebirth"}
};

std::vector<const Mapping*> MapNumToBackgroundWeather =
{
    &NoBackgroundWeatherMapping, // Title Screen (ma0000)
    &NoBackgroundWeatherMapping, // Colony 9 (ma0101)
    &RainBackgroundWeatherMapping, // Tephra Cave (ma0201)
    &RainBackgroundWeatherMapping, // Bionis' Leg (ma0301)
    &RainBackgroundWeatherMapping, // Colony 6 (ma0401)
    &NoBackgroundWeatherMapping, // Ether Mine (ma0402)
    &FogBackgroundWeatherMapping, // Satorl Marsh (ma0501)
    &HeatwaveBackgroundWeatherMapping, // Makna Forest (ma0601)
    &NoBackgroundWeatherMapping, // Frontier Village (ma0701)
    &NoBackgroundWeatherMapping, // Bionis' Shoulder (ma0801) TODO: does bionis' shoulder have weather?
    &NoBackgroundWeatherMapping, // High Entia Tomb (ma0901)
    &StarsBackgroundWeatherMapping, // Eryth Sea (ma1001)
    &StarsBackgroundWeatherMapping, // Alcamoth (ma1101)
    &StarsBackgroundWeatherMapping, // Prison Island (ma1201)
    &NoBackgroundWeatherMapping, // Fallen Prison Island (ma1202)
    &BlizzardBackgroundWeatherMapping, // Valak Mountain (ma1301)
    &SandstormBackgroundWeatherMapping, // Sword Valley (ma1401)
    &NoBackgroundWeatherMapping, // Galahad Fortress (ma1501)
    &RainBackgroundWeatherMapping, // Fallen Arm (ma1601)
    &RainBackgroundWeatherMapping, // Beta Fallen Arm (ma1602)
    &NoBackgroundWeatherMapping, // Mechonis Field (ma1701)
    &NoBackgroundWeatherMapping, // Agniratha (ma1901)
    &NoBackgroundWeatherMapping, // Central Factory (ma2001)
    &SlumberBackgroundWeatherMapping, // Bionis' Interior (ma2101)
    &NoBackgroundWeatherMapping, // Memory Space (ma2201)
    &RebirthBackgroundWeatherMapping, // Mechonis Core (ma2301)
    &NoBackgroundWeatherMapping, // Junks (ma2401)
    &NoBackgroundWeatherMapping, // Post-Game Colony 9 (ma0102) TODO: does post-game colony 9 have weather?
    &RainBackgroundWeatherMapping // Default
};

// QLineEdit
inline void MainWindow::connect(SaveFieldID sfID, QExtendedLineEdit* lineEdit, Type type)
{
    Q_ASSERT(QObject::connect(lineEdit, &QLineEdit::editingFinished, this, &MainWindow::updateText));

    // TODO: could use just one?
    lineEdit->setProperty(SAVE_FIELD_PROPERTY, sfID);
    lineEdit->setSaveFieldID(sfID);

    saveFieldMap.insert({sfID, {lineEdit, type}});
}

// QCheckBox
inline void MainWindow::connect(SaveFieldID sfID, QExtendedCheckBox* checkBox, bool invert = false)
{
    Q_ASSERT(QObject::connect(checkBox, &QCheckBox::stateChanged, this, &MainWindow::updateCheckBox));

    // TODO: could use just one?
    checkBox->setProperty(SAVE_FIELD_PROPERTY, sfID);
    checkBox->setSaveFieldID(sfID);

    saveFieldMap.insert({sfID, {checkBox, Type::BOOL_T}});

    checkBox->setInverted(invert);
}

// QComboBox
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
    comboBox->setSaveFieldID(sfID);

    saveFieldMap.insert({sfID, {comboBox, Type::STRING_T}});
    comboBox->setMapping(mapping);
}

// QComboBox with dynamic mapping
void MainWindow::connect(SaveFieldID sfID, QExtendedComboBox* thisComboBox, QExtendedComboBox* sourceComboBox, std::vector<const Mapping*>& dynamicMapping)
{
    if (thisComboBox->lineEdit() != nullptr)
    {
        QObject::connect(thisComboBox->lineEdit(), &QLineEdit::editingFinished, this, &MainWindow::updateComboBox);
        thisComboBox->lineEdit()->setProperty(SAVE_FIELD_PROPERTY, sfID); // TODO: could use setSaveFieldID instead
    }
    else
    {
        QObject::connect(thisComboBox, &QComboBox::currentTextChanged, this, &MainWindow::updateComboBox);
        thisComboBox->setProperty(SAVE_FIELD_PROPERTY, sfID);
    }
    thisComboBox->setSaveFieldID(sfID);

    saveFieldMap.insert({sfID, {thisComboBox, Type::STRING_T}});
    thisComboBox->setMapping(dynamicMapping);

    QObject::connect(sourceComboBox->lineEdit(), &QLineEdit::editingFinished, this, &MainWindow::updateChildMapping);
    sourceComboBox->addChild(thisComboBox);
}

// QRadioButton
void MainWindow::connect(SaveFieldID sfID, QExtendedRadioButtons* radioButtonFrame, std::unordered_map<QString, QRadioButton*>& rbs)
{
    radioButtonFrame->setSaveFieldID(sfID);

    for (auto i = rbs.begin(); i != rbs.end(); ++i)
    {
        QObject::connect(i->second, &QRadioButton::clicked, this, &MainWindow::updateRadioButton);
        i->second->setProperty(SAVE_FIELD_PROPERTY, sfID);

        radioButtonFrame->addButton(i->second, i->first);
    }

    saveFieldMap.insert({sfID, {radioButtonFrame, Type::UINT_T}});
}

// QSlider
void MainWindow::connect(SaveFieldID sfID, QExtendedSlider* slider, int start, int spacing, int count)
{
    QObject::connect(slider, &QSlider::valueChanged, this, &MainWindow::updateSlider);

    slider->setProperty(SAVE_FIELD_PROPERTY, sfID);
    slider->setSaveFieldID(sfID);

    saveFieldMap.insert({sfID, {slider, Type::UINT_T}});

    slider->setScaling(start, spacing, count);
}

const int MINE_ARRAY_ROW_COUNT = 150;
const Mapping MINEArrayMapping =
{
    {MINE_MapID, MINE_MineID, MINE_NumHarvests, MINE_Cooldown},
    {"Map ID", "Mine ID", "Number of Harvests", "Cooldown"}
};
QList<ExtendedWidgetType> MINEArrayWidgetTypes = {QExtendedComboBox_T, QExtendedLineEdit_T, QExtendedLineEdit_T, QExtendedLineEdit_T};
QList<const Mapping*> MINEArrayColumnMapping = {&MapMapping, nullptr, nullptr, nullptr};

// QTableWidget
void MainWindow::connect(SaveFieldID sfID, QExtendedTableWidget* table, const int rowCount, const Mapping* mapping, QList<ExtendedWidgetType> columnTypes)
{
    table->setRowCount(rowCount);
    table->setColumnCount(std::size(mapping->keys));
    table->setRows(rowCount);
    table->setCols(std::size(mapping->keys));

    QHeaderView* header = table->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

    table->setHorizontalHeaderLabels(mapping->values);

    table->setProperty(SAVE_FIELD_PROPERTY, sfID);
    table->setSaveFieldID(sfID);

    saveFieldMap.insert({sfID, {table, Type::ARRAY_T}});

    table->setup(rowCount, MINEArrayWidgetTypes, MINEArrayColumnMapping, &MINEArrayMapping);

    QObject::connect(table, &QTableWidget::cellChanged, this, &MainWindow::updateTable);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::actionOpen);
    QObject::connect(ui->actionSave, &QAction::triggered, this, &MainWindow::actionSave);

    // THUM
    connect(THUMLevel, ui->THUMLevel, Type::UINT_T);
    connect(THUMNameString, ui->THUMNameString, Type::STRING_T);
    connect(THUMPlayTimeHours, ui->THUMPlayTimeHours, Type::UINT_T);
    connect(THUMPlayTimeMinutes, ui->THUMPlayTimeMinutes, Type::UINT_T);
    connect(THUMSaveTimeDay, ui->THUMSaveTimeDay, Type::UINT_T);
    connect(THUMSaveTimeMonth, ui->THUMSaveTimeMonth, Type::UINT_T);
    connect(THUMSaveTimeYear, ui->THUMSaveTimeYear, Type::UINT_T);
    connect(THUMSaveTimeHour, ui->THUMSaveTimeHour, Type::UINT_T);
    connect(THUMSaveTimeMinute, ui->THUMSaveTimeMinute, Type::UINT_T);
    connect(THUMNGPlusFlag, ui->THUMNGPlusFlag);
    connect(THUMSystemSaveFlag, ui->THUMSystemSaveFlag);
    connect(THUMPictureSlot1, ui->THUMPictureSlot1, &PlayerMapping);
    connect(THUMPictureSlot2, ui->THUMPictureSlot2, &PlayerMapping);
    connect(THUMPictureSlot3, ui->THUMPictureSlot3, &PlayerMapping);
    connect(THUMPictureSlot4, ui->THUMPictureSlot4, &PlayerMapping);
    connect(THUMPictureSlot5, ui->THUMPictureSlot5, &PlayerMapping);
    connect(THUMPictureSlot6, ui->THUMPictureSlot6, &PlayerMapping);
    connect(THUMPictureSlot7, ui->THUMPictureSlot7, &PlayerMapping);

    // FLAG
    connect(FLAGScenarioID, ui->FLAGScenarioID, Type::UINT_T);

    // GAME
    connect(GAMEMapNum, ui->GAMEMapNum, &MapReverseGapMapping);
    connect(GAMEMapNumString, ui->GAMEMapNumString, &MapStringMapping);
    connect(GAMEMapNum2, ui->GAMEMapNum2, &MapReverseGapMapping);
    connect(GAMEMapNumString2, ui->GAMEMapNumString2, &MapStringMapping);
    connect(GAMEPlayer1, ui->GAMEPlayer1, &PlayerMapping);
    connect(GAMEPlayer2, ui->GAMEPlayer2, &PlayerMapping);
    connect(GAMEPlayer3, ui->GAMEPlayer3, &PlayerMapping);
    connect(GAMEPlayer4, ui->GAMEPlayer4, &PlayerMapping);
    connect(GAMEPlayer5, ui->GAMEPlayer5, &PlayerMapping);
    connect(GAMEPlayer6, ui->GAMEPlayer6, &PlayerMapping);
    connect(GAMEPlayer7, ui->GAMEPlayer7, &PlayerMapping);
    connect(GAMEShulkLevel, ui->GAMEShulkLevel, Type::UINT_T);
    connect(GAMEReynLevel, ui->GAMEReynLevel, Type::UINT_T);
    connect(GAMEFioraLevel, ui->GAMEFioraLevel, Type::UINT_T);
    connect(GAMEDunbanLevel, ui->GAMEDunbanLevel, Type::UINT_T);
    connect(GAMESharlaLevel, ui->GAMESharlaLevel, Type::UINT_T);
    connect(GAMERikiLevel, ui->GAMERikiLevel, Type::UINT_T);
    connect(GAMEMeliaLevel, ui->GAMEMeliaLevel, Type::UINT_T);
    connect(GAMESevenLevel, ui->GAMESevenLevel, Type::UINT_T);
    connect(GAMEDicksonLevel, ui->GAMEDicksonLevel, Type::UINT_T);
    connect(GAMEMumkharLevel, ui->GAMEMumkharLevel, Type::UINT_T);
    connect(GAMEAlvisLevel, ui->GAMEAlvisLevel, Type::UINT_T);
    connect(GAMEPrologueDunbanLevel, ui->GAMEPrologueDunbanLevel, Type::UINT_T);

    // TIME
    connect(TIMEPlayTime, ui->TIMEPlayTime, Type::UINT_T);
    connect(TIMEDayTime, ui->TIMEDayTime, Type::FLOAT_T);
    connect(TIMEDayCount, ui->TIMEDayCount, Type::UINT_T);
    connect(TIMEYearCount, ui->TIMEYearCount, Type::UINT_T);

    // PCPM
    connect(PCPMPlayer1X, ui->PCPMPlayer1X, Type::FLOAT_T);
    connect(PCPMPlayer1Y, ui->PCPMPlayer1Y, Type::FLOAT_T);
    connect(PCPMPlayer1Z, ui->PCPMPlayer1Z, Type::FLOAT_T);
    connect(PCPMPlayer1Angle, ui->PCPMPlayer1Angle, Type::FLOAT_T);
    connect(PCPMPlayer2X, ui->PCPMPlayer2X, Type::FLOAT_T);
    connect(PCPMPlayer2Y, ui->PCPMPlayer2Y, Type::FLOAT_T);
    connect(PCPMPlayer2Z, ui->PCPMPlayer2Z, Type::FLOAT_T);
    connect(PCPMPlayer2Angle, ui->PCPMPlayer2Angle, Type::FLOAT_T);
    connect(PCPMPlayer3X, ui->PCPMPlayer3X, Type::FLOAT_T);
    connect(PCPMPlayer3Y, ui->PCPMPlayer3Y, Type::FLOAT_T);
    connect(PCPMPlayer3Z, ui->PCPMPlayer3Z, Type::FLOAT_T);
    connect(PCPMPlayer3Angle, ui->PCPMPlayer3Angle, Type::FLOAT_T);

    // CAMD
    connect(CAMDVerticalPosition, ui->CAMDVerticalPosition, Type::FLOAT_T);
    connect(CAMDHorizontalPosition, ui->CAMDHorizontalPosition, Type::FLOAT_T);
    connect(CAMDDistance, ui->CAMDDistance, Type::FLOAT_T);

    // ITEM

    // WTHR
    connect(WTHRReroll, ui->WTHRReroll, Type::FLOAT_T);
    connect(WTHRMap, ui->WTHRMap, &MapGapMapping);
    connect(WTHRForegroundWeather, ui->WTHRForegroundWeather, &ForegroundWeatherMapping);
    connect(WTHRBackgroundWeather, ui->WTHRBackgroundWeather, ui->WTHRMap, MapNumToBackgroundWeather);
    connect(WTHRUnk1, ui->WTHRUnk1, Type::UINT_T);
    connect(WTHRUnk2, ui->WTHRUnk2, Type::UINT_T);

    // MINE
    connect(MINEArray, ui->MINEArray, MINE_ARRAY_ROW_COUNT, &MINEArrayMapping, MINEArrayWidgetTypes);

    // TBOX

    // OPTD
    std::unordered_map<QString, QRadioButton*> OPTDJapaneseVoiceMap = {{"0", ui->OPTDJapaneseVoice0}, {"1", ui->OPTDJapaneseVoice1}};
    connect(OPTDJapaneseVoice, ui->OPTDJapaneseVoice, OPTDJapaneseVoiceMap);

    connect(OPTDGamma, ui->OPTDGamma, 8, 2, 5);
    connect(OPTDShowControls, ui->OPTDShowControls);
    connect(OPTDShowArtDescriptions, ui->OPTDShowArtDescriptions);
    connect(OPTDShowEnemyIcons, ui->OPTDShowEnemyIcons);
    connect(OPTDShowBuffDebuffInfoEveryTime, ui->OPTDShowBuffDebuffInfoEveryTime);
    connect(OPTDShowBuffDefbuffIndicator, ui->OPTDShowBuffDefbuffIndicator);
    connect(OPTDShowDestinationMarker, ui->OPTDShowDestinationMarker);

    connect(OPTDXAxisSpeed, ui->OPTDXAxisSpeed, 4, -1, 5);
    connect(OPTDNonInvertedXAxis, ui->OPTDNonInvertedXAxis, true);
    connect(OPTDYAxisSpeed, ui->OPTDYAxisSpeed, 4, -1, 5);
    connect(OPTDNonInvertedYAxis, ui->OPTDNonInvertedYAxis, true);
    connect(OPTDZoomSpeed, ui->OPTDZoomSpeed, 4, -1, 5);
    connect(OPTDPointOfView, ui->OPTDPointOfView, 2, -1, 3);
    connect(OPTDAngleCorrection, ui->OPTDAngleCorrection);
    connect(OPTDBattleCamera, ui->OPTDBattleCamera);

    connect(OPTDMinimapOn, ui->OPTDMinimapOn);
    connect(OPTDShowSubtitles, ui->OPTDShowSubtitles);

    std::unordered_map<QString, QRadioButton*> OPTDMinimapRotateMap = {{"0", ui->OPTDMinimapRotate0}, {"1", ui->OPTDMinimapRotate1}};
    connect(OPTDMinimapRotate, ui->OPTDMinimapRotate, OPTDMinimapRotateMap);

    std::unordered_map<QString, QRadioButton*> OPTDAutoEventScrollingMap = {{"0", ui->OPTDAutoEventScrolling0}, {"1", ui->OPTDAutoEventScrolling1}};
    connect(OPTDAutoEventScrolling, ui->OPTDAutoEventScrolling, OPTDAutoEventScrollingMap);

    std::unordered_map<QString, QRadioButton*> OPTDFastDialogueTextMap = {{"0", ui->OPTDFastDialogueText0}, {"1", ui->OPTDFastDialogueText1}};
    connect(OPTDFastDialogueText, ui->OPTDFastDialogueText, OPTDFastDialogueTextMap);

    for (int i = 0; i < LAST_INDEX; i++) setFieldEnabled((SaveFieldID)i, false);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::showStatusBarMessage(std::string str)
{
    ui->statusbar->showMessage(QString::fromStdString(str));
}

QString MainWindow::getField(SaveFieldID sfID, int row, int col)
{
    return this->saveFieldMap.at(sfID).first->getField(row, col);
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
            // TODO: move to QExtendedWidget
            if (widget->getMapping() != nullptr)
            {
                const Mapping* mapping = widget->getMapping();
                unsigned int value = saveFile->getValue<unsigned int>(sfID);
                const QString str = (*mapping).at(value);
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
            for (int row = 0; row < widget->getRows(); row++)
            {
                for (int col = 0; col < widget->getCols(); col++)
                {
                    setArrayField(sfID, row, col);
                }
            }
            break;
        }
    }
}

void MainWindow::setArrayField(SaveFieldID sfID, int row, int column)
{
    if (this->saveFieldMap.find(sfID) == this->saveFieldMap.end()) return;

    QExtendedWidget* widget = this->saveFieldMap.at(sfID).first;
    const Mapping* mapping = widget->getMapping();

    int saveColumn = mapping != nullptr ? mapping->keys[column] : column;

    widget->setField(QString::number(saveFile->getArrayValue<unsigned int>(sfID, row, saveColumn)), row, column);
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
        const Mapping* mapping = comboBox->getMapping();

        bool isInt, isUInt;
        int textToInt = comboBoxText.toInt(&isInt);
        unsigned int textToUInt = comboBoxText.toUInt(&isUInt);
        const int* mappingIntPtr = (*mapping).at(comboBoxText);

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

void MainWindow::updateRadioButton()
{
    QObject* obj = sender();
    SaveFieldID sfID = (SaveFieldID)obj->property(SAVE_FIELD_PROPERTY).toInt();
    QExtendedWidget* rb = saveFieldMap.at(sfID).first;

    saveFile->setValue(sfID, rb->getField().toUInt());
    this->setField(sfID);
}

void MainWindow::updateSlider()
{
    QObject* obj = sender();
    SaveFieldID sfID = (SaveFieldID)obj->property(SAVE_FIELD_PROPERTY).toInt();
    QExtendedWidget* slider = saveFieldMap.at(sfID).first;

    saveFile->setValue(sfID, slider->getField().toUInt());
    this->setField(sfID);
}

void MainWindow::updateTable(int row, int column)
{
    QObject* obj = sender();
    SaveFieldID sfID = (SaveFieldID)obj->property(SAVE_FIELD_PROPERTY).toInt();
    QExtendedWidget* table = saveFieldMap.at(sfID).first;

}

void MainWindow::updateChildMapping()
{
    QObject* obj = sender();
    SaveFieldID sfID = (SaveFieldID)obj->property(SAVE_FIELD_PROPERTY).toInt();

    QExtendedWidget* widget = saveFieldMap.at(sfID).first;
    std::vector<QExtendedWidget*> children = widget->getChildren();

    const Mapping* mapping = widget->getMapping();
    int index = mapping->indexAt(widget->getField());

    for (QExtendedWidget* child : children)
    {
        child->setMappingIndex(index);
        this->setField(child->getSaveFieldID());
    }
}
