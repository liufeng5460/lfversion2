#ifndef INPUTUSERNAMEDIALOG_H
#define INPUTUSERNAMEDIALOG_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class InputUsernameDialog : public QWidget
{
    Q_OBJECT
public:
    explicit InputUsernameDialog(QWidget* parent=0);
    ~InputUsernameDialog();

public slots:
    void onOkButtonClicked();
    void onCancelButtonClicked();

private:
    QLabel* promptLabel;
    QLineEdit* inputEdit;
    QPushButton* cancelButton;
    QPushButton* okButton;
};

#endif // INPUTUSERNAMEDIALOG_H
