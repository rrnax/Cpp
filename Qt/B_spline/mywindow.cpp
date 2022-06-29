#include "mywindow.h"
#include <cmath>
#include <utility>

myWindow::myWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Krzywa Beziera");
    resize(800, 800);

    szer = 740;
    wys = 740;
    poczX = 30;
    poczY = 30;
    basicColor[0] = 56;
    basicColor[1] = 252;
    basicColor[2] = 12;
    bckc[0] = 255;
    bckc[1] = 255;
    bckc[2] = 255;
    img = new QImage(szer, wys, QImage::Format_RGB32);
    backgrd = new QImage(szer, wys, QImage::Format_RGB32);
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
    pierwszy = event->pos();
    pierwszy.setX(pierwszy.x() - poczX);
    pierwszy.setY(pierwszy.y() - poczY);
    zmiana = znajdzPunkt(pierwszy.x(), pierwszy.y());
}

void myWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint drugi = event->pos();
    drugi.setX(drugi.x() - poczX);
    drugi.setY(drugi.y() - poczY);
    if (((pierwszy.x()>=0)&&(pierwszy.y()>=0)&&(pierwszy.x()<szer)&&(pierwszy.y()<wys))
                && ((drugi.x()>=0)&&(drugi.y()>=0)&&(drugi.x()<szer)&&(drugi.y()<wys))){
        if(zmiana != -1){
            pkt.at(zmiana) = drugi;
        }
    }
    copyImg(img, backgrd);
    printPkt();
    rysujKryzwa();
    update();
}

void myWindow::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint drugi = event->pos();
    drugi.setX(drugi.x() - poczX);
    drugi.setY(drugi.y() - poczY);
    if (((pierwszy.x()>=0)&&(pierwszy.y()>=0)&&(pierwszy.x()<szer)&&(pierwszy.y()<wys))
                && ((drugi.x()>=0)&&(drugi.y()>=0)&&(drugi.x()<szer)&&(drugi.y()<wys))){
        if(event->button() == Qt::LeftButton){
            if(zmiana == -1){
                pkt.push_back(drugi);
            } else {
                pkt.at(zmiana) = drugi;
            }
        } else if (event->button() == Qt::RightButton) {
            if(zmiana != -1){
                pkt.erase(pkt.begin()+zmiana);
            }
            if(pkt.size()< 4){
                copyImg(img, backgrd);
                update();
            }
        }
    }
    copyImg(img, backgrd);
    printPkt();
    rysujKryzwa();
    update();
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

int myWindow::znajdzPunkt(int x, int y){
    double d, tmpd;
    int ite = 0;
    if(pkt.size() >= 1){
        d = sqrt(pow(x - pkt[0].x(), 2.0) + pow(y - pkt[0].y(), 2.0));
        for(int i = 1; i <= (int)pkt.size(); i++){
            tmpd = sqrt(pow(x - pkt[i].x(), 2.0) + pow(y - pkt[i].y(), 2.0));
            if(d > tmpd){
                d = tmpd;
                ite = i;
            }
        }
        if(d < 10.0){
            return ite;
        }
    }
    return -1;
}

QPoint myWindow::splineRegule(double t, int pointPosition, std::vector<QPoint> pkt2){
    int temp;
    QPoint p;
    temp = (1.0/6.0) * ((-1.0) * pow(t, 3.0) + 3.0 * pow(t, 2.0) - 3.0 * t + 1.0) * pkt2[pointPosition].x()
            + (1.0/6.0) * (3.0 * pow(t, 3.0) - 6.0 * pow(t, 2.0) + 4.0) * pkt2[pointPosition + 1].x()
            + (1.0/6.0) * ((-3.0) * pow(t, 3.0) + 3.0 * pow(t, 2.0) + 3.0 * t + 1.0) * pkt2[pointPosition + 2].x()
            + (1.0/6.0) * pow(t, 3.0) * pkt2[pointPosition + 3].x();
    p.setX(temp);
    temp = (1.0/6.0) * ((-1.0) * pow(t, 3.0) + 3.0 * pow(t, 2.0) - 3.0 * t + 1.0) * pkt2[pointPosition].y()
            + (1.0/6.0) * (3.0 * pow(t, 3.0) - 6.0 * pow(t, 2.0) + 4.0) * pkt2[pointPosition + 1].y()
            + (1.0/6.0) * ((-3.0) * pow(t, 3.0) + 3.0 * pow(t, 2.0) + 3.0 * t + 1.0) * pkt2[pointPosition + 2].y()
            + (1.0/6.0) * pow(t, 3.0) * pkt2[pointPosition + 3].y();
    p.setY(temp);
    return p;
}

void myWindow::ourLine(int a1, int b1, int a2, int b2, int c[3])
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

void myWindow::rysujKryzwa(){
    if((int)pkt.size() >= 4){
        pkt.insert(pkt.begin(), 2, pkt.front());
        pkt.push_back(pkt.back());
        pkt.push_back(pkt.back());
        for(int i = 0; i < (int)pkt.size()-3; i++){
            for(int j = 0; j < 10; j++){
                double t1 = (double)j/10.0;
                double t2 = (double)(j+1)/10.0;
                QPoint first, second;

                first = splineRegule(t1, i, pkt);
                second = splineRegule(t2, i, pkt);
                ourLine(first.x(), first.y(), second.x(), second.y(), bckc);
                update();
            }
        }
        pkt.erase(pkt.begin());
        pkt.erase(pkt.begin());
        pkt.pop_back();
        pkt.pop_back();
    }
}

void myWindow::printCircle(double r, QPoint tmp, int c[3]){
    for(int x = 0; x <= (r/sqrt(2.0)); x++)
    {
        double temp = sqrt(pow(r, 2.0) - pow((double)x, 2.0));
        int y = (int)floor(temp+0.5);
        //I cwiartka
        part(x + tmp.x(), y + tmp.y(), c);
        part(y + tmp.x(), x + tmp.y(), c);

        //II cwiartka
        part((-x) + tmp.x(),y + tmp.y(), c);
        part(y + tmp.x(),(-x) + tmp.y(), c);

        //III cwiartka
        part((-x) + tmp.x(),(-y) + tmp.y(), c);
        part((-y) + tmp.x(),(-x) + tmp.y(), c);

        //IV cwiartka
        part(x + tmp.x(),(-y) + tmp.y(), c);
        part((-y) + tmp.x(),x + tmp.y(), c);
    }
}

void myWindow::part(int first, int second, int c[3]){
    unsigned char *ptr;
    ptr = img->bits();
    if (((first>=0)&&(first>=0)&&(first<szer)&&(first<wys))
                && ((second>=0)&&(second>=0)&&(second<szer)&&(second<wys))){
        ptr[szer*4*(second) + 4*(first)] = c[0];
        ptr[szer*4*(second) + 4*(first) + 1] = c[1];
        ptr[szer*4*(second) + 4*(first) + 2] = c[2];
    }
}

void myWindow::printPkt(){
    int grey[3];
    grey[0] = 41;
    grey[2] = 41;
    grey[1] = 41;
    if (pkt.size()>0){
        for(int i = 0; i < (int)pkt.size(); i++){
            part(pkt[i].x(), pkt[i].y(), basicColor);
            printCircle(10.0, pkt[i], basicColor);
            if(i < (int)pkt.size() - 1){
                ourLine(pkt[i].x(), pkt[i].y(), pkt[i+1].x(), pkt[i+1].y(), grey);
            }
        }
    } else {
        copyImg(img, backgrd);
    }
    update();
}

