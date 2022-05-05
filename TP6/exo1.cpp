#include "tp6.h"
#include <QApplication>
#include <time.h>

MainWindow* w = nullptr;

void Graph::buildFromAdjenciesMatrix(int **adjacencies, int nodeCount)
{
    /**
      * Make a graph from a matrix
      * first create all nodes, add it to the graph then connect them
      * this->appendNewNode
      * this->nodes[i]->appendNewEdge
      */

    for(int i=0; i<nodeCount; i++)
    {
        //appendNewNode(GraphNode* node) et GraphNode(int valeur) de graph.cpp
        this->appendNewNode(new GraphNode(i)); //l'indice i est la valeur du nouveau sommet
    }

    for(int i=0; i<nodeCount; i++)
    {
        for(int j=0; j<nodeCount; j++)
        {
            if(adjacencies[i][j]!=0){ //fonctionnerait sans cette condition mais c'est pas terrible d'avoir les arrêtes nulles
                                      //et le programme travaillerait pour rien
                //appendNewEdge(GraphNode* destination, int distance) de graph.cpp
                this->nodes[i]->appendNewEdge(this->nodes[j],adjacencies[i][j]);
            }
        }
    }
}

void Graph::deepTravel(GraphNode *first, GraphNode *nodes[], int &nodesSize, bool visited[])
{
    /**
      * Fill nodes array by travelling graph starting from first and using recursivity
      */
//    le print(v) de la consigne est remplacé par un tableau de nodes
//    v i s i t e d [ v . i n d e x ]= t r u e ;
//    f o r ( Edge e=v . f i r s t _ e d g e ; e != NULL ; e=e . n e x t )
//    {
//    i f (! v i s i t e d [ e . second_vertex . index ] )
//    deep_travel ( e . second_vertex , v i s i t e d ) ;
//    }

    nodes[nodesSize]=first;
    nodesSize++;

    visited[first->value]=true;

    for(Edge* e=first->edges; e!=nullptr; e=e->next)
    {
        if(!visited[e->destination->value])
        {
            deepTravel(e->destination, nodes, nodesSize, visited);
        }
    }

}

void Graph::wideTravel(GraphNode *first, GraphNode *nodes[], int &nodesSize, bool visited[])
{
    /**
     * Fill nodes array by travelling graph starting from first and using queue
     * nodeQueue.push(a_node)
     * nodeQueue.front() -> first node of the queue
     * nodeQueue.pop() -> remove first node of the queue
     * nodeQueue.size() -> size of the queue
     */
//        void wide_travel ( Vertex v e r t i c e s [ ] )
//        {
//        Queue q ;
//        bool v i s i t e d [ v e r t i c e s . s i z e ( ) ] ;
//        \\ i n i t a l l v i s i t e d t o f a l s e
//        q . push ( v e r t i c e s [ 0 ] ) ;
//        w h i l e ( ! q . empty ( ) )
//        {
//        V e r t e x v = q . pop ( ) ;
//        print (v) ;
    //        v i s i t e d [ v . index ] = true ;
    //        f o r ( Edge e=v . f i r s t _ e d g e ; e != NULL ; e=e . n e x t )
//        {
//        i f (! v i s i t e d [ e . second_vertex . index ] )
//        q . push ( e . s e c o n d _ v e r t e x ) ;
//        }
//        }
//        }

    std::queue<GraphNode*> nodeQueue;

    visited[first->value]=true;

    nodeQueue.push(first);

    while(nodeQueue.size()!=0)
    {
        nodes[nodesSize]=nodeQueue.front();
        nodeQueue.pop();
        nodesSize++;

        for(Edge* e=first->edges; e!=nullptr; e=e->next)
        {
            if(visited[e->destination->value]==false)
            {
                nodeQueue.push(e->destination);
                visited[e->destination->value]=true;
            }
        }
    }
}

bool Graph::detectCycle(GraphNode *first, bool visited[])
{
    /**
      Detect if there is cycle when starting from first
      (the first may not be in the cycle)
      Think about what's happen when you get an already visited node
    **/

    visited[first->value]=true;

    for(Edge* e=first->edges; e!=nullptr; e=e->next)
    {
        if(visited[e->destination->value]==true)
        {
            return true;
        }
        else if(detectCycle(e->destination, visited)==true)
        {
            return true;
        }
        visited[e->destination->value]=true;
    }

    return false;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow::instruction_duration = 150;
    w = new GraphWindow();
    w->show();

    return a.exec();
}
