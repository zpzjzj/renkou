#ifndef SCHEMEDISPLAYWIZARD_HPP
#define SCHEMEDISPLAYWIZARD_HPP

#include <QWizard>
#include "uiitem.h"
#include "SelDispCombo.hpp"
#include "UiGenerator.hpp"
#include "SchemeListManager.hpp"
#include <memory>

namespace Ui {
class schemeDisplayWizard;
}

class SchemeDisplayWizard : public QWizard, public UiItem
{
    Q_OBJECT

public:
    explicit SchemeDisplayWizard(QWidget *parent = 0);
    ~SchemeDisplayWizard();
    ParasManager* getParasManager() {
        return mParasManager.get();
    }
private slots:
    void accepted();
private:
    Ui::schemeDisplayWizard *ui;
    std::unique_ptr<ParasManager> mParasManager;
};

#endif // SCHEMEDISPLAYWIZARD_HPP
