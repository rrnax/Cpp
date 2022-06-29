#include <QWidget>
#include <QApplication>
#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include <QGroupBox>

class MyWindow : public QWidget
{
    Q_OBJECT

public:
    MyWindow(QWidget *parent = nullptr);
    ~MyWindow();

    void copyImg(QImage *a, QImage *b);

    void ourLine(int a1, int b1, int a2, int b2);

    void part(int first, int second, int col[3]);

    void okrag();

    void takeColor(int x, int y, int color[3]);

    void floodFill();

    bool comparColors(int c1[3], int c2[3]);

    bool checkMargin(QPoint pt);

private:
    QImage *img;
    QImage *backgrd;

    QPoint point1;
    QPoint point2;

    QPushButton *odcinekButton;
    QPushButton *okragButton;
    QPushButton *wypelnienieButton;

    QGroupBox *grupa;

    int szer;
    int wys;
    int poczX;
    int poczY;
    int option;

    int c[3];


private slots:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void slot_odcinek();
    void slot_okrag();
    void slot_wypelnij();
};
