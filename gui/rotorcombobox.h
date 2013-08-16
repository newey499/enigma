#ifndef ROTORCOMBOBOX_H
#define ROTORCOMBOBOX_H

#include <QComboBox>
#include <QContextMenuEvent>

class RotorComboBox : public QComboBox
{
    Q_OBJECT
public:


    explicit RotorComboBox(int rotorPosition, QWidget *parent = 0);

    int getRotorPosition();

signals:

    void rotorChanged(RotorComboBox *);

public slots:

    virtual void slotEmitRotorChanged();

protected:

    int rotorPosition;

    virtual void contextMenuEvent(QContextMenuEvent *e);

private:

};

#endif // ROTORCOMBOBOX_H
