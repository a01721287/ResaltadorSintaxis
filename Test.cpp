#include <iostream>
#include <string>
#include <unordered_map>
#include <regex>
#include <fstream>

using namespace std;

ifstream lectura("debuging.txt",ios::binary);       //Archivo a leer
ofstream escritura("index.html",ios::binary);       //Archivo Construido

unordered_map<std::string, std::string> umap = {        //UMAP para guardar las palabras reservadas
        {"define","palabra reservada define"},
        {"lambda","palabra reservada lambda"},
        {"if","palabra reservada if"},
        {"cond","palabra reservada cond"},
        {"else","palabra reservada else"},
        {"true","palabra reservada true"},
        {"false","palabra reservada false"},
        {"nil","palabra reservada nil"},
        {"car","palabra reservada car"},
        {"cdr","palabra reservada cdr"},
        {"cons","palabra reservada cons"},
        {"list","palabra reservada list"},
        {"apply","palabra reservada apply"},
        {"map","palabra reservada map"},
        {"let","palabra reservada let"},
        {"begin","palabra reservada begin"},
        {"null?","palabra reservada null?"},
        {"eq?","palabra reservada eq?"},
        {"set!","palabra reservada set!"}
};
//Funcion para validar identificadores
bool isID(string split){
    const regex expReg("[ ]*[a-zA-Z]\\w*");
    //La expresi�n \\w significa cualquier caracter (palabra) incluye mayusculas, minusculas, digitos y guion bajo
    return regex_match(split,expReg);
}
//Funcion para validad palabras reservadas
//En la implementacion solo se buscar la palabra en el UMAP
bool isPalabra(string split){
    for(int i=0;i<split.size();i++){
        if(split[i]!=' '){
            split = split.substr(i,split.size()-i);
            break;
        }
    }
    auto result = umap.find(split);
    if(result != umap.end()) return 1;
    else return 0;
}
//Funcion para validar constantes
//Documento tambien como diferenciar los diferentes tipos
bool isConst(string split){
    const regex expReg("[ ]*(|-)[0-9]+(|[.][0-9]+(|((e|E)(|-)[0-9]+)))");   //Cualquier Constante
    /* Esta parte es documentacion de los regex para diferenciar entre cada tipo de constante
    C�digo:
    const regex expRegEntero("[ ]*[0-9]+");                                 //Entero positivo
    const regex expRegNegativo("[ ]*(-)[0-9]+");                            //Entero negativo
    const regex expRegFlotante("[ ]*(|-)[0-9]+[.][0-9]+");                  //Flotante con o sin signo
    const regex expRegExponent("[ ]*(|-)[0-9]+[.][0-9]+(e|E)(|-)[0-9]+");   //Constante con exponente con o sin signo
    Nota:
    En caso de querer generar tokens distintos para cada tipo de constante, se puede cambiar el tipo de la funcion
    isConst, para que retorne un entero diferente segun la expresion con la que haya dado match, lo cual en la practica
    significaria que corresponden a un diferente token.
    */
    return regex_match(split,expReg);
}
//Reconoce agrupa las funciones de validacion, tomando con prioridad la de palabras reservadas
void reconoce(string &sp, bool &dif_esp){
    if(isPalabra(sp))   escritura<<"\t\t<span class=\"palabra\">"<<sp<<"</span>"<<endl;
    else if(isID(sp))   escritura<<"\t\t<span class=\"id\">"<<sp<<"</span>"<<endl;
    else if(isConst(sp))    escritura<<"\t\t<span class=\"const\">"<<sp<<"</span>"<<endl;
    else                escritura<<"\t\t<span class=\"syntax\">"<<sp<<"</span>"<<endl;
    sp="";
    dif_esp=false;
}
