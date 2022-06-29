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
#include <QComboBox>
#include <QGridLayout>
#include <QListWidget>

struct layer{
    std::string name;
    QImage *picture;
    double a;
    int mode;
};

class myWindow : public QWidget
{
    Q_OBJECT

public:
    myWindow(QWidget *parent = 0);

    ~myWindow();

    void updateLayers();

    void blend(QImage *background, layer foregraund, QImage *output);

    void copyImg(QImage *a, QImage *b);

    void fillImg(QImage *a, int color[3]);

    void printPixel(int x, int y, int *color, QImage *pic);

private:
    QImage *img;
    QImage *img1;
    QImage *img2;
    QImage *img3;
    QImage *back;

    std::vector<layer> layers;

    QLabel *txt1, *txt2, *txt3;
    QSlider *alpha;

    QListWidgetItem *item1, *item2, *item3;

    QGroupBox *group;
    QComboBox *box;
    QListWidget *list;

    QGridLayout *layoutbox;

    int wide;
    int high;
    int startX;
    int startY;
    int basicColor[3];
    int bckc[3];
    double a;

private slots:
    void paintEvent(QPaintEvent*);
    void realAlpha(int a);
    void clickTask(QListWidgetItem* item);
    void modeTask(int index);
};
