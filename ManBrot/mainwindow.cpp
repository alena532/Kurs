#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QKeyEvent>
#include<QLabel>
#include <math.h>
#include<QGridLayout>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include <QAbstractButton>
#include<QPushButton>
#include<QLineEdit>
const double ZoomInFactor = 0.7;
const double ZoomOutFactor = 1 / ZoomInFactor;
const int ScrollStep = 20;

Fractal::Fractal(QWidget *parent) :
    QWidget(parent)

{
    minReal=-0.6778907;
    minImaginary=-0.120008;
    pixmapScale= 0.00403897;
    curScale=0.00403897;

   l = new QVBoxLayout();

   button=new QPushButton("Start");

   button->move(300,400);
   button->setFixedSize(100,50);

    label=new QLabel(this);
    QImage *i=new QImage("/Users/alenavorobej/Documents/qt/ManBrot/image");


    label->setPixmap(QPixmap::fromImage(*i));
    label->setAlignment(Qt::AlignCenter);


    l->addWidget(label);
    l->addWidget(button);

    setLayout(l);
    connect(button,&QPushButton::clicked,this,&Fractal::tempSlot);

    setWindowTitle("Fractal");

    setCursor(Qt::CrossCursor);

    resize(600, 500);

}

void Fractal::paintEvent(QPaintEvent * )
{
    QPainter painter(this);
painter.fillRect(rect(), Qt::white);
    if (pixmap.isNull()) {
      painter.setPen(Qt::black);

      QFont font = painter.font() ;

      font.setPointSize(25);

      painter.setFont(font);

    }

    if (qFuzzyCompare(curScale, pixmapScale)) {

        painter.drawPixmap(pixmapOffset, pixmap);

    } else {

        auto previewPixmap = qFuzzyCompare(pixmap.devicePixelRatioF(), qreal(1))
            ? pixmap
            : pixmap.scaled(pixmap.size() / pixmap.devicePixelRatioF(), Qt::KeepAspectRatio,
                            Qt::SmoothTransformation);
        double scaleFactor = pixmapScale / curScale;
        int newWidth = int(previewPixmap.width() * scaleFactor);
        int newHeight = int(previewPixmap.height() * scaleFactor);
        int newX = pixmapOffset.x() + (previewPixmap.width() - newWidth) / 2;
        int newY = pixmapOffset.y() + (previewPixmap.height() - newHeight) / 2;

        painter.save();
        painter.translate(newX, newY);
        painter.scale(scaleFactor, scaleFactor);

        QRectF exposed = painter.transform().inverted().mapRect(rect()).adjusted(-1, -1, 1, 1);
        painter.drawPixmap(exposed, previewPixmap, exposed);
        painter.restore();
    }

    if (!pixmap.isNull())
    {
        QString text = "You can scroll and zoom fractal ";
        painter.setPen(Qt::NoPen);
        painter.setPen(Qt::gray);
        painter.drawText(210,20,text);

    }

}

void Fractal::resizeEvent(QResizeEvent * )
{
    thread.render(minReal, minImaginary, curScale, size(), devicePixelRatioF());
}

void Fractal::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        zoom(ZoomInFactor);
        break;
    case Qt::Key_Minus:
        zoom(ZoomOutFactor);
        break;
    case Qt::Key_Left:
        scroll(-ScrollStep, 0);
        break;
    case Qt::Key_Right:
        scroll(+ScrollStep, 0);
        break;
    case Qt::Key_Down:
        scroll(0, -ScrollStep);
        break;
    case Qt::Key_Up:
        scroll(0, +ScrollStep);
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

void Fractal::wheelEvent(QWheelEvent *event)
{
    const int numDegrees = event->angleDelta().y() / 8;
    const double numSteps = numDegrees / double(15);
    zoom(pow(ZoomInFactor, numSteps));
}

void Fractal::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        lastDragPos = event->pos();
}

void Fractal::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        pixmapOffset += event->pos() - lastDragPos;
        lastDragPos = event->pos();
        repaint();
    }
}

void Fractal::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        pixmapOffset += event->pos() - lastDragPos;
        lastDragPos = QPoint();

        const auto pixmapSize = pixmap.size() / pixmap.devicePixelRatioF();
        int deltaX = (width() - pixmapSize.width()) / 2 - pixmapOffset.x();
        int deltaY = (height() - pixmapSize.height()) / 2 - pixmapOffset.y();
        scroll(deltaX, deltaY);
    }
}

void Fractal::updatePixmap(const QImage &image, double scaleFactor)
{
    if (!lastDragPos.isNull())
        return;

    pixmap = QPixmap::fromImage(image);
    pixmapOffset = QPoint();
    lastDragPos = QPoint();
    pixmapScale = scaleFactor;
    repaint();
}

void Fractal::zoom(double zoomFactor)
{
    curScale *= zoomFactor;
    repaint();
    thread.render(minReal, minImaginary, curScale, size(), devicePixelRatioF());
}

void Fractal::tempSlot()
{
    delete label;
    delete button;
    connect(&thread, &Render::renderedImage,
            this, &Fractal::updatePixmap);
}

void Fractal::scroll(int deltaX, int deltaY)
{

    minReal += deltaX * curScale;
    minImaginary += deltaY * curScale;
    repaint();
    thread.render(minReal, minImaginary, curScale, size(), devicePixelRatioF());
}

