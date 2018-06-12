#ifndef CITYSTATMAINWINDOW_H
#define CITYSTATMAINWINDOW_H

#include <QMainWindow>

class AddNewCityDialog;
class CityStatItemDelegate;
class CityStatModel;

namespace Ui {
class CityStatMainWindow;
}

class CityStatMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CityStatMainWindow(QWidget *parent = 0);
    ~CityStatMainWindow();
public slots:
    void showSaveDataResultMessage(bool isSavingSuccessfull, unsigned int savedItemsCounter);
    void updateStatusBar(unsigned int maxPopulation,unsigned int minPopulation,unsigned int totalPopulation);
signals:
    void initiateDataSave();
private slots:
    void onNewItemAdded(QStringList);
    void on_addNewItem_clicked();

    void on_saveDataPushButton_clicked();

private:
    Ui::CityStatMainWindow *ui;
//    std::unique_ptr<CityStatModel> m_cityStatisticsModel;
//    std::unique_ptr<CityStatItemDelegate> m_comboDelegate;
//    std::unique_ptr<AddNewCityDialog> m_addNewCityDialog;

    CityStatModel *m_cityStatisticsModel;
    CityStatItemDelegate *m_comboDelegate;
    AddNewCityDialog *m_addNewCityDialog;
};

#endif // CITYSTATMAINWINDOW_H
