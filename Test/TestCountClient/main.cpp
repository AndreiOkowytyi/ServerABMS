#include <QApplication>
#include "form.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Form object;
    object.show();

    return a.exec();
}
