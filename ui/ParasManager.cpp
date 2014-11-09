#include "ParasManager.hpp"
#include <numeric>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <utility>

const QString ParasManager::PARA_PATH = ":/display/config/para.json";

ParasManager::ParasManager() : mMultiSelPara(nullptr)
{
}

void ParasManager::read() {
    QFile file(PARA_PATH);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open para file");
        return;
    }
    QString val = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(val.toUtf8()));
    mParaSet = scheme::Para::readParas(doc.object()["paras"].toArray());
    for(auto& paraPtr : mParaSet) {
        buildMap(*paraPtr);
    }
}

/**
 * @brief ParasManager::buildMap
 *        recursive function, insert <child, parent> pair into map
 * @param para
 */
void ParasManager::buildMap(scheme::Para& para) {
    for(auto& paraPtr : para.getAndParas()) {
        buildMap(*paraPtr);
        mParentMap.insert(paraPtr.get(), &para);
        qDebug() << "key" << paraPtr.get() << " value " << &para;
    }

    for(auto& paraPtr : para.getOrParas()) {
        buildMap(*paraPtr);
        mParentMap.insert(paraPtr.get(), &para);
        qDebug() << "key" << paraPtr.get() << " value " << &para;
    }
}

namespace {
    bool setValue(scheme::Para::SelectedType val, scheme::Para& para) {
        auto old = para.getSelectedType();
        para.setSelectedType(val);
        return val != old;
    }

    /**
     *  @return isChanged
     */
    bool setValue(bool val, scheme::Para& para) {
        return setValue(val ? scheme::Para::SelectedType::SINGLE :
                            scheme::Para::SelectedType::INCOMPLETE,
                      para);
    }

    /**
     * @brief isSelComplete
     *          complete when all andParas are selected, and orParas has 1 or more selected
     * @param para
     *          higher level para
     * @return
     */
    scheme::Para::SelectedType getSelectionType(scheme::Para& para) {
        using SelectedType = scheme::Para::SelectedType;
        const auto& orParas = para.getOrParas();
        SelectedType orRes = std::accumulate(orParas.begin(), orParas.end(),
                                             SelectedType::INCOMPLETE,
                                             [](SelectedType x, const scheme::Para::ParaPtr yPtr) {
            auto y = yPtr->getSelectedType();
            if(y == SelectedType::INCOMPLETE)
                return x;
            else if(y == SelectedType::MULTIPLE)
                return SelectedType::MULTIPLE;
            else
                return x != SelectedType::INCOMPLETE ? SelectedType::MULTIPLE : SelectedType::SINGLE;
        });

        const auto& andParas = para.getAndParas();
        return std::accumulate(andParas.begin(), andParas.end(), orRes, // all orParas can be view as 1 andPara
                                               [](SelectedType x, const scheme::Para::ParaPtr yPtr) {
            auto y = yPtr->getSelectedType();
            if(x == SelectedType::INCOMPLETE || y == SelectedType::INCOMPLETE)
                return SelectedType::INCOMPLETE;
            else if(x == SelectedType::MULTIPLE || y == SelectedType::MULTIPLE)
                return SelectedType::MULTIPLE;
            else
                return SelectedType::SINGLE;
        });
    }
}

void ParasManager::setVal(bool val, scheme::Para* dest) {
    bool isSelectionTypeChanged = setValue(val, *dest);
    auto nextIter = mParentMap.find(dest);
    scheme::Para* curr;
    for( ;nextIter != mParentMap.end() && isSelectionTypeChanged;
            nextIter = mParentMap.find(curr)) {
        curr = nextIter.value();
        isSelectionTypeChanged = setValue(getSelectionType(*curr), *curr);
        qDebug() << "para key:" << curr->getKey();
        qDebug() << "selectionTypeChanged:" << isSelectionTypeChanged;
        qDebug() << "type now:" << curr->getSelectedType();
    }

    //the whole para's state is changed
    if(nextIter == mParentMap.end() && isSelectionTypeChanged) {
        qDebug() << "ParasManager::setVal()" << "whole select state changed";
        if(mMultiSelPara == curr){ //not multi anymore
            mMultiSelPara = nullptr;
            emit multiParaChanged(mMultiSelPara);
        }
        else if(mMultiSelPara == nullptr &&
                curr->getSelectedType() == scheme::Para::SelectedType::MULTIPLE) {
            //new multi para
            mMultiSelPara = curr;
            emit multiParaChanged(curr);
        } else {
            emit paraStateChanged(curr);
        }
    }
}
