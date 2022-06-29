#include "mywindow.h"

myWindow::myWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Alpha Blending");
    resize(1000, 500);

    layer temp;

    wide = 640;
    high = 426;
    startX = 30;
    startY = 30;
    basicColor[0] = 0;
    basicColor[1] = 0;
    basicColor[2] = 0;

    img = new QImage(wide, high, QImage::Format_RGB32);
    fillImg(img,basicColor);

    img1 = new QImage("traf.jpg");
    temp.name = "traf.jpg";
    temp.a = 1;
    temp.mode = 0;
    temp.picture = img1;
    layers.push_back(temp);

    img2 = new QImage("hamb.jpg");
    temp.name = "hamb.jpg";
    temp.a = 1;
    temp.mode = 0;
    temp.picture = img2;
    layers.push_back(temp);

    img3 = new QImage("fast.jpg");
    temp.name = "fast.jpg";
    temp.a = 1;
    temp.mode = 0;
    temp.picture = img3;
    layers.push_back(temp);

    back = new QImage(wide, high, QImage::Format_RGB32);
    temp.name = "back";
    temp.a = 1;
    temp.mode = 0;
    temp.picture = back;
    layers.push_back(temp);

    txt1 = new QLabel("Blending: ");
    txt2 = new QLabel("Alpha: ");
    txt3 = new QLabel("Layer: ");
    alpha = new QSlider(Qt::Horizontal, this);
    alpha->setMinimum(0);
    alpha->setMaximum(100);

    group = new QGroupBox("Panel", this);
    group->setGeometry(QRect(700, 10, 260, 445));

    box = new QComboBox();
    box->addItem("Normal mode");
    box->addItem("Multiply mode");
    box->addItem("Screen mode");
    box->addItem("Overlay mode");
    box->addItem("Darken mode");
    box->addItem("Lighten mode");

    list = new QListWidget(this);
    item1 = new QListWidgetItem(tr("traf.jpg"), list);
    item2 = new QListWidgetItem(tr("hamb.jpg"), list);
    item3 = new QListWidgetItem(tr("fast.jpg"), list);

    layoutbox = new QGridLayout;
    layoutbox->addWidget(txt1, 0, 0);
    layoutbox->addWidget(box, 0, 1);
    layoutbox->addWidget(txt2, 1, 0);
    layoutbox->addWidget(alpha, 1, 1);
    layoutbox->addWidget(txt3, 2, 0);
    layoutbox->addWidget(list, 2, 1);

    group->setLayout(layoutbox);

    connect(list,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(clickTask(QListWidgetItem*)));
    connect(alpha,SIGNAL(valueChanged(int)),this,SLOT(realAlpha(int)));
    connect(box,SIGNAL(currentIndexChanged(int)),this,SLOT(modeTask(int)));

    updateLayers();
    list->setCurrentItem(item1);
}

myWindow::~myWindow()
{
     delete img3;
}

void myWindow::paintEvent(QPaintEvent*)
{
    QPainter picture(this);
    picture.drawImage(startX, startY, *img);

}


void myWindow::fillImg(QImage *a, int color[3])
{
    unsigned char *img1;
    img1 = a->bits();
    for(int i = 0; i < high; i++)
    {
        for(int j = 0; j < wide; j++)
        {
            img1[wide * 4 * i + 4 * j] = color[0];
            img1[wide * 4 * i + 4 * j + 1] = color[1];
            img1[wide * 4 * i + 4 * j + 2] = color[2];
        }
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

void myWindow::printPixel(int x, int y, int *color, QImage *pic){
    unsigned char *ptr;
    ptr = pic->bits();
    if ((x >= 0) && (y >= 0) && (x <= wide) && (y <= high)){
        ptr[wide * 4 * y + 4 * x] = color[0];
        ptr[wide * 4 * y + 4 * x + 1] = color[1];
        ptr[wide * 4 * y + 4 * x + 2] = color[2];
    }
}

void myWindow::realAlpha(int a){
    double alp = (double)a/100.0;
    QListWidgetItem *item = list->currentItem();
    for(int i = 0; i < (int)layers.size(); i++){
        if(layers.at(i).name == item->text().toStdString()){
            layers.at(i).a = alp;
            updateLayers();
        }
    }
}

void myWindow::clickTask(QListWidgetItem* item){
    for(int i = 0; i < (int)layers.size(); i++){
        if(layers.at(i).name == item->text().toStdString()){
            alpha->setValue(layers.at(i).a * 100);
            box->setCurrentIndex(layers.at(i).mode);
            //copyImg(img, layers.at(i).picture);
            updateLayers();
        }
    }
}

void myWindow::modeTask(int index){
    QListWidgetItem *item = list->currentItem();
    for(int i = 0; i < (int)layers.size(); i++){
        if(layers.at(i).name == item->text().toStdString()){
            layers.at(i).mode = index;
            updateLayers();
        }
    }
}

void myWindow::updateLayers(){
    for(int i = (int)layers.size() - 1; i >= 0; i--){
        blend(img, layers.at(i), img);
        update();
    }
}

void myWindow::blend(QImage *background, layer foregraund, QImage *output){
    unsigned char *back, *fore;
    back = background->bits();
    fore = foregraund.picture->bits();
    for(int i = 0; i < high; i++)
    {
        for(int j = 0; j < wide; j++)
        {
            int result[3];
            switch (foregraund.mode) {
            case 0:
                result[0] = (foregraund.a * fore[wide * 4 * i + 4 * j]) +
                        ((1.0 - foregraund.a) * back[wide * 4 * i + 4 * j]);
                result[1] = (foregraund.a * fore[wide * 4 * i + 4 * j + 1]) +
                        ((1.0 - foregraund.a) * back[wide * 4 * i + 4 * j + 1]);
                result[2] = (foregraund.a * fore[wide * 4 * i + 4 * j + 2]) +
                        ((1.0 - foregraund.a) * back[wide * 4 * i + 4 * j + 2]);
                break;
            case 1:
                result[0] = (fore[wide * 4 * i + 4 * j] * back[wide * 4 * i + 4 * j]) >> 8;
                result[1] = (fore[wide * 4 * i + 4 * j + 1] * back[wide * 4 * i + 4 * j + 1]) >> 8;
                result[2] = (fore[wide * 4 * i + 4 * j + 2] * back[wide * 4 * i + 4 * j + 2]) >> 8;
                break;
            case 2:
                result[0] = 255 - (((255 - fore[wide * 4 * i + 4 * j]) * (255 - back[wide * 4 * i + 4 * j])) >> 8);
                result[1] = 255 - (((255 - fore[wide * 4 * i + 4 * j + 1]) * (255 - back[wide * 4 * i + 4 * j + 1])) >> 8);
                result[2] = 255 - (((255 - fore[wide * 4 * i + 4 * j + 2]) * (255 - back[wide * 4 * i + 4 * j + 2])) >> 8);
                break;
            case 3:
                if(fore[wide * 4 * i + 4 * j] < 128){
                     result[0] = (fore[wide * 4 * i + 4 * j] * back[wide * 4 * i + 4 * j]) >> 7;
                } else {
                     result[0] = 255 - (((255 - fore[wide * 4 * i + 4 * j]) * (255 - back[wide * 4 * i + 4 * j])) >> 7);
                }
                if(fore[wide * 4 * i + 4 * j + 1] < 128){
                    result[1] = (fore[wide * 4 * i + 4 * j + 1] * back[wide * 4 * i + 4 * j + 1]) >> 7;
                } else {
                    result[1] = 255 - (((255 - fore[wide * 4 * i + 4 * j + 1]) * (255 - back[wide * 4 * i + 4 * j + 1])) >> 7);
                }
                if(fore[wide * 4 * i + 4 * j + 2] < 128){
                    result[2] = (fore[wide * 4 * i + 4 * j + 2] * back[wide * 4 * i + 4 * j + 2]) >> 7;
                } else {
                    result[2] = 255 - (((255 - fore[wide * 4 * i + 4 * j + 2]) * (255 - back[wide * 4 * i + 4 * j + 2])) >> 7);
                }
                break;
            case 4:
                if(fore[wide * 4 * i + 4 * j] < back[wide * 4 * i + 4 * j]){
                    result[0] = fore[wide * 4 * i + 4 * j];
                } else {
                    result[0] = back[wide * 4 * i + 4 * j];
                }
                if(fore[wide * 4 * i + 4 * j + 1] < back[wide * 4 * i + 4 * j + 1]){
                    result[1] = fore[wide * 4 * i + 4 * j + 1];
                } else {
                    result[1] = back[wide * 4 * i + 4 * j + 1];
                }
                if(fore[wide * 4 * i + 4 * j + 2] < back[wide * 4 * i + 4 * j + 2]){
                    result[2] = fore[wide * 4 * i + 4 * j + 2];
                } else {
                    result[2] = back[wide * 4 * i + 4 * j + 2];
                }
                break;
            case 5:
                if(fore[wide * 4 * i + 4 * j] > back[wide * 4 * i + 4 * j]){
                    result[0] = fore[wide * 4 * i + 4 * j];
                } else {
                    result[0] = back[wide * 4 * i + 4 * j];
                }
                if(fore[wide * 4 * i + 4 * j + 1] > back[wide * 4 * i + 4 * j + 1]){
                    result[1] = fore[wide * 4 * i + 4 * j + 1];
                } else {
                    result[1] = back[wide * 4 * i + 4 * j + 1];
                }
                if(fore[wide * 4 * i + 4 * j + 2] > back[wide * 4 * i + 4 * j + 2]){
                    result[2] = fore[wide * 4 * i + 4 * j + 2];
                } else {
                    result[2] = back[wide * 4 * i + 4 * j + 2];
                }
                break;
            }
            printPixel(j, i, result, output);
        }
    }
}



