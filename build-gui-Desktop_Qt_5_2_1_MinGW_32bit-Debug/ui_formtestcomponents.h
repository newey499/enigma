/********************************************************************************
** Form generated from reading UI file 'formtestcomponents.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMTESTCOMPONENTS_H
#define UI_FORMTESTCOMPONENTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormTestComponents
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *testCheckboxLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QPushButton *btnSelectAll;
    QPushButton *btnSelectNone;
    QPushButton *btnRunTests;
    QPlainTextEdit *edtTxt;

    void setupUi(QWidget *FormTestComponents)
    {
        if (FormTestComponents->objectName().isEmpty())
            FormTestComponents->setObjectName(QStringLiteral("FormTestComponents"));
        FormTestComponents->resize(400, 300);
        horizontalLayout = new QHBoxLayout(FormTestComponents);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        testCheckboxLayout = new QVBoxLayout();
        testCheckboxLayout->setObjectName(QStringLiteral("testCheckboxLayout"));
        label = new QLabel(FormTestComponents);
        label->setObjectName(QStringLiteral("label"));

        testCheckboxLayout->addWidget(label);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        testCheckboxLayout->addItem(verticalSpacer);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_2 = new QLabel(FormTestComponents);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 0, 0, 1, 2);

        btnSelectAll = new QPushButton(FormTestComponents);
        btnSelectAll->setObjectName(QStringLiteral("btnSelectAll"));

        gridLayout->addWidget(btnSelectAll, 1, 0, 1, 1);

        btnSelectNone = new QPushButton(FormTestComponents);
        btnSelectNone->setObjectName(QStringLiteral("btnSelectNone"));

        gridLayout->addWidget(btnSelectNone, 1, 1, 1, 1);


        testCheckboxLayout->addLayout(gridLayout);

        btnRunTests = new QPushButton(FormTestComponents);
        btnRunTests->setObjectName(QStringLiteral("btnRunTests"));

        testCheckboxLayout->addWidget(btnRunTests);


        horizontalLayout->addLayout(testCheckboxLayout);

        edtTxt = new QPlainTextEdit(FormTestComponents);
        edtTxt->setObjectName(QStringLiteral("edtTxt"));

        horizontalLayout->addWidget(edtTxt);


        retranslateUi(FormTestComponents);
        QObject::connect(btnRunTests, SIGNAL(clicked()), FormTestComponents, SLOT(slotRunTests()));
        QObject::connect(btnSelectAll, SIGNAL(clicked()), FormTestComponents, SLOT(slotSelectAll()));
        QObject::connect(btnSelectNone, SIGNAL(clicked()), FormTestComponents, SLOT(slotSelectNone()));

        QMetaObject::connectSlotsByName(FormTestComponents);
    } // setupUi

    void retranslateUi(QWidget *FormTestComponents)
    {
        FormTestComponents->setWindowTitle(QApplication::translate("FormTestComponents", "Form", 0));
        label->setText(QApplication::translate("FormTestComponents", "Tests", 0));
        label_2->setText(QApplication::translate("FormTestComponents", "Select", 0));
        btnSelectAll->setText(QApplication::translate("FormTestComponents", "All", 0));
        btnSelectNone->setText(QApplication::translate("FormTestComponents", "None", 0));
        btnRunTests->setText(QApplication::translate("FormTestComponents", "Run Tests", 0));
    } // retranslateUi

};

namespace Ui {
    class FormTestComponents: public Ui_FormTestComponents {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMTESTCOMPONENTS_H
