#ifndef PARA_HPP
#define PARA_HPP

#include <vector>
#include <memory>
#include <QString>
#include <QDebug>

/**
 * @author zhaoping
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
        Para(Para&& para);
        explicit Para(const QString& name,
                      const QString& key = "",
                      const QString& val = "",
                      const ParaSet& andParas = ParaSet(),
                      const ParaSet& orParas = ParaSet());
        ~Para();

        friend QDebug operator<<(QDebug dbg, const Para &para) {
            dbg << "{\n";
            dbg << "name: " << para.name << "\n";
            dbg << "key: " << para.val << "\n";
            dbg << "val: " << para.val << "\n";
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

        void setAndParas(const ParaSet& paras);
        const ParaSet& getAndParas() const;
        ParaSet& getAndParas();

        void setOrParas(const ParaSet& paras);
        const ParaSet& getOrParas() const;
        ParaSet& getOrParas();

        const QString& getName() const{return name;}
        const QString& getKey() const{return key;}
        const QString& getVal() const{return val;}

        void read(const QJsonObject &json);
        void write(QJsonObject &json) const;

        static ParaSet readParas(const QJsonArray &jsonArray);
        static QJsonArray writeParas(const ParaSet &paraSet);

    private:
        QString name;//!<field displayed on UI
        QString key;
        QString val;
        ParaSet andParas;//!<represents different aspects
        ParaSet orParas;//!<selections more than one elements means it's a multiple choice
    };
}
#endif // PARA_HPP
