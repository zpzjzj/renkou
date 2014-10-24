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
        enum SelectedType{NONE, SINGLE, MULTIPLE};
    public:
        Para(); //!<provide default value for members
        Para(Para&& para);
        explicit Para(const QString& name,
                      const QString& key = "",
                      const QString& val = "",
                      const ParaSet& andParas = ParaSet(),
                      const ParaSet& orParas = ParaSet(),
                      const SelectedType& selectedType = NONE);

        friend QDebug operator<<(QDebug dbg, const Para &para) {
            dbg << "{\n";
            dbg << "name: " << para.mName << "\n";
            dbg << "key: " << para.mVal << "\n";
            dbg << "val: " << para.mVal << "\n";
            dbg << "}\n";
            return dbg;
        }

        void setName(const QString& name){this->mName = name;}
        void setKey(const QString& key){this->mKey = key;}
        void setVal(const QString& val){this->mVal = val;}

        void addAndPara(const ParaPtr& para); //!<for the construction of Para
        void addOrPara(const ParaPtr& para);
        void clearOrParas(){mOrParas.clear();} //!<clear all the paras
        void rmOrPara(const QString& mName); //!<remove the option by name

        void setAndParas(const ParaSet& paras);
        const ParaSet& getAndParas() const;
        ParaSet& getAndParas();

        void setOrParas(const ParaSet& paras);
        const ParaSet& getOrParas() const;
        ParaSet& getOrParas();

        const QString& getName() const{return mName;}
        const QString& getKey() const{return mKey;}
        const QString& getVal() const{return mVal;}

        void read(const QJsonObject &json);
        void write(QJsonObject &json) const;

        static ParaSet readParas(const QJsonArray &jsonArray);
        static QJsonArray writeParas(const ParaSet &paraSet);

    private:
        QString mName;//!<field displayed on UI
        QString mKey;
        QString mVal;
        ParaSet mAndParas;//!<represents different aspects
        ParaSet mOrParas;//!<selections more than one elements means it's a multiple choice
        SelectedType mSelectedType;//!<select status for UI
    };
}
#endif // PARA_HPP
