#include <QtGui>
#include <QtGlobal>
#include <QtOpenGL>
#include <QDebug>
#include <QMapIterator>
#include <QMutableMapIterator>
#include <QPainterPath>
#include <QProgressDialog>
#include <QQuaternion>
#include <GL/glu.h>
#include <qgl.h>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <queue>
#include <utility>
#include <algorithm>
#include <cstdlib>
#include "heightmap.h"
using namespace std;

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

#define Pi 3.141592654
#define MAX_N 5

int dist[1024*1024];
bool mark[1024*1024];
int tempmap[1024*1024];

static double CubicFunction(double x)
{
    if(x > 1 || x < 0){
        qDebug()<<"error";
    }
    return (2*x-3)*x*x + 1;
}

HeightMap::HeightMap(QWidget* parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    m_render = true;
    m_fullScreen = true;
    m_scaleValue = 1.0f;
    m_translateX = 1.0f;
    m_translateY = 1.0f;
    m_translateZ = 1.0f;

    m_rotateX = 0.0f;
    m_rotateY = 0.0f;
    m_rotateZ = 0.0f;

    setAutoFillBackground(false);
    setMinimumSize(200, 200);
    setWindowTitle(tr("Overpainting a Scene"));

    m_interval = 100;
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateYear()));

    connect(this, SIGNAL(animationOver()), this, SLOT(stopAnimation()));

//    m_colors.push_back(QColor("#047331"));
//    m_colors.push_back(QColor("#388c04"));
//    m_colors.push_back(QColor("#cace17"));
//    m_colors.push_back(QColor("#e16519"));
//    m_colors.push_back(QColor("#ca0300"));
    m_colors.push_back(QColor("#ffffcc"));
    m_colors.push_back(QColor("#a1dab4"));
    m_colors.push_back(QColor("#41b6c4"));
    m_colors.push_back(QColor("#2c7fb8"));
    m_colors.push_back(QColor("#253494"));

    m_font.initFont();
}

HeightMap::~HeightMap()
{
    delete m_timer;
}

bool HeightMap::init(int sy, int ey, const DataProvider &dp, int resolutionx, int resolutiony)
{
    m_sizeX = resolutionx;
    m_sizeY = resolutiony;
    m_stepX = 1;
    m_stepY = 1;
    m_heightRatio = m_sizeX / 2.0f / 256.0f;
    m_startYear = sy;
//    ey = sy+10;
    m_endYear = ey;
    m_currentYear = sy;

    m_frames.clear();

    QProgressDialog *progress = new QProgressDialog(this);
    progress->setWindowTitle("Creating Elevate Map");
    progress->setRange(sy, ey);
    progress->setMinimumDuration(0);
    progress->setAcceptDrops(false);
    progress->setAutoClose(true);
    progress->setAutoReset(true);
    progress->show();

    for(int i=sy; i<=ey; ++i){
        progress->setValue(i);
        m_frames.push_back(createFrame(dp, i));
    }

    delete progress;

    return true;
}

QSize HeightMap::sizeHint() const
{
    return QSize(600, 400);
}

void HeightMap::initializeGL()
{
    glShadeModel(GL_SMOOTH);
}

/*
// paintEvent function for debug
void HeightMap::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    for(int i=0; i<m_sizeX; i+=1){
        for(int j=0; j<m_sizeY; j+=1){
//            int c = 255 - dist[i+m_sizeX*j];
//            painter.fillRect(QRectF(i,j,1,1), QColor(c, c, c));
//            int c = 255;
//            if(!mark[i+j*m_sizeX]){
//                painter.fillRect(QRectF(i,j,1,1), QColor(c,c,c));
//            }
            int c = getHeight(i, j) / 2;
            if(mark[i+j*m_sizeX])
                painter.fillRect(QRectF(i, j, 1, 1), QColor(128-c, 128-c, 128-c));
            else
                painter.fillRect(QRectF(i, j, 1, 1), QColor(255, 255, 255));
        }
    }
//    painter.setPen(QColor(111,0,0));
//    painter.setBrush(Qt::blue);
//    for(int i=0; i<m_path.size(); ++i){
//        painter.drawPath(m_path[i]);
//    }

//    MapInformation* mi = MapInformation::getMapInformationSingleton();
//    QMapIterator<QString, vector<Region> > it(mi->m_provinces);
//    while(it.hasNext()){
//        it.next();
//        for(int i=0; i<it.value().size(); ++i){
//            Region r = it.value().at(i);
//            int x = (r.m_centerX+1.1)/2.2 * m_sizeX;
//            int y = (r.m_centerY+1.1)/2.2 * m_sizeY;
//            painter.fillRect(QRectF(x, (m_sizeY-y), 2, 2), QColor(111,222,3));
//        }
//    }
    painter.end();
}
*/

void HeightMap::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    makeCurrent();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
    glEnable(GL_MULTISAMPLE);

    resizeGL(width(), height());
    qglClearColor(Qt::white);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(m_sizeX/2, 0, m_sizeY*10, m_sizeX/2, 0, 0, 0, 1, 0);

    //设置全局的旋转平移缩放
//    qDebug()<<m_translateX<<m_translateY<<m_translateZ;
    glTranslated(this->m_translateX, this->m_translateY, this->m_translateZ);
    glScaled(m_scaleValue, m_scaleValue*m_heightRatio, m_scaleValue);
    glRotated(m_rotateX/16.0, 1.0, 0.0, 0.0);
    glRotated(m_rotateY/16.0, 0.0, 1.0, 0.0);
    glRotated(m_rotateZ/16.0, 0.0, 0.0, 1.0);
    glTranslated(-m_sizeX/2, 0, -m_sizeY/2);

    renderHeightMap();
    drawBoundary();
    drawProvinceName();

    glShadeModel(GL_FLAT);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
//    glDisable(GL_LIGHTING);

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    swapBuffers();
}


void HeightMap::resizeGL(int width, int height)
{
    if (height==0)									// Prevent A Divide By Zero By
        height=1;										// Making Height Equal One
                                        // Reset The Current Viewport

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
    glLoadIdentity();									// Reset The Projection Matrix

    // Calculate The Aspect Ratio Of The Window.  Farthest Distance Changed To 500.0f (NEW)
//    gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 5000.0f);
    GLdouble factor = (GLdouble)height / width;
    glOrtho(-m_sizeX, 0.5*m_sizeX,
            -0.5*m_sizeX*factor, 0.5*m_sizeX*factor,
            -1000*m_sizeX, 1000*m_sizeX);
//    glOrtho(-m_sizeX, m_sizeX, -m_sizeX*(GLfloat)height/(GLfloat)width, -m_sizeX*(GLfloat)height/(GLfloat)width, -2*m_sizeX, 2*m_sizeX);

    glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
    glLoadIdentity();
}

static void qNormalizeAngle(int &angle)
{
    while(angle < 0)
        angle += 360 * 16;
    while(angle > 360 * 16)
        angle -= 360 * 16;
}

void HeightMap::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if(angle != this->m_rotateX){
        m_rotateX = angle;
        emit xRotationChanged(m_rotateX);
        update();
    }
}

void HeightMap::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if(angle != this->m_rotateY){
        m_rotateY = angle;
        emit yRotationChanged(m_rotateY);
        update();
    }
}

void HeightMap::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if(angle != this->m_rotateZ){
        m_rotateZ = angle;
        emit zRotationChanged(m_rotateZ);
        update();
    }
}

void HeightMap::setXTranslation(double movement)
{
    if(m_translateX != movement){
        m_translateX = movement;
        update();
    }
}

void HeightMap::setYTranslation(double movement)
{
    if(m_translateY != movement){
        m_translateY = movement;
        update();
    }
}

void HeightMap::setZTranslation(double movement)
{
    if(m_translateZ != movement){
        m_translateZ = movement;
        update();
    }
}

void HeightMap::mousePressEvent(QMouseEvent *event)
{
    m_lastPosition = event->pos();
}

void HeightMap::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - m_lastPosition.x();
    int dy = event->y() - m_lastPosition.y();

    if(event->buttons() & Qt::LeftButton){
        setXTranslation(m_translateX + 100.0*dx/width());
        setYTranslation(m_translateY - 100.0*dy/height());
    }
//    else if(event->buttons() & Qt::RightButton){
//        setXRotation(m_rotateX + 8*dy);
//        setZRotation(m_rotateZ + 8*dx);
//    }

    this->m_lastPosition = event->pos();
}

void HeightMap::wheelEvent(QWheelEvent *event)
{
    m_scaleValue += 0.1*event->delta()/120;
    update();
}

void HeightMap::showEvent(QShowEvent *)
{

}

static char generalizeValue(double v)
{
    if(v >= 255)
        v = 255;

    if(v <= 0)
        v = 0;

    if(v > 127)
        v -= 256;

    return static_cast<char>(v);
}

void HeightMap::Bresenham(int sx, int sy, int ex, int ey)
{
    if(sx == ex){
        if(sy > ey){
            int t = sy;
            sy = ey;
            ey = t;
        }
        for(int i=sy; i<=ey; ++i){
            mark[sx+i*m_sizeX] = true;
        }
        return ;
    }
    if(sy == ey){
        int dx = ex > sx ? 1 : -1;
        for(int i=sx; i!=ex; i+=dx){
            mark[i+sy*m_sizeX] = true;
        }
        return ;
    }
    int x = sx;
    int y = sy;
    int dx = abs(ex - sx);
    int dy = abs(ey - sy);
    int xx = ex > sx ? 1 : -1;
    int yy = ey > sy ? 1 : -1;
    bool flag = false;
    if(dy > dx){
        int t = dy;
        dy = dx;
        dx = t;
        flag = true;
    }
    int nerror = 2 * dy - dx;
    for(int i=1; i<=dx; ++i){
        mark[x+y*m_sizeX] = true;
        if(nerror >= 0){
            if(flag){
                x += xx;
            }else{
                y += yy;
            }
            nerror -= 2 * dx;
        }
        if(flag){
            y += yy;
        }else{
            x += xx;
        }
        nerror += 2 * dy;
    }
}

QByteArray HeightMap::createFrame(const DataProvider &dp, int year)
{
    qDebug()<<"HeightMap::createFrame"<<year;

    QByteArray ba(m_sizeX*m_sizeY, '\0');

    MapInformation* mi = MapInformation::getMapInformationSingleton();
    QMapIterator<QString, vector<Region> > it(mi->m_provinces);

    memset(mark, 0, sizeof mark);
    memset(dist, 0, sizeof dist);
    memset(tempmap, 0, sizeof tempmap);

    double vmax = dp.m_maxValue;
    double vmin = dp.m_minValue;

    while(it.hasNext()){
        it.next();
        int x, y, nx, ny;

        // for every region drawing the bounds
        for(int i=0; i<1/*it.value().size()*/; ++i){
//            QPainterPath path;
            Region r = it.value().at(i);
            x = (r.m_bound[0].first+1.1) / 2.2 * m_sizeX;
            y = (r.m_bound[0].second+1.1) / 2.2 * m_sizeY;
            y = m_sizeY - y;
//            path.moveTo(x, y);
            for(int j=1; j<(int)r.m_bound.size(); ++j){
                nx = (r.m_bound[j].first+1.1) / 2.2 * m_sizeX;
                ny = (r.m_bound[j].second+1.1) / 2.2 * m_sizeY;
                ny = m_sizeY - ny;
                Bresenham(x, y, nx, ny);
                x = nx;
                y = ny;
//                path.lineTo(x, y);
            }

//            m_path.push_back(path);

            // calculate the distance of each points away from the center
            int dx[] = {1, -1, 0, 0};
            int dy[] = {0, 0, 1, -1};
            x = (r.m_centerX + 1.1) / 2.2 * m_sizeX;
            y = (r.m_centerY + 1.1) / 2.2 * m_sizeY;
            y = m_sizeY - y;
//            if(!path.contains(QPointF(x,y)))
//                qDebug()<<it.key()<<i;
            QPoint p(x,y);
            queue<pair<QPoint, int> > q;
            q.push(make_pair(p, 1));
            dist[p.x() + p.y()*m_sizeX] = 1;
            double dmax = 1.0;
            while(!q.empty()){
                pair<QPoint, int> current = q.front();
                q.pop();
                p = current.first;
                for(int j=0; j<4; ++j){
                    nx = p.x() + dx[j];
                    ny = p.y() + dy[j];
                    if(0<=nx&&nx<m_sizeX && 0<=ny&&ny<m_sizeY){
                        if(0 == dist[nx+ny*m_sizeX]){
                            dist[nx+ny*m_sizeX] = current.second+1;
                            dmax = max(dmax, current.second+1.0);
                            if(!mark[nx+ny*m_sizeX])
                                q.push(make_pair(QPoint(nx,ny), current.second+1));
                        }
                    }
                }
            }// while(!q.empty())

            // use f(x) = 2x^3 - 3x^2 + 1 to gradient the height
            x = (r.m_centerX + 1.1) / 2.2 * m_sizeX;
            y = (r.m_centerY + 1.1) / 2.2 * m_sizeY;
            y = m_sizeY - y;

            QMap<QString, vector<double> >::const_iterator dit = dp.m_data.find(it.key());
            if(dp.m_data.end() == dit){
                qDebug()<<"HeightMap::createFrame" << it.key();
                continue;
            }

            double peek = dit.value().at(year-m_startYear);

            // it means the province has no data
            if(peek < 1e-3)
                continue;

            peek = (peek-vmin)/(vmax-vmin)*255;
            while(!q.empty())
                q.pop();
            q.push(make_pair(QPoint(x,y), 0));
            tempmap[x + y*m_sizeX] = peek;
            while(!q.empty()){
                pair<QPoint, int> current = q.front();
                q.pop();
                p = current.first;
                for(int j=0; j<4; ++j){
                    nx = p.x() + dx[j];
                    ny = p.y() + dy[j];
                    if(0<=nx&&nx<m_sizeX && 0<=ny&&ny<m_sizeY){
                        int grid = nx + ny*m_sizeX;
                        if(!mark[grid]){
                            float v = CubicFunction((dist[grid]-1)/dmax) * peek;
                            tempmap[grid] = v;
                            mark[grid] = true;
                            q.push(make_pair(QPoint(nx, ny), 0));
                        }
                    }
                }
            }// while(!q.empty())

            // Average using the  neighbouring 8 grids
            for(int xi=1; xi<m_sizeX-1; ++xi){
                for(int yi=1; yi<m_sizeY-1; ++yi){
                    double s = 0;
                    for(int j=-1; j<=1; ++j){
                        for(int k=-1; k<=1; ++k){
                            x = xi + j;
                            y = yi + k;
                            s += tempmap[x+y*m_sizeX];
                        }
                    }
                    ba[xi+yi*m_sizeX] = generalizeValue(s / 9.0);
                }
            }

        }// for(int i=0; i<it.value().size(); ++i)

    }// while(it.hasNext())

    return ba;
}

// Using Bresenham Algorithm  to draw edge lines over height map
void HeightMap::drawEdgeLine(int sx, int sy, int ex, int ey)
{
    if(sx == ex){
        if(sy > ey){
            int t = sy;
            sy = ey;
            ey = t;
        }
        for(int i=sy; i<=ey; ++i){
            int h = getHeight(sx, i);
            glVertex3i(sx, h, i);
        }
        return ;
    }
    if(sy == ey){
        int dx = ex > sx ? 1 : -1;
        for(int i=sx; i!=ex; i+=dx){
            int h = getHeight(i, sy);
            glVertex3i(i, h, sy);
        }
        return ;
    }
    int x = sx;
    int y = sy;
    int dx = abs(ex - sx);
    int dy = abs(ey - sy);
    int xx = ex > sx ? 1 : -1;
    int yy = ey > sy ? 1 : -1;
    bool flag = false;
    if(dy > dx){
        int t = dy;
        dy = dx;
        dx = t;
        flag = true;
    }
    int nerror = 2 * dy - dx;
    for(int i=1; i<=dx; ++i){
        int h = getHeight(x, y);
        glVertex3i(x, h, y);
        if(nerror >= 0){
            if(flag){
                x += xx;
            }else{
                y += yy;
            }
            nerror -= 2 * dx;
        }
        if(flag){
            y += yy;
        }else{
            x += xx;
        }
        nerror += 2 * dy;
    }
}

void HeightMap::drawBoundary()
{
    MapInformation *mi = MapInformation::getMapInformationSingleton();
    QMapIterator<QString, vector<Region> > it(mi->m_provinces);

    qglColor(Qt::black);
    glLineWidth(2.0f);

    while(it.hasNext()){
        it.next();
        int x, y;
        int nx, ny;
        for(int i=0; i<(int)it.value().size(); ++i){
            Region r = it.value().at(i);
            glBegin(GL_LINE_LOOP);
            x = (r.m_bound[0].first+1.1) / 2.2 * m_sizeX;
            y = (r.m_bound[0].second+1.1) / 2.2 * m_sizeY;
            y = m_sizeY - y;
            for(int j=0; j<(int)r.m_bound.size(); ++j){
                nx = (r.m_bound[j].first+1.1) / 2.2 * m_sizeX;
                ny = (r.m_bound[j].second+1.1) / 2.2 * m_sizeY;
                ny = m_sizeY - ny;
                drawEdgeLine(x, y, nx, ny);
                x = nx;
                y = ny;
            }
            glEnd();
        }
    }// while(it.hasNext())
}

void HeightMap::drawProvinceName()
{
    MapInformation *mi = MapInformation::getMapInformationSingleton();
    QMapIterator<QString, vector<Region> > it(mi->m_provinces);

    while(it.hasNext()){
        it.next();
        Region r = it.value().at(0);
        int x = (r.m_centerX + 1.1) / 2.2 * m_sizeX;
        int z = (r.m_centerY + 1.1) / 2.2 * m_sizeY;
        z = m_sizeY - z;
        int y = getHeight(x, z);
        m_font.printText(this, it.key(), x, y, z);
    }
}

void HeightMap::setVertexColor(int x, int y)
{
    double fColor = (getHeight(x, y) / 256.0);
    QColor c1 = m_colors.first();
    QColor c2 = m_colors.last();
    double t;
    double div[] = {0.0, 0.25, 0.5, 0.75, 1.0};
    for(int i=0; i<4; ++i){
        if(div[i]<=fColor && fColor<=div[i+1]){
            c1 = m_colors[i];
            c2 = m_colors[i+1];
            t = (fColor-div[i])*4;
            break;
        }
    }
    // Use linear interpolation to get the color
    QQuaternion q1(1, c1.redF(), c1.greenF(), c1.blueF());
    QQuaternion q2(1, c2.redF(), c2.greenF(), c2.blueF());
    QQuaternion q = QQuaternion::slerp(q1, q2, t);
    glColor3f(q.x(), q.y(), q.z());
}

void HeightMap::renderHeightMap()
{
    int X = 0, Y = 0;

    int x, y, z;

    if(m_frames.at(m_currentYear-m_startYear).isEmpty())
        return;

    if(m_render)
        glBegin(GL_QUADS);
    else
        glBegin(GL_LINES);

    for(X=0; X<(m_sizeX-m_stepX); X += m_stepX){
        for(Y=0; Y<(m_sizeY-m_stepY); Y+=m_stepY){
            x = X;
            y = getHeight(X, Y);
            z = Y;
            setVertexColor(x, z);
            glVertex3i(x, y, z);

            x = X;
            y = getHeight(X, Y+m_stepY);
            z = Y + m_stepY;
            setVertexColor(x, z);
            glVertex3i(x, y, z);

            x = X + m_stepX;
            y = getHeight(X+m_stepX, Y+m_stepY);
            z = Y + m_stepY;
            setVertexColor(x, z);
            glVertex3i(x, y, z);

            x = X + m_stepX;
            y = getHeight(X+m_stepX, Y);
            z = Y;
            setVertexColor(x, z);
            glVertex3i(x, y, z);
        }
    }
    glEnd();

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

int HeightMap::getHeight(int x, int y)
{
    int index = m_currentYear - m_startYear;
    if(m_frames[index].isEmpty())
        return 0;

    int xx = x % m_sizeX;
    int yy = y % m_sizeY;

    char c = m_frames[index][xx + yy*m_sizeX];
    int ret = static_cast<int>(c);
    if(ret < 0)
        ret += 256;

    return ret;
}

void HeightMap::updateYear()
{
    if(m_currentYear < m_endYear){
        m_currentYear++;
        update();
    }
    else{
        emit animationOver();
        stopAnimation();
    }
}

void HeightMap::startAnimation()
{
    m_currentYear = m_startYear;
    m_timer->start(m_interval);
}

void HeightMap::stopAnimation()
{
    m_timer->stop();
}

void HeightMap::pauseAnimation()
{
    m_timer->stop();
}

void HeightMap::restartAnimation()
{
    m_timer->start(m_interval);
}

int HeightMap::getStartYear()
{
    return m_startYear;
}

int HeightMap::getEndYear()
{
    return m_endYear;
}

int HeightMap::getCurrentYear()
{
    return m_currentYear;
}

void HeightMap::setCurrentYear(int y)
{
    if(y < m_startYear){
        m_currentYear = m_startYear;
    }
    else if(y > m_endYear){
        m_currentYear = m_endYear;
        emit animationOver();
    }
    else{
        m_currentYear = y;
    }
    update();
}
