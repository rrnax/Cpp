#include "mywindow.h"
#include <cmath>
#include <utility>
#include <QVBoxLayout>
#include <stack>

MyWindow::MyWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Flood Fill");
    resize(1000, 800);

    szer = 740;
    wys = 740;
    poczX = 30;
    poczY = 30;

    c[0] = 255;
    c[1] = 255;
    c[2] = 255;


    img = new QImage(szer, wys, QImage::Format_RGB32);
    backgrd = new QImage(szer, wys, QImage::Format_RGB32);

    grupa = new QGroupBox("Edycja",this);
    grupa->setGeometry(QRect(800,poczY,150,poczY+270));

    QVBoxLayout *boxLayout = new QVBoxLayout;

    odcinekButton = new QPushButton("Odcinek");
    okragButton = new QPushButton("Okrag");
    wypelnienieButton = new QPushButton("Wypelnij");

    boxLayout->addWidget(odcinekButton);
    boxLayout->addWidget(okragButton);
    boxLayout->addWidget(wypelnienieButton);

    grupa->setLayout(boxLayout);
    connect(odcinekButton,SIGNAL(clicked()),this,SLOT(slot_odcinek()));
    connect(okragButton,SIGNAL(clicked()),this,SLOT(slot_okrag()));
    connect(wypelnienieButton,SIGNAL(clicked()),this,SLOT(slot_wypelnij()));



}

MyWindow::~MyWindow()
{
     delete img;
}

void MyWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(poczX,poczY,*img);
}

void MyWindow::mousePressEvent(QMouseEvent *event)
{
    point1 = event->pos();
    point1.setX(point1.x() - poczX);
    point1.setY(point1.y() - poczY);
}

void MyWindow::mouseMoveEvent(QMouseEvent *event)
{
    point2 = event->pos();
    point2.setX(point2.x() - poczX);
    point2.setY(point2.y() - poczY);
    if ((point1.x()>=0)&&(point1.y()>=0)&&(point1.x()<szer)&&(point1.y()<wys)){
        copyImg(img, backgrd);
        update();
        switch(option){
        case 1:
            ourLine(point1.x(), point1.y(), point2.x(), point2.y());
            break;
        case 2:
            okrag();
            break;
        case 3:
            floodFill();
            break;
        }
        update();
    }
}

void MyWindow::mouseReleaseEvent(QMouseEvent *event)
{
    point2 = event->pos();
    point2.setX(point2.x() - poczX);
    point2.setY(point2.y() - poczY);
    if ((point1.x()>=0)&&(point1.y()>=0)&&(point1.x()<szer)&&(point1.y()<wys)){
        copyImg(img, backgrd);
        update();
        switch(option){
        case 1:
            ourLine(point1.x(), point1.y(), point2.x(), point2.y());
            break;
        case 2:
            okrag();
            break;
        case 3:
            floodFill();
            break;
        }
        copyImg(backgrd, img);
        update();
    }
}

void MyWindow::copyImg(QImage *a, QImage *b)
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

void MyWindow::ourLine(int a1, int b1, int a2, int b2)
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
            part(a1, b1, c);
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
            part(a1, b1, c);
        }
   }
}

void MyWindow::part(int first, int second, int col[3]){
    unsigned char *ptr;
    ptr = img->bits();
    if ((first >= 0) && (second >= 0) && (first < szer) && (second < wys)){
        ptr[szer*4*(second) + 4*(first)] = col[0];
        ptr[szer*4*(second) + 4*(first) + 1] = col[1];
        ptr[szer*4*(second) + 4*(first) + 2] = col[2];
    }
}

void MyWindow::takeColor(int x, int y, int color[3]){
    unsigned char *ptr;
    ptr = img->bits();
    color[0] = ptr[szer*4*(y) + 4*(x)];
    color[1] = ptr[szer*4*(y) + 4*(x) + 1];
    color[2] = ptr[szer*4*(y) + 4*(x) + 2];
}

bool MyWindow::comparColors(int *c1, int *c2){
    if(c1[0] == c2[0] && c1[1] == c2[1] && c1[2] == c2[2])
        return true;
    else
        return false;
}

void MyWindow::floodFill(){
    int filler[3], tlo[3], tempColor[3];
    std::stack<QPoint> stos;
    QPoint temp;
    filler[0] = 0;
    filler[1] = 255;
    filler[2] = 26;
    stos.push(point2);
    takeColor(point2.x(), point2.y(), tlo);
    while(!stos.empty()){
        temp = stos.top();
        takeColor(temp.x(), temp.y(), tempColor);
        stos.pop();
        if(comparColors(tempColor, tlo)){
            part(temp.x(), temp.y(), filler);
            temp.setX(temp.x() - 1);
            if(checkMargin(temp))
                stos.push(temp);
            temp.setX(temp.x() + 2);
            if(checkMargin(temp))
                stos.push(temp);
            temp.setX(temp.x() - 1);
            temp.setY(temp.y() - 1);
            if(checkMargin(temp))
                stos.push(temp);
            temp.setY(temp.y() + 2);
            if(checkMargin(temp))
                stos.push(temp);
        }
    }
}

/*void MyWindow::floodFill(){
    int filler[3], tlo[3], tempColor[3];
    std::stack<QPoint> stos;
    QPoint temp;
    filler[0] = 0;
    filler[1] = 255;
    filler[2] = 26;
    stos.push(point2);
    takeColor(point2.x(), point2.y(), tlo);
    while(!stos.empty()){
        temp = stos.top();
        takeColor(temp.x(), temp.y(), tempColor);
        stos.pop();
        if(comparColors(tempColor, tlo)){
            int w = temp.x();
            int e = temp.x();
            QPoint left = temp;
            QPoint right = temp;
            int leftColor[3], rightColor[3];
            left.setX(w);
            right.setX(e);
            takeColor(left.x(), left.y(), leftColor);
            takeColor(right.x(), right.y(), rightColor);
            while(comparColors(leftColor, tlo) && checkMargin(left)){
                w--;
                left.setX(w);
                if(checkMargin(left))
                    takeColor(left.x(), left.y(), leftColor);
            }
            while(comparColors(rightColor, tlo) && checkMargin(right)){
                e++;
                right.setX(e);
                if(checkMargin(right))
                    takeColor(right.x(), right.y(), rightColor);
            }
            for(int i = w+1; i < e; i++){
                temp.setX(i);
                part(temp.x(), temp.y(), filler);
            }
            left.setY(left.y()-1);
            right.setY(right.y()+1);
            for(int i = w+1; i < e; i++){
                left.setX(i);
                right.setX(i);
                if(checkMargin(left))
                    takeColor(left.x(), left.y(), leftColor);
                if(checkMargin(right))
                    takeColor(right.x(), right.y(), rightColor);
                if(comparColors(leftColor, tlo) && checkMargin(left)){
                    stos.push(left);
                }
                if(comparColors(rightColor, tlo) && checkMargin(right)){
                    stos.push(right);
                }
            }
        }
    }
}*/

bool MyWindow::checkMargin(QPoint pt){
    if ((pt.x() >= 0) && (pt.y() >= 0) && (pt.x() < szer) && (pt.y() < wys))
        return true;
    else
        return false;
}

void MyWindow::okrag(){
    double r = sqrt(pow((double)(point2.x() - point1.x()), 2.0)
                    + pow((double)(point2.y() - point1.y()), 2.0));
    for(int x = 0; x <= (r/sqrt(2.0) + 1.0); x++)
    {
        double temp = sqrt(pow(r, 2.0) - pow((double)x, 2.0));
        int y = (int)floor(temp+0.5);
        //I cwiartka
        part(x + point1.x(), y + point1.y(), c);
        part(y + point1.x(), x + point1.y(), c);

        //II cwiartka
        part((-x) +point1.x(),y + point1.y(), c);
        part(y + point1.x(),(-x) + point1.y(), c);

        //III cwiartka
        part((-x) + point1.x(),(-y) + point1.y(), c);
        part((-y) + point1.x(),(-x) + point1.y(), c);

        //IV cwiartka
        part(x + point1.x(),(-y) + point1.y(), c);
        part((-y) + point1.x(),x + point1.y(), c);
    }
}


void MyWindow::slot_odcinek(){
    option = 1;

}

void MyWindow::slot_okrag(){
    option = 2;

}

void MyWindow::slot_wypelnij(){
    option = 3;

}
