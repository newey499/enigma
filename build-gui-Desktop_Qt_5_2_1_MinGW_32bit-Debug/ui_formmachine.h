/********************************************************************************
** Form generated from reading UI file 'formmachine.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMMACHINE_H
#define UI_FORMMACHINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormMachine
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *lblMachineName;
    QLineEdit *edtMachineId;
    QLabel *lblMachineName_2;
    QLineEdit *edtMachineName;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *machineDefinitionLayout;
    QLabel *label_3;
    QHBoxLayout *rotorDefinitionLayout;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QPlainTextEdit *edtOutput;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_3;
    QPlainTextEdit *edtInput;

    void setupUi(QWidget *FormMachine)
    {
        if (FormMachine->objectName().isEmpty())
            FormMachine->setObjectName(QStringLiteral("FormMachine"));
        FormMachine->resize(566, 415);
        verticalLayout = new QVBoxLayout(FormMachine);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lblMachineName = new QLabel(FormMachine);
        lblMachineName->setObjectName(QStringLiteral("lblMachineName"));

        horizontalLayout->addWidget(lblMachineName);

        edtMachineId = new QLineEdit(FormMachine);
        edtMachineId->setObjectName(QStringLiteral("edtMachineId"));
        edtMachineId->setMaximumSize(QSize(50, 16777215));
        edtMachineId->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(edtMachineId);

        lblMachineName_2 = new QLabel(FormMachine);
        lblMachineName_2->setObjectName(QStringLiteral("lblMachineName_2"));

        horizontalLayout->addWidget(lblMachineName_2);

        edtMachineName = new QLineEdit(FormMachine);
        edtMachineName->setObjectName(QStringLiteral("edtMachineName"));

        horizontalLayout->addWidget(edtMachineName);

        horizontalSpacer = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        machineDefinitionLayout = new QHBoxLayout();
        machineDefinitionLayout->setObjectName(QStringLiteral("machineDefinitionLayout"));
        label_3 = new QLabel(FormMachine);
        label_3->setObjectName(QStringLiteral("label_3"));

        machineDefinitionLayout->addWidget(label_3);


        verticalLayout->addLayout(machineDefinitionLayout);

        rotorDefinitionLayout = new QHBoxLayout();
        rotorDefinitionLayout->setObjectName(QStringLiteral("rotorDefinitionLayout"));
        label_4 = new QLabel(FormMachine);
        label_4->setObjectName(QStringLiteral("label_4"));

        rotorDefinitionLayout->addWidget(label_4);


        verticalLayout->addLayout(rotorDefinitionLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(FormMachine);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        edtOutput = new QPlainTextEdit(FormMachine);
        edtOutput->setObjectName(QStringLiteral("edtOutput"));

        verticalLayout->addWidget(edtOutput);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(FormMachine);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_3);

        edtInput = new QPlainTextEdit(FormMachine);
        edtInput->setObjectName(QStringLiteral("edtInput"));

        verticalLayout->addWidget(edtInput);


        retranslateUi(FormMachine);

        QMetaObject::connectSlotsByName(FormMachine);
    } // setupUi

    void retranslateUi(QWidget *FormMachine)
    {
        FormMachine->setWindowTitle(QApplication::translate("FormMachine", "Form", 0));
        lblMachineName->setText(QApplication::translate("FormMachine", "Machine Id: ", 0));
        lblMachineName_2->setText(QApplication::translate("FormMachine", "Machine Name: ", 0));
        label_3->setText(QApplication::translate("FormMachine", "Machine : ", 0));
        label_4->setText(QApplication::translate("FormMachine", "Rotor Settings : ", 0));
        label->setText(QApplication::translate("FormMachine", "Output", 0));
        label_2->setText(QApplication::translate("FormMachine", "Input", 0));
    } // retranslateUi

};

namespace Ui {
    class FormMachine: public Ui_FormMachine {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMMACHINE_H
