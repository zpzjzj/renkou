#ifndef PARA_H
#define PARA_H

#include <vector>
#include <memory>
#include <QString>
#include <QDebug>

/**
 * @brief The Para class Tree structure for inner relations
 *
 */
namespace scheme {
    class Para {
    public:
        typedef std::shared_ptr<Para> ParaPtr;
        typedef std::vector<ParaPtr> ParaSet;
    public:
        Para(); //!<provide default value for members
        explicit Para(const QString& name, const QString& key = "", const QString& val = "", const ParaSet& andParas = ParaSet(), const ParaSet& orParas = ParaSet());

        friend QDebug operator<<(QDebug dbg, const Para &para){
            dbg << para.name << "{\n";
            dbg << "}\n";
            return dbg;
        }
        void setName(const QString& name){this->name = name;}
        void setKey(const QString& key){this->key = key;}
        void setVal(const QString& val){this->val = val;}

        void addAndPara(const ParaPtr& para); //!<for the construction of Para
        void addOrPara(const ParaPtr& para);
        void clearOrParas(){orParas.clear();} //!<clear all the paras
        void rmOrPara(const QString& name); //!<remove the option by name

        const QString& getName() const{return name;}
        const QString& getKey() const{return key;}
        const QString& getVal() const{return val;}
        const ParaSet& getAndParas() const{return andParas;}
        const ParaSet& getOrParas() const{return orParas;}
    private:
        QString name;
        QString key;
        QString val;
        ParaSet andParas;//!<represents different aspects
        ParaSet orParas;//!<selections more than one elements means it's a multiple choice
    };
}
#endif // PARA_H
