#include "mywindow.h"

myWindow::myWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Operacje Morfologiczne");
    resize(720, 720);

    wide = 512;
    high = 640;
    startX = 30;
    startY = 30;
    basicColor[0] = 0;
    basicColor[1] = 0;
    basicColor[2] = 0;
    col[0] = 255;
    col[1] = 255;
    col[2] = 255;

    img = new QImage(wide, high, QImage::Format_RGB32);
    backgrd = new QImage(wide, high, QImage::Format_RGB32);

    group = new QGroupBox("Opcje",this);
    group->setGeometry(QRect(560,startY,150,startY+270));

    layout = new QVBoxLayout;

    loadImg = new QPushButton("Wczytaj obraz");
    dil = new QPushButton("Dylatacja");
    ero = new QPushButton("Erozja");
    open = new QPushButton("Otwarcie");
    close = new QPushButton("Domkniecie");

    layout->addWidget(loadImg);
    layout->addWidget(dil);
    layout->addWidget(ero);
    layout->addWidget(open);
    layout->addWidget(close);

    group->setLayout(layout);

    connect(loadImg,SIGNAL(clicked()),this,SLOT(load_img()));
    connect(dil,SIGNAL(clicked()),this,SLOT(dilatation()));
    connect(ero,SIGNAL(clicked()),this,SLOT(erosion()));
    connect(open,SIGNAL(clicked()),this,SLOT(open_op()));
    connect(close,SIGNAL(clicked()),this,SLOT(close_op()));
}

myWindow::~myWindow()
{
    delete img;
}

void myWindow::paintEvent(QPaintEvent*)
{
    QPainter picture(this);
    picture.drawImage(startX, startY, *img);

}

void myWindow::load_img(){
    QImage *picture = new QImage("kot.jpg");
    white_Black(picture);
    copyImg(img, picture);
    copyImg(backgrd, picture);
    update();
}

void myWindow::copyImg(QImage *a, QImage *b)
{
    unsigned char *img1, *img2;
    img1 = a->bits();
    img2 = b->bits();
    for(int i = 0; i < high; i++)
    {
        for(int j = 0; j < wide; j++)
        {
            img1[wide * 4 * i + 4 * j] = img2[wide * 4 * i + 4 * j];
            img1[wide * 4 * i + 4 * j + 1] = img2[wide * 4 * i + 4 * j + 1];
            img1[wide * 4 * i + 4 * j + 2] = img2[wide * 4 * i + 4 * j + 2];
        }
    }
}

void myWindow::white_Black(QImage *img){
    unsigned char *temp;
    temp = img->bits();
    for(int i = 0; i < high; i++)
    {
        for(int j = 0; j < wide; j++)
        {
            int color = floor((temp[wide * 4 * i + 4 * j] +
                    temp[wide * 4 * i + 4 * j + 1] + temp[wide * 4 * i + 4 * j + 2])/3);
            if(color < 128){
                temp[wide * 4 * i + 4 * j] = 0;
                temp[wide * 4 * i + 4 * j + 1] = 0;
                temp[wide * 4 * i + 4 * j + 2] = 0;
            } else {
                temp[wide * 4 * i + 4 * j] = 255;
                temp[wide * 4 * i + 4 * j + 1] = 255;
                temp[wide * 4 * i + 4 * j + 2] = 255;
            }
        }
    }
}

void myWindow::printPixel(int x, int y, int *color){
    unsigned char *ptr;
    ptr = img->bits();
    if ((x >= 0) && (y >= 0) && (x <= wide) && (y <= high)){
        ptr[wide * 4 * y + 4 * x] = color[0];
        ptr[wide * 4 * y + 4 * x + 1] = color[1];
        ptr[wide * 4 * y + 4 * x + 2] = color[2];
    }
}

void myWindow::dilatation(){
    unsigned char *back;
    back = backgrd->bits();
    for(int i = 0; i < high; i++)
    {
        for(int j = 0; j < wide; j++)
        {
            int neighbors[4];
            neighbors[0] = j - 1;
            neighbors[1] = j + 1;
            neighbors[2] = i - 1;
            neighbors[3] = i + 1;
            if(neighbors[0] < 0)
                neighbors[0] = j + 1;
            if(neighbors[1] >= wide)
                neighbors[1] = j - 1;
            if(neighbors[2] < 0)
                neighbors[2] = i + 1;
            if(neighbors[3] >= high)
                neighbors[3] = i - 1;
            if(back[wide * 4 * i + 4 * neighbors[0]] == 255 ||
                back[wide * 4 * i + 4 * neighbors[1]] == 255 || back[wide * 4 * neighbors[2] + 4 * j] == 255 ||
                    back[wide * 4 * neighbors[3] + 4 * j] == 255){
                printPixel(j, i, col);
            }
        }
    }
    copyImg(backgrd, img);
    update();
}

void myWindow::erosion(){
    unsigned char *back;
    back = backgrd->bits();
    for(int i = 0; i < high; i++)
    {
        for(int j = 0; j < wide; j++)
        {
            int neighbors[4];
            neighbors[0] = j - 1;
            neighbors[1] = j + 1;
            neighbors[2] = i - 1;
            neighbors[3] = i + 1;
            if(neighbors[0] < 0)
                neighbors[0] = j + 1;
            if(neighbors[1] >= wide)
                neighbors[1] = j - 1;
            if(neighbors[2] < 0)
                neighbors[2] = i + 1;
            if(neighbors[3] >= high)
                neighbors[3] = i - 1;
            if(back[wide * 4 * i + 4 * neighbors[0]] == 0 ||
                back[wide * 4 * i + 4 * neighbors[1]] == 0 || back[wide * 4 * neighbors[2] + 4 * j] == 0 ||
                    back[wide * 4 * neighbors[3] + 4 * j] == 0){
                printPixel(j, i, basicColor);
            }
        }
    }
    copyImg(backgrd, img);
    update();
}

void myWindow::open_op(){
    erosion();
    dilatation();
}

void myWindow::close_op(){
    dilatation();
    erosion();
}


