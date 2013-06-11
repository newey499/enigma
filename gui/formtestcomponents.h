#ifndef FORMTESTCOMPONENTS_H
#define FORMTESTCOMPONENTS_H


#include <QWidget>
#include <QCheckBox>

#include "genlib.h"
#include "testharness.h"

#include "guimessagehandler.h"

namespace Ui {
class FormTestComponents;
}

class FormTestComponents : public QWidget
{
    Q_OBJECT

public:
    explicit FormTestComponents(QWidget *parent = 0);
    ~FormTestComponents();


public slots:

    virtual void buildTestCheckBoxes();
    virtual void slotRunTests();
    virtual void slotSelectAll();
    virtual void slotSelectNone();
    virtual void slotAppendString(QString msg);

protected:

    QPointer<TestHarness> testHarness;
    QList<QCheckBox *> lstChkBox;

private:
    Ui::FormTestComponents *ui;
};


#endif // FORMTESTCOMPONENTS_H
