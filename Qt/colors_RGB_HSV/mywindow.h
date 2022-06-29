#include <QWidget>
#include <QApplication>
#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include <vector>
#include <QLabel>
#include <QGroupBox>
#include <QPoint>
#include <QSlider>
#include <QHBoxLayout>
#include <QGridLayout>
#include <cmath>

class myWindow : public QWidget
{
    Q_OBJECT

public:
    myWindow(QWidget *parent = 0);
    ~myWindow();

    void copyImg(QImage *a, QImage *b);

    void printPixel(int first, int second,int c[3]);

    void convertHSVtoRGB(double h, double s, double v, double c[3]);


private:
    QImage *img;
    QImage *backgrd;

    QPoint pierwszy;
    std::vector<QPoint> pkt;

    QSlider *sliderR, *sliderG, *sliderB;
    QSlider *sliderH, *sliderS, *sliderV;
    QLabel *txtR, *txtG, *txtB, *txtH, *txtS, *txtV;

    QGroupBox *group;
    QGroupBox *group2;

    int wide;
    int high;
    int startX;
    int startY;
    int x;
    int y;
    int zmiana;
    int basicColor[3];
    int bckc[3];

private slots:
    void paintEvent(QPaintEvent*);
    void constBlue(int val);
    void constGreen(int val);
    void constRed (int val);
    void constH (int val);
    void constS (int val);
    void constV (int val);
};
