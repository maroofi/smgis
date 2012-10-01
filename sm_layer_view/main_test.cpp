#include <QApplication>
#include "sm_layer_view.h"


int main(int argc,char ** argv)
{
    QApplication app(argc,argv);

   SmLayerView a;
    QTreeView tree;
    tree.setModel(&a);
    tree.show();



    return app.exec();
}

