#ifndef XMLMANAGER_HPP
#define XMLMANAGER_HPP

///
/// \brief xml_manager
/// load the data items from 'dataItem.xml'
///
class QString;
class QStringList;
class QList;
class DataItem;

class title{
private:
    QString* value;
    int subtitle_count;
    bool single;
    QStringList* subtitles;

public:
    bool isSingle() const{
        return single;
    }
    int getSubCount() const{
        return subtitle_count;
    }
    QString& getSubtitleAt(int index) const;

};

class XMLManager
{
public:
    XMLManager(QWidget *widget);
    int size() const;
    bool read(QIODevice *device);
    QString errorString() const;
private:
    void readXML();
    /*read title, and single attribute*/
    void readTitle(DataItem* item);
    void readSeparator();
    void readSubTitle(DataItem* item);
    QList<title*>* titleList;
};

#endif // XMLMANAGER_HPP
