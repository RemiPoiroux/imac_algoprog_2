#include <QApplication>
#include <QString>
#include <time.h>
#include <stdio.h>
#include <string>

#include <tp5.h>

MainWindow* w = nullptr;
using std::size_t;
using std::string;


std::vector<string> TP5::names(
{
    "Yolo", "Anastasiya", "Clement", "Sirine", "Julien", "Sacha", "Leo", "Margot",
    "JoLeClodo", "Anais", "Jolan", "Marie", "Cindy", "Flavien", "Tanguy", "Audrey",
    "Mr.PeanutButter", "Bojack", "Mugiwara", "Sully", "Solem",
    "Leo", "Nils", "Vincent", "Paul", "Zoe", "Julien", "Matteo",
    "Fanny", "Jeanne", "Elo"
});

unsigned long int hash(string key)
{
    // return an unique hash id from key
    unsigned long int id=0;

    int index=0;
    for(int i=key.size()-1; i>=0; i--)
    {
        //On utilise les  premiers charactères encodés en Ascii
        //Ainsi on hash avec ascii(charac1)*128^(size-1)+...+ascii(derniercharac)*128⁰
        //ce qui permettra de retrouver chaque charactere avec des divisions euclidiennes succéssives par 128^i
        id+=(int)key[index]*pow(128,i);
        index++;
    }

    return id;
}

struct MapNode : public BinaryTree
{

    string key;
    unsigned long int key_hash;

    int value;

    MapNode* left;
    MapNode* right;

    MapNode(string key, int value) : BinaryTree (value)
    {
        this->key = key;
        this->value = value;
        this->key_hash = hash(key);

        this->left = this->right = nullptr;
    }

    /**
     * @brief insertNode insert a new node according to the key hash
     * @param node
     */
    void insertNode(MapNode* node)
    {
        if(node->key_hash < this->key_hash)
        {
            if (this->left)
            {
                this->left->insertNode(node);
            }
            else
            {
                this->left=node;
            }
        }
        else
        {
            if (this->right)
            {
                this->right->insertNode(node);
            }
            else
            {
                this->right=node;
            }
        }
    }

    void insertNode(string key, int value)
    {
        this->insertNode(new MapNode(key, value));
    }

    virtual ~MapNode() {}
    QString toString() const override {return QString("%1:\n%2").arg(QString::fromStdString(key)).arg(value);}
    Node* get_left_child() const {return left;}
    Node* get_right_child() const {return right;}
};

struct Map
{
    Map() {
        this->root = nullptr;
    }

    /**
     * @brief insert create a node and insert it to the map
     * @param key
     * @param value
     */
    void insert(string key, int value)
    {
        if(this->root)
        {
            this->root->insertNode(key,value);
        }
        else{
            this->root=new MapNode(key, value);
        }
    }

    /**
     * @brief get return the value of the node corresponding to key
     * @param key
     * @return
     */
    int get(string key)
    {
        unsigned long int id=hash(key);

        MapNode* current=this->root;
        while(current!=nullptr){
            if(current->key_hash==id)
            {
                return current->value;
            }
            else if(current->key_hash > id)
            {
                current=current->left;
            }
            else
            {
                current=current->right;
            }
        }

        return 0;
    }

    MapNode* root;
};


int main(int argc, char *argv[])
{
    srand(time(NULL));
    Map map;

    map.insert("Yolo", 20);
    for (std::string& name : TP5::names)
    {
        if (rand() % 3 == 0)
        {
            map.insert(name, rand() % 21);
        }
    }

    printf("map[\"Margot\"]=%d\n", map.get("Margot"));
    printf("map[\"Jolan\"]=%d\n", map.get("Jolan"));
    printf("map[\"Lucas\"]=%d\n", map.get("Lucas"));
    printf("map[\"Clemence\"]=%d\n", map.get("Clemence"));
    printf("map[\"Yolo\"]=%d\n", map.get("Yolo"));
    printf("map[\"Tanguy\"]=%d\n", map.get("Tanguy"));


    QApplication a(argc, argv);
    MainWindow::instruction_duration = 200;
    w = new MapWindow(*map.root);
    w->show();
    return a.exec();
}
