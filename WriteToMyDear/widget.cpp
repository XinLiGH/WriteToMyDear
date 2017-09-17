#include "widget.h"
#include "ui_widget.h"

#define IMAGE_SIZE   (QWidget::size() - QSize(18, 18))

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    musicDir(new QDir),
    musicFileInfo(new QList<QFileInfo>),
    mediaPlayer(new QMediaPlayer),
    mediaPlaylist(new QMediaPlaylist),
    imageDir(new QDir),
    imageFileInfo(new QList<QFileInfo>),
    imageTimer(new QTimer),
    imageRefreshTimer(new QTimer)
{
    ui->setupUi(this);
    ui->image->setAlignment(Qt::AlignCenter);

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
    imageRefreshTimer->start(10);
    connect(imageTimer, SIGNAL(timeout()), this, SLOT(imageDisplay()));
    connect(imageRefreshTimer, SIGNAL(timeout()), this, SLOT(imageRefresh()));
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
    delete imageRefreshTimer;
}

void Widget::imageDisplay()
{
    if(imageSize != IMAGE_SIZE)
    {
        imageSize = IMAGE_SIZE;

        QRect imageRect = ui->image->geometry();
        imageRect.setSize(imageSize);
        ui->image->setGeometry(imageRect);
    }

    imageFilePath = imageFileInfo->at(imageRandomNumber->getRandomNumber()).filePath();
    QPixmap pixmap = QPixmap(imageFilePath).scaled(imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->image->setPixmap(pixmap);
}

void Widget::imageRefresh()
{
    if(imageSize != IMAGE_SIZE)
    {
        imageSize = IMAGE_SIZE;

        QRect imageRect = ui->image->geometry();
        imageRect.setSize(imageSize);
        ui->image->setGeometry(imageRect);
        QPixmap pixmap = QPixmap(imageFilePath).scaled(imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->image->setPixmap(pixmap);
    }
}
