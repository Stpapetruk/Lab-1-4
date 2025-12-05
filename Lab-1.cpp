#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

const int MAX_BOOKS = 1000;

struct Book
{
    char title[50];
    char author[30];
    int year;
    float rating;
};

Book books[MAX_BOOKS];
int bookCount = 0;

void loadBooks(const char *filename)
{
    ifstream fin(filename);

    if (!fin)
        return;

    while (fin >> books[bookCount].title >> books[bookCount].author >> books[bookCount].year >> books[bookCount].rating)
    {
        bookCount++;
    }

    fin.close();
}

void saveBookToFile(const char *filename, Book b)
{
    ofstream fout(filename, ios::app);

    if (!fout)
    {
        cout << "Ошибка сохранения файла!" << endl;
        return;
    }

    fout << b.title << " " << b.author << " " << b.year << " " << b.rating << endl;

    fout.close();
}

void addBook()
{
    if (bookCount >= MAX_BOOKS)
    {
        cout << "Превышен лимит книг!" << endl;
        return;
    }

    Book b;

    cout << "Введите название книги: ";
    cin >> b.title;

    cout << "Введите автора: ";
    cin >> b.author;

    cout << "Введите год прочтения: ";
    cin >> b.year;

    cout << "Ваша оценка книги (0-10): ";
    cin >> b.rating;

    books[bookCount++] = b;
    saveBookToFile("books.txt", b);

    cout << "Книга добавлена!\n";
}

void showAllBooks()
{
    if (bookCount == 0)
    {
        cout << "Нет данных о книгах.\n";
        return;
    }

    cout << "\nВсе книги\n";
    cout << left << setw(32) << "Название"
         << setw(30) << "Автор"
         << setw(27) << "Год"
         << "Оценка\n";
    cout << "-----------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < bookCount; i++)
    {
        cout << left << setw(25) << books[i].title
             << setw(25) << books[i].author
             << setw(25) << books[i].year
             << books[i].rating << "/10\n";
    }
}

void showStats()
{
    if (bookCount == 0)
    {
        cout << "Нет данных для анализа.\n";
        return;
    }

    float totalRating = 0;
    float maxRating = books[0].rating;
    float minRating = books[0].rating;
    int bestBookIndex = 0;

    for (int i = 0; i < bookCount; i++)
    {
        totalRating += books[i].rating;

        if (books[i].rating > maxRating)
        {
            maxRating = books[i].rating;
            bestBookIndex = i;
        }

        if (books[i].rating < minRating)
        {
            minRating = books[i].rating;
        }
    }

    float averageRating = totalRating / bookCount;

    cout << "\n    Статистика    \n";
    cout << "Всего прочитано книг: " << bookCount << "\n";
    cout << "Средняя оценка: " << averageRating << "/10\n";
    cout << "Самая высокая оценка: " << maxRating << "/10\n";
    cout << "Самая низкая оценка: " << minRating << "/10\n";
    cout << "Самая высоко оценённая книга: \"" << books[bestBookIndex].title 
         << "\" автора " << books[bestBookIndex].author << " (" << books[bestBookIndex].rating << "/10)\n";
}

void showMenu()
{
    cout << "\n  Трекер книг  \n";
    cout << "1. Добавить книгу\n";
    cout << "2. Показать все книги\n";
    cout << "3. Показать статистику\n";
    cout << "4. Выход\n";
    cout << "Выберите пункт: ";
}

int main()
{
    #ifdef _WIN32
        system("chcp 65001 > nul");
    #endif

    loadBooks("books.txt");

    int choice;

    do
    {
        showMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            addBook();
            break;
        case 2:
            showAllBooks();
            break;
        case 3:
            showStats();
            break;
        case 4:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Неверный выбор.\n";
        }

    } while (choice != 4);

    return 0;
}