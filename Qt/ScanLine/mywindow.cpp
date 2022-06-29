#include "mywindow.h"
#include <algorithm>

myWindow::myWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("ScanLine");
    resize(800, 800);

    wide = 740;
    high = 740;
    startX = 30;
    startY = 30;
    basicColor[0] = 217;
    basicColor[1] = 20;
    basicColor[2] = 20;
    col[0] = 255;
    col[1] = 255;
    col[2] = 255;
    img = new QImage(wide, high, QImage::Format_RGB32);
    backgrd = new QImage(wide, high, QImage::Format_RGB32);

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

void myWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        tmp = event->pos();
        tmp.setX(tmp.x() - startX);
        tmp.setY(tmp.y() - startY);
        if((tmp.x() < wide && tmp.x() >= 0) && (tmp.y() < high && tmp.y() >= 0)){
            peak.push_back(tmp);
        }
    }

}

void myWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        for(int i = 1; i < (int)peak.size(); i++){
            printLine(peak[i-1].x(), peak[i-1].y(), peak[i].x(), peak[i].y(), col);
            update();
        }
    }
    if(event->button() == Qt::RightButton){
        if((int)peak.size() > 2){
            printLine(peak[(int)peak.size() - 1].x(), peak[(int)peak.size() - 1].y(), peak[0].x(), peak[0].y(), basicColor);
            drawInsideFigure();
            copyImg(backgrd, img);
            peak.clear();
            copyImg(img, backgrd);
            update();
        }
    }
}

void myWindow::drawInsideFigure(){
    int Ymin = peak[0].y();
    int Ymax = peak[0].y();
    for(int i = 1; i < (int)peak.size(); i++){ //Wybranie min i max figury
        if(peak[i].y() > Ymax){
            Ymax = peak[i].y();
        }
        if(peak[i].y() < Ymin){
            Ymin = peak[i].y();
        }
    }
    peak.push_back(peak[0]);    //dodajemy aby sprawdzilo krawedz miedzy ostatnim a pierwszym wierzcholiem
    for(int y = Ymin; y <= Ymax; y++){  //iteracja po y figury(liniach)
        std::vector<int> crose;
        for(int i = 0; i < (int)peak.size() - 1; i++){
            if(!((peak[i].y() <= y && peak[i + 1].y() <= y)   //Sprawdzenie czy linie przecina krawedz i rozwiazanie problemu dwoch przeciec
                    || (peak[i].y() > y && peak[i + 1].y() > y))){
                if(!(peak[i+1].y() - peak[i].y() == 0)){
                    int x = peak[i].x() + (int)floor((double)(y - peak[i].y()) * ((double)(peak[i+1].x() - peak[i].x())/(double)(peak[i+1].y() - peak[i].y())));
                    crose.push_back(x);
                }   //wyliczenie punktu przeciecia
            }
        }
        sort(crose.begin(), crose.end());
        for(int i = 0; i < (int)crose.size()-1; i++){
            if(i % 2 == 0){
                for(int x = crose[i]+1; x <= crose[i+1]; x++){
                    printPixel(x, y, basicColor);
                }
            }
        }
    }
    for(int i = 0; i < (int)peak.size() - 1; i++){
        printLine(peak[i].x(), peak[i].y(), peak[i+1].x(), peak[i+1].y(), col);
    }
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

void myWindow::printLine(int x1, int y1, int x2, int y2, int color[3])
{
    int deltax, deltay,err;
    int xKier, yKier;

    if(x1 < x2){
        xKier = 1;
        deltax = x2 - x1;
    } else {
        xKier = -1;
        deltax = x1 - x2;
    }
    if(y1 < y2){
        yKier = 1;
        deltay = y2 - y1;
    } else {
        yKier = -1;
        deltay = y1 - y2;
    }

    if(deltax >= deltay){
        err = deltax/2;
        for(int i = 0; i < deltax; i++ ){
            x1 += xKier;
            err -= deltay;
            if(err < 0){
                y1 += yKier;
                err += deltax;
            }
            printPixel(x1, y1, color);
        }
   } else {
        err = deltay/2;
        for(int i = 0; i < deltay; i++){
            y1 += yKier;
            err -= deltax;
            if(err < 0){
                x1 += xKier;
                err += deltay;
            }
            printPixel(x1, y1, color);
        }
   }
}

void myWindow::printPixel(int x, int y, int *color){
    unsigned char *ptr;
    ptr = img->bits();
    if ((x >= 0) && (y >= 0) && (x < wide) && (y < high)){
        ptr[wide * 4 * y + 4 * x] = color[0];
        ptr[wide * 4 * y + 4 * x + 1] = color[1];
        ptr[wide * 4 * y + 4 * x + 2] = color[2];
    }
}
