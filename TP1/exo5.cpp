#include "tp1.h"
#include <QApplication>
#include <time.h>

int isMandelbrot(Point z, int n, Point point){
    // check n
    if (n==0){
        return 0;
    }
    else {
        // check length of z
        if(sqrt(z.x*z.x+z.y*z.y)>2) {
            // if Mandelbrot, return 1 or n (check the difference)
            return n;
        }
        // otherwise, process the square of z and recall
        else {
            float temp=z.x;
            z.x=(z.x*z.x-z.y*z.y)+point.x;
            z.y=(2*temp*z.y)+point.y;
            return isMandelbrot(z , n-1, point);
        }
    }
}






int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w = new MandelbrotWindow(isMandelbrot);
    w->show();

    a.exec();
}
