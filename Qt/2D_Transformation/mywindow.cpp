#include "mywindow.h"
#include <string>
#include <cmath>
#include <iostream>
#include <iomanip>

#define PI 3.14159265

//Operations on matrixes
void copyMatrix(double [], double []);
void matrxMultipling_3x3(double [], double []);
void multiplingMatrix_X_Vector(double [], double []);
void writeValue(double matrix[], int rows, int columns);

//Matixes of transformation
double translationMatrix[9];
double rotationMatrix[9];
double scalingMatrix[9];
double shXMatrix[9];
double shYMatrix[9];

//Temporary matrixes for calculations
double resultTranslationMatrix[9];
double moveToCordsBegining[9];
double temp[9];

//Vectors with cordinates of actual pixels
double cordinatesVector[3];
double resultVector[3];


myWindow::myWindow(QWidget *parent)
    : QWidget(parent)
{
    for(int i = 0; i < 3; i++ ){    //Fill matrixes to identity matrix
        for(int j = 0; j < 3; j ++ ){
            if(i == j){
                translationMatrix[i * 3 + j] = 1;
                rotationMatrix[i * 3 + j] = 1;
                shXMatrix[i * 3 + j] = 1;
                shYMatrix[i * 3 + j] = 1;
                scalingMatrix[i * 3 + j] = 1;
                moveToCordsBegining[i * 3 + j] = 1;
            } else {
                translationMatrix[i * 3 +j] = 0;
                rotationMatrix[i * 3 + j] = 0;
                shXMatrix[i * 3 + j] = 0;
                shYMatrix[i * 3 + j] = 0;
                scalingMatrix[i * 3 +j] = 0;
                moveToCordsBegining[i * 3 + j] = 0;
            }
        }
    }
    cordinatesVector[2] = 1;

    //Seting elements and window
    setWindowTitle("Translation 2D");
    this->setFixedSize(1200, 800);

    wide = 800;
    high = 750;
    startX = 30;
    startY = 30;
    basicColor[0] = 0;          //Color in RGB
    basicColor[1] = 0;
    basicColor[2] = 0;

    //Images
    img = new QImage(wide, high, QImage::Format_RGB32);
    img1 = new QImage("picture.png");
    back = new QImage(wide, high, QImage::Format_RGB32);
    toCompare = new QImage(wide, high, QImage::Format_RGB32);
    imgX = 30 + ((int)round(wide/2) - (int)round(img1->width()/2));
    imgY = 30 + ((int)round(high/2) - (int)round(img1->height()/2));
    cordinatesVector[0] = imgX;
    cordinatesVector[1] = imgY;

    //Intrface
    group = new QGroupBox("Controls", this);
    group->setGeometry(865, 8, 300, 772);

    xlabel = new QLabel("Displacment x:");
    x = new QSlider(Qt::Horizontal, this);
    x->setMinimum(-400);
    x->setMaximum(400);
    x->setValue(0);
    ylabel = new QLabel("Displacment y:");
    y = new QSlider(Qt::Horizontal, this);
    y->setMinimum(-325);
    y->setMaximum(325);
    y->setValue(0);
    sxlabel = new QLabel("Scaling x:");
    sx = new QSlider(Qt::Horizontal, this);
    sx->setMinimum(0);
    sx->setMaximum(1000);
    sx->setValue(100);
    sylabel = new QLabel("Scaling y:");
    sy = new QSlider(Qt::Horizontal, this);
    sy->setMinimum(0);
    sy->setMaximum(1000);
    sy->setValue(100);
    obrotlabel = new QLabel("Rotation angel:");
    alpha = new QSlider(Qt::Horizontal, this);
    alpha->setMinimum(-360);
    alpha->setMaximum(360);
    alpha->setValue(0);
    shxlabel = new QLabel("Shreding x:");
    shx = new QSlider(Qt::Horizontal, this);
    shx->setMinimum(-360);
    shx->setMaximum(360);
    shx->setValue(0);
    shylabel = new QLabel("Shreding y:");
    shy = new QSlider(Qt::Horizontal, this);
    shy->setMinimum(-360);
    shy->setMaximum(360);
    shy->setValue(0);

    inverseMatrix = new QCheckBox("Inverse Matrix", this);
    interpolation = new QCheckBox("Bilinear interpolation", this);

    resetBt = new QPushButton("Reset controls", this);
    load = new QPushButton("Load", this);

    path = new QLineEdit("Enter path to file...", this);

    layoutbox = new QGridLayout;
    layoutbox->addWidget(xlabel, 0, 0);
    layoutbox->addWidget(x, 1, 0);
    layoutbox->addWidget(ylabel, 2, 0);
    layoutbox->addWidget(y, 3, 0);
    layoutbox->addWidget(sxlabel, 4, 0);
    layoutbox->addWidget(sx, 5, 0);
    layoutbox->addWidget(sylabel, 6, 0);
    layoutbox->addWidget(sy, 7, 0);
    layoutbox->addWidget(obrotlabel, 8, 0);
    layoutbox->addWidget(alpha, 9, 0);
    layoutbox->addWidget(shxlabel, 10, 0);
    layoutbox->addWidget(shx, 11, 0);
    layoutbox->addWidget(shylabel, 12, 0);
    layoutbox->addWidget(shy, 13, 0);
    layoutbox->addWidget(inverseMatrix, 14, 0);
    layoutbox->addWidget(interpolation, 15, 0);
    layoutbox->addWidget(resetBt, 16, 0);

    loadPath = new QHBoxLayout;
    loadPath->addWidget(path);
    loadPath->addWidget(load);
    layoutbox->addLayout(loadPath, 17, 0);

    group->setLayout(layoutbox);

    //Action on events
    connect(x,SIGNAL(valueChanged(int)),this,SLOT(translationX(int)));
    connect(y,SIGNAL(valueChanged(int)),this,SLOT(translationY(int)));
    connect(alpha,SIGNAL(valueChanged(int)),this,SLOT(rotation(int)));
    connect(shx,SIGNAL(valueChanged(int)),this,SLOT(sheringX(int)));
    connect(shy,SIGNAL(valueChanged(int)),this,SLOT(sheringY(int)));
    connect(sx,SIGNAL(valueChanged(int)),this,SLOT(graduationX(int)));
    connect(sy,SIGNAL(valueChanged(int)),this,SLOT(graduationY(int)));
    connect(interpolation,SIGNAL(stateChanged(int)),this,SLOT(changingState(int)));
    connect(inverseMatrix,SIGNAL(stateChanged(int)),this,SLOT(changingState(int)));
    connect(resetBt,SIGNAL(clicked()),this,SLOT(reset()));
    connect(load,SIGNAL(clicked()),this,SLOT(loading()));

    translateImage();
}

myWindow::~myWindow()       //Destuctor
{
    delete img;
}

void myWindow::paintEvent(QPaintEvent*)         //Drawing images in Window
{
    scene = new QPainter(this);
    scene->drawImage(startX, startY, *img);
}

void myWindow::copyImg(QImage *a, QImage *b)            //Copying pixels from b image to a
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

//Chceck boxes handler
void myWindow::changingState(int state){
    translateImage();
}

//Buttons functions
void myWindow::reset(){
    copyImg(img, back);
    x->setValue(0);
    y->setValue(0);
    sx->setValue(100);
    sy->setValue(100);
    alpha->setValue(0);
    shx->setValue(0);
    shy->setValue(0);
    inverseMatrix->setChecked(false);
    interpolation->setChecked(false);
    translateImage();
}

void myWindow::loading(){           //Load other picture to program
    QImage *tmp = new QImage(path->text());
    img1 = tmp;
    imgX = 30 + ((int)round(wide/2) - (int)round(img1->width()/2));
    imgY = 30 + ((int)round(high/2) - (int)round(img1->height()/2));
    cordinatesVector[0] = imgX;
    cordinatesVector[1] = imgY;
    reset();
}

//Sliders connection with transletion
void myWindow::translationX(int x){
    translationMatrix[2] = x;
    translationMatrix[5] = y->value();
    translateImage();
}

void myWindow::translationY(int y){
    translationMatrix[2] = x->value();
    translationMatrix[5] = y;
    translateImage();
}

void myWindow::rotation(int a){
    rotationMatrix[0] = (cos(a * PI / 180));
    rotationMatrix[1] = ((-1) * sin(a * PI / 180));
    rotationMatrix[3] = (sin(a * PI / 180));
    rotationMatrix[4] = (cos(a * PI / 180));
    translateImage();
}

void myWindow::graduationX(int scalx){
    scalingMatrix[0] = scalx/100.0;
    scalingMatrix[4] = sy->value()/100.0;
    translateImage();
}

void myWindow::graduationY(int scaly){
    scalingMatrix[4] = scaly/100.0;
    scalingMatrix[0] = sx->value()/100.0;
    translateImage();
}

void myWindow::sheringX(int shx){
    shXMatrix[1] = shx/100.0;
    translateImage();
}

void myWindow::sheringY(int shy){
    shYMatrix[3] = shy/100.0;
    translateImage();
}

//The source of translation
void myWindow::translateImage(){
    unsigned char *ptr1, *ptr2;
    ptr1 = img->bits();
    ptr2 = img1->bits();
    //The sequence of matixes
    moveToCordsBegining[2] = (-1.0) * ((wide/2.0) + 30);
    moveToCordsBegining[5] = (-1.0) * ((high/2.0) + 30);
    matrxMultipling_3x3(rotationMatrix, moveToCordsBegining);
    matrxMultipling_3x3(scalingMatrix, temp);
    matrxMultipling_3x3(shXMatrix, temp);
    matrxMultipling_3x3(shYMatrix, temp);
    moveToCordsBegining[2] = ((wide/2.0) + 30);
    moveToCordsBegining[5] = ((high/2.0) + 30);
    matrxMultipling_3x3(moveToCordsBegining, temp);
    matrxMultipling_3x3(translationMatrix, temp);

    //First seting picture on the screen
    copyImg(img, back);
    if(!(inverseMatrix->isChecked())){
        for(int i = 0; i < img1->height(); i++){
            for(int j = 0; j < img1->width(); j++){
                cordinatesVector[0] = imgX + j;
                cordinatesVector[1] = imgY + i;
                multiplingMatrix_X_Vector(resultTranslationMatrix, cordinatesVector);
                if (((int)round(resultVector[0]) >= 0) && ((int)round(resultVector[1]) >= 0) &&
                        ((int)round(resultVector[0]) < wide) && ((int)round(resultVector[1]) < high)){
                    ptr1[wide * 4 * (int)round(resultVector[1]) + 4 * (int)round(resultVector[0])] = ptr2[img1->width() * 4 * i + 4 * j];
                    ptr1[wide * 4 * (int)round(resultVector[1]) + 4 * (int)round(resultVector[0]) + 1] = ptr2[img1->width() * 4 * i + 4 * j + 1];
                    ptr1[wide * 4 * (int)round(resultVector[1]) + 4 * (int)round(resultVector[0]) + 2] = ptr2[img1->width() * 4 * i + 4 * j + 2];
                }
            }
        }
    } else {
        inversion();
    }
    update();
}

void myWindow::inversion(){
    unsigned char *ptr1, *ptr2;
    ptr1 = img->bits();
    ptr2 = img1->bits();

    //Temporary matrixes to use revers matrix
    double reverseRotation[9];
    double reverseScaling[9];
    double reverseShx[9];
    double reverseShy[9];
    double reverseTranslation[9];

    //Coping data to revers matrixes
    copyMatrix(reverseRotation, rotationMatrix);
    copyMatrix(reverseScaling, scalingMatrix);
    copyMatrix(reverseShx, shXMatrix);
    copyMatrix(reverseShy, shYMatrix);
    copyMatrix(reverseTranslation, translationMatrix);

    //Reversing matrixes
    reverseRotation[3] = ((-1.0) * rotationMatrix[3]);
    reverseRotation[1] = ((-1.0) * rotationMatrix[1]);
    reverseScaling[0] = 1.0/scalingMatrix[0];
    reverseScaling[4] = 1.0/scalingMatrix[4];
    reverseShx[1] = (-1.0) * shXMatrix[1];
    reverseShy[3] = (-1.0) * shYMatrix[3];
    reverseTranslation[2] = (-1.0) * translationMatrix[2];
    reverseTranslation[5] = (-1.0) * translationMatrix[5];


    //Making a generally reverse matrix
    moveToCordsBegining[2] = (-1.0) * ((wide/2.0) + 30);
    moveToCordsBegining[5] = (-1.0) * ((high/2.0) + 30);
    matrxMultipling_3x3(moveToCordsBegining, reverseTranslation);
    matrxMultipling_3x3(reverseShy, temp);
    matrxMultipling_3x3(reverseShx, temp);
    matrxMultipling_3x3(reverseScaling, temp);
    matrxMultipling_3x3(reverseRotation, temp);
    moveToCordsBegining[2] = ((wide/2) + 30);
    moveToCordsBegining[5] = ((high/2) + 30);
    matrxMultipling_3x3(moveToCordsBegining, temp);

    for(int i = 0; i < high; i++){
        for(int j = 0; j < wide; j++){
            cordinatesVector[0] = j;
            cordinatesVector[1] = i;
            multiplingMatrix_X_Vector(resultTranslationMatrix, cordinatesVector);
            if (((int)round(resultVector[1]) - imgY) > 0
                    && ((int)round(resultVector[1]) - imgY) < img1->height() - 1
                    && ((int)round(resultVector[0]) - imgX) > 0
                    && ((int)round(resultVector[0]) - imgX) < img1->width() - 1 ){
                if(interpolation->isChecked()){         //interpolation on
                    ptr1[wide * 4 * i + 4 * j] = interpolations(resultVector[0], resultVector[1], 0);
                    ptr1[wide * 4 * i + 4 * j + 1] = interpolations(resultVector[0], resultVector[1], 1);
                    ptr1[wide * 4 * i + 4 * j + 2] = interpolations(resultVector[0], resultVector[1], 2);
                } else {            //interpolation off
                    ptr1[wide * 4 * i + 4 * j] = ptr2[img1->width() * 4 * ((int)round(resultVector[1]) - imgY) + 4 * ((int)round(resultVector[0]) - imgX)];
                    ptr1[wide * 4 * i + 4 * j + 1] = ptr2[img1->width() * 4 * ((int)round(resultVector[1]) - imgY) + 4 * ((int)round(resultVector[0]) - imgX) + 1];
                    ptr1[wide * 4 * i + 4 * j + 2] = ptr2[img1->width() * 4 * ((int)round(resultVector[1]) - imgY) + 4 * ((int)round(resultVector[0]) - imgX) + 2];
                }
            }
        }
    }

}

int myWindow::interpolations(double x, double y, int option){           //make pixels smooth
    unsigned char *p;
    p = img1->bits();
    double a = x - floor(x);
    double b = ceil(y) - y;
    int leftPointsX = floor(x);
    int bottomPointsY = floor(y);
    int rightPointsX = ceil(x);
    int topPointsY= ceil(y);
    return  b * ((1 - a) * p[img1->width() * 4 * (bottomPointsY - imgY) + 4 * (leftPointsX - imgX) + option]
            + a * p[img1->width() * 4 * (bottomPointsY - imgY) + 4 * (rightPointsX - imgX) + option])
            + (1 - b) * ((1 - a) * p[img1->width() * 4 * (topPointsY - imgY) + 4 * (leftPointsX - imgX) + option]
            + a * p[img1->width() * 4 * (topPointsY - imgY) + 4 * (rightPointsX - imgX) + option]);
}

void matrxMultipling_3x3(double MA[], double MB[]){     //Multipling function for 3x3 matrixes
    double tmp;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            tmp = 0.0;
            for(int p = 0; p < 3; p++){
                tmp += MA[i * 3 + p] * MB[p * 3 + j];
                resultTranslationMatrix[i * 3 + j] = tmp;
            }
        }
    }
    copyMatrix(temp, resultTranslationMatrix);
}

void multiplingMatrix_X_Vector(double MA[], double MB[]){         //Multipling function for 3x1 matrixes
    double tmp;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 1; j++){
            tmp = 0;
            for(int p = 0; p < 3; p++){
                tmp += MA[i * 3 + p] * MB[p];
            }
        }
        resultVector[i] = tmp;
    }
}

void copyMatrix(double a[], double b[]){            //Coping matrixes
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            a[i * 3 + j] = b[i * 3 + j];
        }
    }
}

void writeValue(double matrix[], int rows, int columns) {     //Write matrix
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < columns; j++){
      std::cout << std::setw(12) << matrix[i * columns + j];
    }
    std::cout << std::endl;
  }
}

