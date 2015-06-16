#include "glfont.h"
#include <QtOpenGL>
#include <QDebug>
#include <QObject>
#include <QString>
#define WIN_IMPL

GLFont::GLFont()
{
}

GLFont::~GLFont()
{
#ifdef WIN_IMPL
    if(m_hFont)
        DeleteObject(m_hFont);
#endif
}

bool GLFont::initFont() {
#ifdef WIN_IMPL
    QString s = QObject::tr("宋体");
    wchar_t ws[8];
    s.toWCharArray(ws);
    m_hFont = CreateFont(-12,               // Height
                         0,                 // Width
                         0,                 // Angle Of Escapement
                         0,                 // Orientation Angle
                         FW_BOLD,           // Font Weigth
                         FALSE,             // Italic
                         FALSE,             // Underline
                         FALSE,             // Strikeout
                         GB2312_CHARSET,    // Character Set Identifier
                         OUT_TT_PRECIS,     // Output Precision
                        CLIP_DEFAULT_PRECIS,// Clipping Precision
                        ANTIALIASED_QUALITY,// Output Quality
                  FF_DONTCARE|DEFAULT_PITCH,// Family And Pitch
                         ws              // Font Name
                         );
    if(!m_hFont){
        qDebug()<<"GLFont::initFont failed.";
        return false;
    }
    return true;
#endif
}

#ifdef WIN_IMPL
void GLFont::printText(QGLWidget* , const QString& string, int x, int y, int z)
{
    qDebug()<<string;
    wchar_t ws[16];
    int len = string.length();
    string.toWCharArray(ws);

    HBITMAP hBitmap, hOldBmp;       // Define two bitmap handle
    BITMAP bm;                      // bitmap struct
    SIZE size;                      // bitmap size
    GLboolean lp, tp;
    HDC hDC = CreateCompatibleDC(0);  // Store Device Scene
    glGetBooleanv(GL_LIGHTING, &lp);    // Check lighting in the scene
    glGetBooleanv(GL_TEXTURE_2D, &tp);  // Check texture in the scene

//    glLoadIdentity();
//    glPushMatrix();
//    glTranslatef(0, 0, -10.0f);
//    glDisable(GL_LIGHTING);
//    glDisable(GL_TEXTURE_2D);
//    glDisable(GL_DEPTH_TEST);
    SelectObject(hDC, m_hFont);
    GetTextExtentPoint32(hDC, ws, len, &size);   // get size of font bitmap
    hBitmap = CreateBitmap(size.cx, size.cy, 1, 1, NULL);       // create bitmap with single color
    hOldBmp = (HBITMAP)SelectObject(hDC, hBitmap);

    SetBkColor(hDC, RGB(0, 0, 0));      // set backgroud color
    SetTextColor(hDC, RGB(255, 255, 255));    // set font color
    SetBkMode(hDC, TRANSPARENT);             // use current background color fill the background
    TextOut(hDC, 0, 0, ws, len); // save string to hDC

    // get bitmap struct
    GetObject(hBitmap, sizeof(bm), &bm);
    size.cx = (bm.bmWidth+31) & (~31);      // edge alignment
    size.cy = bm.bmHeight;
    int bufsize = size.cx * size.cy / 8;    // size of bitmap data

    //define single color bitmap
    struct{
        BITMAPINFOHEADER bih;
        RGBQUAD col[2];
    }bic;

    // get single color bitmap infos
    BITMAPINFO *binf = (BITMAPINFO*)&bic;
    binf->bmiHeader.biSize = sizeof(binf->bmiHeader);
    binf->bmiHeader.biWidth = bm.bmWidth;
    binf->bmiHeader.biHeight = bm.bmHeight;
    binf->bmiHeader.biPlanes = 1;
    binf->bmiHeader.biBitCount = 1;         // means single color
    binf->bmiHeader.biCompression = BI_RGB; // color
    binf->bmiHeader.biSizeImage = bufsize;
    binf->bmiHeader.biXPelsPerMeter = 1;
    binf->bmiHeader.biYPelsPerMeter = 1;
    binf->bmiHeader.biClrUsed = 0;
    binf->bmiHeader.biClrImportant = 0;

    // Define picture data block
    UCHAR* pBmpBits = new UCHAR[bufsize];
    memset(pBmpBits, 0, sizeof (UCHAR)*bufsize);

    // Store Device independent datas in the pBmpBits block
    GetDIBits(hDC, hBitmap, 0, bm.bmHeight, pBmpBits, binf, DIB_RGB_COLORS);

    // show the string
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glRasterPos3i(x, y, z);
    glBitmap(size.cx, size.cy, 0.0, 0.0, 0.0, 0.0, pBmpBits);

    delete pBmpBits;
    SelectObject(hDC, hOldBmp);     // restore
    DeleteObject(hBitmap);
    DeleteDC(hDC);
//    if(lp)
//        glEnable(GL_LIGHTING);
//    if(tp)
//        glEnable(GL_TEXTURE_2D);
//    glEnable(GL_DEPTH_TEST);
//    glPopMatrix();
}
#else
    void GLFont::printText(QGLWidget *widget, const QString& string, int x, int y, int z) {
        widget->renderText(x, y, z, string, mFont);
    }
#endif
