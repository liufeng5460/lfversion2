
#include "ui-inputusernamedialog.h"
#include "status.h"

#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QApplication>

InputUsernameDialog::InputUsernameDialog(QWidget *parent):
    QWidget(parent)
{
    promptLabel  = new QLabel("请输入您的名字：");
    inputEdit = new QLineEdit;
    cancelButton = new QPushButton("取消");
    okButton = new QPushButton("确定");

    auto mainLayout = new QVBoxLayout;
    mainLayout->addWidget(promptLabel);
    mainLayout->addWidget(inputEdit);
    mainLayout->addWidget(okButton);
    mainLayout->addWidget(cancelButton);

    mainLayout->setMargin(20);
    setMinimumWidth(300);
    setWindowTitle("输入用户名");
    setLayout(mainLayout);

    connect(okButton,SIGNAL(clicked(bool)),this,SLOT(onOkButtonClicked()));
    connect(cancelButton,SIGNAL(clicked(bool)),this,SLOT(onCancelButtonClicked()));
    connect(inputEdit,SIGNAL(returnPressed()),okButton,SLOT(click()));
}

InputUsernameDialog::~InputUsernameDialog()
{
    delete promptLabel;
    delete inputEdit;
    delete cancelButton;
    delete okButton;
}

void InputUsernameDialog::onCancelButtonClicked()
{
    if(QMessageBox::question(this,"确认信息","不填写用户名将无法使用本软件，\n确定不填写用户名?"
                             )==QMessageBox::Yes)
    {
        QApplication::exit();
    }
}


void InputUsernameDialog::onOkButtonClicked()
{
    QFile profile(Status::profile);
    profile.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream out(&profile);
    QString username = inputEdit->text();
    out<<"username:"<<username;
    profile.close();
    this->close();
    Status::mainWindow->setWindowTitle(Status::appName+"--当前用户: "+username);
    Status::username = username;
}
