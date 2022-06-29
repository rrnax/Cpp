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

class myWindow : public QWidget
{
    Q_OBJECT

public:
    myWindow(QWidget *parent = 0);
    ~myWindow();

    void copyImg(QImage *a, QImage *b);

    void rysujKryzwa();

    void ourLine(int a1, int b1, int a2, int b2, int c[3]);

    void part(int first, int second,int c[3]);

    int znajdzPunkt(int x, int y);

    void printCircle(double r, QPoint tmp,int c[3]);

    void printPkt();

    QPoint splineRegule(double t, int pointPosition, std::vector<QPoint> pkt2);

private:
    QImage *img;
    QImage *backgrd;

    QPoint pierwszy;
    std::vector<QPoint> pkt;

    int szer;
    int wys;
    int poczX;
    int poczY;
    int x;
    int y;
    int zmiana;
    int basicColor[3];
    int bckc[3];

private slots:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

