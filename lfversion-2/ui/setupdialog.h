#ifndef SETUODIALOG_H
#define SETUODIALOG_H

#include <QWidget>
#include <QLineEdit>
#include <QRadioButton>
#include <QPushButton>
class SetupDialog: public QWidget
{
    Q_OBJECT
public:
    explicit SetupDialog(QWidget* parent = 0 );

public slots:
    void applySetup();

private:
    void initComponents();

    QLineEdit*  nameEdit;
    QLineEdit* portEdit;
    QPushButton* okButton;
    QPushButton* cancelButton;
};

#endif // SETUODIALOG_H
