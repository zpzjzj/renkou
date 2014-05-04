#include "para.h"
#include <algorithm>

scheme::Para::Para():name(""), key(""), val(""),
    andParas(Para::ParaSet()), orParas(Para::ParaSet()){}

scheme::Para::Para(const QString& name, const QString& key, const QString& val, const Para::ParaSet& andParas, const Para::ParaSet& orParas)
    :name(name), key(key), val(val), andParas(andParas), orParas(orParas){}

namespace{
    void addPara(const scheme::Para::ParaPtr& para, scheme::Para::ParaSet& paraSet){
        paraSet.push_back(para);
    }
}

void scheme::Para::addAndPara(const scheme::Para::ParaPtr& para){
    addPara(para, andParas);
}

void scheme::Para::addOrPara(const scheme::Para::ParaPtr& para){
    addPara(para, orParas);
}

void scheme::Para::rmOrPara(const QString& name){
    std::remove_if(orParas.begin(), orParas.end(),
        [&name](const ParaPtr& paraPtr){
            return paraPtr->getName() == name;}
    );
}
