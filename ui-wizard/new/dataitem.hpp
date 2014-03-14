#ifndef DATAITEM_HPP
#define DATAITEM_HPP
///
/// dataItem
/// title, and subtitles
///
class QGroupBox;
class QAbstractButton;
class QWidget;
class QList;

class DataItem
{
public:
    DataItem();
    void setTitle(QString& title);
    void addSubTitle(QString& subtitle);
    void insertToWidget(QWidget* widget);
private:
    /*whether the multiple choice is permitted*/
    bool single;

    /*title of group*/
    QGroupBox* title;

    /*subtitles of items*/
    QList<QAbstractButton*>* subtitles;
    QAbstractButton* getButton(QString& subtitle);
};

#endif // DATAITEM_HPP
