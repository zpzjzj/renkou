#ifndef INDICATORSELTABWIDGET_HPP
#define INDICATORSELTABWIDGET_HPP

#include <QTabWidget>
#include <QStandardItemModel>
#include <QItemSelection>

class IndicatorSelTabWidget : public QTabWidget
{
    Q_PROPERTY(QString indicator MEMBER mIndicator NOTIFY indicatorChanged)
    Q_PROPERTY(QString category MEMBER mCategory NOTIFY categoryChanged)
    Q_OBJECT
public:
    explicit IndicatorSelTabWidget(QWidget *parent = 0);

signals:
    void indicatorChanged(QString newIndicator);
    void categoryChanged(QString newCategory);
private:
    void selectionChanged(const QStandardItemModel *model, const QModelIndexList indexes);
private:
    //! container for resources of model for treeView
    std::vector<std::unique_ptr<QStandardItemModel> > mModels;
    QString mIndicator;
    QString mCategory;
};

#endif // INDICATORSELTABWIDGET_HPP
