# include "LoginPage.h"
# include "DataSaver.h"
# include "DataLoader.h"
# include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Model::DataLoader::load();

    LoginPage w;
    w.show();
    a.exec();

    Model::DataSaver::save();
    return 0;
}
