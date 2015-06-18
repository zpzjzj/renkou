#ifndef GLFONT_H
#define GLFONT_H

//#include<windows.h>
#include <QFont>
#include <QString>
#include <QGLWidget>

class GLFont
{
public:
    GLFont();
    ~GLFont();

    bool initFont();

    void printText(QGLWidget *, const QString &string, int x, int y, int z);

protected:
    HFONT m_hFont;
    QFont mFont;
};

#endif // GLFONT_H
