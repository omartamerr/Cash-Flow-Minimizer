#include <iostream>
#include <cstring>
using namespace std;

class DebtGraph {
private:
    int** matrix;
    int size;

public:
    DebtGraph() : size(2) {
        matrix = new int* [size];
        for (int i = 0; i < size; i++) {
            matrix[i] = new int[size];
            memset(matrix[i], 0, size * sizeof(int));
        }
    }

    void addDebt(int lender, int borrower, double amount) {
        while (lender >= size || borrower >= size) {
            addSize();
        }
        matrix[lender][borrower] += amount;
    }

    void addSize() {
        int newSize = size + 1;
        int** newMatrix = new int* [newSize];
        for (int i = 0; i < newSize; i++) {
            newMatrix[i] = new int[newSize];
            memset(newMatrix[i], 0, newSize * sizeof(int));
        }
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                newMatrix[i][j] = matrix[i][j];
            }
        }
        for (int i = 0; i < size; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix = newMatrix;
        size = newSize;
    }

    void minimizeTransactions() {
        int* netBalance = new int[size];
        memset(netBalance, 0, size * sizeof(int));

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                netBalance[i] += matrix[j][i] - matrix[i][j];
            }
        }

        int* debtors = new int[size];
        int* creditors = new int[size];
        int debtorsCount = 0, creditorsCount = 0;

        for (int i = 0; i < size; i++) {
            if (netBalance[i] < 0) {
                debtors[debtorsCount++] = i;
            }
            else if (netBalance[i] > 0) {
                creditors[creditorsCount++] = i;
            }
        }

        int i = 0, j = 0;
        while (i < debtorsCount && j < creditorsCount) {
            int amount = min(-netBalance[debtors[i]], netBalance[creditors[j]]);
            cout << "Person " << debtors[i] << " pays Person " << creditors[j] << " $ " << amount << endl;
            netBalance[debtors[i]] += amount;
            netBalance[creditors[j]] -= amount;
            if (netBalance[debtors[i]] == 0) {
                i++;
            }
            if (netBalance[creditors[j]] == 0) {
                j++;
            }
        }

        delete[] netBalance;
        delete[] debtors;
        delete[] creditors;
    }

    void printGraph() const {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    void displayDebts() const {
        bool hasdebt = false;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (matrix[i][j] > 0) {
                    cout << "Lender " << i << " is owed $ " << matrix[i][j] << " by Borrower " << j << endl;
                    hasdebt = true;
                }
            }
        }
        if (!hasdebt) {
            cout << "No debts recorded.\n";
        }
    }


    ~DebtGraph() {
        for (int i = 0; i < size; i++)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

};

int main() {
    DebtGraph graph;
    int choice;


    do {
        cout << "\n------Debt Minimalizer---- - \n";
        cout << "1. Add debt\n";
        cout << "2. Print debt matrix\n";
        cout << "3. Display all debts\n";
        cout << "4. Minimize transactions\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int lender, borrower;
            double amount;
            cout << "Enter lender id: ";
            cin >> lender;
            cout << "Enter borrower id: ";
            cin >> borrower;
            cout << "Enter amount borrowed: ";
            cin >> amount;
            graph.addDebt(lender, borrower, amount);
            break;
        }
        case 2:
            cout << "\nCurrent Debt Matrix:\n";
            graph.printGraph();
            break;

        case 3:
            graph.displayDebts();
            break;
        case 4:
            cout << "Minimalize Transaction\n";
            graph.minimizeTransactions();
            break;
        case 5:
            cout << "Exit";
            break;
        default:
            cout << "Invalide choice.";
        }



    } while (choice != 5);
    return 0;

}