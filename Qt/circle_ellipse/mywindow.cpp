#include "mywindow.h"
#include <QVBoxLayout>
#include <cmath>
#include <utility>
#include <QString>
#define PI 3.14159265358979323846

myWindow::myWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Rysowanie pixeli w QT");
    resize(1000, 800);

    szer = 740;
    wys = 740;
    poczX = 30;
    poczY = 30;
    amountPoints = 5;

    img = new QImage(szer, wys, QImage::Format_RGB32);
    backgrd = new QImage(szer, wys, QImage::Format_RGB32);

    group = new QGroupBox("Ilosc wierzchołkow:", this);

    group->setGeometry(QRect(800, 30, 170, 100));

    QVBoxLayout *boxLayout = new QVBoxLayout;

    slider = new QSlider(Qt::Horizontal, this);
    slider->setMinimum(5);
    slider->setMaximum(100);
    txt = new QLabel("5");

    boxLayout->addWidget(slider);
    boxLayout->addWidget(txt);
    group->setLayout(boxLayout);

    connect(slider,SIGNAL(valueChanged(int)),this,SLOT(value(int)));
}

myWindow::~myWindow()
{
    delete img;
}

void myWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(poczX,poczY,*img);

}

void myWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        QPoint p1 = event->pos();
        x1 = p1.x();
        y1 = p1.y();

        x1 = x1 - poczX;
        y1 = y1 - poczY;

        which = true;
    } else if(event->button() == Qt::RightButton){
        QPoint p1 = event->pos();
        x1 = p1.x();
        y1 = p1.y();

        x1 = x1 - poczX;
        y1 = y1 - poczY;

        which = false;
    }
    update();
}

void myWindow::mouseMoveEvent(QMouseEvent *event)
{
    double r;

    QPoint p2 = event->pos();
    x2 = p2.x();
    y2 = p2.y();

    x2 = x2 - poczX;
    y2 = y2 - poczY;
    r = sqrt(pow((double)(x2 - x1), 2.0) + pow((double)(y2 - y1), 2.0));

    copyImg(img, backgrd);
    update();
    if(which){
        if (((x1>=0)&&(y1>=0)&&(x1<szer)&&(y1<wys))
                && ((x2>=0)&&(y2>=0)&&(x2<szer)&&(y2<wys))){

            if((r <= x1 && r <= y1) && (r <= (szer - x1) && r <= (wys - y1))){
                for(int x = 0; x <= (r/sqrt(2.0)); x++)
                    {
                        double temp = sqrt(pow(r, 2.0) - pow((double)x, 2.0));
                        int y = (int)floor(temp+0.5);
                        //I cwiartka
                        part(x, y);
                        part(y, x);

                        //II cwiartka
                        part((-x),y);
                        part(y,(-x));

                        //III cwiartka
                        part((-x),(-y));
                        part((-y),(-x));

                        //IV cwiartka
                        part(x,(-y));
                        part((-y),x);
                    }
            }
        }
    } else {
        double a1, b1, a2, b2, a, b;
        if (((x1>=0)&&(y1>=0)&&(x1<szer)&&(y1<wys))
                && ((x2>=0)&&(y2>=0)&&(x2<szer)&&(y2<wys))){
            double step = (2.0 * PI) / (double) amountPoints;
            a = abs(x2 - x1);
            b = abs(y2 - y1);
            if((a <= x1 && b <= y1) && (a <= (szer - x1) && b <= (wys - y1))){
                for(int i = 0; i < amountPoints; i++){
                    a1 = (a * cos(i * step));
                    b1 = (b * sin(i * step));
                    a2 = (a * cos((i+1) * step));
                    b2 = (b * sin((i+1) * step));
                    ourLine(a1, b1, a2, b2);
                }
            }
        }
    }
    update();
}

void myWindow::mouseReleaseEvent(QMouseEvent *event)
{
    double r;
    QPoint p2 = event->pos();
    x2 = p2.x();
    y2 = p2.y();

    x2 = x2 - poczX;
    y2 = y2 - poczY;

    r = sqrt(pow((double)(x2 - x1), 2.0) + pow((double)(y2 - y1), 2.0));

    if(event->button() == Qt::LeftButton){
        if (((x1>=0)&&(y1>=0)&&(x1<szer)&&(y1<wys))
                && ((x2>=0)&&(y2>=0)&&(x2<szer)&&(y2<wys))){

            if((r <= x1 && r <= y1) && (r <= (szer - x1) && r <= (wys - y1))){
                for(int x = 0; x <= (r/sqrt(2.0)); x++)
                    {
                        double temp = sqrt(pow(r, 2.0) - pow((double)x, 2.0));
                        int y = (int)floor(temp+0.5);
                        //I cwiartka
                        part(x, y);
                        part(y, x);

                        //II cwiartka
                        part((-x),y);
                        part(y,(-x));

                        //III cwiartka
                        part((-x),(-y));
                        part((-y),(-x));

                        //IV cwiartka
                        part(x,(-y));
                        part((-y),x);
                    }
            }
        }
        copyImg(backgrd, img);

    } else if(event->button() == Qt::RightButton){
        double a1, b1, a2, b2, a, b;
        if (((x1>=0)&&(y1>=0)&&(x1<szer)&&(y1<wys))
                && ((x2>=0)&&(y2>=0)&&(x2<szer)&&(y2<wys))){
            double step = (2.0 * PI) / (double) amountPoints;
            a = abs(x2 - x1);
            b = abs(y2 - y1);
            if((a <= x1 && b <= y1) && (a <= (szer - x1) && b <= (wys - y1))){
                for(int i = 0; i < amountPoints; i++){
                    a1 = (a * cos(i * step));
                    b1 = (b * sin(i * step));
                    a2 = (a * cos((i+1) * step));
                    b2 = (b * sin((i+1) * step));
                    ourLine(a1, b1, a2, b2);
                }
            }
        }
        copyImg(backgrd, img);
    }
    update();

}

void myWindow::part(int first, int second){
    unsigned char *ptr;
    ptr = img->bits();

    ptr[szer*4*(second+y1) + 4*(first+x1)] = 255;
    ptr[szer*4*(second+y1) + 4*(first+x1) + 1] = 255;
    ptr[szer*4*(second+y1) + 4*(first+x1) + 2] = 255;
}

void myWindow::copyImg(QImage *a, QImage *b)
{
    unsigned char *img1, *img2;
    img1 = a->bits();
    img2 = b->bits();
    for(int i = 0; i < wys; i++)
        {
            for(int j = 0; j < szer; j++)
            {
                img1[szer*4*i + 4*j] = img2[szer*4*i + 4*j];
                img1[szer*4*i + 4*j + 1] = img2[szer*4*i + 4*j + 1];
                img1[szer*4*i + 4*j + 2] = img2[szer*4*i + 4*j + 2];
            }
        }
}

void myWindow::value(int val)
{
    amountPoints = val;
    txt->setText(QString("%1").arg(amountPoints));
}

void myWindow::ourLine(int a1, int b1, int a2, int b2)
{
    int deltax, deltay,err;
    int xKier, yKier;

    if(a1 < a2){
        xKier = 1;
        deltax = a2 - a1;
    } else {
        xKier = -1;
        deltax = a1 - a2;
    }
    if(b1 < b2){
        yKier = 1;
        deltay = b2 - b1;
    } else {
        yKier = -1;
        deltay = b1 - b2;
    }

    if(deltax >= deltay){
        err = deltax/2;
        for(int i = 0; i < deltax; i++ ){
            a1 += xKier;
            err -= deltay;
            if(err < 0){
                b1 += yKier;
                err += deltax;
            }
            part(a1, b1);
        }
   } else {
        err = deltay/2;
        for(int i = 0; i < deltay; i++){
            b1 += yKier;
            err -= deltax;
            if(err < 0){
                a1 += xKier;
                err += deltay;
            }
            part(a1, b1);
        }
   }
}

