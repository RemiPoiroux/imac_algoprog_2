#include <QApplication>
#include <time.h>

#include "tp2.h"

MainWindow* w = nullptr;

void selectionSort(Array& toSort)
{
    // selectionSort

    for (uint i=0; i<toSort.size(); i++)
    {
        uint minimum=i;

        for (uint j=i+1; j<toSort.size(); j++){
            if (toSort[j]<toSort[minimum])
            {
                minimum=j;
            }
        }
        uint temp=toSort[i];
        toSort[i]=toSort[minimum];
        toSort[minimum]=temp;

    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    uint elementCount=15; // number of elements to sort
    MainWindow::instruction_duration = 100; // delay between each array access (set, get, insert, ...)
    w = new TestMainWindow(selectionSort); // window which display the behavior of the sort algorithm
    w->show();

    return a.exec();
}
