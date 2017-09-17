#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDir>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTimer>
#include "randomnumber.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void imageDisplay();
    void imageRefresh();

private:
    Ui::Widget *ui;
    QDir *musicDir;
    QList<QFileInfo> *musicFileInfo;
    QMediaPlayer *mediaPlayer;
    QMediaPlaylist *mediaPlaylist;
    RandomNumber *musicRandomNumber;
    QDir *imageDir;
    QList<QFileInfo> *imageFileInfo;
    RandomNumber *imageRandomNumber;
    QTimer *imageTimer;
    QTimer *imageRefreshTimer;
    QString imageFilePath;
    QSize imageSize;
};

#endif // WIDGET_H
