#ifndef XMLMANAGER_HPP
#define XMLMANAGER_HPP

///
/// \brief xml_manager
/// load the data items from any xml file
///
#include <QDomDocument>
class DataTreeWidget;
class DataTreeWidgetItem;

class XMLManager{
public:
    XMLManager(DataTreeWidget *widget, QString& filetype);

    bool read(QIODevice *device);
    bool write(QIODevice *device);

private:
    void parseTitleElement(const QDomElement &element,
                           DataTreeWidgetItem *parentItem = nullptr);

    void readExtension();
    DataTreeWidgetItem *createChildItem(const QDomElement &element, DataTreeWidgetItem *parentItem);

private:
    DataTreeWidget* treeWidget;

    QDomDocument domDocument;
    ///data or parameters
    /// data -- <ImportData>
    /// parameters -- <ImportParameters>
    /// etc...
    QString filetype;

    ///extension name, e.g: xml, xls
    QString extension;

};

#endif // XMLMANAGER_HPP
