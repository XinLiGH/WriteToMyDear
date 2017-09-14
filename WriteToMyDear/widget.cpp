#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    musicDir(new QDir),
    musicFileInfo(new QList<QFileInfo>),
    mediaPlayer(new QMediaPlayer),
    mediaPlaylist(new QMediaPlaylist),
    imageDir(new QDir),
    imageFileInfo(new QList<QFileInfo>),
    imageTimer(new QTimer)
{
    frameSize = QSize(18, 18);

    ui->setupUi(this);
    ui->image->setAlignment(Qt::AlignCenter);
    imageSize = QWidget::size() - frameSize;

    musicDir->setPath("music");
    musicDir->setNameFilters(QStringList("*.mp3"));
    *musicFileInfo = musicDir->entryInfoList();
    mediaPlaylist->setPlaybackMode(QMediaPlaylist::Random);
    mediaPlayer->setPlaylist(mediaPlaylist);

    for(int i = 0; i < musicFileInfo->count(); i++)
    {
        mediaPlaylist->addMedia(QUrl::fromLocalFile(musicFileInfo->at(i).filePath()));
    }

    musicRandomNumber = new RandomNumber(1, musicFileInfo->count());
    mediaPlaylist->setCurrentIndex(musicRandomNumber->getRandomNumber());
    mediaPlayer->play();

    imageDir->setPath("image");
    imageDir->setNameFilters(QStringList("*.jpg"));
    *imageFileInfo = imageDir->entryInfoList();

    imageRandomNumber = new RandomNumber(0, imageFileInfo->count() - 1);

    imageDisplay();

    imageTimer->start(5000);
    connect(imageTimer, SIGNAL(timeout()), this, SLOT(imageDisplay()));
}

Widget::~Widget()
{
    delete ui;
    delete musicDir;
    delete musicFileInfo;
    delete mediaPlayer;
    delete mediaPlaylist;
    delete musicRandomNumber;
    delete imageDir;
    delete imageFileInfo;
    delete imageRandomNumber;
    delete imageTimer;
}

void Widget::imageDisplay()
{
    QPixmap pixmap = QPixmap(imageFileInfo->at(imageRandomNumber->getRandomNumber()).filePath()).scaled(imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QWidget::setMaximumSize(pixmap.size() + frameSize);
    ui->image->setPixmap(pixmap);
}
