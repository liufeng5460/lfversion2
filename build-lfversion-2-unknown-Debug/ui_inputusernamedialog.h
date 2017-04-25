/********************************************************************************
** Form generated from reading UI file 'inputusernamedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTUSERNAMEDIALOG_H
#define UI_INPUTUSERNAMEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_InputUserNameDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit;
    QLabel *label;

    void setupUi(QDialog *InputUserNameDialog)
    {
        if (InputUserNameDialog->objectName().isEmpty())
            InputUserNameDialog->setObjectName(QStringLiteral("InputUserNameDialog"));
        InputUserNameDialog->setWindowModality(Qt::ApplicationModal);
        InputUserNameDialog->resize(387, 183);
        buttonBox = new QDialogButtonBox(InputUserNameDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(-60, 130, 401, 32));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);
        lineEdit = new QLineEdit(InputUserNameDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(30, 70, 311, 41));
        lineEdit->setAutoFillBackground(false);
        label = new QLabel(InputUserNameDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 20, 191, 41));

        retranslateUi(InputUserNameDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), InputUserNameDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), InputUserNameDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(InputUserNameDialog);
    } // setupUi

    void retranslateUi(QDialog *InputUserNameDialog)
    {
        InputUserNameDialog->setWindowTitle(QApplication::translate("InputUserNameDialog", "Input username", 0));
        label->setText(QApplication::translate("InputUserNameDialog", "Please input your name:", 0));
    } // retranslateUi

};

namespace Ui {
    class InputUserNameDialog: public Ui_InputUserNameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTUSERNAMEDIALOG_H
