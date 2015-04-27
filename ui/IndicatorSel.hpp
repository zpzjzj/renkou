#ifndef INDICATORSEL_HPP
#define INDICATORSEL_HPP

#include <QDialog>
#include "SchemeListManager.hpp"
#include "../Scheme/AbstractScheme.hpp"
#include <QStandardItemModel>
#include <vector>

namespace Ui {
class IndicatorSel;
}

class IndicatorSel : public QDialog
{
    Q_OBJECT
public:
    using AbstractSchemeList = ParasManager::AbstractSchemeList;
    using SchemeList = std::vector<SchemePtr>;
public:
    IndicatorSel(ParasManager* parasManager, QWidget *parent = 0);
    ~IndicatorSel();

    void setAbstractSchemes(const AbstractSchemeList& list) {
        mAbstractSchemes = list;
    }
private slots:
    void coordDisplay();
    void mapDisplay();
private:
    void createTreeView();//read file and create tree view and add to tab
    QStandardItem* getSelection();
    /**
     * @brief use current indicator and abstractSchemes to generate valid schemes
     * @return valid schemes
     */
    SchemeList getSchemes(schememetadata::Category category) const;
private:
    Ui::IndicatorSel *ui;
    SchemeListManager *mSchemeListManagerPtr;
    //TODO: used to update list info, shall be changed
    //TODO: has abstract scheme

    //! container for resources of model for treeView
    std::vector<std::unique_ptr<QStandardItemModel> > mModels;
    AbstractSchemeList mAbstractSchemes;
};

#endif // INDICATORSEL_HPP
