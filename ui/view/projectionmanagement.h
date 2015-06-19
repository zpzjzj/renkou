#ifndef PROJECTIONMANAGEMENT_H
#define PROJECTIONMANAGEMENT_H

#include <QDialog>

class QLabel;

namespace Ui {
class ProjectionManagement;
}

class ProjectionManagement : public QDialog
{
    Q_OBJECT

public:
    explicit ProjectionManagement(QWidget *parent = 0);
    ~ProjectionManagement();

private:
    QString getFileName(int year, const QString area);
    void reloadData();

public slots:
    void saveProjection();
    void areaChanged(QString _area);
    void yearChanged(QString _year);
    void finish();
    void accept();
private:
    Ui::ProjectionManagement *ui;

    QLabel *filePathLabel;
    QString area;
    int year;
    QString filePath;
};

#endif // PROJECTIONMANAGEMENT_H
