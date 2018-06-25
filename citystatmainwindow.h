#ifndef CITYSTATMAINWINDOW_H
#define CITYSTATMAINWINDOW_H

#include "cityitem.h"
#include "citystatitemdelegate.h"
#include "citystatmodel.h"
#include "statusbarwidget.h"

#include <QMainWindow>
#include <QLabel>

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
signals:
    void initiateDataSave();
private slots:
    void onNewItemAdded(CityItem item);
    void onAddNewItemClicked();
    void onSaveDataPushButtonClicked();

    void onPopulationStatisticsChanged();
private:
    Ui::CityStatMainWindow *ui;
    StatusBarWidget *m_statusBarWidget;
    CityStatModel m_cityStatisticsModel;
    CityStatItemDelegate m_comboDelegate;
};

#endif // CITYSTATMAINWINDOW_H
