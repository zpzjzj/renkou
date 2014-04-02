#ifndef ENUMCLASS_H
#define ENUMCLASS_H

namespace EnumClass {
const int FROM_YEAR = 1980;
const int TO_YEAR = 2050;
const QList<QString> ProvinceList={
  "北京市", "天津市", "河北省", "陕西省", "内蒙古", "辽宁省", "吉林省",
    "黑龙江"
};
const QHash<QString, QString> CodeMap={
    {"BJ", "10"},
    {"TJ", "12"},
    {"HE", "13"},
    {"SX", "14"},
    {"NM", "15"},
    {"LN", "21"},
    {"JL", "22"},
    {"HL", "23"}
};

const QHash<QString, QString> NameMap={
    {"BJ", "北京市"},
    {"TJ", "天津市"},
    {"HE", "河北省"},
    {"SX", "陕西省"},
    {"NM", "内蒙古"},
    {"LN", "辽宁省"},
    {"JL", "吉林省"},
    {"HL", "黑龙江"}
};
}

#endif // ENUMCLASS_H
