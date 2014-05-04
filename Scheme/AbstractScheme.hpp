#ifndef ABSTRACTSCHEME_HPP
#define ABSTRACTSCHEME_HPP
#include "SchemeParameter.hpp"
#include "schememetadata.h"
#include "Scheme.hpp"
#include "SchemeBuffer.hpp"

/**
 * @brief this class provide an interface between outer name & internal name
 *        this class accepts parameters as input and generate the desired Scheme class by providing the correct metadata
 *        and it's responsble for the mapping between the uniformed outer parameter & the internal name
 */

/**
 * @brief The AbstractScheme class
 *        结果集，内部可分夫妇子女、人口概要、生育孩次、政策 四类，即包含四个Scheme
 */
class AbstractScheme {
        typedef std::shared_ptr<SchemeParameter> SchemeParaPtr;
    public:
        AbstractScheme(SchemeParaPtr SchemeParaPtr, SchemeBufferPtr buffer_):para(SchemeParaPtr), buffer(buffer_){}
        AbstractScheme() = delete;
        ~AbstractScheme(){}
    public:
        bool set(const QString& key, const QString& value) {
            return para->set(key, value);
        }

        //get scheme's parameter
        const QString& value(const QString& key) const {return para->value(key);}

        //generate scheme according to its metadata (or indicator)
        SchemePtr generate(schememetadataPtr meta) const {
            return std::make_shared<Scheme>(Scheme(meta, buffer, para->generate(meta)));
        }
    private:
        SchemeParaPtr para;
        SchemeBufferPtr buffer;
};

#endif // ABSTRACTSCHEME_HPP
