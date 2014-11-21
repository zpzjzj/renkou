#ifndef SCHEMESEL_HPP
#define SCHEMESEL_HPP
#include "../Scheme/Para.hpp"
#include "ParasManager.hpp"
#include "Scheme.hpp"
#include <QCheckBox>
#include <QDialog>
#include <QMap>
#include <QVector>

namespace Ui {
class SchemeSel;
}

class SchemeSel : public QDialog
{
    Q_OBJECT
public:
    typedef QCheckBox* SchemeWidgetPtr;
    typedef QVector<SchemeWidgetPtr> SchemeSet;
public:
    explicit SchemeSel(QWidget *parent = 0);
    ~SchemeSel();
    const scheme::Para& getScheme() {return mCurrScheme;}
    void build();
public slots:
    void addScheme();//!<check existance and emit signal
signals:
    void addScheme(const scheme::Para &scheme, SchemeWidgetPtr checkBoxPtr);
private:
    void read();
    /**
     * @brief buildScheme
     *      put all widgets into container(mAgriScheme, mNonAgriScheme)
     */
    void buildScheme();
    void bind();  //!<bind mCurrScheme to qWidget
private:
    Ui::SchemeSel *ui;
    scheme::Para mCurrScheme;
    display::Scheme mAgriScheme;
    display::Scheme mNonAgriScheme;
    SchemeSet mSchemeList;
};

#endif // SCHEMESEL_HPP
