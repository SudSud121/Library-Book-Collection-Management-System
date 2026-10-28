
#include <iostream>
#include <string>
#include <utility>
using namespace std;

struct BookNode
{
    int bookID;
    string title;
    BookNode* next;
};

class LinkedList
{
    BookNode* head;
    int count;

    BookNode* GetNodeAt(int index)
    {
        BookNode* p = head;
        for (int i = 0; i < index; i++)
            p = p->next;
        return p;
    }

public:
    LinkedList()
    {
        head = NULL;
        count = 0;
    }

    void Insert(BookNode* b)
    {
        b->next = head;
        head = b;
        count++;
    }

    BookNode* Remove()
    {
        if (IsEmpty()) return NULL;

        BookNode* b = head;
        head = head->next;
        b->next = NULL;
        count--;
        return b;
    }

    bool IsEmpty()
    {
        return head == NULL;
    }

    bool IsNotEmpty()
    {
        return head != NULL;
    }

    void InsertAt(BookNode* b, int index)
    {
        if (index < 0) index = 0;
        if (index > count) index = count;

        if (index == 0)
        {
            Insert(b);
            return;
        }

        BookNode* p = GetNodeAt(index - 1);
        b->next = p->next;
        p->next = b;
        count++;
    }

    BookNode* RemoveAt(int index)
    {
        if (IsEmpty()) return NULL;

        if (index < 0) index = 0;
        if (index >= count) index = count - 1;
        if (index == 0) return Remove();

        BookNode* p = GetNodeAt(index - 1);
        BookNode* b = p->next;
        p->next = b->next;
        b->next = NULL;
        count--;
        return b;
    }

    void Swap(int a, int b)
    {
        if (a < 0 || a >= count || b < 0 || b >= count)
            return;

        BookNode* x = GetNodeAt(a);
        BookNode* y = GetNodeAt(b);

        swap(x->bookID, y->bookID);
        swap(x->title, y->title);
    }

    void Sort()
    {
        for (BookNode* i = head; i != NULL; i = i->next)
        {
            for (BookNode* j = i->next; j != NULL; j = j->next)
            {
                if (i->bookID > j->bookID)
                {
                    swap(i->bookID, j->bookID);
                    swap(i->title, j->title);
                }
            }
        }
    }

    void Reverse()
    {
        BookNode *p = NULL, *c = head, *n;

        while (c != NULL)
        {
            n = c->next;
            c->next = p;
            p = c;
            c = n;
        }
        head = p;
    }

    void Print()
    {
        BookNode* p = head;
        int i = 0;

        cout << "\nIndex\tID\tTitle\n";

        while (p != NULL)
        {
            cout << i++ << "\t" << p->bookID
                 << "\t" << p->title << endl;
            p = p->next;
        }

        cout << "Total books: " << count << endl;
    }

    ~LinkedList()
    {
        while (!IsEmpty())
            delete Remove();
    }
};

BookNode* CreateBook(int id, string title)
{
    return new BookNode{id, title, NULL};
}

int main()
{
    LinkedList library;
    int ch, id, index, a, b;
    string title;
    BookNode* r;

    library.InsertAt(CreateBook(103, "Operating Systems"), 0);
    library.InsertAt(CreateBook(101, "Data Structures"), 1);
    library.InsertAt(CreateBook(105, "Computer Networks"), 2);
    library.InsertAt(CreateBook(102, "Database Systems"), 3);
    library.InsertAt(CreateBook(104, "Software Engineering"), 4);

    do
    {
        cout << "\n===== LIBRARY SYSTEM =====\n";
        cout << "1. Display All Books\n";
        cout << "2. Insert Book at Head\n";
        cout << "3. Remove Book from Head\n";
        cout << "4. Insert Book at Index\n";
        cout << "5. Remove Book at Index\n";
        cout << "6. Swap Books\n";
        cout << "7. Sort Books by ID\n";
        cout << "8. Reverse Collection\n";
        cout << "9. Check Collection Status\n";
        cout << "10. Exit\n";
        cout << "Enter choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            library.Print();
            break;

        case 2:
        case 4:
            cout << "Enter book ID: ";
            cin >> id;
            cin.ignore();

            cout << "Enter title: ";
            getline(cin, title);

            if (ch == 2)
                library.Insert(CreateBook(id, title));
            else
            {
                cout << "Enter index: ";
                cin >> index;
                library.InsertAt(CreateBook(id, title), index);
            }
            break;

        case 3:
        case 5:
            if (ch == 5)
            {
                cout << "Enter index: ";
                cin >> index;
                r = library.RemoveAt(index);
            }
            else
                r = library.Remove();

            if (r != NULL)
            {
                cout << "Removed: " << r->title << endl;
                delete r;
            }
            else
                cout << "Library is empty!\n";
            break;

        case 6:
            cout << "Enter two indexes: ";
            cin >> a >> b;
            library.Swap(a, b);
            break;

        case 7:
            library.Sort();
            cout << "Books sorted!\n";
            break;

        case 8:
            library.Reverse();
            cout << "Collection reversed!\n";
            break;

        case 9:
            if (library.IsEmpty())
                cout << "Library is empty!\n";
            else if (library.IsNotEmpty())
                cout << "Library has books.\n";
            library.Print();
            break;

        case 10:
            cout << "Program ended.\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (ch != 10);

    return 0;
}

