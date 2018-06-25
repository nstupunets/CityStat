#ifndef ADDNEWCITYDIALOG_H
#define ADDNEWCITYDIALOG_H

#include "cityitem.h"

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
    void itemAdded(CityItem item);
private slots:
    void onSaveCancelButtonBoxAccepted();
    void onSaveCancelButtonBoxRejected();
    void showErrorMessage(const QString &reason);

private:
    Ui::AddNewCityDialog *ui;
};

#endif // ADDNEWCITYDIALOG_H
