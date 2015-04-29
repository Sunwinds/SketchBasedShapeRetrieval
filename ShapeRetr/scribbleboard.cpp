#include <QtGui>

#include "scribbleboard.h"
#include <fstream>
#include <math.h>

using namespace std;


ScribbleBoard::ScribbleBoard(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    modified = false;
    scribbling = false;
    myPenWidth = 1;
    myPenColor = Qt::black;

}


bool ScribbleBoard::openImage(const QString &fileName)

{
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;

    QImage scalImg = loadedImage.scaled(500,400);
	QSize newSize = scalImg.size().expandedTo(size());
    resizeImage(&scalImg, newSize);
    image = scalImg;
    modified = false;
    update();
    return true;
}


bool ScribbleBoard::saveImage(const QString &fileName, const char *fileFormat)

{
    QImage visibleImage = image;
    resizeImage(&visibleImage, size());

    if (visibleImage.save(fileName, fileFormat)) {
        modified = false;
        return true;
    } else {
        return false;
    }
}


void ScribbleBoard::setPenColor(const QColor &newColor)

{
    myPenColor = newColor;
}


void ScribbleBoard::setPenWidth(int newWidth)

{
    myPenWidth = newWidth;
}


void ScribbleBoard::clearImage()

{
    image.fill(qRgb(255, 255, 255));
    modified = true;

    update();
}



void ScribbleBoard::mousePressEvent(QMouseEvent *event)

{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();

		scribbling = true;
    }
}

void ScribbleBoard::mouseMoveEvent(QMouseEvent *event)
{
	if ((event->buttons() & Qt::LeftButton) && scribbling){
        drawLineTo(event->pos());
	}
}

void ScribbleBoard::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        drawLineTo(event->pos());
		scribbling = false;
    }
}


void ScribbleBoard::paintEvent(QPaintEvent *event)

{
    QPainter painter(this);
    painter.drawImage(QPoint(0, 0), image);
}


void ScribbleBoard::resizeEvent(QResizeEvent *event)

{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}


void ScribbleBoard::drawLineTo(const QPoint &endPoint)

{
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}


void ScribbleBoard::resizeImage(QImage *image, const QSize &newSize)

{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}


void ScribbleBoard::print()
{
#ifndef QT_NO_PRINTER
    QPrinter printer(QPrinter::HighResolution);
 
    QPrintDialog *printDialog = new QPrintDialog(&printer, this);

    if (printDialog->exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = image.size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(image.rect());
        painter.drawImage(0, 0, image);
    }
#endif // QT_NO_PRINTER
}