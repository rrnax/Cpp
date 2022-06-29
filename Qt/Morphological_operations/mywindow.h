#include <QWidget>
#include <QApplication>
#include <QImage>
#include <QPainter>
#include <QPushButton>
#include <QGroupBox>
#include <QVBoxLayout>
class myWindow : public QWidget
{
    Q_OBJECT

public:
    myWindow(QWidget *parent = nullptr);
    ~myWindow();

    void copyImg(QImage *a, QImage *b);

    void printPixel(int x, int y,int color[3]);

    void white_Black(QImage *img);

private:
    QImage *img;
    QImage *backgrd;

    QPushButton *loadImg;
    QPushButton *dil;
    QPushButton *ero;
    QPushButton *open;
    QPushButton *close;

    QGroupBox *group;
    QVBoxLayout *layout;

    int wide;
    int high;
    int startX;
    int startY;
    int basicColor[3];
    int col[3];

private slots:
    void paintEvent(QPaintEvent*);
    void load_img();
    void dilatation();
    void erosion();
    void open_op();
    void close_op();
};
