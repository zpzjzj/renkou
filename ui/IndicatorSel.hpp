#ifndef INDICATORSEL_HPP
#define INDICATORSEL_HPP

#include <QDialog>
#include "SchemeListManager.hpp"
#include <QStandardItemModel>
#include <vector>

namespace Ui {
class IndicatorSel;
}

class IndicatorSel : public QDialog
{
    Q_OBJECT
public:
    IndicatorSel(ParasManager* parasManager, QWidget *parent = 0);
    ~IndicatorSel();
private slots:
    void coordDisplay();
    void mapDisplay();
private:
    void createTreeView();//read file and create tree view and add to tab
    QStandardItem* getSelection();
private:
    Ui::IndicatorSel *ui;
    SchemeListManager *mSchemeListManagerPtr;
    //TODO: used to update list info, shall be changed
    //TODO: has abstract scheme

    //! container for resources of model for treeView
    std::vector<std::unique_ptr<QStandardItemModel> > mModels;
};

#endif // INDICATORSEL_HPP
