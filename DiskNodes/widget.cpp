#include "widget.h"
#include "ui_widget.h"
#include <QTcpSocket>
#include "connectiondialog.h"
#include <QTextStream>
#include <QtCore>
#include <QtXml/QtXml>
#include <QtDebug>
#include <tinyxml2.h>
#include <string>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <stdlib.h>
#include <fstream>
#include <QFile>
#include <sstream>
#include <bitset>


using namespace tinyxml2;
using namespace std;
#define CADENA_VACIA ""

QString camino1 = "C:\\Users\\jmars\\Documents\\ProyectosQT\\Proyecto-3-TEC-File-System\\RAID\\DISK-NODE-1\\";
QString camino2 = "C:\\Users\\jmars\\Documents\\ProyectosQT\\Proyecto-3-TEC-File-System\\RAID\\DISK-NODE-2\\";
QString camino3 = "C:\\Users\\jmars\\Documents\\ProyectosQT\\Proyecto-3-TEC-File-System\\RAID\\DISK-NODE-3\\";
QString textoRecibido = "";
QString numero = "1";


/// Un nodo de arbol
struct Nodo{
    char dato;
    int frequiencia;
    Nodo *izquierda, *derecha;
};

/// Funcion para asignar un nuevo nodo del arbol
Nodo* getNode(char dato, int freq, Nodo* izq, Nodo* der){
    Nodo* nodo = new Nodo();

    nodo->dato = dato;
    nodo->frequiencia = freq;
    nodo->izquierda = izq;
    nodo->derecha = der;

    return nodo;
}

/// Objeto de comparacion que se utilizara para ordenar el monton
struct comparar{
    bool operator()(const Nodo* izquierda, const Nodo* derecha) const
    {
        ///El elemento más prioritario tiene la menor frecuencia
        return izquierda->frequiencia > derecha->frequiencia;
    }
};

///Función de utilidad para comprobar si el arbol Huffman contiene un solo nodo
bool esHoja(Nodo* root) {
    return root->izquierda == nullptr && root->derecha == nullptr;
}

///Recorrer el arbol Huffman y almacenar los Codigos Huffman en un mapa.
void codificar(Nodo* root, string str, unordered_map<char, string> &huffmanCode){
    if (root == nullptr) {
        return;
    }

    ///Se ha encontrado un nodo hoja
    if (esHoja(root)) {
        huffmanCode[root->dato] = (str != CADENA_VACIA) ? str : "1";
    }
    ///A la izquierda van los 0 y a la derecha van los 1.
    codificar(root->izquierda, str + "0", huffmanCode);
    codificar(root->derecha, str + "1", huffmanCode);
}

///Recorrer el arbol Huffman y decodificar la cadena codificada
void descodificar(Nodo* root, int &index, string str){
    if (root == nullptr) {
        return;
    }

    ///Se ha encontrado un nodo hoja
    if (esHoja(root))
    {
        cout << root->dato;
        return;
    }

    index++;

    if (str[index] == '0') {
        descodificar(root->izquierda, index, str);
    }
    else {
        descodificar(root->derecha, index, str);
    }
}

///Construye el arbol de Huffman y decodifica el texto de entrada dado
void arbolHuffman(string texto){
    ///caso base: cadena vacía
    if (texto == CADENA_VACIA) {
        return;
    }

    /// contar la frecuencia de aparición de cada caracter y almacenarlo en un mapa
    unordered_map<char, int> freq;
    for (char ch: texto) {
        freq[ch]++;
    }

    ///Crear una cola de prioridad para almacenar los nodos vivos del árbol Huffman
    priority_queue<Nodo*, vector<Nodo*>, comparar> pq;

    /// Crear un nodo hoja para cada personaje y añadirlo a la cola de prioridad.
    for (auto pair: freq) {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }

    ///Hacer hasta que haya más de un nodo en la cola
    while (pq.size() != 1)
    {
        // Eliminar los dos nodos de mayor prioridad (la frecuencia más baja) de la cola

        Nodo* izquierda = pq.top(); pq.pop();
        Nodo* derecha = pq.top();    pq.pop();

        /// Crear un nuevo nodo interno con estos dos nodos como hijos y
        /// con una frecuencia igual a la suma de las frecuencias de los dos nodos.
        /// Añade el nuevo nodo a la cola de prioridades.

        int sum = izquierda->frequiencia + derecha->frequiencia;
        pq.push(getNode('\0', sum, izquierda, derecha));
    }

    /// 'raiz' almacena el puntero a la raíz del árbol de Huffman
    Nodo* raiz = pq.top();

    /// Recorrer el árbol de Huffman y almacenar los códigos de Huffman en un mapa. Además, imprimirlos
    unordered_map<char, string> huffmanCode;
    codificar(raiz, CADENA_VACIA, huffmanCode);

    cout << "Los codigos Huffman son:\n" << endl;
    for (auto pair: huffmanCode) {
        cout << pair.first << " " << pair.second << endl;
    }

    cout << "\nLa cadena original es: " << texto << endl;

    ///Imprimir cadena codificada
    string str;
    for (char ch: texto) {
        str += huffmanCode[ch];
    }

    cout << "\nLa cadena codificada es: " << str << endl;
    cout << "\nLa cadena decodificada es: ";

    if (esHoja(raiz))
    {
        /// Caso especial: Para entradas como a, aa, aaa, etc.
        while (raiz->frequiencia--) {
            cout << raiz->dato;
        }
    }
    else {
        /// Recorrer el árbol Huffman de nuevo y esta vez decodificar la cadena codificada
        int index = -1;
        while (index < (int)str.size() - 1) {
            descodificar(raiz, index, str);
        }
    }
}

///
/// \brief Widget::Widget
/// \param parent
///
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mSocket = new QTcpSocket(this);

    XMLDocument doc;
    doc.LoadFile("C:/Users/jmars/Documents/ProyectosQT/Proyecto-3-TEC-File-System/DiskNodes/Infor.xml");

    auto xmlElement = doc.FirstChildElement("TECFS-Disk");
    auto headElement = xmlElement->FirstChildElement("Server");
    auto ipElement = headElement->FirstChildElement("Ip");
    auto portElement = headElement -> FirstChildElement ("Port");
    auto bodyElement = xmlElement->FirstChildElement("File");
    auto pElement1 = bodyElement -> FirstChildElement("Path1")->GetText();
    auto pElement2 = bodyElement -> FirstChildElement("Path2")->GetText();
    auto pElement3 = bodyElement -> FirstChildElement("Path3")->GetText();

    QString parse1 = QString::fromStdString(pElement1);
    QString parse2 = QString::fromStdString(pElement2);
    QString parse3 = QString::fromStdString(pElement3);

    mSocket->connectToHost(ipElement -> GetText(), portElement->FloatText());

    connect(mSocket, &QTcpSocket::readyRead, [&](){
        QTextStream T(mSocket);
        //auto text = T.readAll();
        textoRecibido = T.readAll();
        QFile file1(camino1 +"Archivo" + numero + ".txt");
        QFile file2(camino2 +"Archivo" + numero + ".txt");
        QFile file3(camino3 +"Archivo" + numero + ".txt");

        string cambiar = numero.toStdString();
        int aux = stoi(cambiar);
        aux++;
        cambiar = to_string(aux);
        numero = QString::fromStdString(cambiar);


        if (!file1.open(QIODevice::WriteOnly | QIODevice::Text))
            cout<<"no se que paso" << endl;

        ///En esta funcion se convierte el contenido del archivo de texto en
        ///una cadena de numeros binarios, con el fin de almacenar esta cadena
        ///en las diferentes carpetas del RAID

         string cadena = "";
         for (std::size_t i = 0; i < textoRecibido.toStdString().size(); ++i)
         {
             cout << bitset<8>(textoRecibido.toStdString().c_str()[i]) << endl;
             cadena += bitset<8>(textoRecibido.toStdString().c_str()[i]).to_string();
         }

         cout << cadena << endl;
         string aux1 = cadena;
         string aux2 = cadena;

        QTextStream archivo1(&file1);
        archivo1 << cadena.c_str();
        QTextStream archivo2(&file2);
        archivo2 << aux1.c_str();
        QTextStream archivo3(&file3);
        archivo3 << aux2.c_str();

//        cout << "textoRecibido: " << textoRecibido.toStdString() << endl;


        //descodificar(text.toStdString());
        ui->textEdit->append(textoRecibido);
    });



}

///
/// \brief Widget::~Widget
///
Widget::~Widget()
{
    delete ui;
}


void Widget::on_botonEnviar_clicked()
{
    XMLDocument doc;
    doc.LoadFile("C:/Users/jmars/Documents/ProyectosQT/Proyecto-3-TEC-File-System/DiskNodes/Infor.xml");

    auto xmlElement = doc.FirstChildElement("TECFS-Disk");
    auto headElement = xmlElement->FirstChildElement("Server");
    auto ipElement = headElement->FirstChildElement("Ip");
    auto portElement = headElement -> FirstChildElement ("Port");
    auto bodyElement = xmlElement->FirstChildElement("File");
    auto pElement1 = bodyElement -> FirstChildElement("Path1")->GetText();
    auto pElement2 = bodyElement -> FirstChildElement("Path2")->GetText();
    auto pElement3 = bodyElement -> FirstChildElement("Path3")->GetText();

    QString parse1 = QString::fromStdString(pElement1);
    QString parse2 = QString::fromStdString(pElement2);
    QString parse3 = QString::fromStdString(pElement3);

    QFile file1("C:\\Users\\jmars\\Documents\\ProyectosQT\\Proyecto-3-TEC-File-System\\RAID\\DISK-NODE-1\\prueba.txt");
    QFile file2(parse2 + "prueba.txt");
    QFile file3(parse3 + "prueba.txt");
    if (!file1.open(QIODevice::WriteOnly | QIODevice::Text))
        cout<<"no se que paso" << endl;

  QTextStream archivo1(&file1);
  archivo1 << textoRecibido.toStdString().c_str();
}
