#pragma once

#include "QWidget"
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
};

class QExtendedWidget
{
public:
    virtual void setField(QString value) = 0;
    virtual QString getField() = 0;
    virtual void setFieldEnabled(bool enabled) = 0;
    virtual const Mapping* getMapping() = 0;
};

class QExtendedLineEdit : public QLineEdit, public QExtendedWidget
{
    Q_OBJECT
public:
    QExtendedLineEdit(QWidget* parent = nullptr) : QLineEdit(parent) { }
    void setField(QString value) { this->setText(value); }
    QString getField() { return this->text(); }
    void setFieldEnabled(bool enabled) { this->setEnabled(enabled); }
    const Mapping* getMapping() { return nullptr; }
};

class QExtendedCheckBox : public QCheckBox, public QExtendedWidget
{
    Q_OBJECT
public:
    QExtendedCheckBox(QWidget* parent = nullptr) : QCheckBox(parent) { }
    void setField(QString value) { this->setChecked(QString::compare(value, "0")); }
    QString getField() { return this->isChecked() ? "1" : "0"; }
    void setFieldEnabled(bool enabled) { this->setEnabled(enabled); }
    const Mapping* getMapping() { return nullptr; }
};

class QExtendedComboBox : public QComboBox, public QExtendedWidget
{
    Q_OBJECT
    const Mapping* mapping = nullptr;
public:
    QExtendedComboBox(QWidget* parent = nullptr) : QComboBox(parent) { }
    void setField(QString value) { this->setCurrentText(value); }
    QString getField() { return this->currentText(); }
    void setFieldEnabled(bool enabled) { this->setEnabled(enabled); }

    void setMapping(const Mapping* mapping)
    {
        this->mapping = mapping;
        this->clear();
        this->addItems((*mapping).values);
    }
    const Mapping* getMapping() { return mapping; }
};
