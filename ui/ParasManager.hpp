#ifndef PARASMANAGER_HPP
#define PARASMANAGER_HPP
#include "../Scheme/Para.hpp"

class ParasManager
{
public:
    ParasManager();
    const scheme::Para::ParaSet& getParaSet() const {return mParaSet;}
    void read();
private:
    scheme::Para::ParaSet mParaSet;
    static const QString PARA_PATH;
};

#endif // PARASMANAGER_HPP
