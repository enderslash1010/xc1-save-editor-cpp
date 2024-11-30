#pragma once

#include "QWidget"
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qlineedit.h>

class QExtendedWidget
{
public:
    virtual void setField(QString value) = 0;
    virtual QString getField() = 0;
    virtual void setFieldEnabled(bool enabled) = 0;
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
public:
    QExtendedComboBox(QWidget* parent = nullptr) : QComboBox(parent) { }
    void setField(QString value) { this->setCurrentText(value); }
    QString getField() { return this->currentText(); }
    void setFieldEnabled(bool enabled) { this->setEnabled(enabled); }
};
