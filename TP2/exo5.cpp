#include <QApplication>
#include <time.h>
#include "tp2.h"

MainWindow* w=nullptr;

void merge(Array& first, Array& second, Array& result);

void splitAndMerge(Array& origin)
{
    // stop statement = condition + return (return stop the function even if it does not return anything)
    if (origin.size()>1){

        // initialisation
        Array& first = w->newArray(origin.size()/2);
        Array& second = w->newArray(origin.size()-first.size());

        // split
        for (int i=0; i<first.size(); i++){
            first[i]=origin[i];
        }

        for (int i=0; i<second.size(); i++){
            second[i]=origin[i+first.size()];
        }

        // recursiv splitAndMerge of fisrtArray and secondArray
        splitAndMerge(first);
        splitAndMerge(second);

        // merge
        merge(first, second, origin);
}
}

void merge(Array& first, Array& second, Array& result)
{
    int parcourtFirst=0;
    int parcourtSecond=0;

    for (int i=0; i<result.size(); i++){

        if (parcourtFirst<first.size()){

            if (parcourtSecond<second.size()){

                if (first[parcourtFirst]<second[parcourtSecond]){
                    result[i]=first[parcourtFirst];
                    parcourtFirst++;
                }
                else{
                    result[i]=second[parcourtSecond];
                    parcourtSecond++;
                }
            }

            else {
                result[i]=first[parcourtFirst];
                parcourtFirst++;
            }
        }

        else{

            if (parcourtSecond<second.size()){
                result[i]=second[parcourtSecond];
                parcourtSecond++;
            }
        }
    }
}

void mergeSort(Array& toSort)
{
    splitAndMerge(toSort);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow::instruction_duration = 50;
    w = new TestMainWindow(mergeSort);
    w->show();

    return a.exec();
}
