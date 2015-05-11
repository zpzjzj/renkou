#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QColor>
#include <QVector>
    const QColor BGCOLOR = QColor(224, 224, 224);
    const QColor BLACK = QColor(0, 0, 0);
    const QColor CHOSEN = QColor(0, 0, 0);
    const QColor WHITE = QColor(255, 255, 255);
    const QColor RED = QColor(255, 0, 0);
    const QColor DARKRED = QColor(128, 0, 0);
    const QColor GREEN = QColor(0, 255, 0);
    const QColor DARKGREEN = QColor(0, 128, 0);
    const QColor BLUE = QColor(0, 0, 255);
    const QColor DARKBLUE = QColor(0, 0, 128);
    const QColor CYAN = QColor(0, 255, 255);
    const QColor DARKCYAN = QColor(0, 128, 128);
    const QColor MAGENTA = QColor(255, 0, 255);
    const QColor DARKMAGENTA = QColor(128, 0, 128);
    const QColor YELLOW = QColor(255, 255, 0);
    const QColor DARKYELLOW = QColor(128, 128, 0);
    const QColor GRAY = QColor(128, 128, 128);
    const QColor DARKGRAY = QColor(64, 64, 64);
    const QColor DASHCOLOR = QColor(39, 40, 34);
    const QColor LINECOLOR1 = QColor(70, 137, 102);
    const QColor LINECOLOR2 = QColor(255, 240, 165);
    const QColor LINECOLOR3 = QColor(255, 176, 59);
    const QColor LINECOLOR4 = QColor(182, 73, 38);
    const QColor LINECOLOR5 = QColor(142, 40, 0);
    const QColor ColorForLine[] = {
        RED,
        GREEN,
        BLUE,
        CYAN,
        MAGENTA,
        YELLOW,
        LINECOLOR5,
        LINECOLOR4,
        LINECOLOR3,
        LINECOLOR2,
        LINECOLOR1,
    };
    static const double Pi = 3.14159265;
    enum face{top_face, bottom_face, side_face};
    enum map_view_type{bar, color};
#endif // CONSTANTS_H
