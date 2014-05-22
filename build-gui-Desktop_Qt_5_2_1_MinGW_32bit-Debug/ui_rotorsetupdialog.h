/********************************************************************************
** Form generated from reading UI file 'rotorsetupdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROTORSETUPDIALOG_H
#define UI_ROTORSETUPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_RotorSetupDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *edtRotorName;
    QLabel *label_4;
    QLineEdit *edtRotorPosition;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QComboBox *cbxWindowChar;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QComboBox *cbxRingSetting;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *RotorSetupDialog)
    {
        if (RotorSetupDialog->objectName().isEmpty())
            RotorSetupDialog->setObjectName(QStringLiteral("RotorSetupDialog"));
        RotorSetupDialog->resize(382, 191);
        verticalLayout_3 = new QVBoxLayout(RotorSetupDialog);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(RotorSetupDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        edtRotorName = new QLineEdit(RotorSetupDialog);
        edtRotorName->setObjectName(QStringLiteral("edtRotorName"));

        horizontalLayout_2->addWidget(edtRotorName);

        label_4 = new QLabel(RotorSetupDialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_2->addWidget(label_4);

        edtRotorPosition = new QLineEdit(RotorSetupDialog);
        edtRotorPosition->setObjectName(QStringLiteral("edtRotorPosition"));

        horizontalLayout_2->addWidget(edtRotorPosition);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(RotorSetupDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(16777215, 50));

        verticalLayout->addWidget(label);

        cbxWindowChar = new QComboBox(RotorSetupDialog);
        cbxWindowChar->setObjectName(QStringLiteral("cbxWindowChar"));

        verticalLayout->addWidget(cbxWindowChar);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(RotorSetupDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(16777215, 50));

        verticalLayout_2->addWidget(label_2);

        cbxRingSetting = new QComboBox(RotorSetupDialog);
        cbxRingSetting->setObjectName(QStringLiteral("cbxRingSetting"));

        verticalLayout_2->addWidget(cbxRingSetting);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(RotorSetupDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_3->addWidget(buttonBox);


        retranslateUi(RotorSetupDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), RotorSetupDialog, SLOT(slotAccept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), RotorSetupDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(RotorSetupDialog);
    } // setupUi

    void retranslateUi(QDialog *RotorSetupDialog)
    {
        RotorSetupDialog->setWindowTitle(QApplication::translate("RotorSetupDialog", "Dialog", 0));
        label_3->setText(QApplication::translate("RotorSetupDialog", "Name", 0));
        label_4->setText(QApplication::translate("RotorSetupDialog", "Position", 0));
        label->setText(QApplication::translate("RotorSetupDialog", "Window Character", 0));
        label_2->setText(QApplication::translate("RotorSetupDialog", "Ring Setting", 0));
    } // retranslateUi

};

namespace Ui {
    class RotorSetupDialog: public Ui_RotorSetupDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROTORSETUPDIALOG_H
