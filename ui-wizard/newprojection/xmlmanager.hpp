#ifndef XMLMANAGER_HPP
#define XMLMANAGER_HPP

///
/// \brief xml_manager
/// load the data items from any xml file
///
#include <QXmlStreamReader>
class QString;
class QStringList;
class QList;
class DataTreeWidgetItem;
class DataTreeWidget;

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
    XMLManager(DataTreeWidget *widget, QString& filetype);
    int size() const;

    bool read(QIODevice *device);

    QString errorString() const;
private:


    void readXML();
    /*read title, and single attribute*/
    void readTitle(DataTreeWidgetItem* item);
    void readSeparator(DataTreeWidgetItem* item);
    void readSubTitles(DataTreeWidgetItem* item);

    void readExtension();
    DataTreeWidgetItem *createChildItem(DataTreeWidgetItem *item);
    DataTreeWidget* treeWidget;
    QXmlStreamReader xml;

    ///data or parameters
    /// data -- <ImportData>
    /// parameters -- <ImportParameters>
    /// etc...
    QString* filetype;

    ///extension name, e.g: xml, xls
    QString* extension;
    //QList<title*>* titleList;
};

#endif // XMLMANAGER_HPP
