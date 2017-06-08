#include "ui/aboutdialog.h"
#include <QVBoxLayout>
AboutDialog::AboutDialog(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle(tr("关于"));

    // init components
    purpose = new QLabel(tr("本软件主要用于科学研究"));
    name = new QLabel(tr("作者:\t\t杜育松"));
    institution = new QLabel(tr("机构:\t\t中山大学"));
    address = new QLabel(tr("地址:\t\t广州市番禺区大学城"));
    contact  = new QLabel(tr("联系方式:\tliufeng5460@163.com"));
    okButton  = new QPushButton(tr("确定"));

    // layout
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setMargin(30);
    mainLayout->setSpacing(15);

    mainLayout->addStretch(1);
    mainLayout->addWidget(purpose,1,Qt::AlignLeft);
    mainLayout->addWidget(name,1,Qt::AlignLeft);
    mainLayout->addWidget(institution,1,Qt::AlignLeft);
    mainLayout->addWidget(address,1,Qt::AlignLeft);
    mainLayout->addWidget(contact,1,Qt::AlignLeft);
    mainLayout->addWidget(okButton,1,Qt::AlignRight);
    mainLayout->addStretch(1);

    this->setLayout(mainLayout);

    // signal and slot
    connect(okButton,SIGNAL(clicked(bool)),this,SLOT(close()));

}

