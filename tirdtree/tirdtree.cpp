#include <iostream>
#include <stack>
#include <queue>
#include <cstring>

using namespace std;

template <class T>
class ArvoreNo
{
public:
    T valor;
    ArvoreNo<T> *left, *right;

    ArvoreNo(T v)
    {
        valor = v;
        left = right = nullptr;
    }
};

template <class T>
class Arvore
{
public:
    ArvoreNo<T> *raiz;

    Arvore()
    {
        raiz = nullptr;
    }

    bool isEmpty()
    {
        return (raiz == nullptr);
    }

    void inserirComRecursao(ArvoreNo<T> *&arv, ArvoreNo<T> *n)
    {
        if (arv == nullptr)
        {
            arv = n;
        }
        else
        {
            if (n->valor < arv->valor)
            {
                inserirComRecursao(arv->left, n);
            }
            else
            {
                inserirComRecursao(arv->right, n);
            }
        }
    }

    void removerNo(ArvoreNo<T> *&p, T valor)
    {
        if (p == nullptr)
        {
            return; // Nó não encontrado
        }

        if (valor < p->valor)
        {
            removerNo(p->left, valor);
        }
        else if (valor > p->valor)
        {
            removerNo(p->right, valor);
        }
        else
        {
            if (p->left == nullptr)
            {
                ArvoreNo<T> *temp = p->right;
                delete p;
                p = temp;
            }
            else if (p->right == nullptr)
            {
                ArvoreNo<T> *temp = p->left;
                delete p;
                p = temp;
            }
            else
            {
                ArvoreNo<T> *temp = removeMinimo(p->right);
                p->valor = temp->valor;
                delete temp;
            }
        }
    }

    ArvoreNo<T> *BuscaComRecursao(ArvoreNo<T> *p, T el)
    {
        if (p != nullptr)
        {
            if (el == p->valor)
            {
                return p;
            }
            else if (el < p->valor)
            {
                return BuscaComRecursao(p->left, el);
            }
            else
            {
                return BuscaComRecursao(p->right, el);
            }
        }
        return nullptr;
    }

    void montarArvoreExpressao(char *expressao)
    {
        stack<ArvoreNo<T> *> pilha;

        for (int i = 0; expressao[i]; i++)
        {
            if (isalpha(expressao[i]))
            {
                ArvoreNo<T> *novoNo = new ArvoreNo<T>(expressao[i]);
                pilha.push(novoNo);
            }
            else if (strchr("+-/*", expressao[i]))
            {
                if (!pilha.empty()) // Verifica se a pilha não está vazia
                {
                    ArvoreNo<T> *novoNo = new ArvoreNo<T>(expressao[i]);
                    novoNo->right = pilha.top();
                    pilha.pop();
                    if (!pilha.empty()) // Verifica se a pilha não está vazia
                    {
                        novoNo->left = pilha.top();
                        pilha.pop();
                    }
                    pilha.push(novoNo);
                }
                else
                {
                    // Tratar caso em que a pilha está vazia e não pode ser desempilhada
                    cout << "Erro: Pilha vazia durante a construção da árvore de expressão." << endl;
                    return; // Encerra a função prematuramente
                }
            }
        }

        if (!pilha.empty()) // Verifica se a pilha não está vazia
        {
            raiz = pilha.top();
        }
        else
        {
            // Tratar caso em que a pilha está vazia e não há nó raiz
            cout << "Erro: Pilha vazia após a construção da árvore de expressão." << endl;
        }
    }

    char *posfixa(char *e)
    {
        static char s[256]; // Para armazenar a expressão pós-fixa
        int j = 0;          // Índice para a string s

        stack<char> P; // Pilha para operadores

        for (int i = 0; e[i]; i++)
        {
            if (e[i] == '(')
            {
                P.push('(');
            }
            else if (isdigit(e[i])) /*else if(isalpha(e[i]))*/
            {
                s[j++] = e[i];
            }
            else if (strchr("+-/*", e[i]))
            {
                while (!P.empty() && prio(P.top()) >= prio(e[i]))
                {
                    s[j++] = P.top();
                    P.pop();
                }
                P.push(e[i]);
            }
            else if (e[i] == ')')
            {
                while (!P.empty() && P.top() != '(')
                {
                    s[j++] = P.top();
                    P.pop();
                }
                if (!P.empty() && P.top() == '(')
                {
                    P.pop(); // Desempilha '('
                }
            }
        }

        // Desempilhando os operadores restantes
        while (!P.empty())
        {
            s[j++] = P.top();
            P.pop();
        }

        s[j] = '\0'; // Adiciona terminador nulo à string s
        return s;
    }

    void percursoEmOrdem(ArvoreNo<T> *n)
    {
        if (n != nullptr)
        {
            percursoEmOrdem(n->left);  // Percurso no nó à esquerda
            cout << n->valor << " ";   // Visita o próprio nó
            percursoEmOrdem(n->right); // Percurso no nó à direita
        }
    }

private:
    int prio(char c)
    {
        if (c == '+' || c == '-')
            return 1;
        else if (c == '*' || c == '/')
            return 2;
        return 0; // Retornar 0 para outros caracteres (como parênteses)
    }
};

int main()
{
    Arvore<char> arvore;
    char infixa[] = "(9*9+9)*(7+7)";
    char *posfixa_resultado = arvore.posfixa(infixa);
    cout << "Expressão pós-fixa para " << infixa << " | " << posfixa_resultado << endl;

    arvore.montarArvoreExpressao(posfixa_resultado);
    cout << "Árvore de expressão montada." << endl;

    cout << "Percurso em ordem: ";
    arvore.percursoEmOrdem(arvore.raiz);
    cout << endl;

    cout << arvore.raiz << endl;

    return 0;
}
