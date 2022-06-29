#include "mywindow.h"

myWindow::myWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("ScanLine");
    resize(1000, 800);

    wide = 740;
    high = 740;
    startX = 30;
    startY = 30;
    basicColor[0] = 56;
    basicColor[1] = 252;
    basicColor[2] = 12;
    img = new QImage(wide, high, QImage::Format_RGB32);
    backgrd = new QImage(wide, high, QImage::Format_RGB32);

    group = new QGroupBox("RGB", this);
    group2 = new QGroupBox("HSV", this);

    group->setGeometry(QRect(800, 30, 170, 250));
    group2->setGeometry(QRect(800, 300, 170, 250));

    QGridLayout *boxLayout = new QGridLayout;
    QGridLayout *boxLayout2 = new QGridLayout;

    sliderR = new QSlider(Qt::Vertical, this);
    sliderR->setMinimum(0);
    sliderR->setMaximum(255);
    sliderG = new QSlider(Qt::Vertical, this);
    sliderG->setMinimum(0);
    sliderG->setMaximum(255);
    sliderB = new QSlider(Qt::Vertical, this);
    sliderB->setMinimum(0);
    sliderB->setMaximum(255);

    sliderH = new QSlider(Qt::Vertical, this);
    sliderH->setMinimum(0);
    sliderH->setMaximum(360);
    sliderS = new QSlider(Qt::Vertical, this);
    sliderS->setMinimum(0);
    sliderS->setMaximum(739);
    sliderV = new QSlider(Qt::Vertical, this);
    sliderV->setMinimum(0);
    sliderV->setMaximum(739);

    txtR = new QLabel("R");
    txtG = new QLabel("G");
    txtB = new QLabel("B");
    txtH = new QLabel("H");
    txtS = new QLabel("S");
    txtV = new QLabel("V");


    boxLayout->addWidget(sliderR, 0, 0);
    boxLayout->addWidget(sliderG, 0, 1);
    boxLayout->addWidget(sliderB, 0, 2);
    boxLayout->addWidget(txtR, 1, 0);
    boxLayout->addWidget(txtG, 1, 1);
    boxLayout->addWidget(txtB, 1, 2);

   boxLayout2->addWidget(sliderH, 0, 0);
    boxLayout2->addWidget(sliderS, 0, 1);
    boxLayout2->addWidget(sliderV, 0, 2);
    boxLayout2->addWidget(txtH, 1, 0);
    boxLayout2->addWidget(txtS, 1, 1);
    boxLayout2->addWidget(txtV, 1, 2);

    group->setLayout(boxLayout);
    group2->setLayout(boxLayout2);


    connect(sliderR,SIGNAL(valueChanged(int)),this,SLOT(constRed(int)));
    connect(sliderG,SIGNAL(valueChanged(int)),this,SLOT(constGreen(int)));
    connect(sliderB,SIGNAL(valueChanged(int)),this,SLOT(constBlue(int)));
    connect(sliderH,SIGNAL(valueChanged(int)),this,SLOT(constH(int)));
    connect(sliderS,SIGNAL(valueChanged(int)),this,SLOT(constS(int)));
    connect(sliderV,SIGNAL(valueChanged(int)),this,SLOT(constV(int)));
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



void myWindow::printPixel(int x, int y, int *color){
    unsigned char *ptr;
    ptr = img->bits();
    if ((x >= 0) && (y >= 0) && (x <= wide) && (y <= high)){
        ptr[wide * 4 * y + 4 * x] = color[0];
        ptr[wide * 4 * y + 4 * x + 1] = color[1];
        ptr[wide * 4 * y + 4 * x + 2] = color[2];
    }
}

void myWindow::constRed(int val){
    int colorTmp[3];
    colorTmp[2] = val;
    for(int y = 0; y < high; y++){
       colorTmp[1] = (int)(((double)y/(double)(high - 1))*255.0);
       for(int x = 0; x < wide; x++){
           colorTmp[0] = (int)(((double)x/(double)(wide - 1))*255.0);
           printPixel(x, y, colorTmp);
       }
    }
    update();
}

void myWindow::constGreen(int val){
    int colorTmp[3];
    colorTmp[1] = val;
    for(int y = 0; y < high; y++){
       colorTmp[2] = (int)(((double)y/(double)(high - 1))*255.0);
       for(int x = 0; x < wide; x++){
           colorTmp[0] = (int)(((double)x/(double)(wide - 1))*255.0);
           printPixel(x, y, colorTmp);
       }
    }
    update();
}

void myWindow::constBlue(int val){
    int colorTmp[3];
    colorTmp[0] = val;
    for(int y = 0; y < high; y++){
       colorTmp[1] = (int)(((double)y/(double)(high - 1))*255.0);
       for(int x = 0; x < wide; x++){
           colorTmp[2] = (int)(((double)x/(double)(wide - 1))*255.0);
           printPixel(x, y, colorTmp);
       }
    }
    update();
}

void myWindow::constH (int val){
    double h = (double) val;
    double s, v, cf[3];
    int cd[3];
    for(int y = 0; y < high; y++){
        s = (double) y / (double)(high - 1);
        for (int x = 0; x < wide; x++) {
            v = (double) x / (double)(high - 1);
            convertHSVtoRGB(h, s, v, cf);
            cd[0] = (int) cf[0];
            cd[1] = (int) cf[1];
            cd[2] = (int) cf[2];
            printPixel(x, y, cd);
        }
    }
    update();
}

void myWindow::constS (int val){
    double s = (double) val/ (double)(wide - 1);
    double h, v, cf[3];
    int cd[3];
    for(int y = 0; y < high; y++){
        v = (double) y / (double)(high - 1);
        for (int x = 0; x < wide; x++) {
            h = (((double)x/(double)(wide - 1))*360.0);
            convertHSVtoRGB(h, s, v, cf);
            cd[0] = (int) cf[0];
            cd[1] = (int) cf[1];
            cd[2] = (int) cf[2];
            printPixel(x, y, cd);
        }
    }
    update();
}

void myWindow::constV (int val){
    double v = (double) val /(double)(wide - 1);
    double s, h, cf[3];
    int cd[3];
    for(int y = 0; y < high; y++){
        s = (double) y / (double)(high - 1);
        for (int x = 0; x < wide; x++) {
            h = (((double)x/(double)(wide - 1))*360.0);
            convertHSVtoRGB(h, s, v, cf);
            cd[0] = (int) cf[0];
            cd[1] = (int) cf[1];
            cd[2] = (int) cf[2];
            printPixel(x, y, cd);
        }
    }
    update();
}

void myWindow::convertHSVtoRGB(double h, double s, double v, double c[3]){
    double chroma = s * v;
    double shue = h/60.0;
    double varible = chroma * (1.0 - std::abs(std::fmod(shue, 2.0) - 1.0));
    if(shue >= 0 && shue <= 1){
        c[0] = chroma;
        c[1] = varible;
        c[2] = 0;
    } else if(shue > 1 && shue <= 2){
        c[0] = varible;
        c[1] = chroma;
        c[2] = 0;
    } else if(shue > 2 && shue <= 3){
        c[0] = 0;
        c[1] = chroma;
        c[2] = varible;
    } else if(shue > 3 && shue <= 4){
        c[0] = 0;
        c[1] = varible;
        c[2] = chroma;
    } else if(shue > 4 && shue <= 5){
        c[0] = varible;
        c[1] = 0;
        c[2] = chroma;
    } else if(shue > 5 && shue <= 6){
        c[0] = chroma;
        c[1] = 0;
        c[2] = varible;
    } else {
        c[0] = 0;
        c[1] = 0;
        c[2] = 0;
    }
    double same = v - chroma;
    c[0] = (c[0] + same) * 255.0;
    c[1] = (c[1] + same) * 255.0;
    c[2] = (c[2] + same) * 255.0;
}

