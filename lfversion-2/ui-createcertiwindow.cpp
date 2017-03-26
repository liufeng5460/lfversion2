#include "ui-createcertiwindow.h"
#include <QGridLayout>
CreateCertiWindow::CreateCertiWindow(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle(tr("新建证书"));

    nameLabel=new QLabel(tr("姓名"));
    mailLabel=new QLabel(tr("邮箱"));
    validFromLabel=new QLabel(tr("生效期"));
    validUtilLabel=new QLabel(tr("失效期"));

    nameEdit=new QLineEdit;
    mailEdit=new QLineEdit;
    validFromEdit=new QLineEdit;
    validUtilEdit=new QLineEdit;

    submitBtn=new QPushButton(tr("提交"));

    QGridLayout *mainLayout =new QGridLayout(this);
    mainLayout->setMargin(5);
    mainLayout->setSpacing(5);

    mainLayout->addWidget(nameLabel,0,0);
    mainLayout->addWidget(nameEdit,0,1);
    mainLayout->addWidget(mailLabel,1,0);
    mainLayout->addWidget(mailEdit,1,1);
    mainLayout->addWidget(validFromLabel,2,0);
    mainLayout->addWidget(validFromEdit,2,1);
    mainLayout->addWidget(validUtilLabel,3,0);
    mainLayout->addWidget(validUtilEdit,3,1);
    mainLayout->addWidget(submitBtn,4,1);

}

