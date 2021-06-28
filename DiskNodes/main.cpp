#include "widget.h"

#include <QApplication>
#include <QtCore>
#include <QtXml/QtXml>
#include <QtDebug>
#include <tinyxml2.h>
#include <QFile>

#include <sstream>
#include <bitset>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*
     * En esta funcion se convierte el contenido del archivo de texto en
     * una cadena de numeros binarios, con el fin de almacenar esta cadena
     * en las diferentes carpetas del RAID
     */
    string myString = "osu! es un juego de clickear los circulos al ritmo de la musica";

      string cadena = "";
      for (std::size_t i = 0; i < myString.size(); ++i)
      {
          cout << bitset<8>(myString.c_str()[i]) << endl;
          cadena += bitset<8>(myString.c_str()[i]).to_string();
      }

      cout << cadena << endl;

      /*
      * Esta funcion es para pasar los datos almacenados en codigo binario
      * a un string normal, con la frase que fue previamente almacenada en el archivo
      * de texto del RAID
      */
      string data = cadena;
          stringstream sstream(data);
          string output;
          while(sstream.good())
          {
              bitset<8> bits;
              sstream >> bits;
              char c = char(bits.to_ulong());
              output += c;
          }

          cout << output << endl;


          /*
           * Esta funcion almacena los archivos de texto en los diferentes discos nodos
           * como corresponde
           */
        QFile file("C:\\Users\\Tutor\\OneDrive\\Documentos\\GitHub\\Proyecto-3-TEC-File-System\\RAID\\DISK-NODE-1\\prueba.txt");
          if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
              cout<<"no se que paso" << endl;

           QTextStream archivo(&file);

           archivo << cadena.c_str();

    a.setStyle("fusion");
    Widget w;
    w.show();

    return a.exec();
}
