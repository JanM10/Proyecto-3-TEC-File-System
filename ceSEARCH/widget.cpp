#include "widget.h"
#include "ui_widget.h"
#include <QTcpSocket>
#include <QTextStream>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include <string>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <stdlib.h>
#include <fstream>

using namespace std;
#define CADENA_VACIA ""
string texto = "";
string comprimido = "";

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
        ///Eliminar los dos nodos de mayor prioridad (la frecuencia más baja) de la cola

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
    comprimido = str;
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

//    connect(mSocket, &QTcpSocket::readyRead, [&](){
//        QTextStream T(mSocket);
//        auto text = T.readAll();
//        ui->textoBuscado->append(text);
//    });
    QString hostname = "localhost";
    quint16 puerto = 3333;

    mSocket->connectToHost(hostname,puerto);
}

///
/// \brief Widget::~Widget
///
Widget::~Widget()
{
    delete ui;
}

//void Widget::on_Enviar_clicked()
//{
//    QTextStream T(mSocket);
//    T << ui->Nickname->text() << ": " << ui->Message->text();
//    mSocket->flush();
//    ui->Message->clear();


//}

//void Widget::on_Conectar_clicked()
//{
//    ConnectionDialog D(this);
//    if(D.exec() == QDialog::Rejected){
//        return;
//    }
//    mSocket->connectToHost(D.hostname(),D.port());
//}

///Abre el explorador de archivos para poder abrir el archivo que se desee
void Widget::on_botonBuscar_clicked()
{
    QString filter = "All File (*.*) ;; Text File (*.txt) ;; XML File (*.xml)";
    QString nombre_archivo = QFileDialog::getOpenFileName(this,"open a file","C://",filter);
    QFile archivo(nombre_archivo);

    if(!archivo.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "title", "file not open");
    }
    QTextStream in(&archivo);
    QString texto = in.readAll();
    ui->textoBuscado->setPlainText(texto);
    archivo.close();
}

///Sube la infromacion del archivo de texto que ha sido cargado
void Widget::on_botonSubir_clicked()
{
    QTextStream T(mSocket);
    string texto2 = ui->textoBuscado->toPlainText().toStdString();
    arbolHuffman(texto2);
    QString qstr = QString::fromStdString(comprimido);
    cout << "\nTEXTO: " << qstr.toStdString() << endl;
    T << "Cliente: " << qstr;
    mSocket->flush();
    ui->textoBuscado->clear();
}


///Busca la palabra ingresada
void Widget::on_botonBuscar2_clicked()
{
    string texto = ui->buscarTexto->text().toStdString();
    cout << texto << endl;
}

///Devuelve el archivo que se haya seleccionado
void Widget::on_botonMostrar_clicked()
{

}


