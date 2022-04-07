//Actividad Integradora: Resaltador de Sintaxis
//El siguiente codigo incluye un resaltado de Sintaxis para el lenguaje de programacion C++
//Hecho por:
//Jose Miguel Beltrán Cinco A00227714
//Alejandro Hernández A01721287
//Ricardo Garza A01197406
//Octavio Augusto Alemán Esparza A01660702
//Erick Daniel Padilla Verdugo A01740287
//Para la Materia de Implementacion de Metodos computacionales.
#include <iostream>
#include <string>
#include <unordered_map>
#include <regex>
#include <fstream>

using namespace std;
ifstream lectura("debuging.txt", ios::binary);       //Archivo a leer
ofstream escritura("index.html", ios::binary);       //Archivo Construido

unordered_map<std::string, std::string> umap = {        //UMAP para guardar las palabras reservadas
        {"program","tk_program"},
        {"begin","tk_begin"},
        {"read","tk_read"},
        {"var","tk_var"},
        {"int","tk_int"},
        {"integer","tk_int"},
        {"float","tk_float"},
        {"real","tk_real"},
        {"end","tk_end"},
        {"write","tk_write"},
        {"print","tk_print"},
        {"pause","tk_pause"},
        {"none","tk_none"}
};
//Funcion para validar identificadores
bool isID(string split) {
    const regex expReg("[ ]*[a-zA-Z]\\w*");
    //La expresin \\w significa cualquier caracter (palabra) incluye mayusculas, minusculas, digitos y guion bajo
    return regex_match(split, expReg);
}
//Funcion para validad palabras reservadas
//En la implementacion solo se buscar la palabra en el UMAP
bool isKeyword(string split) {
    for (int i = 0; i < split.size(); i++) {
        if (split[i] != ' ') {
            split = split.substr(i, split.size() - i);
            break;
        }
    }
    auto result = umap.find(split);
    if (result != umap.end()) return 1;
    else return 0;
}
//Funcion para validar constantes
//Documento tambien como diferenciar los diferentes tipos
bool isConst(string split) {
    const regex expReg("[ ]*(|-)[0-9]+(|[.][0-9]+(|((e|E)(|-)[0-9]+)))");   //Cualquier Constante
    /* Esta Regex Indica la busqueda de Entero Positivo, Entero negativo, Flotante con o sin signo y flotante con exponente con o sin signo
    */
    return regex_match(split, expReg);
}
//Reconoce agrupa las funciones de validacion, tomando con prioridad la de palabras reservadas
void reconoce(string& sp, bool& dif_esp) {
    if (isKeyword(sp))   escritura << "\t\t<span class=\"Keyword\">" << sp << "</span>" << endl;
    else if (isID(sp))   escritura << "\t\t<span class=\"id\">" << sp << "</span>" << endl;
    else if (isConst(sp))    escritura << "\t\t<span class=\"const\">" << sp << "</span>" << endl;
    else                escritura << "\t\t<span class=\"syntaxError\">" << sp << "</span>" << endl;
    sp = "";
    dif_esp = false;
}
//Escribe el inicio del HTML
void iniciohtml() {
    escritura <<
        "<!DOCTYPE html>\n" <<
        "<html>\n" <<
        "    <head>\n" <<
        "        <meta charset=\"utf-8\"/>\n" <<
        "        <title>Resaltador de Sintaxix</title>\n" <<
        "        <link rel=\"stylesheet\" href=\"estilos.css\">\n" <<
        "    </head>\n" <<
        "    <body>\n";
}
//Escribe el final del HTML
void finalhtml() {
    escritura <<
        "    </body>\n" <<
        "</html>\n";
}
int main()
{
    string linea;
    iniciohtml();
    //Se abren cada una de las lineas en el documento de lectura
    while (getline(lectura, linea)) {
        string sp;
        bool dif_esp = 0;
        sp = "";
        for (int i = 0; i < linea.size(); i++) {    //Para cada caracter en la linea, se hace un append para formar una string "split"
            bool append = true;
            char c = linea[i];
            string aux(1, c);
            /*En terminos generales, al llegar a algun delimitador, se reconoce lo que llevamos escrito,
            formamos un token para el delimitador y reiniciamos las variables a su estado inicial*/
            switch (c) {
            case ';':
                if (dif_esp) {
                    reconoce(sp, dif_esp);
                }
                escritura << "\t\t<span class=\"com\">" << linea.substr(i, linea.size() - i) << "</span>" << endl;
                i = linea.size();
                sp = "";
                break;
                //Revisar Caso de Salto de linea
            case ' ':
                if (dif_esp) {
                    reconoce(sp, dif_esp);
                }
                break;
            case '(':
            case ')':
                if (dif_esp) {
                    reconoce(sp, dif_esp);
                }
                sp.append(aux);
                escritura << "\t\t<span class=\"op\">" << sp << "</span>" << endl;
                dif_esp = false;
                append = false;
                sp = "";
                break;
            case '<':
                if (dif_esp) {
                    reconoce(sp, dif_esp);
                }
                sp.append(aux);
                escritura << "\t\t<span class=\"op\">" << sp << "</span>" << endl;
                dif_esp = false;
                append = false;
                sp = "";
                break;
            case '>':
                if (dif_esp) {
                    reconoce(sp, dif_esp);
                }
                sp.append(aux);
                escritura << "\t\t<span class=\"op\">" << sp << "</span>" << endl;
                dif_esp = false;
                append = false;
                sp = "";
                break;
            case '=':
                if (dif_esp) {
                    reconoce(sp, dif_esp);
                }
                sp.append(aux);
                escritura << "\t\t<span class=\"op\">" << sp << "</span>" << endl;
                dif_esp = false;
                append = false;
                sp = "";
                break;
            case ',':
                if (dif_esp) {
                    reconoce(sp, dif_esp);
                }
                sp.append(aux);
                escritura << "\t\t<span class=\"op\">" << sp << "</span>" << endl;
                dif_esp = false;
                append = false;
                sp = "";
                break;
            case '-':
                if (i < linea.size() - 1 && c == '-') {
                    if (linea[i + 1] == '0' | linea[i + 1] == '1' | linea[i + 1] == '2' | linea[i + 1] == '3' | linea[i + 1] == '4' | linea[i + 1] == '5' | linea[i + 1] == '6' | linea[i + 1] == '7' | linea[i + 1] == '8' | linea[i + 1] == '9')
                        break;
                }
            case '+':
                if (dif_esp) {
                    reconoce(sp, dif_esp);
                }
                sp.append(aux);
                escritura << "\t\t<span class=\"op\">" << sp << "</span>" << endl;
                dif_esp = false;
                append = false;
                sp = "";
                break;
            case '/':
                if (dif_esp) {
                    reconoce(sp, dif_esp);
                }
                sp.append(aux);
                escritura << "\t\t<span class=\"op\">" << sp << "</span>" << endl;
                dif_esp = false;
                append = false;
                sp = "";
                break;
            case '*':
                if (sp.size() == 0) {
                    sp.append(aux);
                    escritura << "\t\t<span class=\"op\">" << sp << "</span>" << endl;
                    append = false;
                    sp = "";
                }
                else if (sp[sp.size() - 1] == ' ') {
                    sp.append(aux);
                    escritura << "\t\t<span class=\"syntaxError\">" << sp << "</span>" << endl;
                    append = false;
                    sp = "";
                }
                break;
            default:
                dif_esp = true;
            }
            if (append)sp.append(aux);
        }
        if (sp.size() > 1) {
            reconoce(sp, dif_esp);
        }
        escritura << "\t\t<br>" << endl;        //Tras terminar de leer la linea, genera salto de linea
    }
    finalhtml();
    return 0;
}
