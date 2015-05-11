#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include <QGLWidget>
#include <QByteArray>
#include <QVector>
#include "Constants.h"
#include "mapinformation.h"
#include "dataprovider.h"
#include "glfont.h"

QT_BEGIN_NAMESPACE
class QPaintEvent;
class QWidget;
class QKeyEvent;
class QPainterPath;
QT_END_NAMESPACE

class HeightMap : public QGLWidget
{
    Q_OBJECT
public:
    explicit HeightMap(QWidget *parent = 0);
    bool init(int sy, int ey, const DataProvider& dp, int resolutionx=512, int resolutiony=512);
    ~HeightMap();

    int getStartYear();
    int getCurrentYear();
    int getEndYear();
    void setCurrentYear(int y);

    QSize sizeHint() const;

signals:
    void animationOver();
    void xRotationChanged(int);
    void yRotationChanged(int);
    void zRotationChanged(int);

public slots:
    void setXRotation(int angle);   //设置地图绕x轴旋转角度
    void setYRotation(int angle);   //设置地图绕y轴旋转角度
    void setZRotation(int angle);   //设置地图绕z轴旋转角度
    void setXTranslation(double movement);  //设置地图沿x轴平移距离
    void setYTranslation(double movement);  //设置地图沿y轴平移距离
    void setZTranslation(double movement);  //设置地图沿z轴平移距离
    void updateYear();  // add currentyear by one
    void stopAnimation();
    void startAnimation();
    void pauseAnimation();
    void restartAnimation();

protected:
    void initializeGL();
    void paintEvent(QPaintEvent *event);
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void showEvent(QShowEvent *event);

private:
    QByteArray createFrame(const DataProvider& dp, int year);
    void setVertexColor(int x, int y);
    void renderHeightMap();
    void drawBoundary();
    void drawProvinceName();
    void Bresenham(int sx, int sy, int ex, int ey);
    void drawEdgeLine(int sx, int sy, int ex, int ey);
    int getHeight(int x, int y);

    QVector<QByteArray> m_frames;

    int m_sizeX;
    int m_sizeY;
    int m_stepX;
    int m_stepY;
    float m_heightRatio;
    bool m_render;
    bool m_fullScreen;
    double m_scaleValue;
    double m_translateX;
    double m_translateY;
    double m_translateZ;
    double m_rotateX;
    double m_rotateY;
    double m_rotateZ;
    QPoint m_lastPosition;

    int m_startYear;
    int m_endYear;
    int m_currentYear;

    QTimer *m_timer;
    int m_interval;     //time for one frame 这两个应该互换
    int m_duration;     //time for one update
    int m_tick;

    QVector<QPainterPath> m_path;

    QVector<QColor> m_colors;

    GLFont m_font;
};

#endif // HEIGHTMAP_H
