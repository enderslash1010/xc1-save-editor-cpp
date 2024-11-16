#pragma once

#include "QWidget"
#include <qlineedit.h>

class QExtendedWidget
{
public:
    virtual void setField(QString value) = 0;
    virtual QString getField() = 0;
};

class QExtendedLineEdit : public QLineEdit, public QExtendedWidget
{
    Q_OBJECT
public:
    QExtendedLineEdit(QWidget* parent = nullptr) : QLineEdit(parent) { }
    void setField(QString value) { this->setText(value); }
    QString getField() { return this->text(); }
};
