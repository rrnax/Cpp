#include <QWidget>
#include <QApplication>
#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <QPoint>

class myWindow : public QWidget
{
    Q_OBJECT

public:
    myWindow(QWidget *parent = nullptr);
    ~myWindow();

    void copyImg(QImage *a, QImage *b);

    void printLine(int x1, int y1, int x2, int y2, int color[3]);

    void printPixel(int x, int y,int color[3]);

    void drawInsideFigure();

private:
    QImage *img;
    QImage *backgrd;

    QPoint tmp;
    std::vector<QPoint> peak;

    int wide;
    int high;
    int startX;
    int startY;
    int x;
    int y;
    int basicColor[3];
    int col[3];

private slots:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};
