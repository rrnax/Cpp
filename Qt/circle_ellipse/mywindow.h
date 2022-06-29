#include <QWidget>
#include <QApplication>
#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include <QGroupBox>
#include <QSlider>
#include <QLabel>

class myWindow : public QWidget
{
    Q_OBJECT

public:
    myWindow(QWidget *parent = 0);
    ~myWindow();

    void part(int first, int second);

    void copyImg(QImage *a, QImage *b);

    void ourLine(int a1, int b1, int a2, int b2);

private:
    QImage *img;
    QImage *backgrd;

    QSlider *slider;
    QLabel *txt;

    QGroupBox *group;

    int szer;
    int wys;
    int poczX;
    int poczY;
    int x1;
    int x2;
    int y1;
    int y2;

    int amountPoints;

    bool which;



private slots:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void value(int val);
};

