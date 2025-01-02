#pragma once

#include "QWidget"
#include "SaveFieldID.h"
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qlineedit.h>
#include <qradiobutton.h>

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

class QExtendedWidget
{
    std::vector<QExtendedWidget*> children;
    SaveFieldID sfID;
public:
    virtual void setField(QString value) = 0;
    virtual QString getField() = 0;
    virtual void setFieldEnabled(bool enabled) = 0;

    virtual const Mapping* getMapping() { return nullptr; }
    virtual void setMappingIndex(int i) { return; }

    virtual std::vector<QExtendedWidget*> getChildren() { return this->children; }
    virtual void addChild(QExtendedWidget* widget) { children.push_back(widget); }

    virtual SaveFieldID getSaveFieldID() { return this->sfID; }
    virtual void setSaveFieldID(SaveFieldID sfID) { this->sfID = sfID; }
};

class QExtendedLineEdit : public QLineEdit, public QExtendedWidget
{
    Q_OBJECT
public:
    QExtendedLineEdit(QWidget* parent = nullptr) : QLineEdit(parent) { }
    void setField(QString value) { this->setText(value); }
    QString getField() { return this->text(); }
    void setFieldEnabled(bool enabled) { this->setEnabled(enabled); }
};

class QExtendedCheckBox : public QCheckBox, public QExtendedWidget
{
    Q_OBJECT
    bool inverted = false;
public:
    QExtendedCheckBox(QWidget* parent = nullptr) : QCheckBox(parent) { }
    void setField(QString value)
    {
        inverted ? this->setChecked(!QString::compare(value, "0")) : this->setChecked(QString::compare(value, "0"));
    }
    QString getField()
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
    void setField(QString value) { this->setCurrentText(value); }
    QString getField() { return this->currentText(); }
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

    void setField(QString value)
    {
        auto it = valueToButtonMapping.find(value);
        if (it != valueToButtonMapping.end())
        {
            it->second->setChecked(true);
        }
        // All buttons unchecked if value isn't an option
        else for (auto i = valueToButtonMapping.begin(); i != valueToButtonMapping.end(); ++i) i->second->setChecked(false);
    }

    QString getField()
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

    void setField(QString value)
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

    QString getField()
    {
        return QString::number(sliderToRawValue.at(this->value()));
    }

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
