#include "addnewcitydialog.h"
#include "ui_addnewcitydialog.h"
#include "dataloader.h"

#include <QIcon>
#include <QIntValidator>
#include <QDoubleValidator>

AddNewCityDialog::AddNewCityDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewCityDialog)
{
    ui->setupUi(this);

    auto *intValidator = new QIntValidator(this);
    intValidator->setBottom(0);
    auto *doubleValidator = new QDoubleValidator(this);

    ui->inputPopulationLineEdit->setValidator(intValidator);
    ui->inputLowTempLineEdit->setValidator(doubleValidator);
    ui->inputHighTempLineEdit->setValidator(doubleValidator);

    for(auto &i : DataLoader::CONTINENTS)
    {
        ui->inputContinentComboBox->addItem(i);
    }

    connect(ui->saveCancelButtonBox, &QDialogButtonBox::rejected, this, &AddNewCityDialog::onSaveCancelButtonBoxRejected);
    connect(ui->saveCancelButtonBox, &QDialogButtonBox::accepted, this, &AddNewCityDialog::onSaveCancelButtonBoxAccepted);
}

AddNewCityDialog::~AddNewCityDialog()
{
    delete ui;
}

void AddNewCityDialog::onSaveCancelButtonBoxAccepted()
{
    auto continent = ui->inputContinentComboBox->currentText();
    auto country = ui->inputCountryLineEdit->text();
    auto city = ui->inputCityLineEdit->text();
    auto population = ui->inputPopulationLineEdit->text();
    auto highestT = ui->inputHighTempLineEdit->text();
    auto lowestT = ui->inputLowTempLineEdit->text();

    if ( country.isEmpty() || city.isEmpty()
         || population.isEmpty() || highestT.isEmpty() || lowestT.isEmpty())
    {
        showErrorMessage("Empty fields were found, please fill all data");
        return;
    }

    CityItem itemInfo (continent.toUtf8().constData(), country.toUtf8().constData(),
                       city.toUtf8().constData(), population.toUInt(), highestT.toDouble(),
                       lowestT.toDouble());
    emit itemAdded(itemInfo);
    this->close();
}

void AddNewCityDialog::onSaveCancelButtonBoxRejected()
{
    this->close();
}

void AddNewCityDialog::showErrorMessage(const QString &reason)
{
    QMessageBox *messageBoxInfo = new QMessageBox(this);
    messageBoxInfo->setAttribute(Qt::WA_DeleteOnClose, true);
    messageBoxInfo->setIcon(QMessageBox::Critical);
    messageBoxInfo->setText(QString("Cannot add new item"));
    messageBoxInfo->setInformativeText(reason);
    messageBoxInfo->setDefaultButton(QMessageBox::Ok);
    messageBoxInfo->show();
    return;
}
