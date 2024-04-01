#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

// Function to split a string into words
std::vector<std::string> split(const std::string &str) {
    std::vector<std::string> words;
    std::string word;

    for (char c : str) {
        if (std::isalnum(c)) {
            word += std::tolower(c);
        } else if (!word.empty()) {
            words.push_back(word);
            word.clear();
        }
    }

    if (!word.empty()) {
        words.push_back(word);
    }

    return words;
}

struct Book {
    std::string title;
    std::string description;
    std::string publisher;
    std::string year;
    std::string isbn;

    Book(const std::string &title, const std::string &description,
         const std::string &publisher, const std::string &year,
         const std::string &isbn)
        : title(title), description(description),
          publisher(publisher), year(year), isbn(isbn) {}
};

int main() {
    std::vector<Book> books;
    std::vector<std::vector<std::string>> tags;

    while (true) {
        std::cout << "Enter command (add/search/exit): ";
        std::string command;
        std::cin >> command;

        if (command == "add") {
            std::string title, description, publisher, year, isbn;

            std::cout << "Enter book title: ";
            std::getline(std::cin, title);

            std::cout << "Enter book description: ";
            std::getline(std::cin, description);

            std::cout << "Enter book publisher: ";
            std::getline(std::cin, publisher);

            std::cout << "Enter book year: ";
            std::getline(std::cin, year);

            std::cout << "Enter book ISBN: ";
            std::getline(std::cin, isbn);

            books.push_back(Book(title, description, publisher, year, isbn));

            std::vector<std::string> book_tags = split(title);
            book_tags.push_back(publisher);
            book_tags.push_back(year);

            tags.push_back(book_tags);

        } else if (command == "search") {
            std::cout << "Enter search keywords: ";
            std::string keywords;
            std::getline(std::cin, keywords);

            std::vector<std::string> search_tags = split(keywords);

            for (size_t i = 0; i < books.size(); ++i) {
                bool found = true;
                for (const std::string &tag : search_tags) {
                    if (std::find(tags[i].begin(), tags[i].end(), tag) == tags[i].end()) {
                        found = false;
                        break;
                    }
                }

                if (found) {
                    std::cout << "Found book: " << books[i].title << "\n";
                    std::cout << "Description: " << books[i].description << "\n";
                    std::cout << "Publisher: " << books[i].publisher << "\n";
                    std::cout << "Year: " << books[i].year << "\n";
                    std::cout << "ISBN: " << books[i].isbn << "\n";
                }
            }

        } else if (command == "exit") {
            break;

        } else {
            std::cout << "Invalid command\n";
        }
    }

    return 0;
}