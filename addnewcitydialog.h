#ifndef ADDNEWCITYDIALOG_H
#define ADDNEWCITYDIALOG_H

#include <QDialog>
#include <QStringList>
#include <QMessageBox>

namespace Ui {
class AddNewCityDialog;
}

class AddNewCityDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewCityDialog(QWidget *parent = 0);
    ~AddNewCityDialog();
signals:
    void addNewItem(QStringList itemInfo);
private slots:
    void on_save_cancel_buttonBox_accepted();
    void on_save_cancel_buttonBox_rejected();

private:
    void clearInputData();
    Ui::AddNewCityDialog *ui;
    QMessageBox *m_messageBoxInfo;
};

#endif // ADDNEWCITYDIALOG_H
