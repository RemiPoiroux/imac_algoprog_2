#include "tp4.h"
#include "mainwindow.h"

#include <QApplication>
#include <time.h>
#include <stdio.h>

MainWindow* w = nullptr;
using std::size_t;
using std::string;

int Heap::leftChild(int nodeIndex)
{
    return 2*nodeIndex+1;
}

int Heap::rightChild(int nodeIndex)
{
    return 2*nodeIndex+2;
}

void Heap::insertHeapNode(int heapSize, int value)
{
    // use (*this)[i] or this->get(i) to get a value at index i

    int i = heapSize;
    this->get(i)=value;

    while (i>0 && this->get(i) > this->get((i-1)/2))
    {
        int temp=this->get(i);
        this->get(i)=this->get((i-1)/2);
        this->get((i-1)/2)=temp;
        i=(i-1)/2;
    }

}

void Heap::heapify(int heapSize, int nodeIndex)
{
    int i_max=nodeIndex; //indice de la valeur la plus grande entre le nœud i et ses enfants

    int i_left=leftChild(nodeIndex);

    int i_right=rightChild(nodeIndex);


      if(i_right<heapSize && this->get(nodeIndex)<this->get(i_right))
      {
          if(this->get(i_right)<this->get(i_left))
          {
              i_max=i_left;
          }
          else
          {
              i_max=i_right;
          }
      }

      else if(i_left<heapSize && this->get(nodeIndex)<this->get(i_left))
      {
          if(i_right<heapSize && this->get(i_left)<this->get(i_right))
          {
              i_max=i_right;
          }
          else
          {
              i_max=i_left;
          }
      }


    if(i_max!=nodeIndex){
        int temp=this->get(i_max);
        this->get(i_max)=this->get(nodeIndex);
        this->get(nodeIndex)=temp;
        this->heapify(heapSize, i_max);
    }
}

void Heap::buildHeap(Array& numbers)
{
    for (int i=0 ; i<numbers.size(); i++){
        this->insertHeapNode(i,numbers[i]);
    }
}

void Heap::heapSort()
{
    for(int i=this->size()-1; i>0; i--)
        {
            int temp=this->get(0);
            this->get(0)=this->get(i);
            this->get(i)=temp;
            heapify(i,0);
        }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow::instruction_duration = 50;
    w = new HeapWindow();
    w->show();

    return a.exec();
}
