#include "formtestcomponents.h"
#include "ui_formtestcomponents.h"

FormTestComponents::FormTestComponents(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormTestComponents)
{
    ui->setupUi(this);
    ui->edtTxt->setReadOnly(true);

    testHarness = new TestHarness(this);

    buildTestCheckBoxes();

}

FormTestComponents::~FormTestComponents()
{
    delete ui;
}


void FormTestComponents::buildTestCheckBoxes()
{
    int j;
    QCheckBox *cb;

    TestHash *testHash = testHarness->getPerform();
    QHash<TestHash::TESTS, TestHash::testStatus_t *> perform = testHash->getPerform();
    QHashIterator<TestHash::TESTS, TestHash::testStatus_t *> i(perform);
    j = 1;
    while (i.hasNext())
    {
        i.next();
        QString prompt = QString(i.value()->prompt->toStdString().data());
        cb = new QCheckBox(prompt, this);
        cb->setProperty ("TEST_KEY_VALUE", i.key());
        cb->setChecked(i.value()->enabled);
        ui->testCheckboxLayout->insertWidget(j++, cb);
        lstChkBox.append(cb); // Stash a pointer to the created checkbox
    }

}


void FormTestComponents::slotRunTests()
{
    this->ui->edtTxt->clear();

    for (int i = 0; i < lstChkBox.count(); i++)
    {
        testHarness->getPerform()->
                setEnabled((TestHash::TESTS) lstChkBox.at(i)->property("TEST_KEY_VALUE").toInt(),
                           lstChkBox.at(i)->isChecked());
    }

    GuiMessageHandler gmh(this);

    // Install handler that indirectly ends up with calling
    // FormTestComponents::slotAppendString(QString msg) which
    // is defined below
    //qInstallMessageHandler(GuiMessageHandler::guiMessageOutput);
    qInstallMessageHandler(GuiMessageHandler::guiMessageOutput);

    // MessageHandler::messageHandler is a public static function
    // qInstallMessageHandler(MessageHandler::messageHandler);

    testHarness->exec();
    qInstallMessageHandler(0); // Restore original handler
    ui->edtTxt->moveCursor(QTextCursor::Start); // Move cursor to top
    ui->edtTxt->ensureCursorVisible();
}


// This is called indirectly from the message handler via the
// EmitString class
void FormTestComponents::slotAppendString(QString msg)
{
    ui->edtTxt->appendPlainText(msg);
}


void FormTestComponents::slotSelectAll()
{
    for (int i = 0; i < lstChkBox.count(); i++)
    {
        lstChkBox.at(i)->setChecked(true);
    }
}


void FormTestComponents::slotSelectNone()
{
    for (int i = 0; i < lstChkBox.count(); i++)
    {
        lstChkBox.at(i)->setChecked(false);
    }
}
