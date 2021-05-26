#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPixmap>
#include <QWidget>
#include "render.h"
#include<QPushButton>
#include<QGridLayout>
#include<QHBoxLayout>
#include<QLabel>
#include<QLineEdit>
#include<QVBoxLayout>
class Fractal : public QWidget
{
    Q_OBJECT

public:
    Fractal(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void updatePixmap(const QImage &image, double scaleFactor);
    void zoom(double zoomFactor);
    void tempSlot();

private:
    void scroll(int deltaX, int deltaY);

     QPushButton *button;
     QVBoxLayout *l;
     QHBoxLayout *l2;

      QLabel *mytxt;
     QImage *i;
     QLabel *label;
    Render thread;
    QPixmap pixmap;
    QPoint pixmapOffset;
    QPoint lastDragPos;
    double minReal;
    double minImaginary;
    double pixmapScale;
    double curScale;
};
#endif // MAINWINDOW_H
