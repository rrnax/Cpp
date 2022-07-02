#include "mywindow.h"
#include <algorithm>
#include <iostream>
#include <cmath>


myWindow::myWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Textruring");

    //Left image cordinates relative to window
    startX = 30;
    startY = 30;

    //intens green
    col[0] = 28;
    col[1] = 252;
    col[2] = 3;

    //Images
    picture = new QImage("br.jpeg");
    imgLeft = new QImage("br.jpeg");
    wide = imgLeft->width();
    high = imgLeft->height();
    imgRight = new QImage(wide, high, QImage::Format_RGB32);
    backgrd = new QImage(wide, high, QImage::Format_RGB32);

    this->setFixedSize(2 * wide + 3 * 30, 50 + high + 100);

    //Interface
    group = new QGroupBox("Controls", this);
    group->setGeometry( 30, high + 40, 2 * wide + 30, 100);

    interpolation = new QCheckBox("Bilinear interpolation", this);

    layoutBox = new QGridLayout;

    path = new QLineEdit("Enter path to file...", this);

    reset = new QPushButton("Clear", this);
    load = new QPushButton("Load", this);

    layoutBox->addWidget(interpolation, 0, 0);
    layoutBox->addWidget(reset, 0, 1);
    layoutBox->addWidget(path, 1, 0);
    layoutBox->addWidget(load, 1, 1);

    group->setLayout(layoutBox);

    connect(interpolation,SIGNAL(stateChanged(int)),this,SLOT(changingState()));
    connect(reset,SIGNAL(clicked()),this,SLOT(clear()));
    connect(load,SIGNAL(clicked()),this,SLOT(loadNewImage()));
}

//Destructor
myWindow::~myWindow()
{
    delete imgLeft;
    delete imgRight;
}

//Placing images on the window
void myWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(startX, startY, *imgLeft);
    p.drawImage(2 * startX + wide, startY, *imgRight);
}

//Control functions
void myWindow::changingState(){
    if(peaksFrom.size() == 3 && peaksTo.size() == 3){
        scanLine(peaksTo);
        update();
    }
}

void myWindow::clear(){
    peaksFrom.clear();
    peaksTo.clear();
    //Clear images
    copyImg(imgLeft, picture);
    copyImg(imgRight, backgrd);
    update();
}

void myWindow::loadNewImage(){
    QImage *temp1 = new QImage(path->text());
    QImage *temp2 = new QImage(path->text());
    picture = temp1;
    imgLeft = temp2;

    wide = imgLeft->width();
    high = imgLeft->height();
    imgRight = new QImage(wide, high, QImage::Format_RGB32);
    backgrd = new QImage(wide, high, QImage::Format_RGB32);

    this->setFixedSize(2 * wide + 3 * 30, 50 + high + 100);
    group->setGeometry( 30, high + 40, 2 * wide + 30, 100);

    std::cout << "yey" << std::endl;

    repaint();
}

//Mouse actions
void myWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        pressCordinates = event->pos();
        changeLeftTriangle = -1;
        changeRightTriangle = -1;

        if(pressCordinates.x() >= startX            //Click on the left image
                && pressCordinates.y() >= startY
                && pressCordinates.y() < startY + high
                && pressCordinates.x() < (startX + wide)){

            pressCordinates.setX(pressCordinates.x() - startX);
            pressCordinates.setY(pressCordinates.y() - startY);
            changeLeftTriangle = findPoint(pressCordinates.x(), pressCordinates.y(), peaksFrom);

        } else if (pressCordinates.x() >= (2 * startX + wide)           //Click on the right image
                   && pressCordinates.y() >= startY
                   && pressCordinates.y() < startY + high
                   && pressCordinates.x() < (2 * startX + 2 * wide)){

            pressCordinates.setX(pressCordinates.x() - (2 * startX + wide));
            pressCordinates.setY(pressCordinates.y() - startY);
            changeRightTriangle = findPoint(pressCordinates.x(), pressCordinates.y(), peaksTo);
        }
    }

}

void myWindow::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint newPoint = event->pos();
    if(event->button() == Qt::LeftButton){
        if(newPoint.x() >= startX            //Click on the left image
                && newPoint.y() >= startY
                && newPoint.y() < startY + high
                && newPoint.x() < (startX + wide)){

            if(changeLeftTriangle != -1){               //Changing point position on left image
                newPoint.setX(newPoint.x() - startX);
                newPoint.setY(newPoint.y() - startY);
                peaksFrom.at(changeLeftTriangle) = newPoint;

            } else if(changeLeftTriangle == -1
                      && peaksFrom.size() < 3){
                peaksFrom.push_back(pressCordinates);
            }

        } else if(newPoint.x() >= (2 * startX + wide)            //Click on the left image
                  && newPoint.y() >= startY
                  && newPoint.y() < startY + high
                  && newPoint.x() < (2 * startX +  2 * wide)){

            if (changeRightTriangle != -1){           //Changing point position on right image
                newPoint.setX(newPoint.x() -  (2 * startX + wide));
                newPoint.setY(newPoint.y() - startY);
                peaksTo.at(changeRightTriangle) = newPoint;

            } else if(changeRightTriangle == -1
                      && peaksTo.size() < 3){
                peaksTo.push_back(pressCordinates);
            }

        }
        writeTiangle();
    }
    if(peaksFrom.size() == 3 && peaksTo.size() == 3){
        scanLine(peaksTo);
    }
    update();
}

void myWindow::mouseMoveEvent(QMouseEvent *event){
    QPoint newPoint = event->pos();
    if(newPoint.x() >= startX            //Click on the left image
            && newPoint.y() >= startY
            && newPoint.y() < startY + high
            && newPoint.x() < (startX + wide)){

        if(changeLeftTriangle != -1){           //Changing point position on left image
            newPoint.setX(newPoint.x() - startX);
            newPoint.setY(newPoint.y() - startY);
            peaksFrom.at(changeLeftTriangle) = newPoint;
        }
    }else if(newPoint.x() >= (2 * startX + wide)            //Click on the left image
             && newPoint.y() >= startY
             && newPoint.y() < startY + high
             && newPoint.x() < (2 * startX +  2 * wide)){

        if(changeRightTriangle != -1){          //Changing point position on right image
            newPoint.setX(newPoint.x() -  (2 * startX + wide));
            newPoint.setY(newPoint.y() - startY);
            peaksTo.at(changeRightTriangle) = newPoint;
        }
    }
        writeTiangle();
        if(peaksFrom.size() == 3 && peaksTo.size() == 3){
            scanLine(peaksTo);
        }
        update();
}

int myWindow::findPoint(int x, int y, std::vector<QPoint> vertices){            //To find the closest peak of triangle if it has distance < 10
    double firstVertexRadius, secondVertexRadius;
    int vertexNumber = 0;
    if(vertices.size() > 0){
        firstVertexRadius = sqrt(pow(x - vertices[0].x(), 2.0) + pow(y - vertices[0].y(), 2.0));
        for(int i = 1; i < (int)vertices.size(); i++){
            secondVertexRadius = sqrt(pow(x - vertices[i].x(), 2.0) + pow(y - vertices[i].y(), 2.0));
            if(firstVertexRadius > secondVertexRadius){
                firstVertexRadius = secondVertexRadius;
                vertexNumber = i;
            }
        }
        if(firstVertexRadius < 10.0){
            return vertexNumber;
        }
    }
    return -1;
}



void myWindow::copyImg(QImage *a, QImage *b)            //Copying image b to a
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

void myWindow::printLine(int x1, int y1, int x2, int y2, int color[3], QImage *pic)         //Print line between points
{
    int deltaX, deltaY, missError;
    int directX, directY;

    if(x1 < x2){
        directX = 1;
        deltaX = x2 - x1;

    } else {
        directX = -1;
        deltaX = x1 - x2;
    }

    if(y1 < y2){
        directY = 1;
        deltaY = y2 - y1;
    } else {
        directY = -1;
        deltaY = y1 - y2;
    }

    if(deltaX >= deltaY){
        missError = deltaX/2;

        for(int i = 0; i < deltaX; i++ ){
            x1 += directX;
            missError -= deltaY;
            if(missError < 0){
                y1 += directY;
                missError += deltaX;
            }
            printPixel(x1, y1, color, pic);
        }

    } else {
        missError = deltaY/2;
        for(int i = 0; i < deltaY; i++){
            y1 += directY;
            missError -= deltaX;
            if(missError < 0){
                x1 += directX;
                missError += deltaY;
            }
            printPixel(x1, y1, color, pic);
        }
    }
}

void myWindow::printPixel(int x, int y, int *color, QImage *pic){           //Print one single pixel
    unsigned char *ptr;
    ptr = pic->bits();
    if ((x >= 0) && (y >= 0) && (x < wide) && (y < high)){
        ptr[wide * 4 * y + 4 * x] = color[0];
        ptr[wide * 4 * y + 4 * x + 1] = color[1];
        ptr[wide * 4 * y + 4 * x + 2] = color[2];
    }
}


void myWindow::markPoint(QPoint p, QImage *pic){            //Print point place
    printPixel(p.x(), p.y(), col, pic);
    printCircle(10.0, p, col, pic);
}

void myWindow::printCircle(double radius, QPoint vertex, int color[3], QImage *pic){        //Print circle around point
    for(int x = 0; x <= (radius/sqrt(2.0)); x++)
    {
        double findY = sqrt(pow(radius, 2.0) - pow((double)x, 2.0));
        int y = (int)floor(findY + 0.5);
        //I cwiartka
        printPixel(x + vertex.x(), y + vertex.y(), color, pic);
        printPixel(y + vertex.x(), x + vertex.y(), color, pic);

        //II cwiartka
        printPixel((-x) + vertex.x(),y + vertex.y(), color, pic);
        printPixel(y + vertex.x(),(-x) + vertex.y(), color, pic);

        //III cwiartka
        printPixel((-x) + vertex.x(),(-y) + vertex.y(), color, pic);
        printPixel((-y) + vertex.x(),(-x) + vertex.y(), color, pic);

        //IV cwiartka
        printPixel(x + vertex.x(),(-y) + vertex.y(), color, pic);
        printPixel((-y) + vertex.x(),x + vertex.y(), color, pic);
    }
}

void myWindow::writeTiangle(){
    //Clear images
    copyImg(imgLeft, picture);
    copyImg(imgRight, backgrd);

    //Print new left triangle
    for(int i = 0; i < (int)peaksFrom.size(); i++){
        markPoint(peaksFrom[i], imgLeft);
    }
    if((int)peaksFrom.size() == 3){
        for(int i = 1; i < (int)peaksFrom.size(); i++){
            printLine(peaksFrom[i-1].x(), peaksFrom[i-1].y(), peaksFrom[i].x(), peaksFrom[i].y(), col, imgLeft);
        }
        printLine(peaksFrom[2].x(), peaksFrom[2].y(), peaksFrom[0].x(), peaksFrom[0].y(), col, imgLeft);
    }

    //Print new right triangle
    for(int i = 0; i < (int)peaksTo.size(); i++){
        markPoint(peaksTo[i], imgRight);
    }
    if((int)peaksTo.size() == 3){
        for(int i = 1; i < (int)peaksTo.size(); i++){
            printLine(peaksTo[i-1].x(), peaksTo[i-1].y(), peaksTo[i].x(), peaksTo[i].y(), col, imgRight);
        }
        printLine(peaksTo[2].x(), peaksTo[2].y(), peaksTo[0].x(), peaksTo[0].y(), col, imgRight);
    }
}

//u -> 0, v -> 1, w -> 2
void myWindow::barycentricCordinates(int x, int y,int color[3]){         //Find point baricentric coridnates
    double determinant, determinantV, determinantW, u, v, w;
    double finalX, finalY;

    determinant = (peaksTo[1].x() - peaksTo[0].x()) * (peaksTo[2].y() - peaksTo[0].y())
            - (peaksTo[1].y() - peaksTo[0].y()) * (peaksTo[2].x() - peaksTo[0].x());
    determinantV = (x - peaksTo[0].x()) *  (peaksTo[2].y() - peaksTo[0].y())
            - (y - peaksTo[0].y()) * (peaksTo[2].x() - peaksTo[0].x());
    determinantW = (peaksTo[1].x() - peaksTo[0].x()) * (y - peaksTo[0].y())
            - (peaksTo[1].y() - peaksTo[0].y()) * (x- peaksTo[0].x());

    v = determinantV/determinant;
    w = determinantW/determinant;
    u = 1 - v - w;

    finalX = u * peaksFrom[0].x() + v * peaksFrom[1].x() + w * peaksFrom[2].x();
    finalY = u * peaksFrom[0].y() + v * peaksFrom[1].y() + w * peaksFrom[2].y();

    if(interpolation->isChecked()){
        color[0] = interpolations(finalX, finalY, 0, picture);
        color[1] = interpolations(finalX, finalY, 1, picture);
        color[2] = interpolations(finalX, finalY, 2, picture);
    } else {
        color[0] = picture->bits()[wide * 4 * (int)round(finalY) + 4 * (int)round(finalX)];
        color[1] = picture->bits()[wide * 4 * (int)round(finalY) + 4 * (int)round(finalX) + 1];
        color[2] = picture->bits()[wide * 4 * (int)round(finalY) + 4 * (int)round(finalX) + 2];
    }
}

void myWindow::scanLine(std::vector<QPoint> v){         //Scaning lines to find pixels in triangle
    std::vector<QPoint> peaks;
    peaks = v;

    //Find triangle maxY and minY
    int Ymin = peaks[0].y();
    int Ymax = peaks[0].y();
    for(int i = 1; i < (int)peaks.size(); i++){ //Wybranie min i max figury
        if(peaks[i].y() > Ymax){
            Ymax = peaks[i].y();
        }
        if(peaks[i].y() < Ymin){
            Ymin = peaks[i].y();
        }
    }

    peaks.push_back(peaks[0]);          //We need it in loop

    for(int y = Ymin ; y <= Ymax; y++){           //Find crossing pixels
        std::vector<int> pointsOfCrose;
        for(int i = 0; i < (int)peaks.size() - 1; i++){
            if(!((peaks[i].y() <= y && peaks[i + 1].y() <= y)
                 || (peaks[i].y() > y && peaks[i + 1].y() > y))){
                if(!(peaks[i+1].y() - peaks[i].y() == 0)){
                    int x = peaks[i].x()
                            + (int)floor((double)(y - peaks[i].y())
                                         * ((double)(peaks[i+1].x() - peaks[i].x())
                                         / (double)(peaks[i+1].y() - peaks[i].y())));
                    pointsOfCrose.push_back(x);
                }
            }
        }
        sort(pointsOfCrose.begin(), pointsOfCrose.end());           //Sort the cross points
        for(int i = 0; i < (int)pointsOfCrose.size() - 1; i++){         //Find cordinates in trinagle
            if(i % 2 == 0){
                for(int x = pointsOfCrose.front() + 1; x <= pointsOfCrose.back(); x++){
                    barycentricCordinates(x, y, textureColor);
                    printPixel(x, y, textureColor, imgRight);
                }
            }
        }
    }
    for(int i = 0; i < (int)peaks.size() - 1; i++){
        printLine(peaks[i].x(), peaks[i].y(), peaks[i+1].x(), peaks[i+1].y(), col, imgRight);
    }
}

int myWindow::interpolations(double x, double y, int option, QImage *img){           //make pixels smooth
    unsigned char *p;
    p = img->bits();
    double a = x - floor(x);
    double b = ceil(y) - y;
    int leftPointsX = floor(x);
    int bottomPointsY = floor(y);
    int rightPointsX = ceil(x);
    int topPointsY= ceil(y);
    return  b * ((1 - a) * p[img->width() * 4 * (bottomPointsY) + 4 * (leftPointsX) + option]
            + a * p[img->width() * 4 * (bottomPointsY) + 4 * (rightPointsX) + option])
            + (1 - b) * ((1 - a) * p[img->width() * 4 * (topPointsY) + 4 * (leftPointsX) + option]
            + a * p[img->width() * 4 * (topPointsY) + 4 * (rightPointsX) + option]);
}
