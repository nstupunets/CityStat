#include "citystatmainwindow.h"

#include "addnewcitydialog.h"
#include "ui_citystatmainwindow.h"

CityStatMainWindow::CityStatMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CityStatMainWindow),
    m_statusBarWidget(new StatusBarWidget(this))
{
    ui->setupUi(this);
    ui->statusBarLayout->addWidget(m_statusBarWidget);

    QString message;
    unsigned int skippedItemsCount = 0;
    auto successfull = m_cityStatisticsModel.readData(skippedItemsCount);
    if (!successfull)
        message = "Not able to load from file";
    else if (skippedItemsCount)
        message = QString::number(skippedItemsCount) + "item(s) skipped during loading from file";
    else
        message = "Data successfully loaded";
    m_statusBarWidget->showAdditionalInfo(message);
    m_statusBarWidget->changePopulationStatisticsMessage(m_cityStatisticsModel);

    ui->cityTableView->setModel(&m_cityStatisticsModel);
    ui->cityTableView->setItemDelegateForColumn(0,&m_comboDelegate);
    ui->cityTableView->resizeColumnsToContents();

    //connections
    connect(&m_cityStatisticsModel, &CityStatModel::populationStatisticsChanged, this, &CityStatMainWindow::onPopulationStatisticsChanged);
    connect(&m_cityStatisticsModel, &CityStatModel::dataSaved, this, &CityStatMainWindow::showSaveDataResultMessage);
    connect(ui->addNewItem, &QPushButton::clicked, this, &CityStatMainWindow::onAddNewItemClicked);
    connect(ui->saveDataPushButton, &QPushButton::clicked, this, &CityStatMainWindow::onSaveDataPushButtonClicked);
}

CityStatMainWindow::~CityStatMainWindow()
{
    delete ui;
}

void CityStatMainWindow::onNewItemAdded(CityItem item)
{
    m_cityStatisticsModel.insertCityItem(item);
    m_statusBarWidget->showAdditionalInfo("New item added");
}

void CityStatMainWindow::onSaveDataPushButtonClicked()
{
    m_cityStatisticsModel.saveData();
}

void CityStatMainWindow::showSaveDataResultMessage(bool success, unsigned int savedItemsCounter)
{
    QMessageBox msgBox(this);
    if (success)
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

void CityStatMainWindow::onAddNewItemClicked()
{
    auto *addNewCityDialog = new AddNewCityDialog(this);
    addNewCityDialog->setAttribute(Qt::WA_DeleteOnClose, true);

    connect(addNewCityDialog, &AddNewCityDialog::itemAdded, this, &CityStatMainWindow::onNewItemAdded);

    addNewCityDialog->show();
}

void CityStatMainWindow::onPopulationStatisticsChanged()
{
    m_statusBarWidget->changePopulationStatisticsMessage(m_cityStatisticsModel);
}
