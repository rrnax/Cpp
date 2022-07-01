#include <QWidget>
#include <QApplication>
#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <vector>
#include <QLabel>
#include <QGroupBox>
#include <QPoint>
#include <QSlider>
#include <QGridLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>

class myWindow : public QWidget
{
    Q_OBJECT

public:
    myWindow(QWidget *parent = 0);

    ~myWindow();

    void copyImg(QImage *a, QImage *b);

    void translateImage();

    void inversion();

    int interpolations(double x, double y, int option);

private:
    QImage *img;
    QImage *img1;
    QImage *back;
    QImage *toCompare;

    QPainter *scene;

    QPushButton *resetBt, *load;

    QLineEdit *path;

    QLabel *xlabel, *ylabel, *sxlabel, *sylabel, *obrotlabel, *shxlabel, *shylabel;

    QSlider *x, *y, *sx, *sy, *alpha, *shx, *shy;

    QCheckBox *inverseMatrix, *interpolation;

    QGroupBox *group;

    QGridLayout *layoutbox;

    QHBoxLayout *loadPath;

    int wide;
    int high;
    int startX;
    int startY;
    int basicColor[3];
    int bckc[3];
    int imgX;
    int imgY;

private slots:
    void paintEvent(QPaintEvent*);
    void translationX(int);
    void translationY(int);
    void rotation(int);
    void graduationX(int);
    void graduationY(int);
    void sheringX(int);
    void sheringY(int);
    void changingState(int);
    void reset();
    void loading();
};
