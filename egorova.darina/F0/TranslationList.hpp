#ifndef TRANSLATION_LIST_HPP
#define TRANSLATION_LIST_HPP

#include <string>
#include <set>

/**
 * Класс хранит список переводов для одного английского слова.
 * Согласно заданию, переводы отсортированы по алфавиту.
 */
class TranslationList {
public:
    void addTranslation(const std::string& translation) {
        if (!translation.empty()) {
            mTranslations.insert(translation);
        }
    }

    const std::set<std::string>& getTranslations() const {
        return mTranslations;
    }

private:
    // std::set всегда хранит элементы отсортированными
    std::set<std::string> mTranslations;
};

#endif
