#pragma once

#include "QWidget"
#include "SaveFieldID.h"
#include "Types.h"
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qlineedit.h>
#include <qradiobutton.h>
#include <qtablewidget.h>

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
        for(int i = 0; i < values.count(); i++) if(!QString::compare(values.at(i), x)) return &keys.at(i);
        return nullptr;
    }

    const int indexAt(int x) const noexcept
    {
        for(int i = 0; i < keys.count(); i++) if(keys.at(i) == x) return i;
        return -1;
    }

    const int indexAt(QString x) const noexcept
    {
        for(int i = 0; i < values.count(); i++) if(!QString::compare(values.at(i), x)) return i;
        return -1;
    }
};

enum ExtendedWidgetType
{
    QExtendedLineEdit_T,
    QExtendedCheckBox_T,
    QExtendedComboBox_T,
    QExtendedRadioButtons_T,
    QExtendedSlider_T
};

class QExtendedWidget
{
    std::vector<QExtendedWidget*> children;
    SaveFieldID sfID;
    int rows = 1, cols = 1;
    Type type = Type::UINT_T;
public:
    virtual void setField(QString value, int row = 0, int col = 0) = 0;
    virtual QString getField(int row = 0, int col = 0) = 0;
    virtual void setFieldEnabled(bool enabled) = 0;

    virtual const Mapping* getMapping() { return nullptr; }
    virtual void setMappingIndex(int i) { return; }

    virtual std::vector<QExtendedWidget*> getChildren() { return this->children; }
    virtual void addChild(QExtendedWidget* widget) { children.push_back(widget); }

    virtual SaveFieldID getSaveFieldID() { return this->sfID; }
    virtual void setSaveFieldID(SaveFieldID sfID) { this->sfID = sfID; }

    int getRows() { return this->rows; }
    int getCols() { return this->cols; }
    void setRows(int rows) { this->rows = rows; }
    void setCols(int cols) { this->cols = cols; }

    virtual Type getType() { return this->type; }
    void setType(Type type) { this->type = type; }

    virtual QExtendedWidget* at(int row = 0, int col = 0) { return this; }
};

class QExtendedLineEdit : public QLineEdit, public QExtendedWidget
{
    Q_OBJECT
public:
    QExtendedLineEdit(QWidget* parent = nullptr) : QLineEdit(parent) { }
    void setField(QString value, int row = 0, int col = 0) { this->setText(value); }
    QString getField(int row = 0, int col = 0) { return this->text(); }
    void setFieldEnabled(bool enabled) { this->setEnabled(enabled); }
};

class QExtendedCheckBox : public QCheckBox, public QExtendedWidget
{
    Q_OBJECT
    bool inverted = false;
public:
    QExtendedCheckBox(QWidget* parent = nullptr) : QCheckBox(parent) { }
    void setField(QString value, int row = 0, int col = 0)
    {
        inverted ? this->setChecked(!QString::compare(value, "0")) : this->setChecked(QString::compare(value, "0"));
    }
    QString getField(int row = 0, int col = 0)
    {
        return inverted ? (this->isChecked() ? "1" : "0") : (this->isChecked() ? "1" : "0");
    }
    void setFieldEnabled(bool enabled) { this->setEnabled(enabled); }
    void setInverted(bool inverted) { this->inverted = inverted; }
};

class QExtendedComboBox : public QComboBox, public QExtendedWidget
{
    Q_OBJECT
    unsigned int currMapping = 0;
    std::vector<const Mapping*> mappings;

    void loadItems()
    {
        this->clear();
        this->addItems(mappings.at(currMapping)->values);
    }
public:
    QExtendedComboBox(QWidget* parent = nullptr) : QComboBox(parent) { }

    void setField(QString value, int row = 0, int col = 0)
    {
        QString str = mappings.at(currMapping)->at(value.toUInt());
        if (str == "") this->setCurrentText(value);
        else this->setCurrentText(str);
    }

    QString getField(int row = 0, int col = 0)
    {
        const int* num = mappings.at(currMapping)->at(this->currentText());
        if (num == nullptr) return this->currentText();
        return QString::number(*num);
    }

    void setFieldEnabled(bool enabled) { this->setEnabled(enabled); }

    void setMapping(const Mapping* mapping)
    {
        this->mappings.clear();
        this->mappings.push_back(mapping);

        loadItems();
    }
    void setMapping(const std::vector<const Mapping*> mappings)
    {
        this->mappings = mappings;
        this->currMapping = 0;

        loadItems();
    }

    const Mapping* getMapping() { return (this->mappings.size() > currMapping) ? mappings.at(currMapping) : nullptr; }
    void setMappingIndex(int i)
    {
        if (mappings.size() < i) return;
        this->currMapping = (i > 0) ? i : mappings.size() - 1;

        loadItems();
    }
};

class QExtendedRadioButtons : public QFrame, public QExtendedWidget
{
    Q_OBJECT
    std::unordered_map<QString, QRadioButton*> valueToButtonMapping;
public:
    QExtendedRadioButtons(QWidget* parent = nullptr) : QFrame(parent) { }

    void addButton(QRadioButton* rb, QString val)
    {
        valueToButtonMapping.insert({val, rb});
    }

    void setField(QString value, int row = 0, int col = 0)
    {
        auto it = valueToButtonMapping.find(value);
        if (it != valueToButtonMapping.end())
        {
            it->second->setChecked(true);
        }
        // All buttons unchecked if value isn't an option
        else for (auto i = valueToButtonMapping.begin(); i != valueToButtonMapping.end(); ++i) i->second->setChecked(false);
    }

    QString getField(int row = 0, int col = 0)
    {
        for (auto i = valueToButtonMapping.begin(); i != valueToButtonMapping.end(); ++i) if (i->second->isChecked()) return i->first;
        return "";
    }

    void setFieldEnabled(bool enabled)
    {
        for (auto i = valueToButtonMapping.begin(); i != valueToButtonMapping.end(); ++i) i->second->setEnabled(enabled);
    }
};

class QExtendedSlider : public QSlider, public QExtendedWidget
{
    Q_OBJECT
    std::vector<int> sliderToRawValue;
public:
    QExtendedSlider(QWidget* parent = nullptr) : QSlider(parent) { }

    void setField(QString value, int row = 0, int col = 0)
    {
        int rawValue = value.toInt();
        for (int i = 0; i < sliderToRawValue.size(); i++)
        {
            if (sliderToRawValue.at(i) == rawValue)
            {
                this->setSliderPosition(i);
                break;
            }
        }
    }

    QString getField(int row = 0, int col = 0) { return QString::number(sliderToRawValue.at(this->value())); }
    void setFieldEnabled(bool enabled) { this->setEnabled(enabled); }

    void setScaling(int start, int spacing, int count)
    {
        sliderToRawValue.clear();
        while (count-- > 0)
        {
            sliderToRawValue.push_back(start);
            start += spacing;
        }
    }
};

struct TableDefinition
{
    int row_count;
    Mapping array_mapping;
    QList<ExtendedWidgetType> widget_types;
    QList<const Mapping*> column_mapping;
    QList<Type> column_types;
};

class QExtendedTableWidget : public QTableWidget, public QExtendedWidget
{
    Q_OBJECT
    std::vector<std::vector<QExtendedWidget*>> widgetArray;
    const Mapping* tableMapping;

private slots:
    void cellEdited()
    {
        QObject* obj = sender();
        emit tableCellChanged(obj->property("row").toInt(), obj->property("column").toInt());
    }
signals:
    void tableCellChanged(int row, int col);

public:
    QExtendedTableWidget(QWidget* parent = nullptr) : QTableWidget(parent) { }
    void setup(const TableDefinition* def)
    {
        this->tableMapping = &def->array_mapping;

        for (int row = 0; row < def->row_count; row++)
        {
            std::vector<QExtendedWidget*> newRow;
            for (int col = 0; col < def->widget_types.size(); col++)
            {
                switch (def->widget_types.at(col))
                {
                case QExtendedLineEdit_T:
                {
                    QExtendedLineEdit* le = new QExtendedLineEdit();
                    newRow.push_back(le);
                    this->setCellWidget(row, col, le);
                    QObject::connect(le, &QLineEdit::editingFinished, this, &QExtendedTableWidget::cellEdited);

                    le->setProperty("row", row);
                    le->setProperty("column", col);
                    le->setType(def->column_types.at(col));
                    break;
                }
                case QExtendedCheckBox_T:
                    break;
                case QExtendedComboBox_T:
                {
                    QExtendedComboBox* cb = new QExtendedComboBox();
                    cb->setEditable(true);
                    newRow.push_back(cb);
                    this->setCellWidget(row, col, cb);
                    if (def->column_mapping.at(col) != nullptr) cb->setMapping(def->column_mapping.at(col));
                    QObject::connect(cb, &QComboBox::currentTextChanged, this, &QExtendedTableWidget::cellEdited);

                    cb->setProperty("row", row);
                    cb->setProperty("column", col);
                    cb->setType(def->column_types.at(col));
                    break;
                }
                case QExtendedRadioButtons_T:
                    break;
                case QExtendedSlider_T:
                    break;
                }
            }
            widgetArray.push_back(newRow);
        }
    }

    void setField(QString value, int row = 0, int col = 0) { widgetArray.at(row).at(col)->setField(value); }
    QString getField(int row = 0, int col = 0) { return widgetArray.at(row).at(col)->getField(); }

    void setFieldEnabled(bool enabled) { this->setEnabled(enabled); }
    const Mapping* getMapping() { return this->tableMapping; }

    QExtendedWidget* at(int row = 0, int col = 0) { return widgetArray.at(row).at(col); }
};
