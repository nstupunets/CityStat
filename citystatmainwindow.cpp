#include "citystatmainwindow.h"

#include "addnewcitydialog.h"
#include "citystatitemdelegate.h"
#include "citystatmodel.h"
#include "ui_citystatmainwindow.h"

CityStatMainWindow::CityStatMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CityStatMainWindow),
    m_cityStatisticsModel{new CityStatModel()},
    m_comboDelegate{new CityStatItemDelegate()},
    m_addNewCityDialog{new AddNewCityDialog()}
{
    ui->setupUi(this);

    ui->cityTableView->setModel(m_cityStatisticsModel);
    ui->cityTableView->setItemDelegateForColumn(0,m_comboDelegate);

    //table view style
    ui->cityTableView->setStyleSheet("QHeaderView::section { background-color:#e1e1e1; border: 1px solid #6c6c6c; padding-left: 6px;padding-right: 6px;}");
    ui->cityTableView->resizeColumnsToContents();

    //connections
    connect(m_addNewCityDialog, SIGNAL(addNewItem(QStringList)), this, SLOT(onNewItemAdded(QStringList)));
    connect(this, SIGNAL(initiateDataSave()), m_cityStatisticsModel, SLOT(saveDataInitiated()));
    connect(m_cityStatisticsModel, SIGNAL(populationChanged(unsigned int,unsigned int,unsigned int)),this, SLOT(updateStatusBar(unsigned int,unsigned int,unsigned int)));
    connect(m_cityStatisticsModel, SIGNAL(isSaveDataSuccessfull(bool, unsigned int)), this, SLOT(showSaveDataResultMessage(bool, unsigned int)));

    m_cityStatisticsModel->fillPopulationInfo();
}

CityStatMainWindow::~CityStatMainWindow()
{
    delete m_cityStatisticsModel;
    delete m_comboDelegate;
    delete m_addNewCityDialog;
    delete ui;
}

void CityStatMainWindow::onNewItemAdded(QStringList itemInfo)
{
    m_cityStatisticsModel->insertRows(m_cityStatisticsModel->rowCount(),1);
    m_cityStatisticsModel->setData(m_cityStatisticsModel->index(m_cityStatisticsModel->rowCount()-1,0),QVariant(itemInfo.at(0)));
    m_cityStatisticsModel->setData(m_cityStatisticsModel->index(m_cityStatisticsModel->rowCount()-1,1),QVariant(itemInfo.at(1)));
    m_cityStatisticsModel->setData(m_cityStatisticsModel->index(m_cityStatisticsModel->rowCount()-1,2),QVariant(itemInfo.at(2)));
    m_cityStatisticsModel->setData(m_cityStatisticsModel->index(m_cityStatisticsModel->rowCount()-1,3),QVariant(itemInfo.at(3)));
    m_cityStatisticsModel->setData(m_cityStatisticsModel->index(m_cityStatisticsModel->rowCount()-1,4),QVariant(itemInfo.at(4)));
    m_cityStatisticsModel->setData(m_cityStatisticsModel->index(m_cityStatisticsModel->rowCount()-1,5),QVariant(itemInfo.at(5)));
}

void CityStatMainWindow::on_addNewItem_clicked()
{
    m_addNewCityDialog->show();
}


void CityStatMainWindow::on_saveDataPushButton_clicked()
{
    emit initiateDataSave();
}

void CityStatMainWindow::showSaveDataResultMessage(bool isSavingSuccessfull, unsigned int savedItemsCounter)
{
    QMessageBox msgBox(this);
    if (isSavingSuccessfull)
    {
        msgBox.setText("Data was saved successfully");
        msgBox.setInformativeText(QString::number(savedItemsCounter) + " item(s) were written to file");
    }
    else
    {
        msgBox.setText("Unable to save data");
    }
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
}

void CityStatMainWindow::updateStatusBar(unsigned int maxPopulation,unsigned int minPopulation,unsigned int totalPopulation)
{
    QString message = "Max: " + QString::number(maxPopulation) +
                      "\t\tMin: " + QString::number(minPopulation) +
                      "\t\tTotal: " + QString::number(totalPopulation);
    ui->statisticsStatusBar->showMessage(message);
}
