#include <QWidget>
#include <QApplication>
#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <QPoint>
#include <QCheckBox>
#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>

class myWindow : public QWidget
{
    Q_OBJECT

public:
    myWindow(QWidget *parent = nullptr);
    ~myWindow();

    //Declarations
    void copyImg(QImage *a, QImage *b);

    void printLine(int x1, int y1, int x2, int y2, int color[3], QImage *pic);

    void printPixel(int x, int y,int color[3], QImage *pic);

    void markPoint(QPoint p, QImage *pic);

    void printCircle(double r, QPoint tmp, int c[3], QImage *pic);

    int findPoint(int x, int y, std::vector<QPoint> vertices);

    void writeTiangle();

    void barycentricCordinates(int x,int y, int color[3]);

    void scanLine(std::vector<QPoint> v);

    int interpolations(double x, double y, int option, QImage *img);

private:

    //Images
    QImage *imgRight;
    QImage *backgrd;
    QImage *picture;
    QImage *imgLeft;

    QGroupBox *group;

    QGridLayout *layoutBox;

    QCheckBox *interpolation;

    QLineEdit *path;

    QPushButton *reset, *load;

    //peak and edges
    QPoint pressCordinates;
    std::vector<QPoint> peaksTo, peaksFrom;

    //global varibles in class
    int wide;
    int high;
    int startX;
    int startY;
    int x;
    int y;
    int textureColor[3];
    int col[3];

    //State of chosen triangels
    int changeLeftTriangle;
    int changeRightTriangle;

private slots:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent * event);
    void changingState();
    void clear();
    void loadNewImage();
};
