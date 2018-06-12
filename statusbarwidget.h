#ifndef STATUSBAR_H
#define STATUSBAR_H

#include "iaggragateddataprovider.h"

#include <QWidget>
#include <QLabel>
#include <QStatusBar>
#include <QHBoxLayout>

class StatusBarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StatusBarWidget(QWidget *parent = 0);
    ~StatusBarWidget(){}
    void showAdditionalInfo(const QString &message);
    void changePopulationStatisticsMessage(const IAggragatedDataProvider &data);
private:
    QLabel *m_minPopulation;
    QLabel *m_maxPopulation;
    QLabel *m_totalPopulation;
    QLabel *m_additionalInfo;
    QStatusBar *m_statusBar;
    QHBoxLayout *m_horizontalLayout;
};

#endif // STATUSBAR_H
