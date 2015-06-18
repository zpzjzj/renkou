#ifndef SCHEMESEL_HPP
#define SCHEMESEL_HPP
#include "../Scheme/Para.hpp"
#include "ParasManager.hpp"
#include "Scheme.hpp"
#include "paraUtil.hpp"
#include <QCheckBox>
#include <QDialog>
#include <QMap>
#include <QVector>

namespace Ui {
class SchemeSel;
}

/**
 * @brief The SchemeSel class
 *        for scheme para in para selection
 *        responsible for add para to list
 */
class SchemeSel : public QDialog
{
    Q_OBJECT
public:
    typedef QCheckBox* SchemeWidgetPtr;
    typedef QVector<SchemeWidgetPtr> SchemeSet;
public:
    explicit SchemeSel(QWidget *parent = 0);
    ~SchemeSel();
    /**
     * @brief build
     *          init, bind logic
     */
    void build();
    /**
     * @brief createSchemeWidget
     * @param para
     * @return created checkbox ptr for para
     */
    SchemeWidgetPtr createSchemeWidget(const scheme::Para &para) {
        return createSchemeWidget(para.getName(), util::isSelected(para));
    }
public slots:
    void addScheme();//!<check existance and emit signal
signals:
    void addScheme(const scheme::Para scheme, SchemeWidgetPtr checkBoxPtr);
private:
    const scheme::Para& getScheme() {return mCurrScheme;}
    void read();//!<read in scheme para data
    /**
     * @brief buildScheme
     *      put all widgets into container(mAgriScheme, mNonAgriScheme)
     */
    void buildScheme();
    void bind();  //!<bind mCurrScheme to qWidget
    SchemeWidgetPtr createSchemeWidget(const QString& text, bool isChecked = false);
private slots:
    void synchronizeScheme();
private:
    Ui::SchemeSel *ui;
    scheme::Para mCurrScheme;
    display::Scheme mAgriScheme;
    display::Scheme mNonAgriScheme;
    SchemeSet mSchemeList;
};

#endif // SCHEMESEL_HPP
