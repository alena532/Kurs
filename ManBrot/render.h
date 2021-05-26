#ifndef RENDER_H
#define RENDER_H

#include <QMutex>
#include <QSize>
#include <QThread>
#include <QWaitCondition>

class Render : public QThread
{
    Q_OBJECT

public:
    Render(QObject *parent = nullptr);
    ~Render();

    void render(double centerX, double centerY, double scaleFactor, QSize resultSize,
                double devicePixelRatio);

signals:
    void renderedImage(const QImage &image, double scaleFactor);

protected:
    void run() override;

private:
    static uint WaveLength(double wave);

    QMutex mutex;
    QWaitCondition condition;
    double minReal;
    double minImaginary;
    double scaleFactor;
    double devicePixelRatio;
    QSize resultSize;
    bool restart = false;
    bool abort = false;

    enum { ColormapSize = 512 };
    uint colormap[ColormapSize];
};


#endif // RENDER_H
