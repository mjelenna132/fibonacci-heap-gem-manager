
#include <iostream>
#include<queue>
#include <fstream>
#include <sstream>
using namespace std;

class Node {
public:
    Node* left;
    Node* right;
    Node* father;
    Node* leftSon;
    int degree;
    int info;

    Node(int value) : left(nullptr), right(nullptr), father(nullptr), leftSon(nullptr), degree(0), info(value) {}
};

class FibonacciHeap {
public:
    FibonacciHeap(int type) : head(nullptr), extremeValue(nullptr), heapType(type), n(0) {}
    void levelOrder() {
        if (head == nullptr) {
            cout << " PRAZNA VRECA " << endl;
            return;
        }

        queue<Node*> q;
        Node* temp = head;

       
        

        do {
            q.push(temp);
            temp = temp->right;
        } while (temp != head);

        int nivo = 0;
        cout << "--- Nivo " << nivo++ << " ---" << endl;

        while (!q.empty()) {
            int levelSize = q.size();
            while (levelSize--) {
                Node* current = q.front();
                q.pop();

                cout << (current == extremeValue ? "EKSTREMNA VREDNOST " : "Vrednost ")
                    << current->info
                    << " (parent: "
                    << (current->father ? current->father->info : 0)
                    << ") ";

                if (current->leftSon) {
                    Node* child = current->leftSon;
                    do {
                        q.push(child);
                        child = child->right;
                    } while (child != current->leftSon);
                }
            }

            if (!q.empty()) {
                cout << "\n--- Nivo " << nivo++ << " ---" << endl;
            }
        }

        cout << endl;
    }



    ~FibonacciHeap() {
        if (head == nullptr) return;

        queue<Node*> q;
        Node* temp = head;

        // Dodaj sve čvorove na nivou 0 (korenski nivo)
        do {
            q.push(temp);
            temp = temp->right;
        } while (temp != head);

        q.push(nullptr); // Dodaj nullptr kao granicnik za novi nivo

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            if (current == nullptr) {
                // Kada naiđemo na nullptr, znači da smo završili trenutni nivo
                if (!q.empty()) {
                    q.push(nullptr); // Dodaj nullptr za sledeći nivo
                }
            }
            else {
                
               
                // Ako postoji levi sin, stavljamo njega i svu braću u red
                if (current->leftSon) {
                    Node* child = current->leftSon;
                    do {
                        q.push(child);
                        child = child->right;
                    } while (child != current->leftSon);
                }
                // Brisemo cvor
                delete current;
            }
        }
        head = nullptr;
        extremeValue = nullptr;

        // Vrati head na null;
        //Extreme value null?


    }
    void insert(int value) {
        n++;
        Node* add = new Node(value);
        if (!this->head) {
            this->head = add;
            add->left = add->right = add;
            this->extremeValue = add;
        }
        else {
            Node* temp = extremeValue->left;
            temp->right = add;
            add->left = temp;
            add->right = extremeValue;
            extremeValue->left = add;
            if (extremeValue == head) {
                head = add;
            }
            if ((isMax() && add->info > extremeValue->info) ||
                    (isMin() && (add->info < extremeValue->info))) {
                    this->extremeValue = add;
            }
        }
    }

    void consolidate() {
        if (head == nullptr) {
        extremeValue=nullptr;
            cout << "Obrisali ste poslednji element u vreci" << endl;
            return;
        }
        const int maxDeg = 20;
        vector<Node*> degreeTable(maxDeg, nullptr);
        Node* current = this->head;
        int deg, flag1=1, greenLight=0;
   
        while(flag1)
        {
            
            deg = current->degree;
           
            if (!degreeTable[deg]) {
                degreeTable[deg] = current;
                if (head == nullptr) {
                    greenLight = 0;
                }
                if (current == head) {
                    //NE UDJE JER MI CURRENT 5 A HEAD 17
                    greenLight = 0;
                    if (head->left == head->right && head->left == head) {
                        head = nullptr;
                    }
                    else {
                        current->left->right = current->right;
                        current->right->left = current->left;
                        head = current->right;
                        current->right = current->left=current;

                    }
                    
                }
                //umesto green light proveri samo da li je head nullptr

                //GRESKA PROVERI I U DRUGOM DELU

                if (!head && !greenLight) {
// NISAM SIGURNA
                    flag1 = 0;
                    //17 DODA JOS JEDNOM VISKA
                }
     
                current = head;
            }
            else {
                Node* first, * second;
                first = current;
                second = degreeTable[deg];
                //&& current->left!=nullptr && current->right!=nullptr
                if (current == head ) {//Ako ga brisemo da ga izbacimo iz liste
                    current->left->right = current->right;
                    current->right->left = current->left;
                    if (head->right == head->left && head->left == head) {
                        head = nullptr;
                    }
                    else {
                        head = first->right;
                       
                    }
                    current->left->right = current->right;
                    current->right->left = current->left;
                }
                if ((isMax() && second->info > first->info) || (isMin() && second->info < first->info)) {
                    if (!second->leftSon) {
                        second->leftSon = first;
                        first->father = second;
                        
                        first->left = first->right = first;
                    }
                    else {
                        /*if (!greenLight) {
// DA PROVERIM OVDE AKO NIJE GREEN LIGHT I AKO JE HEAD->NEXT=HEAD->RIGHT;
                            head = first->right;
                        }  //MOZES ZA OBA DA IZVUCES GORE I MOZE IF CURRENT=HEAD?
                        */
                        
                        Node* firstSon, * lastSon;
                        firstSon = second->leftSon;
                        lastSon = second->leftSon->left;
                        first->right = firstSon;
                        first->left = lastSon;
                        firstSon->left = first;
                        lastSon->right = first;
                        second->leftSon = first;
                        first->father = second;

                        
                    }
                
                    second->degree++;
                    current = second;


                }
                else {
                    if (!first->leftSon) {
                        first->leftSon = second;
                        second->father = first;
                        second->left = second->right = second;
                    }
                    else {
                        
                      
                        Node* firstSon, * lastSon;
                        firstSon = first->leftSon;
                        lastSon = first->leftSon->left;
                        second->right = firstSon;
                        second->left = lastSon;
                        firstSon->left = second;
                        lastSon->right = second;
                        first->leftSon = second;
                        second->father = first;
                       
                    }
                    
                
                    first->degree++;
                    //pregazim 10 30 sa 17 2
                    
                    
                    current = first;
                    //first->left = first->right = nullptr;
                   
                }

                degreeTable[deg] = nullptr;
                
               
                greenLight = 1;
                

            }
          

        }  //LOS USLOV
       
       // prevezi sve sad iz pomocnog niza;
        extremeValue = nullptr;
        for (Node* node : degreeTable) {
            
            if (node) {
           
                if (!extremeValue) {
                    head = node;
                    node->left = node->right = node;
                    extremeValue = node;
                }
                else {
                    node->left = head->left;
                    node->right = head;
                    head->left->right = node;
                    head->left = node;
                    if ((isMax() && node->info > extremeValue->info) || (isMin() && node->info < extremeValue->info)) {
                        extremeValue = node;
                    }
                }
            }
        }

    }
    void deleteExtreme() {
        if (!head) {
            cout << "Vreca je prazna ne postoje elementi za brisanje" << endl;
            return;
        } 
        n--;
        //ako brises bez dece onda prevezi samo ako ima decu izvuci manji/veci
        Node* left, *right, *temp;
        temp = this->extremeValue;
        left = temp->left;
        right = temp->right;
        // Ako nema decu
        
        if (!temp->leftSon) {
            if (left == right && right == temp) {
                head = nullptr;

            }
            else {
                left->right = right;
                right->left = left;
                if (temp == head) {
                    head = right;
                }
            }
            
          
        }
        else {
          
         
            Node* Fson = temp->leftSon;
            Node* Lson = Fson->left;
            Node* help = Fson->right;
            //nece da udje ako ima jednog sina
            Fson->father = nullptr;
            while(help!=Fson) {
                help->father = nullptr;
                help = help->right;
            } //da li ce da radi 
            if (left == right && right == temp) {
                Fson->left = Lson;
                Lson->right = Fson;
            }
            else {
                left->right = Fson;
                Lson->right = right;
                Fson->left = left;
                right->left = Lson;
            }

            if (temp == head) {
                head = Fson;
            }
            
        }
        delete temp;
        if (head == nullptr) {
            extremeValue = nullptr;
            return; // ništa ne pozivaš dalje ako je struktura prazna
        }

        consolidate();
        
        // Spajanje zatim trazimo novi min/max
    }
    static void merge(FibonacciHeap* blue, FibonacciHeap* red) {
        FibonacciHeap* in, * out;
        
        if (red->n > blue->n) {
            in = red;
            out = blue;
        }
        else {
            in = blue;
            out = red;
        }
        while (out->n > 0) {
            in->insert(out->extremeValue->info);
            out->deleteExtreme();
        }
        
        ///ne treba head1 na head2 da vezemo jer je jedan heap min a drugi max morali bi da okrecemo
        /*Node* inFirst, * inLast, * outFirst, * outLast;
        // Spajanje hipova
        inFirst = in->head, inLast = in->head->left, outFirst = out->head, outLast = out->head->left;
        inFirst->left = outLast;
        outLast->right = inFirst;
        inLast->right = outFirst;
        outFirst->left = inLast;
        // Azuriranje heapa 
        if ((out->extremeValue->info < in->extremeValue->info && in->isMin()) || (out->extremeValue->info > in->extremeValue->info && in->isMax())) {
            in->extremeValue=out->extremeValue;
        }
        in->n += out->n;
        // Azuriranje obrisanog heapa
        out->n = 0;
        out->head = nullptr;
        out->extremeValue = nullptr; */
    }
    bool isEmpty() {
        if (!head) return true;
        return false;
    }
private:
    Node* head;
    Node* extremeValue;
    int heapType; // 1 for min-heap, 2 for max-heap
    int n;

    bool isMin() {
        return heapType == 1;
    }

    bool isMax() {
        return heapType == 2;
    }
};

int main() {
    int choice;
    FibonacciHeap *minHeap, *maxHeap;
    minHeap = nullptr;
    maxHeap = nullptr;
    bool made = false;
    do {
        cout << "=== Meni ===" << endl;
        cout << "1. Kupovina plave i crvene vrece za igraca " << endl; // Stvaranje praznih hipova
        cout << "2. Poklanjanje plave i crvene vrece siromasnima" << endl; // Brisanje hipova
        cout << "3. Dodavanje novog dragulja u vrecu" << endl;
        cout << "4. Dohvatanje dragulja iz odgovaracuje vrece" << endl;
        cout << "5. Prebacivanje svih dragulja u jednu vrecu" << endl;
        cout << "6. Pretres na granici" << endl; // Ispis
        cout << "7. Komande iz fajla" << endl;
        cout << "0. Izlaz" << endl;
        cout << "Izaberite opciju: ";

        cin >> choice;

        switch (choice) {

        case 1: {
            minHeap=new FibonacciHeap(1); // Create a min-heap
            maxHeap= new FibonacciHeap(2); // Create a max-heap
            made = true;
            cout << "Fibonacci Heap created!" << endl;
        }
              break;
        case 2: {
            if (made) {
                delete minHeap;
                delete maxHeap;
                minHeap = nullptr;
                maxHeap = nullptr;
            }
            else {
                cout << "Niste napravili" << endl;
            }
        }
              break;
        case 3: {
            if (made) {

                int value, choice;
                
                cout << "Unesite 1 za mojsanit, 2 za dijamant: " << endl;
                cin >> choice;
                if (choice == 1) {
                    cout << "UNESITE VREDNOST MOJSANITA: " << endl;
                    cin >> value;
                    minHeap->insert(value);
                }
                else if (choice == 2) {
                    cout << "UNESITE VREDNOST DIJAMANTA: " << endl;
                    cin >> value;
                    maxHeap->insert(value);
                }
                else {
                    cout << "GRESKA, trebali ste da unesete 1 za mojsanit ili 2 za dijamant" << endl;
                }


                
            }
            else {
                cout << "Niste napravili" << endl;
            }
        }
              break;
        case 4: { //brisanje
            if (made) {
                minHeap->deleteExtreme();
            }
            else {
                cout << "Niste napravili" << endl;
            }
        }
              break;
        case 5: {
            if (made) {
                FibonacciHeap::merge(maxHeap, minHeap);
                //obrisi iz jednog dodaj u drugi
            }
            else {
                cout << "Niste napravili" << endl;
            }

        }
        case 6: {
            if (made) {
                minHeap->levelOrder();
            }
            else {
                cout << "Niste napravili" << endl;
            }
        }
              break;
        case 7: {
            ifstream file("Commands10.txt"); // Otvaranje fajla za čitanje
            if (!file) {
                cerr << "Greska pri otvaranju fajla!" << endl;
                return 1;
            }

            char komanda;
            int vrednost;

            while (file >> komanda) {
               
                switch (komanda) {
                case 'V':
                    //cout << "// Kupovina plave i crvene vreće" << endl;
                     minHeap = new FibonacciHeap(1);
                     maxHeap = new FibonacciHeap(2);
                     made = true;
                    cout << "Vrece su kupljenje!" << endl;
                    break;
                case 'B':
                    //cout << "// Poklanjanje plave i crvene vreće" << endl;
                    if (made) {
                        delete minHeap;
                        delete maxHeap;
                        minHeap = nullptr;
                        maxHeap = nullptr;
                    }
                    else {
                        cout << "Niste napravili" << endl;
                    }
                    break;
                case 'D':
                    //POSLE
                   
                case 'M':
                    //POSLE
                    
                case 'R': {
                    string line;
                    getline(file, line); // Učitavamo ostatak reda
                    stringstream ss(line);
                    char bracket;
                    ss >> bracket >> vrednost; // Očekujemo format [x]

                    if (bracket == '[') {
                        if (komanda == 'D') {
                            maxHeap->insert(vrednost);

                        } 
                            //cout << "// Pronalaženje dijamanta vrednosti " << vrednost << endl;
                        else if (komanda == 'M'){
                           
                            minHeap->insert(vrednost);
                        }

                            //cout << "// Pronalaženje mojsanita vrednosti " << vrednost << endl;
                        else if (komanda == 'R'){
                            for (int i = 0; i < vrednost; i++)
                            {
                                if (maxHeap->isEmpty()) break;
                                maxHeap->deleteExtreme();
                            }
                            

                        }
                          
                    }
                    else {
                        cout << "// Pogrešan format komande" << endl;
                    }
                    break;
                }
                case 'T':
                    //cout << "// Nailazak na putujućeg trgovca oružja" << endl;
                    if (made) {
                        maxHeap->deleteExtreme();
                    }
                    else {
                        cout << "Niste napravili" << endl;
                    }
                    break;
                case 'P':
                    //cout << "// Nailazak na putujućeg pekara" << endl;
                    if (made) {
                        minHeap->deleteExtreme();
                    }
                    else {
                        cout << "Niste napravili" << endl;
                    }
                    break;
                case 'G':
                    //cout << "// Nailazak na granični prelaz" << endl;
                    if (made) {
                        cout << " CRVENA VRECA " << endl;
                        minHeap->levelOrder();
                        cout << " PLAVA VRECA " << endl;
                        maxHeap->levelOrder();
                        cout << endl;
                    }
                    else {
                        cout << "Niste napravili" << endl;
                    }
                    break;
                case 'L':
                    //cout << "// Nailazak na lopova" << endl;
                    if (made) {
                        FibonacciHeap::merge(maxHeap, minHeap);
                        //obrisi iz jednog dodaj u drugi
                    }
                    else {
                        cout << "Niste napravili" << endl;
                    }
                    break;
                default:
                    cout << "// Nepoznata komanda" << endl;
                }
            }

            file.close();
             
                  
        }
              break;
        case 0: {
            cout << "Kraj programa<<endl";
            return 0;
        }
        default:
            cout << "Nepravilan izbor, pokusajte ponovo." << endl;
            break;
        }
    } while (choice != 0);
    

    return 0;
}
/*
* 
* V – Куповина плаве и црвене вреће. 
• B – Поклањање плаве и црвене вреће. 
• D[x] – Проналажење дијаманта чија је вредност x. 
• M[x] – Проналажење мојсанита чија је вредност x. 
• T – Наилазак на путујућег трговца оружја. 
• P – Наилазак на путујућег пекара. 
• G – Наилазак на гранични прелаз. 
• L – Наилазак на лопова. 
• R[k] – Наилазак на ретког трговца који захтева k драгуља.
*/