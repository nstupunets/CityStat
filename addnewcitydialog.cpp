#include "addnewcitydialog.h"
#include "ui_addnewcitydialog.h"

#include <QIcon>

AddNewCityDialog::AddNewCityDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewCityDialog),
    m_messageBoxInfo{new QMessageBox(this)}
{
    ui->setupUi(this);
}

AddNewCityDialog::~AddNewCityDialog()
{
    delete ui;
}

void AddNewCityDialog::on_save_cancel_buttonBox_accepted()
{
    if (ui->inputContinentComboBox->currentText() == "Select continent"
        || ui->inputCountryLineEdit->text().isEmpty()
        || ui->inputCityLineEdit->text().isEmpty()
        || ui->inputPopulationLineEdit->text().isEmpty()
        || ui->inputHighTempLineEdit->text().isEmpty()
        || ui->inputLowTempLineEdit->text().isEmpty())
    {
        m_messageBoxInfo->setIcon(QMessageBox::Critical);
        m_messageBoxInfo->setText(QString("Cannot add new item"));
        m_messageBoxInfo->setInformativeText(QString("Empty fields were found, please fill all data"));
        m_messageBoxInfo->setDefaultButton(QMessageBox::Ok);
        m_messageBoxInfo->show();
        return;
    }

    bool wasConvertedPopulation(false), wasConvertedHighTemp(false), wasConvertedLowTemp(false);
    //if (ui->inputCountryLineEdit->text().toUInt(&wasConverted); !wasConverted)
    ui->inputPopulationLineEdit->text().toUInt(&wasConvertedPopulation);
    ui->inputHighTempLineEdit->text().toInt(&wasConvertedHighTemp);
    ui->inputLowTempLineEdit->text().toInt(&wasConvertedLowTemp);

    if (!wasConvertedPopulation || !wasConvertedHighTemp || !wasConvertedLowTemp)
    {
        m_messageBoxInfo->setIcon(QMessageBox::Critical);
        m_messageBoxInfo->setText(QString("Cannot add new item"));
        if (!wasConvertedPopulation)
            m_messageBoxInfo->setInformativeText("Invalid population info");
        else if (!wasConvertedHighTemp)
            m_messageBoxInfo->setInformativeText("Invalid \"Record high temperature\" value");
        else
            m_messageBoxInfo->setInformativeText("Invalid \"Record low temperature\" value");
        m_messageBoxInfo->setDefaultButton(QMessageBox::Ok);
        m_messageBoxInfo->show();
        return;
    }
    QStringList itemInfo { ui->inputContinentComboBox->currentText()
                          ,ui->inputCountryLineEdit->text()
                          ,ui->inputCityLineEdit->text()
                          ,ui->inputPopulationLineEdit->text()
                          ,ui->inputHighTempLineEdit->text()
                          ,ui->inputLowTempLineEdit->text()};
    emit addNewItem(itemInfo);

    clearInputData();
    this->close();
}

void AddNewCityDialog::on_save_cancel_buttonBox_rejected()
{
    clearInputData();
    this->close();
}

void AddNewCityDialog::clearInputData()
{
    ui->inputContinentComboBox->clearEditText();
    ui->inputCountryLineEdit->clear();
    ui->inputCityLineEdit->clear();
    ui->inputPopulationLineEdit->clear();
    ui->inputHighTempLineEdit->clear();
    ui->inputLowTempLineEdit->clear();
}
