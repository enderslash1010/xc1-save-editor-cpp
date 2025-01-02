#pragma once

#include "QWidget"
#include "SaveFieldID.h"
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qlineedit.h>

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
public:
    QExtendedCheckBox(QWidget* parent = nullptr) : QCheckBox(parent) { }
    void setField(QString value) { this->setChecked(QString::compare(value, "0")); }
    QString getField() { return this->isChecked() ? "1" : "0"; }
    void setFieldEnabled(bool enabled) { this->setEnabled(enabled); }
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
