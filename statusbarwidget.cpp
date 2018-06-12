#include "statusbarwidget.h"
#include <QHBoxLayout>
#include <QFont>
#include <QSpacerItem>
#include <QTimer>

StatusBarWidget::StatusBarWidget(QWidget *parent) : QWidget(parent)
                                                  , m_minPopulation(new QLabel(this))
                                                  , m_maxPopulation(new QLabel(this))
                                                  , m_totalPopulation(new QLabel(this))
                                                  , m_additionalInfo(new QLabel(this))
                                                  , m_statusBar(new QStatusBar(this))
                                                  , m_horizontalLayout(new QHBoxLayout(this))
{
    m_horizontalLayout->addWidget(m_statusBar);
    setLayout(m_horizontalLayout);

    QFont font("Microsoft YaHei UI");
    font.setPointSize(10);

    m_minPopulation->setFont(font);
    m_maxPopulation->setFont(font);
    m_totalPopulation->setFont(font);
    m_additionalInfo->setFont(font);

    m_statusBar->setSizeGripEnabled(false);
    m_statusBar->addPermanentWidget(m_minPopulation,1);
    m_statusBar->addPermanentWidget(m_maxPopulation,1);
    m_statusBar->addPermanentWidget(m_totalPopulation,1);
    m_statusBar->addPermanentWidget(m_additionalInfo,2);
}

void StatusBarWidget::showAdditionalInfo(const QString &message)
{
    m_additionalInfo->setText(message);
//    m_additionalInfo->setVisible(true);
//    QTimer::singleShot(5000, m_additionalInfo, &QLabel::hide);
}

void StatusBarWidget::changePopulationStatisticsMessage(const IAggragatedDataProvider &data)
{
    m_minPopulation->setText(QString("Min: ") + QString::number(data.getMinPopulation()));
    m_maxPopulation->setText(QString("Max: ") + QString::number(data.getMaxPopulation()));
    m_totalPopulation->setText(QString("Total: ") + QString::number(data.getTotalPopulation()));
}
