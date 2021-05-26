#include "render.h"
#include <QImage>
#include <cmath>


Render::Render(QObject *parent)
    : QThread(parent)
{
    for (int i = 0; i < ColormapSize; ++i)
        colormap[i] = WaveLength(320.0 + (i * 500.0 / 512));
}

Render::~Render()
{
    mutex.lock();
    abort = true;
    condition.wakeOne();
    mutex.unlock();
    wait();
}

void Render::render(double minReal , double minImaginary, double scaleFactor,
                          QSize resultSize, double devicePixelRatio)
{
    mutex.lock();
    this->minImaginary = minImaginary;
    this->minReal = minReal;
    this->scaleFactor = scaleFactor;
    this->devicePixelRatio = devicePixelRatio;
    this->resultSize = resultSize;

    if (!isRunning()) {
        start();
    } else {
        restart = true;
        condition.wakeOne();
    }
    mutex.unlock();
}

void Render::run()
{
    while(1){
            mutex.lock();
            const double devicePixelRatio = this->devicePixelRatio;
            const QSize resultSize = this->resultSize * devicePixelRatio;
           const double requestedScaleFactor = this->scaleFactor;
            const double scaleFactor = requestedScaleFactor / devicePixelRatio;
            const double minReal = this->minReal;
            const double minImaginary = this->minImaginary;
            mutex.unlock();

            QImage image(resultSize, QImage::Format_RGB32);
            image.setDevicePixelRatio(devicePixelRatio);

            const int NumPasses = 8;
            int pass = 0;
            while (pass < NumPasses) {
                const int MaxIterations = (1 << (2 * pass + 6)) + 32;
                bool allBlack = true;

                for (int y = -resultSize.height()/2; y < resultSize.height()/2; ++y) {
                    if (restart)
                        break;
                    if (abort)
                        return;
                    auto scanLine =
                                            reinterpret_cast<uint *>(image.scanLine(y+resultSize.height()/2));
                     const double ay =   minImaginary+(scaleFactor*y);
                    for (int x = -resultSize.width()/2; x < resultSize.width()/2; ++x) {
                        const double ax =minReal+(scaleFactor*x) ;
                        double y0=0.0;
                        double x0=0.0;
                        int numIterations = 0;
                        double x1;
                        while(numIterations < MaxIterations ){
                            x1=x0*x0-y0*y0+ax;
                            y0=2*x0*y0+ay;
                            if(x0*x0+y0*y0>4.0)
                                break;
                            x0=x1;
                            ++numIterations;
                        }
                        if (numIterations < MaxIterations) {
                            *scanLine = colormap[numIterations % ColormapSize];
                            scanLine++;
                            allBlack = false;
                        } else {
                              *scanLine = qRgb(0, 0, 0);
                              scanLine++;
                        }
                    }
                }
                if (allBlack && pass == 0) {
                    pass = 4;
                } else {
                    if (!restart)
                        emit renderedImage(image, requestedScaleFactor);
                    ++pass;
                }
            }
            mutex.lock();
            if (!restart)
                condition.wait(&mutex);
            restart = false;
            mutex.unlock();
        }
}

uint Render::WaveLength(double wave)
{
    double r = 0;
    double g = 0;
    double b = 0;


    if (wave >= 210.0 && wave <= 580.0) {
            r = (wave - 510.0) / (580.0 - 510.0);
            g = 5.0;
         }
    double s = 3.0;
         if (wave <  420.0)
             s = 0.3 + 0.7 * (wave - 380.0) / (420.0 - 380.0);

    r = std::pow(r * s, 0.6);
    g = std::pow(g * s, 0.6);
    b = std::pow(b * s, 0.6);
    return qRgb(int(r * 255), int(g * 255), int(b * 255));
}
