#include "database.h"


int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    Database database;

    //set the font with form, big, and overstriking
    QFont font("A-OTF Musashino Std Regular", 12, 38);
    app.setFont(font);

    return app.exec();
}
