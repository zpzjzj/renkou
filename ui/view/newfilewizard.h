#ifndef NEWFILEWIZARD_H
#define NEWFILEWIZARD_H

#include <QWizard>
#include "uiitem.h"

namespace Ui {
class NewFileWizard;
}

class NewFileWizard :
        public QWizard,
        public UiItem
{
    Q_OBJECT

public:
    explicit NewFileWizard(QWidget *parent = 0);
    explicit NewFileWizard(UiManager * const uiManager=0, QWidget *parent = 0);
    ~NewFileWizard();

//    int nextId() const;
private:
    Ui::NewFileWizard *ui;
public:
    enum { Page_Select,
           Page_NewObject,
           Page_NewProjection
         };
private:
    /**
     * @brief initiali
     */
    void init();
};

#endif // NEWFILEWIZARD_H
