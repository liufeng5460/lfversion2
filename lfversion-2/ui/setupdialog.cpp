#include "ui/setupdialog.h"
#include "status.h"
#include <QTabWidget>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
SetupDialog::SetupDialog(QWidget *parent):QWidget(parent)
{
    this->setWindowTitle(tr("系统设置"));
    initComponents();
    // layout
    QTabWidget* mainWidget = new QTabWidget;

    // tab1 for personal setup
    QWidget* tab1 = new QWidget;
    QGridLayout* tab1Layout = new QGridLayout;
    int i=0;
    tab1Layout->addWidget(new QLabel("用户名: "),i,0);
    tab1Layout->addWidget(nameEdit,i++,1);
    tab1->setLayout(tab1Layout);
    mainWidget->addTab(tab1, tr("个人信息"));

    // tab2 for file tranfer
    QWidget* tab2 = new QWidget;
    QGridLayout* tab2Layout = new QGridLayout;
    int j=0;
    tab2Layout->addWidget(new QLabel(tr("接收端口: ")), j,0);
    tab2Layout->addWidget(portEdit,j++,1);
    tab2Layout->addWidget(new QLabel(tr("发送前认证对方身份: ")),j,0);
    tab2Layout->addWidget(authRadio,j++,1);
    tab2->setLayout(tab2Layout);
    mainWidget->addTab(tab2,tr("文件传输"));

    // for buttons
    QWidget* buttonWidget = new QWidget;
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->setDirection(QBoxLayout::RightToLeft);
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(okButton);
    buttonLayout->addStretch(2);
    buttonWidget->setLayout(buttonLayout);

    // for all
    QVBoxLayout* dialogLayout = new QVBoxLayout;
    dialogLayout->setMargin(20);
    dialogLayout->setSpacing(15);
    dialogLayout->addWidget(mainWidget);
    dialogLayout->addWidget(buttonWidget);
    this->setLayout(dialogLayout);

    // signal & slot
    connect(cancelButton,SIGNAL(clicked(bool)), this,SLOT(close()));
    connect(okButton,SIGNAL(clicked(bool)),this,SLOT(applySetup()));


}

void SetupDialog::initComponents()
{
    nameEdit = new QLineEdit;

    portEdit = new QLineEdit;
    portEdit->setPlaceholderText(tr("当前端口")+QString::number(Status::port));
    authRadio = new QRadioButton;
    authRadio->setChecked(true);

    okButton = new QPushButton(tr("修改"));
    cancelButton = new QPushButton(tr("取消"));
}

void SetupDialog::applySetup()
{

    // for server port
    if(!portEdit->text().isEmpty())
    {
        bool isNumber;
        int port = portEdit->text().toInt(&isNumber);
        if(isNumber)
        {
            if(port != Status::port)
            {
                delete Status::server;
                Status::server = new NetAction(nullptr,port);
            }
        }
        else
        {
            QMessageBox::critical(this,"系统设置","修改失败\n端口号格式错误");
            return;
        }
    }

    // for username
    if(! nameEdit->text().isEmpty())
    {
        Status::username = nameEdit->text();
        Status::mainWindow->setWindowTitle(Status::appName+"--当前用户: "+Status::username);
    }

    // complete
    QMessageBox::information(this,"系统设置","修改成功");
    this->close();
    return;
}
