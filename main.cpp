#include <iostream>
#include <string>
using namespace std;

// ── Entity 1: Task ───────────────────────────────────────────
struct Task {
    int    id;
    string name;
    bool   done;
};

// ── Entity 2: TaskManager ────────────────────────────────────
struct TaskManager {
    Task tasks[100];
    Task undoBuf[100];   // deleted tasks (undo stack)
    int  count    = 0;
    int  undoTop  = 0;
    int  nextId   = 1;

    // 1. Add
    void add(const string& name) {
        tasks[count++] = {nextId++, name, false};
        cout << "Added (ID " << nextId-1 << ")\n";
    }

    // 2. Delete
    void del(int id) {
        for (int i = 0; i < count; i++) {
            if (tasks[i].id == id) {
                undoBuf[undoTop++] = tasks[i];
                for (int j = i; j < count-1; j++) tasks[j] = tasks[j+1];
                count--;
                cout << "Deleted ID " << id << "\n";
                return;
            }
        }
        cout << "ID not found\n";
    }

    // 3. Undo
    void undo() {
        if (undoTop == 0) { cout << "Nothing to undo\n"; return; }
        tasks[count++] = undoBuf[--undoTop];
        cout << "Restored last deleted task\n";
    }

    // 4. Show
    void show() {
        if (count == 0) { cout << "(empty)\n"; return; }
        for (int i = 0; i < count; i++)
            cout << "[" << tasks[i].id << "] "
                 << (tasks[i].done ? "[DONE] " : "[    ] ")
                 << tasks[i].name << "\n";
    }

    // 5a. Linear Search
    void linearSearch(int id) {
        for (int i = 0; i < count; i++)
            if (tasks[i].id == id) { cout << "Found: " << tasks[i].name << "\n"; return; }
        cout << "Not found\n";
    }

    // 5b. Binary Search (sorts first)
    void binarySearch(int id) {
        // sort by id (insertion sort — simple)
        for (int i = 1; i < count; i++) {
            Task key = tasks[i]; int j = i-1;
            while (j >= 0 && tasks[j].id > key.id) { tasks[j+1] = tasks[j]; j--; }
            tasks[j+1] = key;
        }
        int lo = 0, hi = count-1;
        while (lo <= hi) {
            int mid = (lo+hi)/2;
            if      (tasks[mid].id == id) { cout << "Found: " << tasks[mid].name << "\n"; return; }
            else if (tasks[mid].id <  id)  lo = mid+1;
            else                           hi = mid-1;
        }
        cout << "Not found\n";
    }

    // 6a. Bubble Sort
    void bubbleSort() {
        for (int i = 0; i < count-1; i++)
            for (int j = 0; j < count-i-1; j++)
                if (tasks[j].id > tasks[j+1].id) swap(tasks[j], tasks[j+1]);
        cout << "Sorted (Bubble)\n"; show();
    }

    // 6b. Merge Sort
    void mergeSort(int l, int r) {
        if (l >= r) return;
        int m = (l+r)/2;
        mergeSort(l, m); mergeSort(m+1, r);
        // merge
        Task tmp[100]; int i=l, j=m+1, k=0;
        while (i<=m && j<=r) tmp[k++] = tasks[i].id <= tasks[j].id ? tasks[i++] : tasks[j++];
        while (i<=m) tmp[k++] = tasks[i++];
        while (j<=r) tmp[k++] = tasks[j++];
        for (int x=0; x<k; x++) tasks[l+x] = tmp[x];
    }
    void doMergeSort() { mergeSort(0, count-1); cout << "Sorted (Merge)\n"; show(); }

    // Mark done (bonus)
    void markDone(int id) {
        for (int i = 0; i < count; i++)
            if (tasks[i].id == id) { tasks[i].done = true; cout << "Marked done\n"; return; }
        cout << "ID not found\n";
    }
};

// ── Main ─────────────────────────────────────────────────────
int main() {
    TaskManager tm;
    tm.add("cigarettes");
    tm.add("Study C++");
    tm.add("Submit report");

    int choice;
    while (true) {
        cout << "\n1)Add 2)Delete 3)Undo 4)Show 5)Search 6)Sort 7)MarkDone 0)Exit\n> ";
        cin >> choice; cin.ignore();

        if (choice == 0) break;

        else if (choice == 1) {
            string n; cout << "Name: "; getline(cin, n); tm.add(n);

        } else if (choice == 2) {
            int id; cout << "ID: "; cin >> id; tm.del(id);

        } else if (choice == 3) {
            tm.undo();

        } else if (choice == 4) {
            tm.show();

        } else if (choice == 5) {
            char t; int id;
            cout << "a)Linear b)Binary: "; cin >> t;
            cout << "ID: "; cin >> id;
            t == 'a' ? tm.linearSearch(id) : tm.binarySearch(id);

        } else if (choice == 6) {
            char t; cout << "a)Bubble b)Merge: "; cin >> t;
            t == 'a' ? tm.bubbleSort() : tm.doMergeSort();

        } else if (choice == 7) {
            int id; cout << "ID: "; cin >> id; tm.markDone(id);
        }
    }
    cout << "Bye!\n";
}
