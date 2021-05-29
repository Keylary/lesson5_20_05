#include <iostream>
#include <vector>
#include <set>
#include <map>




    // Task 1.
    // Создать шаблонную функцию, которая принимает итераторы на начало и конец последовательности слов, и выводящую в консоль список уникальных слов
    // (если слово повторяется больше 1 раза, то вывести его надо один раз).Продемонстрировать работу функции, передав итераторы различных типов.
template<typename T>
void print_words(T begin, T end) {
    std::set<std::string> t;
    copy(begin, end, inserter(t, t.end()));
    copy(t.begin(), t.end(), std::ostream_iterator<std::string>(std::cout, ", "));
    std::cout << std::endl;
}



    // Task 2.
    //  Используя ассоциативный контейнер, напишите программу, которая будет считывать данные введенные пользователем из стандартного потока ввода и разбивать их на предложения.
    // Далее программа должна вывести пользователю все предложения, отсортировав их по длине.
std::string filter_ws(const std::string& s)
{
    const char* ws{ " /n/t/r" };
    const auto a = s.find_first_not_of(ws);
    const auto b = s.find_last_not_of(ws);
    if (a == std::string::npos) {
        return {};       
    }
    return s.substr(a, b - a + 1);
}

std::multimap<size_t, std::string> get_phrase_count(const std::string& text) {
    std::multimap<size_t, std::string> ret;
    const auto end_it = end(text);
    auto it1 = begin(text);
    auto it2 = find(it1, end_it, '.');
    while (it1 != end_it && distance(it1, it2) > 0) {
        std::string s = filter_ws({ it1,it2 });
        if (s.length() > 0) {
            const auto words = count(begin(s), end(s), ' ') + 1;
            ret.emplace(make_pair(words, std::move(s)));
        }
        it1 = next(it2, 1);
        it2 = find(it1, end_it, '.');
        
        if (it2 == end_it) {
            break;
        }
    }
    return ret;
}

int main()
{
    // Task 1.
   
    
    std::cout << "Task 1." << std::endl; 
    std::cout << std::endl;
        
    std::vector<std::string> words1{ "Lets", "say", "I", "have", "the", "following", "class", "class", "the" };
    std::cout << "Original words list: ";
    std::copy(words1.begin(), words1.end(), std::ostream_iterator<std::string>(std::cout, ", "));
    std::cout << std::endl;
    std::cout << "Unique words list: ";
    print_words(words1.begin(), words1.end());
    std::cout << std::endl;

    std::string words2[10] { "Lets", "say", "I", "have", "the", "following", "class", "class", "the", "string" };
    std::cout << "Original words list: ";
    std::copy(begin(words2), end(words2), std::ostream_iterator<std::string>(std::cout, ", "));
    std::cout << std::endl;
    std::cout << "Unique words list: ";
    print_words(begin(words2), end(words2));

    /*std::cout << "Enter the text, please: " << std::endl;
    std::istream_iterator<std::string> begin_iterator{ std::cin };
    std::istream_iterator<std::string> end_iterator;
    print_words(begin_iterator, end_iterator);*/


    std::cout << std::endl;
    std::cout << std::endl;

    // Task 2.
    

    std::cout << "Task 2." << std::endl;
    std::cout << std::endl;
    std::cout << "Enter the text, please: " << std::endl;

    std::cin.unsetf(std::ios::skipws);
    std::string text{ std::istream_iterator<char> {std::cin}, {} };
    for (const auto& [word_count, phrase] : get_phrase_count(text)) {
        std::cout << word_count << " words: " << phrase << ". \n";
    }
}

