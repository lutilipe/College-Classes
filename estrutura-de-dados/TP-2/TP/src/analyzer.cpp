#include <iostream>
#include <getopt.h>
#include "msgassert.h"
#include "wordVector.h"
#include "alphabeticOrder.h"
#include "utils.h"
#include <fstream>

using namespace std;

string logFilename,
    inputFile,
    outputFile;
int regMem = 0,
    minPartSize = 1,
    medianSize = 1;

const string ORDER_COMMAND = "#ORDEM";
const string TEXT_COMMAND = "#TEXTO";

void uso() {
    cout << "Analyzer\n" << endl;
    cout << "\t-h \t(comandos disponiveis)\n" << endl;
    cout << "\t-l \t(registrar acessos a memoria)\n" << endl;
    cout << "\t-p <arq>\t(arquivo de entrada da analise de memoria)\n" << endl;
    cout << "\t-i|I <arq>\t(arquivo de entrada)\n" << endl;
    cout << "\t-o|O <arq>\t(arquivo de saida)\n" << endl;
    cout << "\t-m|M \t(numero da mediana)\n" << endl;
    cout << "\t-s|S \t(tamanho minimo da particao para usar o QuickSort)\n" << endl;
}

int parseNullish(int in) {
    return in ? in : 1;
}

int getInputNumber(char* optarg) {
    try {
        return parseNullish(stoi(optarg));
    } catch (...) {
        return 1;
    }
}

template<class T>
void handleInput(ifstream* in, WordVector<T>* v, string* newOrder) {
    string currCommand = "";
    string next = "";

    while ((*in).peek() != EOF) {
        (*in) >> next;
        if (next[0] == '#') {
            currCommand = next;
            continue;
        }

        string tmp = stringToLowerCase(next);

        if (currCommand == ORDER_COMMAND) {
            (*newOrder) += tmp;
        } else {
            removeUnexpectedChars(&tmp);
            cout << tmp << endl;
        }
    }
}

template<class T>
void addWordToVector(WordVector<T>* v, T word) {
    int index = v->findIndex(word);
    if (index >= 0) {
        v[index] = v[index] + 1;
        return;
    }
    v->push(word);
}

void parse_args(int argc,char ** argv) {
    int c;

    while ((c = getopt(argc, argv, "hlm:s:p:o:i:I:O:S:M:")) != EOF) {
        int parsedArgValue = charToLowerCase(c);
        switch(parsedArgValue) {
            case 'i':
                inputFile = optarg;
                break;
            case 'o':
                outputFile = optarg;
                break;
            case 's':
                minPartSize = getInputNumber(optarg);
                break;
            case 'p':
                logFilename = optarg;
                break;
            case 'l':
                regMem = 1;
                break;
            case 'm':
                medianSize = getInputNumber(optarg);
                break;
            case 'h':
                uso();
                exit(1);
            default:
                uso();
                exit(1);
        }
    }

    erroAssert(inputFile.size() > 0,
        "Analyser - nome do arquivo de entrada precisa ser definido");
    erroAssert(outputFile.size() > 0,
        "Analyser - nome do arquivo de saida precisa ser definido");
}

int main(int argc, char ** argv) {
    parse_args(argc, argv);

    ifstream in = ifstream(inputFile);
    erroAssert(!in.fail(), "File not found");

    WordVector<int>* v = new WordVector<int>(medianSize, minPartSize);
    string newOrder = "";
    handleInput(&in, v, &newOrder);

    AlphabeticOrder order(newOrder);

    delete v;

    in.close();

    return 0;
}